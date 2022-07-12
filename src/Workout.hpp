#ifndef WORKOUT_HPP
#define WORKOUT_HPP
#include <map>
#include <string>
#include <fstream>
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
    Workout& Add(std::string str, uint pds);
    bool HasMachine(std::string machine);
    uint& operator[](std::string machine);
    void Load(std::fstream& file);
    void Print();
};

#endif // WORKOUT_HPP