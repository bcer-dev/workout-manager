#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include "Workout.hpp"

#define STORAGE_FILE "workout_data.csv"

enum class MenuOptions { VIEW_EXISTING, UPDATE_CREATE };

std::istream& operator>>(std::istream& is, MenuOptions& option);
bool CreateNewWorkout(std::fstream& file);
bool UpdateWorkout();

int main(int argc, char **argv)
{
	bool running = true;

	std::fstream save_file;

	while (running)
	{
		MenuOptions selected_option;
		std::cout << "********* workout-mgr *********\n";
		std::cout << "Command-line tool to keep track of your workouts\n\n\n";

		// Get task from user
		std::cout << "What would you like to do?\n";
		std::cout << "1. View existing workout plans\n";
		std::cout << "2. Create or update workout plans\n";

		std::cin >> selected_option;

		switch (selected_option)
		{
		case MenuOptions::VIEW_EXISTING:
			save_file.open(STORAGE_FILE, std::ios::in);
			// GetAllEntries();
			break;

		case MenuOptions::UPDATE_CREATE:
			save_file.open(STORAGE_FILE, std::ios::app);
			CreateNewWorkout(save_file);
			save_file.close();
			break;

		default:
			std::cout << "Sorry, that is an invalid option. Please try again.\n";
			continue;
		}

#ifdef _WIN32
		system("cls");
#elif __linux__
		system("clear");
#endif
	}

	if (save_file.is_open())
	{
		save_file.close();
	}

	return 0;
}

std::istream& operator>>(std::istream& is, MenuOptions& option)
{
	int res;
	if (is >> res)
		option = (MenuOptions)--res;
	return is;
}

bool CreateNewWorkout(std::fstream& file)
{
	if (!file.is_open())
	{
		std::cout << "Failed to write to file\n";
		return false;
	}

	auto _time = time(NULL);
	auto tm = *localtime(&_time);

	Date date;
	date.day = tm.tm_isdst ? tm.tm_mday : tm.tm_mday - 1;
	date.month = tm.tm_mon;
	date.year = tm.tm_year;

	Workout workout {date};

	std::pair<std::string, int> tmp_buf{};
	std::cout << "Create a new workout\n";
	std::cout << "Enter a machine name and how much weight you used.\n";
	std::cout << "Separate inputs with a ';'.\n";
	std::cout << "> ";

	// INPUT: key val; key val; key val
	std::string tmp;
	if (std::getline(std::cin, tmp).fail())
	{
		return false;
	}
	
	file << workout.ToCSVString();
	return true;
}