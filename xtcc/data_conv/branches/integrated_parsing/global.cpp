//Grzegorz Prusak
#include "Format.h"
#include "Type.h"

std::vector<AbstractFormat*> AbstractFormat::list;

template<typename T> class Type : public AbstractType
{
	public:
		Type(const std::string &token) : AbstractType(token) {}
		int size(){ return sizeof(T); }
		
		void parse(const std::string &s, void *buffer, AbstractFormat &F)
		{
			std::stringstream ss(s); //ss.exceptions(std::ios::failbit | std::ios::badbit);
			T x; ss >> x;
			if(!ss) x = -1; //throw "Type::parse: couldn't parse \""+s+'\"';
			*(T*)buffer = (x);
		}
};

template<> void Type<char>::parse(const std::string &s, void *buffer, AbstractFormat &F)
{
	std::stringstream ss(s); //ss.exceptions(std::ios::failbit | std::ios::badbit);
	int x; ss >> x;
	if(!ss) x = -1; //throw "Type::parse: couldn't parse \""+s+'\"';
	*(char*)buffer = F((char)x);
}


//************************************************************

template<bool v> class Assert;
template<> class Assert<true>{};
#define ASSERT(stmt,info) Assert<stmt> info;

ASSERT(sizeof(char  )==1,invalid_INT8_size  );
ASSERT(sizeof(short )==2,invalid_INT16_size );
ASSERT(sizeof(long  )==4,invalid_INT32_size );
ASSERT(sizeof(float )==4,invalid_FLOAT_size );
ASSERT(sizeof(double)==8,invalid_DOUBLE_size);

//************************************************************

Type<char>   _INT8  ("int8"  ); AbstractType &INT8   = _INT8;   
Type<short>  _INT16 ("int16" ); AbstractType &INT16  = _INT16;  
Type<long>   _INT32 ("int32" ); AbstractType &INT32  = _INT32;  
Type<float>  _FLOAT ("float" ); AbstractType &FLOAT  = _FLOAT;  
Type<double> _DOUBLE("double"); AbstractType &DOUBLE = _DOUBLE; 

