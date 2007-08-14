#include <bitset>
#include <string>
#include <vector>
using namespace std;
struct axis_q1{
	bitset<5> flag;
	vector<string> stmt_text;
	bitset<6> is_a_count_text;
	axis_q1():stmt_text(6){
	stmt_text[0]="Q1. Title";
	is_a_count_text[0]=false;
	stmt_text[1]="less= 20";
	is_a_count_text[1]=true;
	stmt_text[2]="greater 20";
	is_a_count_text[2]=true;
	stmt_text[3]="A ";
	is_a_count_text[3]=true;
	stmt_text[4]="B";
	is_a_count_text[4]=true;
	stmt_text[5]="C";
	is_a_count_text[5]=true;
}
	void compute(){
	flag.reset();
	if (global_val  <= 20  ){
		flag[0]=true;
	}
	if (global_val  > 20  ){
		flag[1]=true;
	}
	if (a  == 65  ){
		flag[2]=true;
	}
	if (b  == 66  ){
		flag[3]=true;
	}
	if (d  == 68  ){
		flag[4]=true;
	}
	} /* close compute func */
} ax_q1;
struct axis_q2{
	bitset<4> flag;
	vector<string> stmt_text;
	bitset<5> is_a_count_text;
	axis_q2():stmt_text(5){
	stmt_text[0]="Q2";
	is_a_count_text[0]=false;
	stmt_text[1]="row";
	is_a_count_text[1]=true;
	stmt_text[2]="A ";
	is_a_count_text[2]=true;
	stmt_text[3]="B";
	is_a_count_text[3]=true;
	stmt_text[4]="C";
	is_a_count_text[4]=true;
}
	void compute(){
	flag.reset();
	if (global_val  > 30  ){
		flag[0]=true;
	}
	if (a  == 65  ){
		flag[1]=true;
	}
	if (b  == 66  ){
		flag[2]=true;
	}
	if (d  == 68  ){
		flag[3]=true;
	}
	} /* close compute func */
} ax_q2;
struct axis_q3{
	bitset<4> flag;
	vector<string> stmt_text;
	bitset<5> is_a_count_text;
	axis_q3():stmt_text(5){
	stmt_text[0]="Q3";
	is_a_count_text[0]=false;
	stmt_text[1]="row";
	is_a_count_text[1]=true;
	stmt_text[2]="A ";
	is_a_count_text[2]=true;
	stmt_text[3]="B";
	is_a_count_text[3]=true;
	stmt_text[4]="C";
	is_a_count_text[4]=true;
}
	void compute(){
	flag.reset();
	if (global_val  > 40  ){
		flag[0]=true;
	}
	if (a  == 65  ){
		flag[1]=true;
	}
	if (b  == 66  ){
		flag[2]=true;
	}
	if (d  == 68  ){
		flag[3]=true;
	}
	} /* close compute func */
} ax_q3;
