#pragma once

#include <iostream>
#include"Screens/clsScreen.h"
#include"Libraries/clsInputValidate.h"
#include"Screens/LibraryScreen/ReportsScreen/BooksReportsScreen/clsTotalNumberOfBooksScreen.h"
#include"Screens/LibraryScreen/ReportsScreen/BooksReportsScreen/clsAvailableBooksScreen.h"
#include"Screens/LibraryScreen/ReportsScreen/BooksReportsScreen/clsBorrowedBooksScreen.h"
#include"Screens/LibraryScreen/ReportsScreen/BooksReportsScreen/clsOverdueBooksScreen.h"
using namespace std;

class clsBooksReportsScreen :protected clsScreen
{
	enum enBooksReportsOptions{ ShowTotalNumberOfBooks=1, ShowAvailableBooks=2,
		ShowBorrowedBooks=3, ShowOverdueBooks=4, BackToReportsMenu=5
	};

	static short _ReadBooksReportsOption()
	{
		cout << "\t\t\tPlease enter your choice from 1 to 5: ";
		short UserOption = clsInputValidate::ReadNumberBetween<short>(1, 5,
			"\n\t\t\tNumber is not within range...\n\t\t\tPlease enter a number between 1 to 5: ");

		return UserOption;
	}

	static void _GoToBooksReportsMainMenu()
	{
		cout << "\n\n\nPress any key To go to Books Reports Menu";
		system("pause >nul");

		ShowBooksReportsScreen();
	} 

	static void _ShowTotalNumberOfBooksScreen()
	{
		clsTotalNumberOfBooksScreen::ShowTotalNumberOfBooksScreen();
	}

	static void _ShowAvailableBooksScreen()
	{
		clsAvailableBooksScreen::ShowAvailableBooksScreen();
	}

	static void _ShowBorrowedBooksScreen()
	{
		clsBorrowedBooksScreen::ShowBorrowedBooksScreen();
	}

	static void _ShowOverdueBooksScreen()
	{
		clsOverdueBooksScreen::ShowOverdueBooksScreen();
	}

	static void _PerformBooksReportsOption(enBooksReportsOptions UserOption)
	{
		switch (UserOption)
		{
		case enBooksReportsOptions::ShowTotalNumberOfBooks:
			system("cls");
			_ShowTotalNumberOfBooksScreen();
			_GoToBooksReportsMainMenu();
			break;

		case enBooksReportsOptions::ShowAvailableBooks:
			system("cls");
			_ShowAvailableBooksScreen();
			_GoToBooksReportsMainMenu();
			break;

		case enBooksReportsOptions::ShowBorrowedBooks:
			system("cls");
			_ShowBorrowedBooksScreen();
			_GoToBooksReportsMainMenu();
			break;

		case enBooksReportsOptions::ShowOverdueBooks:
			system("cls");
			_ShowOverdueBooksScreen();
			_GoToBooksReportsMainMenu();
			break;


		case enBooksReportsOptions::BackToReportsMenu:
			break;
		}
	}

public:
	static void ShowBooksReportsScreen()
	{
		system("cls");
		cout << "\n\n\t\t\t_________________________________________\n";

		cout << "\n\t\t\t\t    Books Reports \n";
		cout << "\n\t\t\t_________________________________________\n";

		cout << "\n\t\t\t\t1. Show Total Number Of Books\n";
		cout << "\n\t\t\t\t2. Show Available Books\n";
		cout << "\n\t\t\t\t3. Show Borrowed Books\n";
		cout << "\n\t\t\t\t4. Show Overdue Books\n";
		cout << "\n\t\t\t\t5. Back To Reports Menu\n";
		cout << "\n\t\t\t_________________________________________\n\n";

		_PerformBooksReportsOption((enBooksReportsOptions)_ReadBooksReportsOption());
			
		
	}
};

