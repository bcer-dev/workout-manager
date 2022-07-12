#include "Workout.hpp"
#include <sstream>

Workout::Workout(Date date) : date(date) {}

std::string Workout::ToCSVString()
{
    std::stringstream str{};
    str << date.day << "/" << date.month << "/" << date.year << ",";

    for (auto& p : machines)
    {
        str << p.first << ',' << p.second << '\n';
    }

    return str.str();
}

Workout& Workout::Add(std::string str, int pds)
{
    std::pair<std::string, int> tmp {str, pds};
    machines.insert(tmp);
    return *this;
}