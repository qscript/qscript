//Grzegorz Prusak
#include "Format.h"
#include "Type.h"

std::vector<AbstractFormat*> AbstractFormat::list;

std::vector<AbstractType*> AbstractType::list;

template<typename T> class Type : public AbstractType
{
	public:
		Type(const std::string &token) : AbstractType(token) {}
		int size(){ return sizeof(T); }
		
		void parse(const std::string &s, void *buffer, AbstractFormat &F)
		{
			std::stringstream ss(s); ss.exceptions(std::ios::failbit | std::ios::badbit);
			T x; ss >> x; *(T*)buffer = F(x);
		}
};

template<> void Type<char>::parse(const std::string &s, void *buffer, AbstractFormat &F)
{
	std::stringstream ss(s); ss.exceptions(std::ios::failbit | std::ios::badbit);
	int x; ss >> x; *(char*)buffer = F((char)x);
}

Type<char>   INT8  ("int8");
Type<short>  INT16 ("int16");
Type<long>   INT32 ("int32");
Type<float>  FLOAT ("float");
Type<double> DOUBLE("double");

