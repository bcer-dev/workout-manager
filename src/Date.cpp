#include "Date.hpp"
#include <time.h>

Date::Date()
{
    auto _time = time(NULL);
	auto tm = *localtime(&_time);

    day = tm.tm_mday;
	month = tm.tm_mon; 
	year = tm.tm_year;
}