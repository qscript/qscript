// Neil Xavier D'Souza
// from simple_compiler/src/utils.{h,cpp}
#ifndef utils_h
#define utils_h

#include <string>

struct ExtractNumberInfo {
	bool gotANumber_;
	int numberValue_;
	ExtractNumberInfo()
		: gotANumber_ (false), numberValue_(0)
	{ }
};
struct ExtractNumberInfo extract_number (std::string s);
struct RatingScaleInfo
{
	bool isRatingScale_;
	bool isReversed_;
	int ratingScaleStart_;
	int ratingScaleEnd_;
	RatingScaleInfo ()
		: isRatingScale_ (false), isReversed_(false),
		  ratingScaleStart_(0), ratingScaleEnd_(0)
	{ }
};
struct RatingScaleInfo extract_rating_scale (std::string s);

#endif /* utils_h */
