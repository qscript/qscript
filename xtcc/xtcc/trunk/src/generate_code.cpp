#include "expr.h"
#include "stmt.h"

//struct AbstractStatement;
//struct table;
//struct ax;
extern Statement::AbstractStatement * tree_root;
extern char* work_dir;
extern int rec_len;
extern CodeOutputFiles code_output_files;

#include "Tab.h"
#include "ax_stmt_type.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <cstdlib>

using std::vector;
using std::map;
using std::string;
using std::cout;
using std::endl;
using std::cerr;
extern int no_errors;
extern int line_no;
extern vector<Table::table*>	table_list;
extern map <string, Table::ax*> ax_map;
FILE * global_vars;
#include <cstdio>
//void print_table_code(FILE * op, FILE *tab_drv_func, FILE * tab_summ_func, vector<Table::table*> & table_list);
//void print_latex_print(FILE* op, int table_index);

void print_table_code (FILE * op, FILE * tab_drv_func, FILE * tab_summ_func, vector<Table::table*> & table_list, string tab_fname)
{
	using namespace Table;
	fprintf(op, "#include <iostream>\n");
	fprintf(op, "#include <fstream>\n");
	fprintf(op, "#include <sstream>\n");
	fprintf(op, "#include <vector>\nusing namespace std;\n");
	fprintf(tab_drv_func, "#include \"global.h\"\n");
	fprintf(tab_drv_func, "#include \"my_table.C\"\n");
	fprintf(tab_drv_func, "void tab_compute(){\n");
	set <string> ax_defns;
	for (unsigned int i=0; i<table_list.size(); i++) {
		CMAPITER map_iter_s= ax_map.find(table_list[i]->side);
		CMAPITER map_iter_b= ax_map.find(table_list[i]->banner);
		string s1 = "ax_" + map_iter_b->first;
		if (ax_defns.find (s1) == ax_defns.end()) {
			fprintf(op, "#include \"ax_%s.h\"\n",
						map_iter_b->first.c_str ());
			fprintf (op, "extern struct axis_%s ax_%s;\n",
					map_iter_b->first.c_str(),
					map_iter_b->first.c_str());
			ax_defns.insert(s1);
		}
		string s2 = "ax_" + map_iter_s->first;
		if (ax_defns.find (s2) == ax_defns.end()) {
			fprintf(op, "#include \"ax_%s.h\"\n",
						map_iter_s->first.c_str());
			fprintf (op, "extern struct axis_%s ax_%s;\n",
					map_iter_s->first.c_str(),
					map_iter_s->first.c_str());
			ax_defns.insert(s2);
		}
	}
	for (unsigned int i=0; i<table_list.size(); i++) {
		CMAPITER map_iter_s= ax_map.find(table_list[i]->side);
		CMAPITER map_iter_b= ax_map.find(table_list[i]->banner);
		if (map_iter_s==ax_map.end() || map_iter_b==ax_map.end()) {
			cerr << "Error: axis name " 
				<< table_list[i]->side << " or " 
				<< table_list[i]->banner << "not pres in axes defn"
				<< " line_no: " << line_no 
				<< endl;
			++ no_errors;
		} else {
			Expression::AbstractExpression* f= table_list[i]->filter;
			// cout << "table: " <<
			// 	map_iter_b->first << " by " <<
			// 	map_iter_s->first << endl;
			if ( f ){
				cout << " Filter: " ;
			}
			fprintf(op, "struct table_%s_%s {\n",
					map_iter_s->first.c_str(), map_iter_b->first.c_str ());
			fprintf(op, "\tconst int rows, cols;\n");
			fprintf(op, "\tvector <int> counter;\n");
			fprintf(op, "\ttable_%s_%s():rows(%d), cols(%d),counter(%d*%d){\n\t\tfor (int i=0;i<counter.size();++i) counter[i]=0; \n",
					map_iter_s->first.c_str(), map_iter_b->first.c_str (),
					map_iter_s->second->no_count_ax_elems,
					map_iter_b->second->no_count_ax_elems,
					map_iter_s->second->no_count_ax_elems,
					map_iter_b->second->no_count_ax_elems
					);
			if (map_iter_s->second->no_inc_ax_elems > 0 || 
						map_iter_b->second->no_inc_ax_elems > 0) {
				fprintf(op, "\t\tfor (int i=0; i<mean_inc_%s_%s.size(); ++i) {\n\t\t\tmean_inc_%s_%s[i].sum_n=0.0; mean_inc_%s_%s[i].n=0.0;\n\t\t}\n",
						map_iter_s->first.c_str(), map_iter_b->first.c_str (),
						map_iter_s->first.c_str(), map_iter_b->first.c_str (),
						map_iter_s->first.c_str(), map_iter_b->first.c_str (),
						map_iter_s->first.c_str(), map_iter_b->first.c_str (),
						map_iter_s->first.c_str(), map_iter_b->first.c_str (),
						map_iter_s->first.c_str(), map_iter_b->first.c_str ()
						);
			}
			fprintf(op, "\t}\n");

			/*
			fprintf(op, "\tvoid compute(){\n");
			fprintf(op, "\t\tfor(int i=0; i<rows; ++i){\n");
			fprintf(op, "\t\t\tfor(int j=0; j<cols; ++j){\n");
			fprintf(op, "\t\t\t\tif(");
			fprintf(op, "ax_%s.flag[i]", map_iter_s->first.c_str());
			fprintf(op, " && " );
			fprintf(op, "ax_%s.flag[j]){\n", map_iter_b->first.c_str());
			fprintf(op, "\t\t\t\t\t++counter[i*cols+j];\n");
			fprintf(op, "\t\t\t\t} \n");
			fprintf(op, "\t\t\t} \n");
			fprintf(op, "\t\t}\n");
			fprintf(op, "\t} \n");
			*/

			fprintf(op, "\tvoid compute(){\n");

			int rows=map_iter_s->second->no_count_ax_elems;
			int cols=map_iter_b->second->no_count_ax_elems;
			AbstractCountableAxisStatement* side_stmt=map_iter_s->second->count_ax_stmt_start;
			int inc_stmt_count=0;
			for (int i=0; i<rows; ++i) {
				//cout << "generate_code: i: " << i << endl;
				AbstractCountableAxisStatement* banner_stmt = map_iter_b->second->count_ax_stmt_start;
				if (inc_ax_stmt * inc_st_ptr = dynamic_cast<inc_ax_stmt*>(side_stmt)) {
					string global_vars_fname_C = work_dir + string("/global.C");
					FILE * global_vars_C = fopen (global_vars_fname_C.c_str(), "a+b");
					string global_vars_fname = work_dir + string("/global.h");
					FILE * global_vars_h = fopen (global_vars_fname.c_str(), "a+b");
					if (! (global_vars_h||global_vars_C) ) {
						cerr << "Unable to open file: " << global_vars_fname 
							<< " or " << global_vars_fname_C
							<< " for writing ... exiting \n"
							<< endl;
						exit(1);
					}
					fprintf (global_vars_h, "extern vector<MeanStdDevInc> mean_inc_%s_%s;\n",
							map_iter_s->first.c_str(), map_iter_b->first.c_str(), cols * map_iter_s->second->no_inc_ax_elems);
					fprintf (global_vars_C, "vector<MeanStdDevInc> mean_inc_%s_%s(%d);\n",
							map_iter_s->first.c_str(), map_iter_b->first.c_str(), cols * map_iter_s->second->no_inc_ax_elems);
					//printf  ("vector<MeanStdDevInc> mean_inc_%s_%s(%d);\n",
					//		map_iter_s->first.c_str(), map_iter_b->first.c_str(), cols * map_iter_s->second->no_inc_ax_elems);
					fclose (global_vars_h);
					fclose (global_vars_C);
					++inc_stmt_count;
				}
				for (int j = 0; j < cols; ++j) {
					//cout << "generate_code: j: " << j << endl;
					fprintf(op, "\t\tif(");
					fprintf(op, "ax_%s.flag[%d]", map_iter_s->first.c_str(), i);
					fprintf(op, " && " );
					fprintf(op, "ax_%s.flag[%d]){\n", map_iter_b->first.c_str(), j);
					if (!banner_stmt || ! side_stmt) {
						// handles the case of fld_stmt
						fprintf(op, "\t\t\t++counter[%d*cols+%d];\n",
								i, j);
					} else if(side_stmt->CustomCountExpression() == false
						&& banner_stmt->CustomCountExpression() == false) {
						fprintf(op, "\t\t\t++counter[%d*cols+%d];\n",
								i, j);
					} else if(side_stmt->CustomCountExpression() == true
						&& banner_stmt->CustomCountExpression() == false) {
						// cout << "side is inc_axstmt" << endl;
						// fprintf(op, "\t\t\tcounter[%d*cols+%d]+=",
						// 		i, j);
						inc_ax_stmt * inc_st_ptr = static_cast<inc_ax_stmt*>(side_stmt);
						//inc_st_ptr->PrintIncrExpression(op);
						//fprintf(op, ";\n");

						fprintf(op, "\t\t\t mean_inc_%s_%s[%d*cols+%d].sum_n +=",
								map_iter_s->first.c_str(), map_iter_b->first.c_str(),
								inc_stmt_count-1, j);
						//inc_ax_stmt * inc_st_ptr = static_cast<inc_ax_stmt*>(side_stmt);
						inc_st_ptr->PrintIncrExpression(op);
						fprintf(op, ";\n");
						fprintf(op, "\t\t\t mean_inc_%s_%s[%d*cols+%d].n +=1",
								map_iter_s->first.c_str(), map_iter_b->first.c_str(), 
								inc_stmt_count-1, j);
						fprintf(op, ";\n");
					} else if ( side_stmt->CustomCountExpression() == false
							&& banner_stmt->CustomCountExpression() == true) {
						cout << "banner is inc_axstmt" << endl;
						fprintf(op, "\t\t\tcounter[%d*cols+%d]+=",
								i, j);
						inc_ax_stmt * inc_st_ptr = static_cast<inc_ax_stmt*>(banner_stmt);
						inc_st_ptr->PrintIncrExpression(op);
						fprintf(op, ";\n");
					} else if (side_stmt == banner_stmt && 
							side_stmt->CustomCountExpression() == true) {
						cout << "  axis by axis -> diagonal table" << endl;
						// axis by axis -> diagonal table
						fprintf(op, "\t\t\tcounter[%d*cols+%d]+=",
								i, j);
						inc_ax_stmt * inc_st_ptr = static_cast<inc_ax_stmt*>(side_stmt);
						inc_st_ptr->PrintIncrExpression(op);
						fprintf(op, ";\n");
					} else {
						print_err(Util::compiler_sem_err, "Error: trying to tabulate inc axis statement with inc axis statement"
							, line_no, __LINE__, __FILE__);
					}
					// handles the case of fld_stmt
					if(banner_stmt)
						banner_stmt=banner_stmt->next_;
					fprintf(op, "\t\t}\n");
				}
				// handles the case of fld_stmt
				if(side_stmt)
					side_stmt=side_stmt->next_;
			}
			fprintf(op, "\t} \n");


#if 0
			ax * side_ax = map_iter_s->second;
			if( side_ax->ax_stmt_start && side_ax->fld_stmt==0) {
				fprintf(op, "ax_%s.flag[i]", map_iter_s->first.c_str());
			} else if ( side_ax->ax_stmt_start==0 && side_ax->fld_stmt) {
				fprintf(op, "ax_%s.fld_flag[i]", map_iter_s->first.c_str());
			}
			fprintf(op, " && " );
			ax * banner_ax = map_iter_b->second;
			if( banner_ax->ax_stmt_start && banner_ax->fld_stmt==0) {
				fprintf(op, "ax_%s.flag[i]){", map_iter_b->first.c_str());
			} else if ( banner_ax->ax_stmt_start==0 && banner_ax->fld_stmt) {
				fprintf(op, "ax_%s.fld_flag[i]){", map_iter_b->first.c_str());
			}
#endif /* 0 */
			fprintf(op, "\tvoid print(){\n\t\tint rci=0, cci=0; /* row counter index , col ... */\n");
			fprintf(op, "\t\tofstream tab_op(\"%s\", ios_base::out|ios_base::app);\n", tab_fname.c_str());
			fprintf(op, "\t\ttab_op << \"rows\" << \",\" << rows << \",cols\" << \",\" << cols << endl;\n");
			fprintf(op, "\t\ttab_op << \"\\\"\" << ax_%s.ttl_stmt_text[0] << \"\\\"\" << \",\" <<  \"\\\"\" << ax_%s.ttl_stmt_text[0] << \"\\\"\"  << endl;\n",
					map_iter_s->first.c_str(), map_iter_b->first.c_str()
					);
			fprintf(op, "\t\ttab_op << \",,\";\n");
			fprintf(op, "\t\tfor(int j=0; j<ax_%s.count_stmt_text.size(); ++j){\n", 
					map_iter_b->first.c_str());
			fprintf(op, "\t\t\t tab_op << \"\\\"\" << ax_%s.count_stmt_text[j] << \"\\\"\"  << \",\" ;\n", 
					map_iter_b->first.c_str()); 
			fprintf(op, "\t\t}\n");

#if 0
			if( banner_ax->ax_stmt_start && banner_ax->fld_stmt==0) {
				fprintf(op, "\t\tfor(int j=0; j<ax_%s.stmt_text.size(); ++j){\n", 
						map_iter_b->first.c_str());
				fprintf(op, "\t\t\tif(ax_%s.is_a_count_text[j]){\n", map_iter_b->first.c_str());
				fprintf(op, "\t\t\t\t tab_op << ax_%s.stmt_text[j] << \",\" ;\n", 
						map_iter_b->first.c_str()); 
				fprintf(op, "\t\t\t}\n");
				fprintf(op, "\t\t}\n");
			} else if ( banner_ax->ax_stmt_start==0 && banner_ax->fld_stmt) {
				fprintf(op, "\t\tfor(int j=0; j<ax_%s.bit_stmt_text.size(); ++j){\n", map_iter_b->first.c_str());
				fprintf(op, "\t\t\t tab_op << ax_%s.bit_stmt_text[j] << \",\" ;\n", 
						map_iter_b->first.c_str()); 
				fprintf(op, "\t\t}\n");
			}
#endif /* 0 */

			fprintf(op, "\t\ttab_op << endl;\n");
			fprintf(op, "\t\tint inc_counter=0;\n");
			fprintf(op, "\t\tfor (int i=0; i<ax_%s.count_stmt_text.size(); ++i) {\n",
					map_iter_s->first.c_str());
			fprintf(op, "\t\t\ttab_op << \",\";\n");
			fprintf(op, "\t\t\tstringstream col_perc_str;\n");
			fprintf(op, "\t\t\tstringstream row_perc_str;\n");
			fprintf(op, "\t\t\tcol_perc_str << \",,\";\n");
			fprintf(op, "\t\t\trow_perc_str << \",,\";\n");
			fprintf(op, "\t\t\tcci=0;\n");
			fprintf(op, "\t\t\ttab_op << \"\\\"\" << ax_%s.count_stmt_text[i] << \"\\\"\" << \",\";\n", map_iter_s->first.c_str()); 
			fprintf(op, "\t\t\t\tif (ax_%s.axis_stmt_type_count[rci] == Table::inc_axstmt) {\n", map_iter_s->first.c_str());
			fprintf(op, "\t\t\t\t\t++inc_counter;\n");
			fprintf(op, "\t\t\t\t}\n");
			fprintf(op, "\t\t\tfor (int j=0; j<ax_%s.count_stmt_text.size(); ++j) {\n",
				map_iter_b->first.c_str());
			fprintf(op, "\t\t\t\tif (ax_%s.axis_stmt_type_count[rci] == Table::cnt_axstmt) {\n", map_iter_s->first.c_str());
			fprintf(op, "\t\t\t\t\ttab_op << counter[cci+rci*cols]<<\",\";\n");
			fprintf(op, "\t\t\t\t\tif (ax_%s.tot_elem_pos_vec.size()>0) {\n", map_iter_s->first.c_str() );
			fprintf(op, "\t\t\t\t\t\tcol_perc_str << (((double) counter[cci+rci*cols]) / counter[cci+ax_%s.tot_elem_pos_vec[0]*cols]) * 100 <<\",\";\n", map_iter_s->first.c_str() );
			//fprintf(op, "\t\t\t\t\tcol_perc_str << ( counter[cci+ax_%s.tot_elem_pos_vec[0]*cols]) <<\",\";\n", map_iter_s->first.c_str() );
			fprintf(op, "\t\t\t\t\t}\n");
			fprintf(op, "\t\t\t\t\tif (ax_%s.tot_elem_pos_vec.size()>0) {\n", map_iter_b->first.c_str() );
			//fprintf(op, "\t\t\t\t\trow_perc_str << ax_%s.tot_elem_pos_vec[0] << \"|\" << ( counter[ax_%s.tot_elem_pos_vec[0]+cols*rci]) <<\",\";\n", map_iter_b->first.c_str(), map_iter_b->first.c_str() );
			fprintf(op, "\t\t\t\t\t\trow_perc_str << (((double) counter[cci+rci*cols]) / counter[ax_%s.tot_elem_pos_vec[0]+cols*rci]) * 100 <<\",\";\n", map_iter_b->first.c_str() );
			fprintf(op, "\t\t\t\t\t}\n");
			fprintf(op, "\t\t\t\t}\n");
			fprintf(op, "\t\t\t\tif (ax_%s.axis_stmt_type_count[rci] == Table::tot_axstmt) {\n", map_iter_s->first.c_str());
			fprintf(op, "\t\t\t\t\ttab_op << counter[cci+rci*cols]<<\",\";\n");
			fprintf(op, "\t\t\t\t}\n");

			if (map_iter_s->second->no_inc_ax_elems > 0 || 
						map_iter_b->second->no_inc_ax_elems > 0) {
				fprintf(op, "\t\t\t\tif (ax_%s.axis_stmt_type_count[rci] == Table::inc_axstmt) {\n", map_iter_s->first.c_str());
				fprintf(op, "\t\t\t\t\ttab_op << mean_inc_%s_%s[(inc_counter-1)*cols+cci].sum_n / mean_inc_%s_%s[(inc_counter-1)*cols+cci].n  << \",\";\n", map_iter_s->first.c_str(), map_iter_b->first.c_str(), map_iter_s->first.c_str(), map_iter_b->first.c_str() );
			fprintf(op, "\t\t\t\t}\n");
			}
			fprintf(op, "\t\t\t\t++cci;\n");
			fprintf(op, "\t\t\t}\n");
			fprintf(op, "\t\t\t++rci;\n");
			fprintf(op, "\t\t\ttab_op << endl;\n");
			fprintf(op, "\t\t\ttab_op << col_perc_str.str() << endl;\n");
			fprintf(op, "\t\t\ttab_op << row_perc_str.str() << endl;\n");
			fprintf(op, "\t\t}\n");
			fprintf(op, "\t\ttab_op << endl;\n");
			//fprintf(op, "\t\t}\n");
			fprintf(op, "\t\ttab_op.close();\n");
			fprintf(op, "\t}\n");

#if 0
			if( side_ax->ax_stmt_start && side_ax->fld_stmt==0) {
				fprintf(op, "\t\tfor(int i=1; i<ax_%s.stmt_text.size(); ++i){\n",
						map_iter_s->first.c_str());
				fprintf(op, "\t\t\tcci=0;\n");
				fprintf(op, "\t\t\ttab_op << ax_%s.stmt_text[i] << \",\";\n", map_iter_s->first.c_str()); 
				fprintf(op, "\t\t\tif(ax_%s.is_a_count_text[i]){\n", map_iter_s->first.c_str());
				if( banner_ax->ax_stmt_start && banner_ax->fld_stmt==0) {
					fprintf(op, "//Side is a normal axis, banner is normal\n");
					fprintf(op, "\t\t\t\tfor(int j=0; j<ax_%s.stmt_text.size(); ++j){\n",
						map_iter_b->first.c_str());
					fprintf(op, "\t\t\t\t\tif(ax_%s.is_a_count_text[j]){\n", map_iter_b->first.c_str());
					fprintf(op, "\t\t\t\t\t\t//tab_op << \"rci:\" << rci << \"cci:\" << cci << endl;\n");
					fprintf(op, "\t\t\t\t\t\ttab_op << counter[cci+rci*cols]<<\",\";\n");
					fprintf(op, "\t\t\t\t\t\t++cci;\n");
					fprintf(op, "\t\t\t\t\t}\n");
					fprintf(op, "\t\t\t\t}\n");
					fprintf(op, "\t\t\t\t++rci;\n");
					fprintf(op, "\t\t\t}\n");
					fprintf(op, "\t\t\ttab_op << endl;\n");
					fprintf(op, "\t\t}\n");
					fprintf(op, "\ttab_op.close();\n");
					fprintf(op, "\t}\n");
				} else if ( banner_ax->ax_stmt_start==0 && banner_ax ->fld_stmt) {
					fprintf(op, "//Side is a normal axis, banner is fld\n");
					fprintf(op, "\t\t\t\tfor(int j=0; j<ax_%s.bit_stmt_text.size(); ++j){\n",
						map_iter_b->first.c_str());
					fprintf(op, "\t\t\t\t\t\t//tab_op << \"rci:\" << rci << \"cci:\" << cci << endl;\n");
					fprintf(op, "\t\t\t\t\t\ttab_op << counter[cci+rci*cols]<<\",\";\n");
					fprintf(op, "\t\t\t\t\t\t++cci;\n");
					fprintf(op, "\t\t\t\t}\n");
					fprintf(op, "\t\t\t\t++rci;\n");
					fprintf(op, "\t\t\t}\n");
					fprintf(op, "\t\t\ttab_op << endl;\n");
					fprintf(op, "\t\t}\n");
					fprintf(op, "\ttab_op.close();\n");
					fprintf(op, "\t}\n");
				}
			} else if ( side_ax->ax_stmt_start==0 && side_ax->fld_stmt) {
				// Neil : Work starts from here
				// add :fprintf(op, "\t\t\tif(ax_%s.is_a_count_text[i]){\n", map_iter_s->first.c_str());
				// to the case where not an fld statement
				fprintf(op, "\t\tfor(int i=1; i<ax_%s.bit_stmt_text.size(); ++i){\n",
					map_iter_s->first.c_str());
				fprintf(op, "\t\t\tcci=0;\n");
				fprintf(op, "\t\t\ttab_op << ax_%s.bit_stmt_text[i] << \",\";\n", 
						map_iter_s->first.c_str()); 
				if( banner_ax->ax_stmt_start && banner_ax->fld_stmt==0) {
					fprintf(op, "//Side is a fld axis, banner is normal\n");
					fprintf(op, "\t\t\t\tfor(int j=0; j<ax_%s.stmt_text.size(); ++j){\n",
						map_iter_b->first.c_str());
					fprintf(op, "\t\t\t\t\ttab_op << counter[cci+rci*cols]<<\",\";\n");
					fprintf(op, "\t\t\t\t\t++cci;\n");
					fprintf(op, "\t\t\t\t}\n");
				} else if ( banner_ax->ax_stmt_start==0 && banner_ax->fld_stmt) {
					fprintf(op, "//Side is a fld axis, banner is fld\n");
					fprintf(op, "\t\t\t\tfor(int j=0; j<ax_%s.bit_stmt_text.size(); ++j){\n",
						map_iter_b->first.c_str());
					fprintf(op, "\t\t\t\t\t\ttab_op << counter[cci+rci*cols]<<\",\";\n");
					fprintf(op, "\t\t\t\t\t\t++cci;\n");
					fprintf(op, "\t\t\t\t\t}\n");
				}

				fprintf(op, "\t\t\t\t++rci;\n");
				//fprintf(op, "\t\t\t}\n");
				fprintf(op, "\t\t\ttab_op << endl;\n");
				fprintf(op, "\t\t}\n");
				fprintf(op, "\t\ttab_op.close();\n");
				fprintf(op, "\t}\n");

			}
#endif /* 0 */

			//fprintf(op, "\t\t\tif(ax_%s.is_a_count_text[i]){\n", map_iter_s->first.c_str());
			//fprintf(op, "\t\t\t\tfor(int j=0; j<ax_%s.stmt_text.size(); ++j){\n",
			//		map_iter_b->first.c_str());
			/*
			fprintf(op, "\t\t\t\t\tif(ax_%s.is_a_count_text[j]){\n", map_iter_b->first.c_str());
			fprintf(op, "\t\t\t\t\t\t//tab_op << \"rci:\" << rci << \"cci:\" << cci << endl;\n");
			fprintf(op, "\t\t\t\t\t\ttab_op << counter[cci+rci*cols]<<\",\";\n");
			fprintf(op, "\t\t\t\t\t\t++cci;\n");
			fprintf(op, "\t\t\t\t\t}\n");
			*/

			/*
			fprintf(op, "\t\t\t\t}\n");
			fprintf(op, "\t\t\t\t++rci;\n");
			fprintf(op, "\t\t\t}\n");
			fprintf(op, "\t\t\ttab_op << endl;\n");
			fprintf(op, "\t\t}\n");
			fprintf(op, "\ttab_op.close();\n");
			fprintf(op, "\t}\n");
			*/

			//print_latex_print(op, i);
			fprintf(op, "} tab_%s_%s;\n",
				map_iter_s->first.c_str(), map_iter_b->first.c_str()
				);
			if (map_iter_s->second->filter && map_iter_b->second->filter) {
				ostringstream code_bef_expr1, code_expr1;
				map_iter_s->second->filter->PrintExpressionCode (code_bef_expr1, code_expr1);
				
				ostringstream code_bef_expr2, code_expr2;
				map_iter_b->second->filter->PrintExpressionCode (code_bef_expr2, code_expr2);
				fprintf (tab_drv_func, "if ( %s && %s ) { \n", code_expr1.str().c_str(), code_expr2.str().c_str());
				fprintf (tab_drv_func, "\ttab_%s_%s.compute();\n",
					map_iter_s->first.c_str(), map_iter_b->first.c_str()
					);
				fprintf (tab_drv_func, "}\n");
			} else if (map_iter_s->second->filter) {
				ostringstream code_bef_expr1, code_expr1;
				map_iter_s->second->filter->PrintExpressionCode (code_bef_expr1, code_expr1);
				fprintf (tab_drv_func, "if ( %s ) { \n", code_expr1.str().c_str());
				fprintf (tab_drv_func, "\ttab_%s_%s.compute();\n",
					map_iter_s->first.c_str(), map_iter_b->first.c_str()
					);
				fprintf (tab_drv_func, "}\n");
			} else if (map_iter_b->second->filter) {
				ostringstream code_bef_expr1, code_expr1;
				map_iter_b->second->filter->PrintExpressionCode (code_bef_expr1, code_expr1);
				fprintf (tab_drv_func, "if ( %s ) { \n", code_expr1.str().c_str());
				fprintf (tab_drv_func, "\ttab_%s_%s.compute();\n",
					map_iter_s->first.c_str(), map_iter_b->first.c_str()
					);
				fprintf (tab_drv_func, "}\n");
			} else {
				fprintf (tab_drv_func, "\ttab_%s_%s.compute();\n",
					map_iter_s->first.c_str(), map_iter_b->first.c_str()
					);
			}
		}
	}

	fprintf(tab_drv_func, "}\n");

	fprintf(tab_drv_func, "void tab_summ(){\n");
	for (unsigned int i=0; i<table_list.size(); i++) {
		CMAPITER map_iter_s= ax_map.find(table_list[i]->side);
		CMAPITER map_iter_b= ax_map.find(table_list[i]->banner);
		if(map_iter_s==ax_map.end()||map_iter_b==ax_map.end()){
			cerr << "Error: axis name " 
				<< table_list[i]->side << " or " 
				<< table_list[i]->banner << "not pres in axes defn"
				<< " line_no: " << line_no 
				<< endl;
			++ no_errors;
		} else {
			fprintf (tab_drv_func, "\ttab_%s_%s.print();\n",
				map_iter_s->first.c_str(), map_iter_b->first.c_str()
				);
			/*
			fprintf(tab_drv_func, "\ttab_%s_%s.print_latex();\n",
			map_iter_s->first.c_str(), map_iter_b->first.c_str()
			);
			*/
		}
	}
	fprintf(tab_drv_func, "}\n");

}

void print_latex_print(FILE* op, int table_index)
{
	using namespace Table;
	CMAPITER map_iter_s= ax_map.find(table_list[table_index]->side);
	CMAPITER map_iter_b= ax_map.find(table_list[table_index]->banner);
	fprintf(op, "\tvoid print_latex(){\n\t\tint rci=0, cci=0; /* row counter index , col ... */\n");
	fprintf(op, "\t\t\tofstream tab_op(\"tab_.tex\", ios_base::out|ios_base::app);\n");
	fprintf(op, "\t\ttab_op << \"\\\\documentclass{article}\" << endl;\n");
	fprintf(op, "\t\ttab_op << \"\\\\usepackage{supertabular}\" << endl;\n");
	fprintf(op, "\t\ttab_op <<\"\\\\begin{document}\" << endl;\n");
	fprintf(op, "\t\ttab_op << \"\\\\tablecaption{\" << ax_%s.stmt_text[0] << \" x \" << ax_%s.stmt_text[0] << \"}\"<< endl;\n",
			map_iter_s->first.c_str(), map_iter_b->first.c_str()
			);
	fprintf(op, "\t\ttab_op << \"\\\\tablehead\" << endl;\n");
	fprintf(op, "\t\ttab_op << \"\t{\";\n");
	fprintf(op, "\t\tfor(int j=0; j<ax_%s.stmt_text.size(); ++j){\n", map_iter_b->first.c_str());
	fprintf(op, "\t\t\tif(ax_%s.is_a_count_text[j]){\n", map_iter_b->first.c_str());
	fprintf(op, "\t\t\t\t tab_op << \"\\\\bfseries \" << ax_%s.stmt_text[j] << \"&\" ;\n", map_iter_b->first.c_str()); 
	fprintf(op, "\t\t\t}\n");
	fprintf(op, "\t\ttab_op << \"\\\\\\\\ \\\\hline}\"<< endl ;\n");
	fprintf(op, "\t\ttab_op << \"\\\\tabletail\\n\";\n");
	fprintf(op, "\t\ttab_op << \"{\\\\hline \\\\multicolumn{3}{r}{\\\\emph{Continued on next_ page}}\\\\\\\\}\\\\n\";\n");
	fprintf(op, "\t\t}\n");
	fprintf(op, "\t\ttab_op << endl;\n");
	fprintf(op, "\t\t\tfor(int i=1; i<ax_%s.stmt_text.size(); ++i){\n",
			map_iter_s->first.c_str());
	fprintf(op, "\t\t\t\tcci=0;\n");
	fprintf(op, "\t\t\t\ttab_op << ax_%s.stmt_text[i] << \"&\";\n", map_iter_s->first.c_str()); 
	fprintf(op, "\t\t\t\tif(ax_%s.is_a_count_text[i]){\n", map_iter_s->first.c_str());
	fprintf(op, "\t\t\t\t\tfor(int j=0; j<ax_%s.stmt_text.size(); ++j){\n",
			map_iter_b->first.c_str());
	fprintf(op, "\t\t\t\t\tif(ax_%s.is_a_count_text[j]){\n", map_iter_b->first.c_str());
	fprintf(op, "\t\t\t\t\t\t//tab_op << \"rci:\" << rci << \"cci:\" << cci << endl;\n");
	fprintf(op, "\t\t\t\t\t\ttab_op << counter[cci+rci*cols]<<\"&\";\n");
	fprintf(op, "\t\t\t\t\t\t++cci;\n");
	fprintf(op, "\t\t\t\t\t}\n");
	fprintf(op, "\t\t\t\t}\n");
	fprintf(op, "\t\t\t\t++rci;\n");
	fprintf(op, "\t\t\t}\n");
	fprintf(op, "\t\ttab_op << endl;\n");
	fprintf(op, "\t\t}\n");
	fprintf(op, "\ttab_op.close();\n");
	fprintf(op, "\t}\n");
}


void print_axis_code(FILE * op, FILE * axes_drv_func)
{
	using namespace Table;

	fprintf(op, "#include <bitset>\n" );
	fprintf(op, "#include <string>\n" );
	fprintf(op, "#include <vector>\n" );
	fprintf(op, "#include \"ax_stmt_type.h\"\n");
	fprintf(op, "using namespace std;\n" );
	fprintf(axes_drv_func, "#include \"global.h\"\n");
	fprintf(axes_drv_func, "#include \"my_axes.C\"\n");
	fprintf(axes_drv_func, "void ax_compute() /* :-)  */{\n");
	for(CMAPITER it=ax_map.begin(); it!=ax_map.end(); ++it){
		//struct ax* l_ax = *it;
		//cout << "Processing axis: " << it->first.c_str() << endl;
		stringstream axis_code_str_h;
		stringstream axis_code_str_cpp;
		axis_code_str_h 
			<< "#ifndef xtcc_ax_" << it->first << "_h" << endl
			<< "#define xtcc_ax_" << it->first << "_h" << endl
			<< "#include <bitset>\n" 
			<< "#include <string>\n"
			<< "#include <vector>\n"
			<< "#include \"ax_stmt_type.h\"\n"
			<< "#include \"global.h\"\n"
			<< "using namespace std;\n";

		axis_code_str_cpp 
			<< "extern int "
			<< it->first << "_data;\n";


		fprintf(op, "struct axis_%s{\n", it->first.c_str() );
		axis_code_str_h << "struct axis_" << it->first << " {\n";
		fprintf(op, "\tbitset<%d> flag;\n", it->second->no_count_ax_elems );
		axis_code_str_h << "\tbitset<" << it->second->no_count_ax_elems  << "> flag;\n" ;
		fprintf(op, "\tvector<string> ttl_stmt_text;\n");
		fprintf(op, "\tvector<string> count_stmt_text;\n");
		fprintf(op, "\tvector<int> tot_elem_pos_vec;\n");
		axis_code_str_h 
			<<  "\tvector<string> ttl_stmt_text;\n"
			<<  "\tvector<string> count_stmt_text;\n"
			<<  "\tvector<int> tot_elem_pos_vec;\n";

		fprintf(op, "\tbitset<%d> is_a_count_text;\n", it->second->no_tot_ax_elems);
		axis_code_str_h <<  "\tbitset<" 
			<< it->second->no_tot_ax_elems
			<< "> is_a_count_text;\n";
		fprintf(op, "\tvector<Table::axstmt_type> axis_stmt_type_print;\n");
		fprintf(op, "\tvector<Table::axstmt_type> axis_stmt_type_count;\n");
		axis_code_str_h << "\tvector<Table::axstmt_type> axis_stmt_type_print;\n"
				<< "\tvector<Table::axstmt_type> axis_stmt_type_count;\n";
		fprintf(op, "\taxis_%s():ttl_stmt_text(%d),count_stmt_text(%d), axis_stmt_type_print(%d), axis_stmt_type_count(%d) {\n"
				, it->first.c_str()
				, it->second->no_tot_ax_elems - it->second->no_count_ax_elems
				, it->second->no_count_ax_elems
				, it->second->no_tot_ax_elems - it->second->no_count_ax_elems
				, it->second->no_count_ax_elems
				) ;
		axis_code_str_h << "\taxis_" << it->first << "();" << endl;
		axis_code_str_cpp 
			<< "axis_" << it->first
			<< "::axis_" << it->first
			<<	"():ttl_stmt_text(" << it->second->no_tot_ax_elems - it->second->no_count_ax_elems
			<<	    "),count_stmt_text(" << it->second->no_count_ax_elems
			<<	    "), axis_stmt_type_print(" << it->second->no_tot_ax_elems - it->second->no_count_ax_elems
			<<	    "), axis_stmt_type_count(" << it->second->no_count_ax_elems
			<<	    ") {\n";

		int my_counter=0;
		for(AbstractPrintableAxisStatement* ax_stmt_iter=it->second->ttl_ax_stmt_start; 
				ax_stmt_iter; ax_stmt_iter=ax_stmt_iter->next_,
				++my_counter){
			fprintf(op, "\t\tttl_stmt_text[%d]=%s;\n", my_counter, ax_stmt_iter->ax_text().c_str());
			axis_code_str_cpp
				<< "\t\tttl_stmt_text[" 
				<<  my_counter
				<< "]="
				<< ax_stmt_iter->ax_text()
				<< ";\n"; 
			if (ax_stmt_iter->axtype == Table::txt_axstmt) {
				fprintf(op, "\t\t axis_stmt_type_print[%d]=Table::txt_axstmt;\n", my_counter);
				axis_code_str_cpp 
					<< "\t\t axis_stmt_type_print["
					<< my_counter 
					<< "]=Table::txt_axstmt;\n";
			} else {
				fprintf(op, "\t\t axis_stmt_type_print[%d]= cause a compile error;\n", my_counter);
				axis_code_str_cpp << "\t\t axis_stmt_type_print["
					<< my_counter << "]= cause a compile error;\n";
				print_err(Util::compiler_internal_error, "Error generating code for axes - unknown type for print stmt"
							, line_no, __LINE__, __FILE__);
				++no_errors;
			}

			/*
			if(ax_stmt_iter->axtype<=txt_axstmt){
				fprintf(op, "\tis_a_count_text[%d]=false;\n", my_counter);
			} else {
				fprintf(op, "\tis_a_count_text[%d]=true;\n", my_counter);
			}
			*/
		}
		my_counter=0;
		for( AbstractCountableAxisStatement* ax_stmt_iter=it->second->count_ax_stmt_start; 
				ax_stmt_iter; ax_stmt_iter=ax_stmt_iter->next_,
				++my_counter){
			//fprintf(op, "\tcount_stmt_text[%d]=%s;\n", my_counter, ax_stmt_iter->ax_text().c_str());
			ax_stmt_iter->print_axis_constructor_text(op, my_counter);
			if (tot_ax_stmt * my_tot_ax_stmt = dynamic_cast<tot_ax_stmt*>(ax_stmt_iter)) {
				fprintf(op, "\ttot_elem_pos_vec.push_back(%d);\n", ax_stmt_iter->position_);
				axis_code_str_cpp 
					<< "\ttot_elem_pos_vec.push_back("
					<< ax_stmt_iter->position_
					<< ");\n";
			}
			if (ax_stmt_iter->axtype == Table::tot_axstmt) {
				fprintf(op, "\t\t axis_stmt_type_count[%d]=Table::tot_axstmt;\n", my_counter);
				axis_code_str_cpp 
					<< "\t\t axis_stmt_type_count["
					<< my_counter << "]=Table::tot_axstmt;\n";
			} else if (ax_stmt_iter->axtype == Table::cnt_axstmt) {
				fprintf(op, "\t\t axis_stmt_type_count[%d]=Table::cnt_axstmt;\n", my_counter);
				axis_code_str_cpp
					<< "\t\t axis_stmt_type_count["
					<< my_counter 
					<< "]=Table::cnt_axstmt;\n";
			} else if (ax_stmt_iter->axtype == Table::fld_axstmt) {
				fprintf(op, "\t\t axis_stmt_type_count[%d]=Table::fld_axstmt;\n", my_counter);
				axis_code_str_cpp 
					<< "\t\t axis_stmt_type_count["
					<< my_counter 
					<< "]=Table::fld_axstmt;\n";
			} else if (ax_stmt_iter->axtype == Table::inc_axstmt) {
				fprintf(op, "\t\t axis_stmt_type_count[%d]=Table::inc_axstmt;\n", my_counter);
				axis_code_str_cpp
					<< "\t\t axis_stmt_type_count["
					<< my_counter 
					<< "]=Table::inc_axstmt;\n";
			} else {
				fprintf(op, "\t\tttl_stmt_text[%d]= cause a compile error;\n", my_counter);
				axis_code_str_cpp 
					<< "\t\tttl_stmt_text["
					<< my_counter 
					<< "]= cause a compile error;\n";
				print_err(Util::compiler_internal_error, "Error generating code for axes - unknown type for print stmt"
							, line_no, __LINE__, __FILE__);
				++no_errors;
			}
			
			/*
			if(ax_stmt_iter->axtype<=txt_axstmt){
				fprintf(op, "\tis_a_count_text[%d]=false;\n", my_counter);
			} else {
				fprintf(op, "\tis_a_count_text[%d]=true;\n", my_counter);
			}
			*/
		}

		// cout << "after basic_ax_stmt loop " << endl;
		/*
		for(unsigned int i=0; 
			it->second->fld_stmt &&
				i< it->second->fld_stmt->stub_list.size(); ++i){
			fprintf(op, "\tbit_stmt_text[%d]=%s;\n", i, 
				it->second->fld_stmt->stub_list[i]->text.c_str());
		}
		*/
		fprintf(op, "\t}\n");
		axis_code_str_cpp << "\t}\n";
		fprintf(op, "\tvoid reset(){\n\t\tflag.reset();\n\t}");
		fprintf(op, "\tvoid compute(){\n\t\tflag.reset();\n");
		axis_code_str_h 
			<< "\tvoid " 
			<< "compute();\n";
		axis_code_str_cpp 
			<< "\tvoid axis_" 
			<< it->first
			<< "::compute(){\n\t\tflag.reset();\n";

		AbstractCountableAxisStatement* iter=it->second->count_ax_stmt_start;
		int counter=0;
		while(iter){
			iter->generate_code(op, axis_code_str_cpp, counter);
			++counter;
			iter=iter->next_;
		}
		/*
		while(iter){
			if(iter->axtype>=tot_axstmt){
				AbstractCountableAxisStatement * bc=dynamic_cast<AbstractCountableAxisStatement *> (iter);
					
				if(bc->condn){
					fprintf(op, "\tif (");
					bc->condn->print_expr(op);
					fprintf(op, " ){\n");
					fprintf(op, "\t\tflag[%d]=true;\n", counter);
					fprintf(op, "\t}\n");
				} else {
					fprintf(op, "\tflag[%d]=true;\n", counter);
				}
				++counter;
			}
			iter=iter->next_;
		}
		*/
		/*
		cout << "after basic_ax_stmt if condition code " << endl;
		for(unsigned int i=0; 
			it->second->fld_stmt &&
				i< it->second->fld_stmt->stub_list.size(); ++i){
			fprintf(op, "if( %s[%d]){\n",  it->second->fld_stmt->symp->name,
				it->second->fld_stmt->stub_list[i]->code
					);
			fprintf(op, "\t fld_flag[%d]=true;\n}\n", it->second->fld_stmt->stub_list[i]->code);
		}
		cout << "after fld_stmt if condition code " << endl;
		*/

		fprintf(op, "\t} /* close compute func */\n");
		axis_code_str_cpp 
			<< "\t} /* close compute func */\n";
		fprintf(op, "} ax_%s;\n", it->first.c_str()) ;
		axis_code_str_h
			<< "} " 
			//<< "ax_" << it->first
			<< ";\n"
			<< "#endif /*  xtcc_ax_" << it->first << "_h */ " 
			<< endl;
		if (it->second->filter) {
			//fprintf (axes_drv_func, "/* axis HAS a filter  \n");
			ostringstream code_bef_expr, code_expr;
			it->second->filter->PrintExpressionCode (code_bef_expr, code_expr);
			fprintf (axes_drv_func, "if ( %s ) { \n", code_expr.str().c_str());
			fprintf (axes_drv_func, "\tax_%s.compute();\n",it->first.c_str());
			fprintf (axes_drv_func, "} else { ax_%s.reset(); }\n", it->first.c_str());
			fprintf (axes_drv_func, "\n");
		} else {
			fprintf (axes_drv_func, "/* axis DOES NOT have a filter  */\n");
			fprintf(axes_drv_func, "\tax_%s.compute();\n",it->first.c_str());
		}
		string ax_file_h_name=work_dir+string("/ax_") + it->first + string(".h");
		FILE * ax_file_h =fopen(ax_file_h_name.c_str(), "wb");
		fprintf (ax_file_h, "%s\n", axis_code_str_h.str().c_str());
		fclose (ax_file_h);
		string ax_file_cpp_name=work_dir+string("/ax_") + it->first + string(".cpp");
		FILE * ax_file_cpp =fopen(ax_file_cpp_name.c_str(), "wb");
		fprintf (ax_file_cpp, "#include \"ax_%s.h\"\n", it->first.c_str());
		fprintf (ax_file_cpp, "%s\n", axis_code_str_cpp.str().c_str());
		fclose (ax_file_cpp);
	}
	fprintf(axes_drv_func, "}\n");
}


void	generate_edit_section_code();
void	generate_edit_section_code()
{
	string global_vars_fname = work_dir+string("/global.h");
	global_vars = fopen(global_vars_fname.c_str(), "wb");
	if (!global_vars) {
		cerr << "Unable to open file: " << global_vars_fname << " for writing ... exiting \n";
		exit(1);
	}
	fprintf (global_vars, "#ifndef __NxD_GLOB_VARS_H\n#define __NxD_GLOB_VARS_H\n");
	fprintf (global_vars, "#include <sys/types.h>\n");
	fprintf (global_vars, "#include <map>\n#include <vector>\nusing namespace std;\n");
	fprintf (global_vars, "#include \"mean_stddev_struct.h\"\n");
	fprintf (global_vars, "#include <cstdlib>\n");
	fprintf (global_vars, "#include <cstdio>\n");
	fprintf (global_vars, "extern FILE * runtime_errors ;\n");
	fprintf (global_vars, "void print_list_counts();\n");
	fprintf (global_vars, "void tab_compute();\n");
	fprintf (global_vars, "void tab_summ();\n");
	fprintf (global_vars, "void ax_compute();\n");
	string list_counts_fname = work_dir + string("/print_list_counts.C");
	FILE * print_list_counts=fopen(list_counts_fname.c_str(), "wb");
	fprintf(print_list_counts, "#include \"global.h\"\n");
	fprintf(print_list_counts, "#include <map>\n");
	fprintf(print_list_counts, "#include <string>\n");
	fprintf(print_list_counts, "template <class T>\nvoid print_list_summ(std::map<T,int> &m, std::string var_name, std::string text);\n");
	fprintf(print_list_counts, "void print_list_counts(){\n");
	fclose(print_list_counts);
	string edit_out_fname=work_dir+string( "/edit_out.c");
	FILE * edit_out= fopen(edit_out_fname.c_str(), "w+b");
	if(edit_out==0){
		printf("could not open edit_out.c for writing\n");
		exit(1);
	}
#if __WIN32__
	fprintf (edit_out, "#include \"stubs/iso_types.h\"\n" );
	fprintf (edit_out, "#include \"ax_stmt_type.h\"\n" );
#endif /* __WIN32__ */
	fprintf(edit_out, "#include <cstdio>\n#include <iostream>\n#include <string>\n#include <vector>\nusing namespace std;\n" );

	fprintf (edit_out, "string xtcc_stdout_fname(\"xtcc_stdout.log\");\n");
	fprintf (edit_out, "FILE * xtcc_stdout=0;\n");
	fprintf (edit_out, "#include <sys/types.h>\n" );
	fprintf (edit_out, "int8_t c[%d];\n", rec_len );
	fprintf (edit_out, "#include \"global.h\"\n" );
	cout << "printing edit:" << endl;
	tree_root->GenerateCode(edit_out);
	fclose (edit_out);

	string list_fname = work_dir + string("/print_list_counts.C");
	print_list_counts = fopen (list_fname.c_str(), "a+");
	fprintf (print_list_counts, "}\n");
	fclose (print_list_counts);
	fclose (global_vars);

}

void generate_make_file();
void generate_make_file()
{
	using namespace Table;
	string makefile_name=work_dir+string("/") + string("Makefile");
	FILE * makefile =fopen(makefile_name.c_str(), "wb");
	stringstream source_cpp_str;
	stringstream source_h_str;
	stringstream individual_dep_str;
	stringstream makefile_str;

	for (CMAPITER it=ax_map.begin(); it!=ax_map.end(); ++it) {
		source_cpp_str << "ax_" << it->first << ".cpp ";
		source_h_str << "ax_" << it->first << ".h ";
	}

	makefile_str << "CC = $(CXX) " << endl;
	makefile_str << "CPP_SOURCES = "
		<< source_cpp_str.str() << endl;
	makefile_str << "OBJECTS := $(CPP_SOURCES:.cpp=.o)\n";
	makefile_str << endl
		<< "my_edit.exe: $($CPP_SOURCES) $(OBJECTS)\n"
		<< "\techo \"dummy my_edit.exe target for now\"\n"
		<< endl;

	makefile_str << "%.o: %.cpp %.h\n"
			<< "\t$(CC) -c $(CFLAGS) $<\n"
			<< endl;

	makefile_str 
	<< "%.dep : %.cpp\n"
	<< "	@set -e; rm -f $@; \\\n"
	<< "		$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \\\n"
	<< "		sed 's,\\($*\\)\\.o[ :]*,\\1.o $@ :,g' < $@.$$$$ > $@; \\\n"
	<< "		rm -f $@.$$$$\n" 
	<< endl;




	fprintf(makefile, "%s\n", makefile_str.str().c_str());
	fclose(makefile);

}
