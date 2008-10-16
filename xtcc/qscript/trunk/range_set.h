#ifndef xtcc_rangeset_h
#define xtcc_rangeset_h

#include <sstream>

#define MAX_RANGE_ELEMENTS 4095

struct range_data{
        int ran_start_end[MAX_RANGE_ELEMENTS];
        int ran_indiv[MAX_RANGE_ELEMENTS];
        int icount;
        int rcount;

	void print_range(ostringstream & os){
		//cout << "Entered print_range:\n";
		for(int i=0; i< rcount-1; ++i){
			os << ran_start_end[i*2] << ".." << ran_start_end[i*2+1]
				<< ",";
		}
		if(rcount){
			os << ran_start_end[(rcount-1)*2] << ".." <<
				ran_start_end[(rcount-1)*2+1];
		}
		for(int i=0; i< icount-1; ++i){
			if (rcount) os << "," ;
			os << ran_indiv[i];
		}
		if( icount){
			os << "," << ran_indiv[icount-1];
		}
		//cout << "exit print_range:\n";
	}
	range_data(){
		icount=0;
		rcount=0;
	}
	range_data (range_data& d1){
		icount=d1.icount;
		rcount=d1.rcount;
		//cout << "called copy constructor \n";
		for(int i=0; i<icount; ++i){
			ran_indiv[i]=d1.ran_indiv[i];
		}
		for(int i=0; i<rcount; ++i){
			ran_start_end[2*i]=d1.ran_start_end[2*i];
			ran_start_end[2*i+1]=d1.ran_start_end[2*i+1];
		}
		//return *this;
	}
	range_data& operator=(const range_data& d1){
		icount=d1.icount;
		rcount=d1.rcount;
		//cout << "called operator=\n";
		for(int i=0; i<icount; ++i){
			ran_indiv[i]=d1.ran_indiv[i];
		}
		for(int i=0; i<rcount; ++i){
			ran_start_end[2*i]=d1.ran_start_end[2*i];
			ran_start_end[2*i+1]=d1.ran_start_end[2*i+1];
		}
		return *this;
	}
	void reset(){
		icount=0;
		rcount=0;
	}

};



#endif /* xtcc_rangeset_h */
