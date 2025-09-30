#pragma once

#include <iostream>
#include"Screens/clsScreen.h"
#include"Libraries/clsInputValidate.h"
#include"Screens/LibraryScreen/BookScreen/clsShowAllBooksScreen.h"
#include"Screens/LibraryScreen/BookScreen/clsSearchForABookScreen.h"
#include"Screens/LibraryScreen/BookScreen/clsEditBookScreen.h"
#include"Screens/LibraryScreen/BookScreen/clsAddNewBookScreen.h"
#include"Screens/LibraryScreen/BookScreen/clsDeleteBookScreen.h"
using namespace std;
class clsBookManagementScreen :protected clsScreen
{
	enum enBookScreenOptions{
		ShowAllBooks=1, SearchForABook=2,
		EditBook=3,AddNewBook=4, DeleteBook=5, ReturntoLibraryMenu=6
	};

	static short _ReadBookScreenOption()
	{
		cout << "\t\t\tPlease enter your choice from 1 to 6: ";
		short UserOption = clsInputValidate::ReadNumberBetween<short>(1, 6,
			"\n\t\t\tNumber is not within range...\n\t\t\tPlease enter a number between 1 to 6: ");

		return UserOption;
	}

	static void _GoToBookManagementScreen()
	{
		cout << "\n\n\nPress any key To go to Book Management Menu";
		system("pause >nul");

		ShowBookManagementScreen();
	}

	static void _ShowAllBooksScreen()
	{
		clsShowAllBooksScreen::ShowAllBooksScreen();
	}

	static void _ShowSearchForABookScreen()
	{
		clsSearchForABookScreen::ShowSearchForABookScreen();
	}

	static void _ShowEditBookScreen()
	{
		clsEditBookScreen::ShowEditBookScreen();
	}

	static void _ShowAddNewBookScreen()
	{
		clsAddNewBookScreen::ShowAddNewBookScreen();
	}

	static void _ShowDeleteBookScreen()
	{
		clsDeleteBookScreen::ShowDeleteBookScreen();
	}

	static void _PerformBookScreenOption(enBookScreenOptions UserOption)
	{
		switch (UserOption)
		{
		case enBookScreenOptions::ShowAllBooks:
			system("cls");
			_ShowAllBooksScreen();
			_GoToBookManagementScreen();
			break;

		case enBookScreenOptions::SearchForABook:
			system("cls");
			_ShowSearchForABookScreen();
			_GoToBookManagementScreen();
			break;

		case enBookScreenOptions::EditBook:
			system("cls");
			_ShowEditBookScreen();
			_GoToBookManagementScreen();
			break;

		case enBookScreenOptions::AddNewBook:
			system("cls");
			_ShowAddNewBookScreen();
			_GoToBookManagementScreen();
			break;

		case enBookScreenOptions::DeleteBook:
			system("cls");
			_ShowDeleteBookScreen();
			_GoToBookManagementScreen();
			break;

		case enBookScreenOptions::ReturntoLibraryMenu:
			break;
		}
	}

public:

	static void ShowBookManagementScreen()
	{
		system("cls");
		_DrawScreenHeader("Book Management Screen  ");

		cout << "\n\n\t\t\t__________________________________\n";

		cout << "\n\t\t\t\tBook Management Menu\n";
		cout << "\n\t\t\t__________________________________\n";


		cout << "\n\t\t\t\t1. Show All Books\n";
		cout << "\n\t\t\t\t2. Search for a Book\n";
		cout << "\n\t\t\t\t3. Edit Book\n";
		cout << "\n\t\t\t\t4. Add New Book\n";
		cout << "\n\t\t\t\t5. Delete Book\n"; 
		cout << "\n\t\t\t\t6. Return to Library Menu\n";
		cout << "\n\n\t\t\t__________________________________\n\n";

		_PerformBookScreenOption((enBookScreenOptions)_ReadBookScreenOption());

	}
};

