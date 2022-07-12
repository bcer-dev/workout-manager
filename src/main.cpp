#include <iostream>
#include <string>
#include <map>

enum class MenuOptions { VIEW_EXISTING, UPDATE_CREATE };

std::istream& operator>>(std::istream& is, MenuOptions& option);

int main(int argc, char **argv)
{
	bool running = true;

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
			// GetAllEntries();
			break;

		case MenuOptions::UPDATE_CREATE:
			// if filename.has(entry) then 
			//		UpdateEntry()
			// else CreateEntry(entry)
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
	return 0;
}

std::istream& operator>>(std::istream& is, MenuOptions& option)
{
	int res;
	if (is >> res)
		option = (MenuOptions)--res;
	return is;
}