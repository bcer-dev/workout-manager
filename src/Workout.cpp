#include "Workout.hpp"
#include <sstream>
#include <iostream>

Workout::Workout(Date date) : date(date) {}

// Convert the data into a csv compatible format.
std::string Workout::ToCSVString()
{
    std::stringstream str{};

    for (auto& p : machines)
    {
        str << date.day << "/" << date.month << "/" << date.year << ",";
        str << p.first << ',' << p.second << '\n';
    }

    return str.str();
}

// Add data to the hash table
Workout& Workout::Add(std::string str, uint pds)
{
    std::pair<std::string, uint> tmp {str, pds};
    machines.insert(tmp);
    return *this;
}

// Check if a specific machine has a value already
bool Workout::HasMachine(std::string machine)
{
    return machines.count(machine) != 0;
}

// Get weight from machine
uint& Workout::operator[](std::string machine)
{
    return machines[machine];
}

// Load the pre-existing data from a file
void Workout::Load(std::fstream& file)
{
    if (!file.is_open())
    {
        std::cerr << "Error: Input file not open.\n";
        return;
    }
    
    int line = 1;
    std::string raw_input{};
    while (std::getline(file, raw_input))
    {
        int comma_index = raw_input.find(',');

        if (comma_index == std::string::npos)
        {
            std::cerr << "File is corrupt on line " << line;
            std::cerr << "\"" << raw_input << "\"\n";
            return;
        }

        auto _date = raw_input.substr(0, comma_index);
        raw_input = raw_input.substr(comma_index + 1, std::string::npos);
        comma_index = raw_input.find(',');

        auto machine = raw_input.substr(0, comma_index);
	    auto raw_weight = raw_input.substr(comma_index + 1, std::string::npos);
        auto weight = atoi(raw_weight.c_str());
        Add(machine, weight);
        line++;
    }
}

// Print out the information in a nice format.
void Workout::Print()
{
    std::cout << "Here are your past workouts:\n\n";
    for (auto& p : machines)
    {
        std::cout << "[" << date.day << "/" << date.month << "/" << date.year; 
        std::cout << "] " << p.first << ": " << p.second << '\n';
    }
    std::cout << "\n\n" << "Press enter to continue...";
    getchar();
}