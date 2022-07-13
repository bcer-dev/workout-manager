#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Workout.hpp"

#define STORAGE_FILE 	"workout_data.csv"

enum class MenuOptions { VIEW_EXISTING, UPDATE_CREATE, QUIT };

std::istream& operator>>(std::istream& is, MenuOptions& option);
bool CreateNewWorkout(std::fstream& file, Workout *workout);
void ReadNewWorkoutData(Workout *wk);


int main(int argc, char **argv)
{
	bool running = true;
	std::fstream save_file;
	
	Date date;
	Workout *workout_data = new Workout(date);

	save_file.open(STORAGE_FILE, std::ios::in);
	workout_data->Load(save_file);

	while (running)
	{
		MenuOptions selected_option;
		std::cout << "********* workout-mgr *********\n";
		std::cout << "Command-line tool to keep track of your workouts\n\n\n";

		// Get task from user
		std::cout << "What would you like to do?\n";
		std::cout << "1. View existing workout plans\n";
		std::cout << "2. Create or update workout plans\n";
		std::cout << "3. Quit\n";
		std::cout << "> ";

		std::cin >> selected_option;
		std::cin.ignore();

		switch (selected_option)
		{
		case MenuOptions::VIEW_EXISTING:
			workout_data->Print();

			break;

		case MenuOptions::UPDATE_CREATE:
			save_file.open(STORAGE_FILE, std::ios::out);
			CreateNewWorkout(save_file, workout_data);
			break;

		case MenuOptions::QUIT:
			running = false;
			break;

		default:
			std::cout << "Sorry, that is an invalid option. Please try again.\n";
			continue;
		}

		if (save_file.is_open())
		{
			save_file.close();
		}

#ifdef _WIN32
		system("cls");
#elif __linux__
		system("clear");
#endif
	}

	delete workout_data;

	return 0;
}

// Allows the use of std::cin on objects of type MenuOptions
std::istream& operator>>(std::istream& is, MenuOptions& option)
{
	int res;
	if (is >> res)
		option = (MenuOptions)--res;
	return is;
}

// Add a machine and pair to the workout
bool CreateNewWorkout(std::fstream& file, Workout *workout)
{
	if (!file.is_open())
	{
		std::cout << "Failed to write to file\n";
		return false;
	}

#ifdef _WIN32
		system("cls");
#elif __linux__
		system("clear");
#endif

	std::cout << "Edit workout\n";
	std::cout << "Enter a machine name and how much weight you used or \"save\" to save...\n";

	ReadNewWorkoutData(workout);
	file << workout->ToCSVString();
	file.close();

	return true;
}

// Reads machine and weight from user until they type "done"
void ReadNewWorkoutData(Workout* wk)
{
	std::string raw_input{};
	while (raw_input != "save")
	{
		std::cout << "> ";
		std::getline(std::cin, raw_input);

		int space_index = raw_input.find(0x20);
		if (space_index == std::string::npos)
		{
			std::cout << "Please format as: [machine] [weight]\n";
			continue;
		}

		std::string machine = raw_input.substr(0, space_index);
		std::string raw_weight = raw_input.substr(space_index + 1, std::string::npos);
		int weight = atoi(raw_weight.c_str());
		
		if (wk->HasMachine(machine))
		{
			(*wk)[machine] = weight;
			continue;
		}

		wk->Add(machine, weight);
	}
}
