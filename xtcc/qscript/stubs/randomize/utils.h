
bool recursive_compare_structure (AbstractNamedRange * nr1, AbstractNamedRange * nr2, int nest_level);
void PrintNamedRange2 (AbstractNamedRange * nr, vector <string> & group_str,
	vector <NamedRangeGroup*> & group_list, stringstream & final_answer,
	vector<stub_pair> & flat_display_nr
	);

void display_flat_named_range(const string & name, const vector<stub_pair>  nr_vec);
