#ifndef WORKOUT_HPP
#define WORKOUT_HPP
#include <map>
#include <string>
#include "Date.hpp"

using uint = unsigned int;

class Workout
{
private:
    Date date;
    std::map<std::string, uint> machines;
public:
    Workout(Date date);
    std::string ToCSVString();
    Workout& Add(std::string str, int pds);
};

#endif // WORKOUT_HPP