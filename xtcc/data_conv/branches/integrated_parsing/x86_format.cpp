//Grzegorz Prusak
#include "Format.h"

class MyFormat : public AbstractFormat
{
	public:
		MyFormat() : AbstractFormat("MyFormat") {}
		char   operator()(char   x){ return x; }
		short  operator()(short  x){ return x; }
		long   operator()(long   x){ return x; }
		float  operator()(float  x){ return x; }
		double operator()(double x){ return x; }
};

MyFormat MyFormatObject;

