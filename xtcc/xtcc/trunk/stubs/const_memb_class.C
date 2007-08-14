class const_member{
	const int c;
	int arr[c];
	public:
	const_member(int arr_bounds=1): c(arr_bounds) {}
};

int main(){
	const_member cobj(10);
	//cout << "obj constructed" << endl;
}


