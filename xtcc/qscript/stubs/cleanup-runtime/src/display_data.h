#ifndef display_data_h
#define display_data_h

namespace display_data {

enum DisplayDataType { single_element, range_element };
struct DisplayDataUnit
{
	DisplayDataType displayDataType_;
	int32_t startOfRangeOrSingle_; /* if single_element then only this is valid  
				    - otherwise represents start of range */
	int32_t endOfRange_;
	DisplayDataUnit(int32_t p_single_elem)
		:
		displayDataType_(single_element), startOfRangeOrSingle_(p_single_elem),
		endOfRange_(-1) /* it will show wrong on the screen if we have a bug */
	{ }
	DisplayDataUnit(int32_t p_start_of_range, int32_t p_end_of_range)
		:
		displayDataType_(range_element), 
		startOfRangeOrSingle_(p_start_of_range), endOfRange_(p_end_of_range)
	{ }
};

struct DisplayDataUnitOrder
{
	/* why should this work - because the compiler takes care of overlapping ranges 
	 * if it doesnt then i should fix the bugs there so this code remains simple
	 * */
	bool operator()(const DisplayDataUnit & ddu1, const DisplayDataUnit & ddu2)
	{
		return ddu1.startOfRangeOrSingle_ < ddu2.startOfRangeOrSingle_;
	}
};


}

#endif /* display_data_h */
