
#include <bitset>
#include <string>
#include <vector>
#include <fstream>
#include <sys/types.h>
#include <sstream>
#include "ax_stmt_type.h"

using std::bitset;
using std::vector;
using std::string;
using std::stringstream;
using std::ofstream;
using std::endl;

int32_t qs3a_data; /*  nest_lev:  0 */
int32_t qs2_data; /*  nest_lev:  0 */
struct axis_qs3a {
	//bitset<27> flag;
	char flag[27] __attribute__ ((aligned(16)));
	vector<string> ttl_stmt_text;
	vector<string> count_stmt_text;
	vector<int> tot_elem_pos_vec;
	bitset<28> is_a_count_text;
	vector<Table::axstmt_type> axis_stmt_type_print;
	vector<Table::axstmt_type> axis_stmt_type_count;
	void reset();
	void compute();
int32_t & qs3a_data;
	axis_qs3a(int32_t & p_qs3a_data, const char * p_text_ttls[])
;
};



	void axis_qs3a::reset(){
		//flag.reset();
		for (int i=0; i<27; ++i) {
			flag[i] = 0;
		}
	}
	void axis_qs3a::compute(){
		//flag.reset();
		reset();
		flag[0]=true;
#if 1
		switch (qs3a_data) {
		case 1:
			flag[1] = true;
			break;
		case 2:
			flag[2] = true;
			break;
		case 3:
			flag[3] = true;
			break;
		case 4:
			flag[4] = true;
			break;
		case 5:
			flag[5] = true;
			break;
		case 6:
			flag[6] = true;
			break;
		case 7:
			flag[7] = true;
			break;
		case 8:
			flag[8] = true;
			break;
		case 9:
			flag[9] = true;
			break;
		case 10:
			flag[10] = true;
			break;
		case 11:
			flag[11] = true;
			break;
		case 12:
			flag[12] = true;
			break;
		case 13:
			flag[13] = true;
			break;
		case 14:
			flag[14] = true;
			break;
		case 15:
			flag[15] = true;
			break;
		case 16:
			flag[16] = true;
			break;
		case 17:
			flag[17] = true;
			break;
		case 18:
			flag[18] = true;
			break;
		case 19:
			flag[19] = true;
			break;
		case 20:
			flag[20] = true;
			break;
		case 21:
			flag[21] = true;
			break;
		case 22:
			flag[22] = true;
			break;
		case 23:
			flag[23] = true;
			break;
		case 24:
			flag[24] = true;
			break;
		case 25:
			flag[25] = true;
			break;
		case 99:
			flag[26] = true;
			break;
		}
#endif /* 0 */
#if 0
	if ( qs3a_data==1 ){
		flag[1]=true;
	}
	if ( qs3a_data==2 ){
		flag[2]=true;
	}
	if ( qs3a_data==3 ){
		flag[3]=true;
	}
	if ( qs3a_data==4 ){
		flag[4]=true;
	}
	if ( qs3a_data==5 ){
		flag[5]=true;
	}
	if ( qs3a_data==6 ){
		flag[6]=true;
	}
	if ( qs3a_data==7 ){
		flag[7]=true;
	}
	if ( qs3a_data==8 ){
		flag[8]=true;
	}
	if ( qs3a_data==9 ){
		flag[9]=true;
	}
	if ( qs3a_data==10 ){
		flag[10]=true;
	}
	if ( qs3a_data==11 ){
		flag[11]=true;
	}
	if ( qs3a_data==12 ){
		flag[12]=true;
	}
	if ( qs3a_data==13 ){
		flag[13]=true;
	}
	if ( qs3a_data==14 ){
		flag[14]=true;
	}
	if ( qs3a_data==15 ){
		flag[15]=true;
	}
	if ( qs3a_data==16 ){
		flag[16]=true;
	}
	if ( qs3a_data==17 ){
		flag[17]=true;
	}
	if ( qs3a_data==18 ){
		flag[18]=true;
	}
	if ( qs3a_data==19 ){
		flag[19]=true;
	}
	if ( qs3a_data==20 ){
		flag[20]=true;
	}
	if ( qs3a_data==21 ){
		flag[21]=true;
	}
	if ( qs3a_data==22 ){
		flag[22]=true;
	}
	if ( qs3a_data==23 ){
		flag[23]=true;
	}
	if ( qs3a_data==24 ){
		flag[24]=true;
	}
	if ( qs3a_data==25 ){
		flag[25]=true;
	}
	if ( qs3a_data==99 ){
		flag[26]=true;
	}
#endif /*  0 */
	} /* close compute func */
const char * qs3a_ttl_stmt_arr[] = {
	"qs3a.Fix me",

	(const char *) 0 };

axis_qs3a::axis_qs3a(int32_t & p_qs3a_data, const char * p_text_ttls[])
:ttl_stmt_text (), count_stmt_text (27), axis_stmt_type_print (), axis_stmt_type_count (27) 
, qs3a_data (p_qs3a_data)
{
	for (const char ** a_ptr = p_text_ttls; *a_ptr != (char *) 0; ++a_ptr) {
		ttl_stmt_text.push_back (string(*a_ptr));
		axis_stmt_type_print.push_back (Table::txt_axstmt);
	}
		count_stmt_text[0]="Total";
	tot_elem_pos_vec.push_back(0);
		 axis_stmt_type_count[0]=Table::tot_axstmt;
		count_stmt_text[1]="Wholesale Trade";
		 axis_stmt_type_count[1]=Table::cnt_axstmt;
		count_stmt_text[2]="Retail Trade";
		 axis_stmt_type_count[2]=Table::cnt_axstmt;
		count_stmt_text[3]="Manufacturing/ Industrial";
		 axis_stmt_type_count[3]=Table::cnt_axstmt;
		count_stmt_text[4]="Mining and quarrying (including oil companies, petrochemicals and oilfield services)";
		 axis_stmt_type_count[4]=Table::cnt_axstmt;
		count_stmt_text[5]="Real Estate Development/ Trading";
		 axis_stmt_type_count[5]=Table::cnt_axstmt;
		count_stmt_text[6]="Contracting / sub-contracting (Construction) ";
		 axis_stmt_type_count[6]=Table::cnt_axstmt;
		count_stmt_text[7]="Contracting (Services)";
		 axis_stmt_type_count[7]=Table::cnt_axstmt;
		count_stmt_text[8]="Services (tourism, healthcare, education, etc.)";
		 axis_stmt_type_count[8]=Table::cnt_axstmt;
		count_stmt_text[9]="Telecommunications";
		 axis_stmt_type_count[9]=Table::cnt_axstmt;
		count_stmt_text[10]="Electricity, water, gas, sanitary services";
		 axis_stmt_type_count[10]=Table::cnt_axstmt;
		count_stmt_text[11]="Transportation";
		 axis_stmt_type_count[11]=Table::cnt_axstmt;
		count_stmt_text[12]="Financial institution (insurance company, investment firm, brokerage house, etc.)";
		 axis_stmt_type_count[12]=Table::cnt_axstmt;
		count_stmt_text[13]="Agriculture and fishing";
		 axis_stmt_type_count[13]=Table::cnt_axstmt;
		count_stmt_text[14]="Rentals; machinery and equipment, rent-a car, video/cds";
		 axis_stmt_type_count[14]=Table::cnt_axstmt;
		count_stmt_text[15]="Computers; hardware and software supply, maintenance and consultancy";
		 axis_stmt_type_count[15]=Table::cnt_axstmt;
		count_stmt_text[16]="Other Business Activities; legal, accounting, management consultancy, architectural, engineering, advertising, labour recruiting";
		 axis_stmt_type_count[16]=Table::cnt_axstmt;
		count_stmt_text[17]="publishers-newspapers and magazines, gyms";
		 axis_stmt_type_count[17]=Table::cnt_axstmt;
		count_stmt_text[18]="Other Services; washing and dry cleaners, barbers, photocopy, photographers,";
		 axis_stmt_type_count[18]=Table::cnt_axstmt;
		count_stmt_text[19]="Vehicle workshops, puncture shops,  vehicle body repair shops, other repair shops";
		 axis_stmt_type_count[19]=Table::cnt_axstmt;
		count_stmt_text[20]="Other 20";
		 axis_stmt_type_count[20]=Table::cnt_axstmt;
		count_stmt_text[21]="Other 21";
		 axis_stmt_type_count[21]=Table::cnt_axstmt;
		count_stmt_text[22]="Other 22";
		 axis_stmt_type_count[22]=Table::cnt_axstmt;
		count_stmt_text[23]="Other 23";
		 axis_stmt_type_count[23]=Table::cnt_axstmt;
		count_stmt_text[24]="Other 24";
		 axis_stmt_type_count[24]=Table::cnt_axstmt;
		count_stmt_text[25]="Other 25";
		 axis_stmt_type_count[25]=Table::cnt_axstmt;
		count_stmt_text[26]="Other";
		 axis_stmt_type_count[26]=Table::cnt_axstmt;
	}/*  close constructor */


struct axis_qs2 {
	//bitset<4> flag;
	char flag[4] __attribute__ ((aligned(16))) ;
	vector<string> ttl_stmt_text;
	vector<string> count_stmt_text;
	vector<int> tot_elem_pos_vec;
	bitset<5> is_a_count_text;
	vector<Table::axstmt_type> axis_stmt_type_print;
	vector<Table::axstmt_type> axis_stmt_type_count;
	void reset();
	void compute();
int32_t & qs2_data;
	axis_qs2(int32_t & p_qs2_data, const char * p_text_ttls[])
;
};
	void axis_qs2::reset()
	{
		//flag.reset();
		for (int i=0; i<4; ++i) {
			flag[i] = 0;
		}
	}
	void axis_qs2::compute()
	{
	//		flag.reset();
		reset();
	/*qs2 :is single coded */
		switch (qs2_data) {
			default:
			flag[0]=true;
			case 1:		flag[1]=true;
			break;
			case 2:		flag[2]=true;
			break;
			case 3:		flag[3]=true;
			break;
		} /* close  switch */
	} /* close compute func */
const char * qs2_ttl_stmt_arr[] = {
	"qs2.Fix me",
	(const char *) 0 
};

axis_qs2::axis_qs2(int32_t & p_qs2_data, const char * p_text_ttls[])
	: ttl_stmt_text (), count_stmt_text (4), axis_stmt_type_print (), axis_stmt_type_count (4) 
	, qs2_data (p_qs2_data)
{
	for (const char ** a_ptr = p_text_ttls; *a_ptr != (char *) 0; ++a_ptr) {
		ttl_stmt_text.push_back (string(*a_ptr));
		axis_stmt_type_print.push_back (Table::txt_axstmt);
	}
		count_stmt_text[0]="Total";
	tot_elem_pos_vec.push_back(0);
		 axis_stmt_type_count[0]=Table::tot_axstmt;
		count_stmt_text[1]="Western";
		 axis_stmt_type_count[1]=Table::cnt_axstmt;
		count_stmt_text[2]="Central";
		 axis_stmt_type_count[2]=Table::cnt_axstmt;
		count_stmt_text[3]="Eastern";
		 axis_stmt_type_count[3]=Table::cnt_axstmt;
} /*  close constructor */

struct axis_qs3a ax_qs3a(qs3a_data, qs3a_ttl_stmt_arr);

struct axis_qs2 ax_qs2(qs2_data, qs2_ttl_stmt_arr);



struct table_qs3a_qs2 {
	struct axis_qs3a & ax_qs3a;
	struct axis_qs2 & ax_qs2;
	int32_t & qs3a_data;
	int32_t & qs2_data;
	const int rows, cols;
	//vector <int> counter;
	int counter[27*4] __attribute__ ((aligned(16))) ;
	const int counter_size ;
	table_qs3a_qs2 (struct axis_qs3a & p_ax_qs3a, struct axis_qs2 & p_ax_qs2, int32_t & p_qs3a_data, int32_t & p_qs2_data)
	: rows(27), cols(4),ax_qs3a(p_ax_qs3a), counter_size(27*4)
	, ax_qs2(p_ax_qs2) , qs3a_data (p_qs3a_data) , qs2_data (p_qs2_data)
	{
		for (int i=0;i<counter_size;++i) counter[i]=0; 
	}
	void compute(){
		//bitset<27> & flag1 = ax_qs3a.flag;
		//bitset<4>  & flag2 = ax_qs2.flag;

		char (& flag1)[27] = ax_qs3a.flag;
		char (& flag2)[4] = ax_qs2.flag;
		for (int i=0; i<27; ++i) {
			//for (int j=0; j<cols; ++j) {
			//	//if(ax_qs3a.flag[0] && ax_qs2.flag[0]){
			//	//	++counter[0*cols+0];
			//	//}
			//	(ax_qs3a.flag[i] && ax_qs2.flag[j]) ? ++ counter[i*cols+j]: 0;
			//}

			// this is the real code I want - but vectorizer does not pick it up
			//
 			// g++ -S -fpermissive -O3 -ftree-vectorize -msse2 -msse4.2 -ftree-vectorizer-verbose=5 f1.cpp 2> vectorized.txt   
			//(flag1[i] && flag2[0]) ? ++ counter[i*4+0]: 0;
			//(flag1[i] && flag2[1]) ? ++ counter[i*4+1]: 0;
			//(flag1[i] && flag2[2]) ? ++ counter[i*4+2]: 0;
			//(flag1[i] && flag2[3]) ? ++ counter[i*4+3]: 0;
			const bool b[4] = { (flag1[i] && flag2[0]),
					(flag1[i] && flag2[1]),
					(flag1[i] && flag2[2]),
					(flag1[i] && flag2[3])
			};

			//const bool b1 = (flag1[i] && flag2[0]);
			//const bool b2 = (flag1[i] && flag2[1]);
			//const bool b3 = (flag1[i] && flag2[2]);
			//const bool b4 = (flag1[i] && flag2[3]);
			counter[i*4+0] += b[0];
			counter[i*4+1] += b[1];
			counter[i*4+2] += b[2];
			counter[i*4+3] += b[3];
			//counter[i*cols + 0] += flag1[i] && flag2[0];
			//counter[i*cols + 1] += flag1[i] && flag2[1];
			//counter[i*cols + 2] += flag1[i] && flag2[2];
			//counter[i*cols + 3] += flag1[i] && flag2[3];
			//for (int j=0; i<cols; ++j) {
			//	counter[i*cols+j] += 1;
			//}
		}
#if 0
		if(ax_qs3a.flag[0] && ax_qs2.flag[0]){
			++counter[0*cols+0];
		}
		if(ax_qs3a.flag[0] && ax_qs2.flag[1]){
			++counter[0*cols+1];
		}
		if(ax_qs3a.flag[0] && ax_qs2.flag[2]){
			++counter[0*cols+2];
		}
		if(ax_qs3a.flag[0] && ax_qs2.flag[3]){
			++counter[0*cols+3];
		}
		if(ax_qs3a.flag[1] && ax_qs2.flag[0]){
			++counter[1*cols+0];
		}
		if(ax_qs3a.flag[1] && ax_qs2.flag[1]){
			++counter[1*cols+1];
		}
		if(ax_qs3a.flag[1] && ax_qs2.flag[2]){
			++counter[1*cols+2];
		}
		if(ax_qs3a.flag[1] && ax_qs2.flag[3]){
			++counter[1*cols+3];
		}
		if(ax_qs3a.flag[2] && ax_qs2.flag[0]){
			++counter[2*cols+0];
		}
		if(ax_qs3a.flag[2] && ax_qs2.flag[1]){
			++counter[2*cols+1];
		}
		if(ax_qs3a.flag[2] && ax_qs2.flag[2]){
			++counter[2*cols+2];
		}
		if(ax_qs3a.flag[2] && ax_qs2.flag[3]){
			++counter[2*cols+3];
		}
		if(ax_qs3a.flag[3] && ax_qs2.flag[0]){
			++counter[3*cols+0];
		}
		if(ax_qs3a.flag[3] && ax_qs2.flag[1]){
			++counter[3*cols+1];
		}
		if(ax_qs3a.flag[3] && ax_qs2.flag[2]){
			++counter[3*cols+2];
		}
		if(ax_qs3a.flag[3] && ax_qs2.flag[3]){
			++counter[3*cols+3];
		}
		if(ax_qs3a.flag[4] && ax_qs2.flag[0]){
			++counter[4*cols+0];
		}
		if(ax_qs3a.flag[4] && ax_qs2.flag[1]){
			++counter[4*cols+1];
		}
		if(ax_qs3a.flag[4] && ax_qs2.flag[2]){
			++counter[4*cols+2];
		}
		if(ax_qs3a.flag[4] && ax_qs2.flag[3]){
			++counter[4*cols+3];
		}
		if(ax_qs3a.flag[5] && ax_qs2.flag[0]){
			++counter[5*cols+0];
		}
		if(ax_qs3a.flag[5] && ax_qs2.flag[1]){
			++counter[5*cols+1];
		}
		if(ax_qs3a.flag[5] && ax_qs2.flag[2]){
			++counter[5*cols+2];
		}
		if(ax_qs3a.flag[5] && ax_qs2.flag[3]){
			++counter[5*cols+3];
		}
		if(ax_qs3a.flag[6] && ax_qs2.flag[0]){
			++counter[6*cols+0];
		}
		if(ax_qs3a.flag[6] && ax_qs2.flag[1]){
			++counter[6*cols+1];
		}
		if(ax_qs3a.flag[6] && ax_qs2.flag[2]){
			++counter[6*cols+2];
		}
		if(ax_qs3a.flag[6] && ax_qs2.flag[3]){
			++counter[6*cols+3];
		}
		if(ax_qs3a.flag[7] && ax_qs2.flag[0]){
			++counter[7*cols+0];
		}
		if(ax_qs3a.flag[7] && ax_qs2.flag[1]){
			++counter[7*cols+1];
		}
		if(ax_qs3a.flag[7] && ax_qs2.flag[2]){
			++counter[7*cols+2];
		}
		if(ax_qs3a.flag[7] && ax_qs2.flag[3]){
			++counter[7*cols+3];
		}
		if(ax_qs3a.flag[8] && ax_qs2.flag[0]){
			++counter[8*cols+0];
		}
		if(ax_qs3a.flag[8] && ax_qs2.flag[1]){
			++counter[8*cols+1];
		}
		if(ax_qs3a.flag[8] && ax_qs2.flag[2]){
			++counter[8*cols+2];
		}
		if(ax_qs3a.flag[8] && ax_qs2.flag[3]){
			++counter[8*cols+3];
		}
		if(ax_qs3a.flag[9] && ax_qs2.flag[0]){
			++counter[9*cols+0];
		}
		if(ax_qs3a.flag[9] && ax_qs2.flag[1]){
			++counter[9*cols+1];
		}
		if(ax_qs3a.flag[9] && ax_qs2.flag[2]){
			++counter[9*cols+2];
		}
		if(ax_qs3a.flag[9] && ax_qs2.flag[3]){
			++counter[9*cols+3];
		}
		if(ax_qs3a.flag[10] && ax_qs2.flag[0]){
			++counter[10*cols+0];
		}
		if(ax_qs3a.flag[10] && ax_qs2.flag[1]){
			++counter[10*cols+1];
		}
		if(ax_qs3a.flag[10] && ax_qs2.flag[2]){
			++counter[10*cols+2];
		}
		if(ax_qs3a.flag[10] && ax_qs2.flag[3]){
			++counter[10*cols+3];
		}
		if(ax_qs3a.flag[11] && ax_qs2.flag[0]){
			++counter[11*cols+0];
		}
		if(ax_qs3a.flag[11] && ax_qs2.flag[1]){
			++counter[11*cols+1];
		}
		if(ax_qs3a.flag[11] && ax_qs2.flag[2]){
			++counter[11*cols+2];
		}
		if(ax_qs3a.flag[11] && ax_qs2.flag[3]){
			++counter[11*cols+3];
		}
		if(ax_qs3a.flag[12] && ax_qs2.flag[0]){
			++counter[12*cols+0];
		}
		if(ax_qs3a.flag[12] && ax_qs2.flag[1]){
			++counter[12*cols+1];
		}
		if(ax_qs3a.flag[12] && ax_qs2.flag[2]){
			++counter[12*cols+2];
		}
		if(ax_qs3a.flag[12] && ax_qs2.flag[3]){
			++counter[12*cols+3];
		}
		if(ax_qs3a.flag[13] && ax_qs2.flag[0]){
			++counter[13*cols+0];
		}
		if(ax_qs3a.flag[13] && ax_qs2.flag[1]){
			++counter[13*cols+1];
		}
		if(ax_qs3a.flag[13] && ax_qs2.flag[2]){
			++counter[13*cols+2];
		}
		if(ax_qs3a.flag[13] && ax_qs2.flag[3]){
			++counter[13*cols+3];
		}
		if(ax_qs3a.flag[14] && ax_qs2.flag[0]){
			++counter[14*cols+0];
		}
		if(ax_qs3a.flag[14] && ax_qs2.flag[1]){
			++counter[14*cols+1];
		}
		if(ax_qs3a.flag[14] && ax_qs2.flag[2]){
			++counter[14*cols+2];
		}
		if(ax_qs3a.flag[14] && ax_qs2.flag[3]){
			++counter[14*cols+3];
		}
		if(ax_qs3a.flag[15] && ax_qs2.flag[0]){
			++counter[15*cols+0];
		}
		if(ax_qs3a.flag[15] && ax_qs2.flag[1]){
			++counter[15*cols+1];
		}
		if(ax_qs3a.flag[15] && ax_qs2.flag[2]){
			++counter[15*cols+2];
		}
		if(ax_qs3a.flag[15] && ax_qs2.flag[3]){
			++counter[15*cols+3];
		}
		if(ax_qs3a.flag[16] && ax_qs2.flag[0]){
			++counter[16*cols+0];
		}
		if(ax_qs3a.flag[16] && ax_qs2.flag[1]){
			++counter[16*cols+1];
		}
		if(ax_qs3a.flag[16] && ax_qs2.flag[2]){
			++counter[16*cols+2];
		}
		if(ax_qs3a.flag[16] && ax_qs2.flag[3]){
			++counter[16*cols+3];
		}
		if(ax_qs3a.flag[17] && ax_qs2.flag[0]){
			++counter[17*cols+0];
		}
		if(ax_qs3a.flag[17] && ax_qs2.flag[1]){
			++counter[17*cols+1];
		}
		if(ax_qs3a.flag[17] && ax_qs2.flag[2]){
			++counter[17*cols+2];
		}
		if(ax_qs3a.flag[17] && ax_qs2.flag[3]){
			++counter[17*cols+3];
		}
		if(ax_qs3a.flag[18] && ax_qs2.flag[0]){
			++counter[18*cols+0];
		}
		if(ax_qs3a.flag[18] && ax_qs2.flag[1]){
			++counter[18*cols+1];
		}
		if(ax_qs3a.flag[18] && ax_qs2.flag[2]){
			++counter[18*cols+2];
		}
		if(ax_qs3a.flag[18] && ax_qs2.flag[3]){
			++counter[18*cols+3];
		}
		if(ax_qs3a.flag[19] && ax_qs2.flag[0]){
			++counter[19*cols+0];
		}
		if(ax_qs3a.flag[19] && ax_qs2.flag[1]){
			++counter[19*cols+1];
		}
		if(ax_qs3a.flag[19] && ax_qs2.flag[2]){
			++counter[19*cols+2];
		}
		if(ax_qs3a.flag[19] && ax_qs2.flag[3]){
			++counter[19*cols+3];
		}
		if(ax_qs3a.flag[20] && ax_qs2.flag[0]){
			++counter[20*cols+0];
		}
		if(ax_qs3a.flag[20] && ax_qs2.flag[1]){
			++counter[20*cols+1];
		}
		if(ax_qs3a.flag[20] && ax_qs2.flag[2]){
			++counter[20*cols+2];
		}
		if(ax_qs3a.flag[20] && ax_qs2.flag[3]){
			++counter[20*cols+3];
		}
		if(ax_qs3a.flag[21] && ax_qs2.flag[0]){
			++counter[21*cols+0];
		}
		if(ax_qs3a.flag[21] && ax_qs2.flag[1]){
			++counter[21*cols+1];
		}
		if(ax_qs3a.flag[21] && ax_qs2.flag[2]){
			++counter[21*cols+2];
		}
		if(ax_qs3a.flag[21] && ax_qs2.flag[3]){
			++counter[21*cols+3];
		}
		if(ax_qs3a.flag[22] && ax_qs2.flag[0]){
			++counter[22*cols+0];
		}
		if(ax_qs3a.flag[22] && ax_qs2.flag[1]){
			++counter[22*cols+1];
		}
		if(ax_qs3a.flag[22] && ax_qs2.flag[2]){
			++counter[22*cols+2];
		}
		if(ax_qs3a.flag[22] && ax_qs2.flag[3]){
			++counter[22*cols+3];
		}
		if(ax_qs3a.flag[23] && ax_qs2.flag[0]){
			++counter[23*cols+0];
		}
		if(ax_qs3a.flag[23] && ax_qs2.flag[1]){
			++counter[23*cols+1];
		}
		if(ax_qs3a.flag[23] && ax_qs2.flag[2]){
			++counter[23*cols+2];
		}
		if(ax_qs3a.flag[23] && ax_qs2.flag[3]){
			++counter[23*cols+3];
		}
		if(ax_qs3a.flag[24] && ax_qs2.flag[0]){
			++counter[24*cols+0];
		}
		if(ax_qs3a.flag[24] && ax_qs2.flag[1]){
			++counter[24*cols+1];
		}
		if(ax_qs3a.flag[24] && ax_qs2.flag[2]){
			++counter[24*cols+2];
		}
		if(ax_qs3a.flag[24] && ax_qs2.flag[3]){
			++counter[24*cols+3];
		}
		if(ax_qs3a.flag[25] && ax_qs2.flag[0]){
			++counter[25*cols+0];
		}
		if(ax_qs3a.flag[25] && ax_qs2.flag[1]){
			++counter[25*cols+1];
		}
		if(ax_qs3a.flag[25] && ax_qs2.flag[2]){
			++counter[25*cols+2];
		}
		if(ax_qs3a.flag[25] && ax_qs2.flag[3]){
			++counter[25*cols+3];
		}
		if(ax_qs3a.flag[26] && ax_qs2.flag[0]){
			++counter[26*cols+0];
		}
		if(ax_qs3a.flag[26] && ax_qs2.flag[1]){
			++counter[26*cols+1];
		}
		if(ax_qs3a.flag[26] && ax_qs2.flag[2]){
			++counter[26*cols+2];
		}
		if(ax_qs3a.flag[26] && ax_qs2.flag[3]){
			++counter[26*cols+3];
		}
#endif /*  0 */
	} /*  close compute */
#if 1
	void print(){
		int rci=0, cci=0; /* row counter index , col ... */
		ofstream tab_op("tab_.csv", std::ios_base::out|std::ios_base::app);
		tab_op << "rows" << "," << rows << ",cols" << "," << cols << endl;
		tab_op << "\"" << ax_qs3a.ttl_stmt_text[0] << "\"" << "," <<  "\"" << ax_qs2.ttl_stmt_text[0] << "\""  << endl;
		tab_op << ",,";
		for(int j=0; j<ax_qs2.count_stmt_text.size(); ++j){
			 tab_op << "\"" << ax_qs2.count_stmt_text[j] << "\""  << "," ;
		}
		tab_op << endl;
		int inc_counter=0;
		for (int i=0; i<ax_qs3a.count_stmt_text.size(); ++i) {
			tab_op << ",";
			stringstream col_perc_str;
			stringstream row_perc_str;
			col_perc_str << ",,";
			row_perc_str << ",,";
			cci=0;
			tab_op << "\"" << ax_qs3a.count_stmt_text[i] << "\"" << ",";
				if (ax_qs3a.axis_stmt_type_count[rci] == Table::inc_axstmt) {
					++inc_counter;
				}
			for (int j=0; j<ax_qs2.count_stmt_text.size(); ++j) {
				if (ax_qs3a.axis_stmt_type_count[rci] == Table::cnt_axstmt) {
					tab_op << counter[cci+rci*cols]<<",";
					if (ax_qs3a.tot_elem_pos_vec.size()>0) {
						col_perc_str << (((double) counter[cci+rci*cols]) / counter[cci+ax_qs3a.tot_elem_pos_vec[0]*cols]) * 100 <<",";
					}
					if (ax_qs2.tot_elem_pos_vec.size()>0) {
						row_perc_str << (((double) counter[cci+rci*cols]) / counter[ax_qs2.tot_elem_pos_vec[0]+cols*rci]) * 100 <<",";
					}
				}
				if (ax_qs3a.axis_stmt_type_count[rci] == Table::tot_axstmt) {
					tab_op << counter[cci+rci*cols]<<",";
				}
				++cci;
			}
			++rci;
			tab_op << endl;
			tab_op << col_perc_str.str() << endl;
			tab_op << row_perc_str.str() << endl;
		}
		tab_op << endl;
		tab_op.close();
	} /*  close print */
#endif /* 0 */
} ;

struct table_qs3a_qs2 tab_qs3a_qs2(ax_qs3a, ax_qs2, qs3a_data, qs2_data);

void tab_compute(){
	if ( qs3a_data>0 && qs2_data>0 ) { 
		tab_qs3a_qs2.compute();
	}
}


int main()
{
	qs3a_data = 10;
	qs2_data = 3;
	table_qs3a_qs2 tab_qs3a_qs2 (ax_qs3a, ax_qs2, qs3a_data, qs2_data);

	tab_compute();
	tab_qs3a_qs2.print();

}
