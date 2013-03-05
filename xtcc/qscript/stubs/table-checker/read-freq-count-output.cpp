
#include <iostream>
#include <fstream>

using namespace std;

void read_csv_file(fstream & freq_count_file)
{
    string a_line;
    while (getline(freq_count_file, a_line)){
        cout
            << "got a line:"
            << a_line
            << endl;
        size_t pos_comma = a_line.find_last_of (',');
        if (pos_comma == string::npos) {
            cout << ", found" << endl;
        } else {
            cout << ", not found" << endl;
        }
    }
}

int main()
{
	string freq_count_filename("cmb_decision_maker.freq_count.csv");
	fstream freq_count_file(freq_count_filename.c_str(), ios_base::in);
    read_csv_file (freq_count_file);

}
