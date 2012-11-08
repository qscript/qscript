/*
 * =====================================================================================
 *
 *       Filename:  tabulate_isolate_bug.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Thursday 08 November 2012 06:30:58  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <iostream>

using namespace std;

char shuffle_mask_ban8[] __attribute__ ((aligned(16)))
	= { 	0, 1, 2, 3, 4, 5, 6, 7, 
	 	0, 1, 2, 3, 4, 5, 6, 7
	};
char shuffle_mask_side8[] __attribute__ ((aligned(16)))
	= { 	0, 0, 0, 0, 0, 0, 0, 0, 
		1, 1, 1, 1, 1, 1, 1, 1 
	};

void tabulate_side_n_ban_m (
			  int n_side_elements
			, char * side_ptr
			, int m_ban_elements
			, char * ban_ptr
			, int   counter []
			, char * chk_sid
			, char * chk_ban
			, char * chk_xmm1
			, char * chk_xmm2
		)
{
	cout << __PRETTY_FUNCTION__ << endl;
	cout 	<< "n_side_elements: " << n_side_elements << endl
		<< "m_ban_elements:  " << m_ban_elements  << endl
		<< endl;
	cout << "chk_ban: " << (long) chk_ban << endl;
	cout << "chk_sid: " << (long) chk_sid << endl;
	int l_n_side_elements = n_side_elements;
	int * my_ptr __attribute__ ((aligned(16))) = counter;
	int i = 0, j = 0;
	if (l_n_side_elements > 0) {
		while (l_n_side_elements > 0) {
			//cout << "1 reached here: " << endl;
			int l_m_ban_elements  = m_ban_elements;
			j = 0;
			char * l_ban_ptr = ban_ptr;

			if (l_m_ban_elements >= 4 /*  && l_m_ban_elements <=7 */) {
				// we can process 2 rows at a time
				// and between 10 - 14 conditions in 1 go
				cout << "l_m_ban_elements > 4: i == " << i << endl;

				asm (
						"movdqa (%0), %%xmm1\n\t"
						: /*  outputs */
						: /*  inputs */ "r" (shuffle_mask_ban8)
						: /*  clobbered */ "xmm1"
				    );
				asm (
						"movdqa (%0), %%xmm2\n\t"
						: /*  outputs */
						: /*  inputs */ "r" (shuffle_mask_side8)
						: /*  clobbered */ "xmm2"
				    );
				if (l_n_side_elements >= 2) {
//#if 0
					//while (l_m_ban_elements > 4) {
					asm (
							"movq (%0), %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (l_ban_ptr)
							: /*  clobbered */ "xmm0" 
					    );

					asm (
							"pshufb %%xmm1, %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "xmm0" 
					    );

					asm (
							"xor %%eax, %%eax\n\t"
							"movw (%0), %%ax\n\t"
							"pinsrw $0, %%eax, %%xmm3\n\t"
							"pshufb %%xmm2, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (side_ptr + i)
							: /*  clobbered */ "rax", "xmm3"
					    );

					asm (
						"movdqu %%xmm0, %0\n\t"
							: /*  outputs */ "=m" (*chk_ban)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );

					asm (
						"movdqu %%xmm3, %0\n\t"
							: /*  outputs */ "=m" (*chk_sid)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );

					asm (
							"pand %%xmm3, %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "xmm0"
					    );

#if 1
					// ======= Process the 1st Row ======================

					asm (
							"pextrd $0, %%xmm0, %%eax\n\t"
							"pinsrd $0, %%eax, %%xmm4\n\t"
							"pmovsxbd %%xmm4, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "rax", "xmm4", "xmm3"
					    );
					// load the 1st 4 counter variables
					asm (
							"movdqu (%0), %%xmm5\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (my_ptr)
							: /*  clobbered */ "xmm5"
					    );

					asm (
						"paddd %%xmm3, %%xmm5\n\t"
							: /*  outputs */ 
							: /*  inputs */ 
							: /*  clobbered */ 
								"xmm5"
					    );

					asm (
						"movdqu %%xmm5, %0\n\t"
							: /*  outputs */ "=m" (*my_ptr)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );
					//my_ptr += 4;

					//// note l_m_ban_elements < 8 otherwise the above if condition would
					//// have trapped it
					char residue = l_m_ban_elements - 4;
					char offset = 0;
					// residue can be 3, 2, 1
					if (residue > 1) {
						// note - although we are extracting the double word
						// we only need the 1st 2 bytes of it.
						asm (
								"pextrd $1, %%xmm0, %%eax\n\t"
								"pinsrd $0, %%eax, %%xmm4\n\t"
								"pmovsxbd %%xmm4, %%xmm3\n\t"
								: /*  outputs */
								: /*  inputs */ 
								: /*  clobbered */ "rax", "xmm4", "xmm3"
						    );
						// load the next 2 counter variables
						asm (
								"movq (%0), %%xmm5\n\t"
								: /*  outputs */
								: /*  inputs */ "r" (my_ptr + 4)
								: /*  clobbered */ "xmm5"
						    );

						asm (
							"paddd %%xmm3, %%xmm5\n\t"
								: /*  outputs */ 
								: /*  inputs */ 
								: /*  clobbered */ 
									"xmm5"
						    );

						asm (
							"movq %%xmm5, %0\n\t"
								: /*  outputs */ "=m" (*(my_ptr+4))
								: /*  inputs */ 
								: /*  clobbered */ 
									"memory"
						    );
						//my_ptr += 2;
						residue -= 2;
						offset = 2;
					}
					if (residue == 1) {
						// let the compiler do this
						// nxd l_ban_ptr[6] will not work for 
						//
						if (side_ptr[i] && l_ban_ptr[3+offset+1]) {
							++ my_ptr[3+offset + 1];
						}
						//++my_ptr;
					}
#endif /*  0 */
					// ======= Process the 2nd Row ======================
					// comment this later
					my_ptr += l_m_ban_elements;
#if 1
					asm (
							"pextrd $2, %%xmm0, %%eax\n\t"
							"pinsrd $0, %%eax, %%xmm4\n\t"
							"pmovsxbd %%xmm4, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "rax", "xmm4", "xmm3"
					    );
					// load the 1st 4 counter variables
					asm (
							"movdqu (%0), %%xmm5\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (my_ptr)
							: /*  clobbered */ "xmm5"
					    );

					asm (
						"paddd %%xmm3, %%xmm5\n\t"
							: /*  outputs */ 
							: /*  inputs */ 
							: /*  clobbered */ 
								"xmm5"
					    );

					asm (
						"movdqu %%xmm5, %0\n\t"
							: /*  outputs */ "=m" (*my_ptr)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );
					//my_ptr += 4;

					// note l_m_ban_elements < 8 otherwise the above if condition would
					// have trapped it
					residue = l_m_ban_elements - 4;
					offset = 0;
					// residue can be 3, 2, 1
					if (residue > 1) {
						// note - although we are extracting the double word
						// we only need the 1st 2 bytes of it.
						asm (
								"pextrd $3, %%xmm0, %%eax\n\t"
								"pinsrd $0, %%eax, %%xmm4\n\t"
								"pmovsxbd %%xmm4, %%xmm3\n\t"
								: /*  outputs */
								: /*  inputs */ 
								: /*  clobbered */ "rax", "xmm4", "xmm3"
						    );
						// load the next 2 counter variables
						asm (
								"movq (%0), %%xmm5\n\t"
								: /*  outputs */
								: /*  inputs */ "r" (my_ptr+4)
								: /*  clobbered */ "xmm5"
						    );

						asm (
							"paddd %%xmm3, %%xmm5\n\t"
								: /*  outputs */ 
								: /*  inputs */ 
								: /*  clobbered */ 
									"xmm5"
						    );

						asm (
							"movq %%xmm5, %0\n\t"
								: /*  outputs */ "=m" (*(my_ptr+4))
								: /*  inputs */ 
								: /*  clobbered */ 
									"memory"
						    );
						//my_ptr += 2;
						residue -= 2;
						offset = 2;
					}
					if (residue == 1) {
						// let the compiler do this
						if (side_ptr[i+1] && l_ban_ptr[3 + offset + 1]) {
							++ my_ptr[3 + offset + 1];
							//++my_ptr;
						}
					}
					my_ptr += l_m_ban_elements;
#endif /*  0 */
					i += 2;
					l_n_side_elements -= 2;
					chk_sid  += 16;
					chk_ban  += 16;

					//my_ptr += 4;
				//}
				}
				if (l_n_side_elements == 1) {
#if 1
					// start programming from here : nxd
					//while (l_m_ban_elements > 4) {
					asm (
							"movq (%0), %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (l_ban_ptr)
							: /*  clobbered */ "xmm0" 
					    );

					asm (
							"pshufb %%xmm1, %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "xmm0" 
					    );

					asm (
							"xor %%eax, %%eax\n\t"
							"movb (%0), %%al\n\t"
							"pinsrb $0, %%eax, %%xmm3\n\t"
							"pshufb %%xmm2, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (side_ptr + i)
							: /*  clobbered */ "rax", "xmm3"
					    );

					asm (
						"movdqu %%xmm0, %0\n\t"
							: /*  outputs */ "=m" (*chk_ban)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );

					asm (
						"movdqu %%xmm3, %0\n\t"
							: /*  outputs */ "=m" (*chk_sid)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );

					asm (
							"pand %%xmm3, %%xmm0\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "xmm0"
					    );

					// ======= Process the 1st Row ======================

					asm (
							"pextrd $0, %%xmm0, %%eax\n\t"
							"pinsrd $0, %%eax, %%xmm4\n\t"
							"pmovsxbd %%xmm4, %%xmm3\n\t"
							: /*  outputs */
							: /*  inputs */ 
							: /*  clobbered */ "rax", "xmm4", "xmm3"
					    );
					// load the 1st 4 counter variables
					asm (
							"movdqu (%0), %%xmm5\n\t"
							: /*  outputs */
							: /*  inputs */ "r" (my_ptr)
							: /*  clobbered */ "xmm5"
					    );

					asm (
						"paddd %%xmm3, %%xmm5\n\t"
							: /*  outputs */ 
							: /*  inputs */ 
							: /*  clobbered */ 
								"xmm5"
					    );

					asm (
						"movdqu %%xmm5, %0\n\t"
							: /*  outputs */ "=m" (*my_ptr)
							: /*  inputs */ 
							: /*  clobbered */ 
								"memory"
					    );
					//my_ptr += 4;

					// note l_m_ban_elements < 8 otherwise the above if condition would
					// have trapped it
					char residue = l_m_ban_elements - 4;
					char offset = 0;
					// residue can be 3, 2, 1
					if (residue > 1) {
						// note - although we are extracting the double word
						// we only need the 1st 2 bytes of it.
						asm (
								"pextrd $1, %%xmm0, %%eax\n\t"
								"pinsrd $0, %%eax, %%xmm4\n\t"
								"pmovsxbd %%xmm4, %%xmm3\n\t"
								: /*  outputs */
								: /*  inputs */ 
								: /*  clobbered */ "rax", "xmm4", "xmm3"
						    );
						// load the next 2 counter variables
						asm (
								"movq (%0), %%xmm5\n\t"
								: /*  outputs */
								: /*  inputs */ "r" (my_ptr + 4)
								: /*  clobbered */ "xmm5"
						    );

						asm (
							"paddd %%xmm3, %%xmm5\n\t"
								: /*  outputs */ 
								: /*  inputs */ 
								: /*  clobbered */ 
									"xmm5"
						    );

						asm (
							"movq %%xmm5, %0\n\t"
								: /*  outputs */ "=m" (*(my_ptr + 4))
								: /*  inputs */ 
								: /*  clobbered */ 
									"memory"
						    );
						//my_ptr += 2;
						residue -= 2;
						offset = 2;
					}
					if (residue == 1) {
						// let the compiler do this
						if (side_ptr[i] && l_ban_ptr[3 + offset + 1]) {
							++ my_ptr[3 + offset + 1];
						}
						//++my_ptr;
					}


#endif /*  0 */
					i += 1;
					l_n_side_elements -= 1;
					chk_sid  += 16;
					chk_ban  += 16;

					//my_ptr += 4;
					my_ptr += l_m_ban_elements;
				//}
				}
			}
		}
	}
	cout << "EXIT: " << __PRETTY_FUNCTION__ << endl;
}
	const int m_ban_elements = 7;
	int counter[7 * m_ban_elements] ;
	char  chk_sid  [8*16] __attribute__ ((aligned(16))); 
	char  chk_ban  [8*16] __attribute__ ((aligned(16))); 
	char  chk_xmm1 [16 * 7] __attribute__ ((aligned(16))); 
	char  chk_xmm2 [16 * 7] __attribute__ ((aligned(16))); 

void print_counter (int counter[], int n_side, int m_ban)
{
	for (int i=0; i < n_side; ++i) {
		cout << "i == " << i << " | ";
		for (int j=0; j < m_ban; ++j) {
			cout << " " << counter[i*m_ban + j];
		}
		cout << endl;
	}
}

int main()
{
	{

		//int n_side_elements = 7;
		int n_side_elements = 7;
		//const int m_ban_elements = 44;
		char flag_ban[m_ban_elements] __attribute__ ((aligned(16)));
		char flag_side_7[8]  __attribute__ ((aligned(16)));;
		char * side_ptr __attribute__ ((aligned(16))) = flag_side_7;
		char * ban_ptr   __attribute__ ((aligned(16))) = flag_ban;
		cout << "side_ptr: " << (long) side_ptr << endl;
		cout << "ban_ptr: " << (long) ban_ptr << endl;
		//char  chk_sid  [m_ban_elements * 7] __attribute__ ((aligned(16))); 
		//char  chk_ban  [m_ban_elements * 7] __attribute__ ((aligned(16))); 
		//char  chk_xmm1 [m_ban_elements * 7] __attribute__ ((aligned(16))); 
		//char  chk_xmm2 [m_ban_elements * 7] __attribute__ ((aligned(16))); 

		//char  chk_xmm1 [16 * 7] __attribute__ ((aligned(16))); 
		//char  chk_xmm2 [16 * 7] __attribute__ ((aligned(16))); 

		for (int i=0; i < 7; ++i) {
			for (int j=0; j < m_ban_elements; ++j) {
				counter [i*m_ban_elements + j] = j + (i+1)*10;
				//chk_xmm1[i*m_ban_elements + j] = 0;
				//chk_xmm2[i*m_ban_elements + j] = 0;
			}
			for (int j=0; j < 16; ++j) {
				chk_sid [i*16 + j] = 0;
				chk_ban [i*16 + j] = 0;
			}
			//flag_side_7[i] = 21;
			flag_side_7[i] = 1;
			//flag_side_7[i] = i;
		}
		for (int j=0; j < m_ban_elements; ++j) {
			// if (j%2==0)
			// 	flag_ban[j] = 1;
			// else 
			// 	flag_ban[j] = 0;
			//flag_ban[j] = j*2;
			flag_ban[j] = 0;
			//flag_ban[j] = 1;
			
			//flag_ban[j] = j;
		}
		//flag_side_7[0] = 0;
		//flag_side_7[1] = 0;
		flag_side_7[2] = 0;
		flag_side_7[3] = 1;
		//flag_side_7[4] = 0;
		//flag_side_7[5] = 0;
		//flag_side_7[6] = 0;
		cout << "chk_ban: " << (long) chk_ban << endl;
		cout << "chk_sid: " << (long) chk_sid << endl;


		flag_ban[0] = 0;
		flag_ban[3] = 1;
		flag_ban[4] = 1;
		flag_ban[5] = 1;
		flag_ban[6] = 1;

		print_counter (counter, 7, m_ban_elements);

		char * chk_sid_ptr = chk_sid;
		char * chk_ban_ptr = chk_ban;
		cout << "chk_side_ptr: " << (long) chk_sid_ptr << endl;
		cout << "chk_ban_ptr: " << (long) chk_ban_ptr << endl;

		tabulate_side_n_ban_m (
				  n_side_elements
				, side_ptr
				, m_ban_elements
				, ban_ptr 
				, counter 
				, chk_sid_ptr //, chk_sid
				, chk_ban_ptr //, chk_ban
				, chk_xmm1
				, chk_xmm2
		);
		cout << "chk_ban: " << (long) chk_ban << endl;
		cout << "chk_sid: " << (long) chk_sid << endl;
		cout << "chk_side_ptr: " << (long) chk_sid_ptr << endl;
		cout << "chk_ban_ptr: " << (long) chk_ban_ptr << endl;

		print_counter (counter, 7, m_ban_elements);
		//for (int i=0; i < 7; ++i)
		for (int i=0; i < 7; ++i) {
			for (int j=0; j < 16; ++j) {
				cout << (int) chk_sid[i * 16 + j] ;
			}
			cout << endl;
			// NxD 
			// Cant figure out the memory error below
			for (int j=0; j < 16; ++j) {
				cout << (int) chk_ban[i * 16 + j] ;
			}
			cout << endl;
			//for (int j=0; j < m_ban_elements; ++j) {
			//	cout << (int) chk_xmm1[i * m_ban_elements + j] ;
			//}
			//cout << endl;
			//for (int j=0; j < m_ban_elements; ++j) {
			//	cout << (int) chk_xmm2[i * m_ban_elements + j] ;
			//}
			cout << " ================== " << endl;
		}
#if 0
		for (int i=0; i < 7; ++i) {
			//for (int j=0; j < 16; ++j) {
			//	cout << (int) chk_sid[i * 16 + j] ;
			//}
			//cout << endl;
			// NxD 
			// Cant figure out the memory error below
			for (int j=0; j < 16; ++j) {
				cout << (int) chk_ban[i * 16 + j] ;
			}
			cout << endl;
			//for (int j=0; j < m_ban_elements; ++j) {
			//	cout << (int) chk_xmm1[i * m_ban_elements + j] ;
			//}
			//cout << endl;
			//for (int j=0; j < m_ban_elements; ++j) {
			//	cout << (int) chk_xmm2[i * m_ban_elements + j] ;
			//}
			cout << " ================== " << endl;
		}
#endif /* 0 */
	}
}
