/*
 * =====================================================================================
 *
 *       Filename:  test_stub_pair_gettext.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Thursday 01 March 2012 11:22:44  GMT
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <libintl.h>
#include <locale.h>
#include "stub_pair.h"

int main()
{
	stub_pair sp1 (gettext("Tomates"), 1);
}
