/*
 * =====================================================================================
 *
 *       Filename:  simple.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Saturday 27 October 2012 01:24:40  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
char flag_ban1 [] = { 1 };
char flag_ban2 [] = { 1, 1 };
char flag_side4 [4]  = { 0, 1, 1, 0 };
int counter_4_1 [] __attribute__ ((aligned(16))) = { 1, 2, 3, 4 };
int counter_4_2 [] __attribute__ ((aligned(16))) = { 
	5, 10, 15, 20,
	25, 30, 35, 40
};


void tabulate_side4_ban1 ()
{
	if (flag_side4[0] && flag_ban1[0])
		++ counter_4_1[0];
	if (flag_side4[1] && flag_ban1[0])
		++ counter_4_1[1];
	if (flag_side4[2] && flag_ban1[0])
		++ counter_4_1[2];
	if (flag_side4[3] && flag_ban1[0])
		++ counter_4_1[3];
}


void tabulate_side4_ban2 ()
{

	int cols = 2;

	if (flag_side4[0] && flag_ban2[0])
		++ counter_4_2[0];
	if (flag_side4[1] && flag_ban2[0])
		++ counter_4_2[1];
	if (flag_side4[2] && flag_ban2[0])
		++ counter_4_2[2];
	if (flag_side4[3] && flag_ban2[0])
		++ counter_4_2[3];

	if (flag_side4[0] && flag_ban2[1])
		++ counter_4_2[1 * cols + 0];
	if (flag_side4[1] && flag_ban2[1])
		++ counter_4_2[1 * cols + 1];
	if (flag_side4[2] && flag_ban2[1])
		++ counter_4_2[1 * cols + 2];
	if (flag_side4[3] && flag_ban2[1])
		++ counter_4_2[1 * cols + 3];

}

