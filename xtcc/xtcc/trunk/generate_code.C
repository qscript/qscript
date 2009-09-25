#include "expr.h"
#include "stmt.h"

//struct AbstractStatement;
//struct table;
//struct ax;
extern Statement::AbstractStatement * tree_root;
extern char* work_dir;
extern int rec_len;
#include "Tab.h"
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
#include <cstdio>
void print_table_code(FILE * op, FILE *tab_drv_func, FILE * tab_summ_func);
void print_latex_print(FILE* op, int table_index);
void print_table_code(FILE * op, FILE * tab_drv_func, FILE * tab_summ_func){
	using namespace Table;
	fprintf(op, "#include <iostream>\n");
	fprintf(op, "#include <fstream>\n");
	fprintf(op, "#include <vector>\nusing namespace std;\n");
	fprintf(tab_drv_func, "#include \"my_table.C\"\n");
	fprintf(tab_drv_func, "void tab_compute(){\n");
	for(unsigned int i=0; i<table_list.size(); i++){
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
			Expression::AbstractExpression* f= table_list[i]->filter;
			cout << "table: " <<
				map_iter_b->first << " by " <<
				map_iter_s->first << endl;
			if ( f ){
				cout << " Filter: " ;
			}
			fprintf(op, "struct table_%s_%s {\n",
					map_iter_s->first.c_str(), map_iter_b->first.c_str ());
			fprintf(op, "\tconst int rows, cols;\n");
			fprintf(op, "\tvector <int> counter;\n");
			fprintf(op, "\ttable_%s_%s():rows(%d), cols(%d),counter(%d*%d){\n\t\tfor (int i=0;i<counter.size();++i) counter[i]=0; }\n",
					map_iter_s->first.c_str(), map_iter_b->first.c_str (),
					map_iter_s->second->no_count_ax_elems,
					map_iter_b->second->no_count_ax_elems,
					map_iter_s->second->no_count_ax_elems,
					map_iter_b->second->no_count_ax_elems
					);

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
			for(int i=0; i<rows; ++i){
				for(int j=0; j<cols; ++j){
					fprintf(op, "\t\tif(");
					fprintf(op, "ax_%s.flag[%d]", map_iter_s->first.c_str(), i);
					fprintf(op, " && " );
					fprintf(op, "ax_%s.flag[%d]){\n", map_iter_b->first.c_str(), j);
					//fprintf(op, "\t\t\t++counter[i*cols+j];\n",
					fprintf(op, "\t\t\t++counter[%d*cols+%d];\n",
							i, j);
					fprintf(op, "\t\t}\n");
				}
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
			fprintf(op, "\t\tofstream tab_op(\"tab_.csv\", ios_base::out|ios_base::app);\n");
			fprintf(op, "\t\ttab_op << \"rows: \" << rows << \"cols: \" << cols << endl;\n");
			fprintf(op, "\t\ttab_op << ax_%s.ttl_stmt_text[0] << \" x \" << ax_%s.ttl_stmt_text[0] << endl;\n",
					map_iter_s->first.c_str(), map_iter_b->first.c_str()
					);
			fprintf(op, "\t\ttab_op << \",,\";\n");
			fprintf(op, "\t\tfor(int j=0; j<ax_%s.count_stmt_text.size(); ++j){\n", 
					map_iter_b->first.c_str());
			fprintf(op, "\t\t\t tab_op << ax_%s.count_stmt_text[j] << \",\" ;\n", 
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

			fprintf(op, "\t\tfor(int i=0; i<ax_%s.count_stmt_text.size(); ++i){\n",
					map_iter_s->first.c_str());
			fprintf(op, "\t\ttab_op << \",\";\n");
			fprintf(op, "\t\t\tcci=0;\n");
			fprintf(op, "\t\t\ttab_op << ax_%s.count_stmt_text[i] << \",\";\n", map_iter_s->first.c_str()); 
			fprintf(op, "\t\t\tfor(int j=0; j<ax_%s.count_stmt_text.size(); ++j){\n",
				map_iter_b->first.c_str());
			fprintf(op, "\t\t\t\ttab_op << counter[cci+rci*cols]<<\",\";\n");
			fprintf(op, "\t\t\t\t++cci;\n");
			fprintf(op, "\t\t\t}\n");
			fprintf(op, "\t\t\t++rci;\n");
			fprintf(op, "\t\t\ttab_op << endl;\n");
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
			fprintf(tab_drv_func, "\ttab_%s_%s.compute();\n",
				map_iter_s->first.c_str(), map_iter_b->first.c_str()
				);
		}
	}

	fprintf(tab_drv_func, "}\n");

	fprintf(tab_drv_func, "void tab_summ(){\n");
	for(unsigned int i=0; i<table_list.size(); i++){
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
			fprintf(tab_drv_func, "\ttab_%s_%s.print();\n",
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
void print_latex_print(FILE* op, int table_index){
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


void print_axis_code(FILE * op, FILE * axes_drv_func);
void print_axis_code(FILE * op, FILE * axes_drv_func){
	using namespace Table;

	fprintf(op, "#include <bitset>\n" );
	fprintf(op, "#include <string>\n" );
	fprintf(op, "#include <vector>\n" );
	fprintf(op, "using namespace std;\n" );
	fprintf(axes_drv_func, "#include \"my_axes.C\"\n");
	fprintf(axes_drv_func, "void ax_compute(){\n");
	for(CMAPITER it=ax_map.begin(); it!=ax_map.end(); ++it){
		//struct ax* l_ax = *it;
		cout << "Processing axis: " << it->first.c_str() << endl;

		fprintf(op, "struct axis_%s{\n", it->first.c_str() );
		fprintf(op, "\tbitset<%d> flag;\n", it->second->no_count_ax_elems );
		fprintf(op, "\tvector<string> ttl_stmt_text;\n");
		fprintf(op, "\tvector<string> count_stmt_text;\n");
		fprintf(op, "\tbitset<%d> is_a_count_text;\n", it->second->no_tot_ax_elems);
		fprintf(op, "\taxis_%s():ttl_stmt_text(%d),count_stmt_text(%d) {\n"
				, it->first.c_str()
				, it->second->no_tot_ax_elems - it->second->no_count_ax_elems
				, it->second->no_count_ax_elems
				) ;

		int my_counter=0;
		for(basic_print_ax_stmt* ax_stmt_iter=it->second->ttl_ax_stmt_start; 
				ax_stmt_iter; ax_stmt_iter=ax_stmt_iter->next_,
				++my_counter){
			fprintf(op, "\t\tttl_stmt_text[%d]=%s;\n", my_counter, ax_stmt_iter->ax_text().c_str());

			/*
			if(ax_stmt_iter->axtype<=txt_axstmt){
				fprintf(op, "\tis_a_count_text[%d]=false;\n", my_counter);
			} else {
				fprintf(op, "\tis_a_count_text[%d]=true;\n", my_counter);
			}
			*/
		}
		my_counter=0;
		for( basic_count_ax_stmt* ax_stmt_iter=it->second->count_ax_stmt_start; 
				ax_stmt_iter; ax_stmt_iter=ax_stmt_iter->next_,
				++my_counter){
			//fprintf(op, "\tcount_stmt_text[%d]=%s;\n", my_counter, ax_stmt_iter->ax_text().c_str());
			ax_stmt_iter->print_axis_constructor_text(op, my_counter);
			/*
			if(ax_stmt_iter->axtype<=txt_axstmt){
				fprintf(op, "\tis_a_count_text[%d]=false;\n", my_counter);
			} else {
				fprintf(op, "\tis_a_count_text[%d]=true;\n", my_counter);
			}
			*/
		}

		cout << "after basic_ax_stmt loop " << endl;
		/*
		for(unsigned int i=0; 
			it->second->fld_stmt &&
				i< it->second->fld_stmt->stub_list.size(); ++i){
			fprintf(op, "\tbit_stmt_text[%d]=%s;\n", i, 
				it->second->fld_stmt->stub_list[i]->text.c_str());
		}
		*/
		fprintf(op, "\t}\n");
		fprintf(op, "\tvoid compute(){\n\t\tflag.reset();\n");
		basic_count_ax_stmt* iter=it->second->count_ax_stmt_start;
		int counter=0;
		while(iter){
			iter->generate_code(op, counter);
			++counter;
			iter=iter->next_;
		}
		/*
		while(iter){
			if(iter->axtype>=tot_axstmt){
				basic_count_ax_stmt * bc=dynamic_cast<basic_count_ax_stmt *> (iter);
					
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
		fprintf(op, "} ax_%s;\n", it->first.c_str()) ;
		fprintf(axes_drv_func, "\tax_%s.compute();\n",it->first.c_str());
	}
	fprintf(axes_drv_func, "}\n");
}


void	generate_edit_section_code();
void	generate_edit_section_code(){
	string fname=work_dir+string("/global.C");
	FILE * global_vars=fopen(fname.c_str(), "wb");
	fprintf(global_vars, "#ifndef __NxD_GLOB_VARS_H\n#define __NxD_GLOB_VARS_H\n");
	fprintf(global_vars, "#include <sys/types.h>\n");
	fprintf(global_vars, "#include <map>\n using namespace std;\n");
	fprintf(global_vars, "void print_list_counts();\n");
	fprintf(global_vars, "void tab_compute();\n");
	fprintf(global_vars, "void tab_summ();\n");
	fprintf(global_vars, "void ax_compute();\n");
	fclose(global_vars);
	fname=work_dir+string("/print_list_counts.C");
	FILE * print_list_counts=fopen(fname.c_str(), "wb");
	fprintf(print_list_counts, "template <class T>\nvoid print_list_summ(map<T,int> &m, string var_name, string text);\n");
	fprintf(print_list_counts, "void print_list_counts(){\n");
	fclose(print_list_counts);
	fname=work_dir+string( "/edit_out.c");
	FILE * edit_out= fopen(fname.c_str(), "w+b");
	if(edit_out==0){
		printf("could not open edit_out.c for writing\n");
		exit(1);
	}
#if __WIN32__
	fprintf(edit_out, "#include \"stubs/iso_types.h\"\n" );
#endif /* __WIN32__ */
	fprintf(edit_out, "#include <cstdio>\n#include <iostream>\n#include <string>\n#include <vector>\nusing namespace std;\n" );

	fprintf(edit_out, "string xtcc_stdout_fname(\"xtcc_stdout.log\");\n");
	fprintf(edit_out, "FILE * xtcc_stdout=0;\n");
	fprintf(edit_out, "#include <sys/types.h>\n" );
	fprintf(edit_out, "int8_t c[%d];\n", rec_len );
	fprintf(edit_out, "#include \"global.C\"\n" );
	cout << "printing edit:" << endl;
	tree_root->GenerateCode(edit_out);
	fclose(edit_out);
	fname=work_dir+string("/global.C");
	global_vars=fopen(fname.c_str(), "a+");
	if(!global_vars){
		cerr << "cannot open global.C for writing" << endl;
		exit(1);
	}
	fprintf(global_vars, "#endif /* __NxD_GLOB_VARS_H*/\n");
	fclose(global_vars);
	fname=work_dir+string("/print_list_counts.C");
	print_list_counts=fopen(fname.c_str(), "a+");
	fprintf(print_list_counts, "}\n");
	fclose(print_list_counts);

}
