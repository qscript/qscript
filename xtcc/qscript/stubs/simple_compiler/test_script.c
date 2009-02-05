#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "stmt.h"
#include "xtcc_set.h"
using namespace std;
void read_data (const char *prompt);
extern vector < int >data;
vector < q_stmt * >q_list;
int
main ()
{
  xtcc_set xs_0;
  xs_0.indiv.insert (1);
  xs_0.indiv.insert (2);
  q_stmt *q1 =
    new q_stmt (0, "q1", "Q1. This is question 1", spn, 0, INT32_TYPE, xs_0);
  q_list.push_back (q1);
  xtcc_set xs_1;
  xs_1.indiv.insert (1);
  xs_1.indiv.insert (2);
  xs_1.range.push_back (pair < int, int >(5, 8));
  q_stmt *q2 =
    new q_stmt (1, "q2", "Q2. This is question 2", mpn, 5, INT32_TYPE, xs_1);
  q_list.push_back (q2);

  int ser_no;
  cout << "Enter Serial No (0) to exit: " << flush;
  cin >> ser_no;
  string jno = "j_1001";
  while (ser_no != 0)
    {
      q1->eval ();
      q2->eval ();

      stringstream fname_str;
      fname_str << jno << "_" << ser_no << ".dat";
      FILE *fptr = fopen (fname_str.str ().c_str (), "w+b");
      cout << "Enter Serial No (0) to exit: " << flush;
      cin >> ser_no;
      for (int i = 0; i < q_list.size (); ++i)
	{
	  fprintf (fptr, "%s: ", q_list[i]->name.c_str ());
	  for (set < int >::iterator iter = q_list[i]->input_data.begin ();
	       iter != q_list[i]->input_data.end (); ++iter)
	    {
	      fprintf (fptr, "%d ", *iter);
	    }
	  fprintf (fptr, "\n");
	}
      fclose (fptr);


    }				/* close while */

}				/* close main */
