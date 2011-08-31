#include <iostream>
#include <sys/types.h>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
	vector<int64_t> v;
	v.push_back(100120023003);
	v.push_back(100140043003);
	v.push_back(100120025005);

	stringstream s;
	for (int i=0; i<v.size(); ++i) {
		s << v[i] << " ";
	}
	cout << s.str() << endl;
}

