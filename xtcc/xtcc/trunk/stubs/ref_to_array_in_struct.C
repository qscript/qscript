/*
 * =====================================================================================
 *
 *       Filename:  ref_to_array_in_struct.C
 */

#include <iostream>
using namespace std;

struct ref_to_array_in_struct {
	int (& arr)[50];
	ref_to_array_in_struct (int (& p_arr)[50])
		: arr (p_arr)
	{ arr[0] = 2* arr[0]; arr[1]= 3 *arr[1]; arr[2]=3*arr[2]; }

};

int main()
{
	int arr[50];
	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;
	ref_to_array_in_struct ref_obj (arr);

	cout << arr[0] << ", " << arr[1] << ", " << arr[2] << endl;
}
