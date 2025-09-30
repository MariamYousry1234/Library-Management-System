#pragma once
#include <iostream>
#include"Screens/clsScreen.h"
#include"Libraries/clsInputValidate.h"
#include"Screens/LibraryScreen/BorrowReturnScreen/clsBorrowBookScreen.h"
#include"Screens/LibraryScreen/BorrowReturnScreen/clsReturnBookScreen.h"
#include"Screens/LibraryScreen/BorrowReturnScreen/clsBorrowedBookByMemberScreen.h"
#include"Screens/LibraryScreen/BorrowReturnScreen/clsShowAllBorrowedBooksScreen.h"
using namespace std;

class clsBorrowReturnBooksScreen :protected clsScreen
{

	enum enBorrowReturnOptions {
		BorrowBook = 1, ReturnBook = 2,
		ShowBorrowedBookByMember = 3, ShowAllBorrowedBooks = 4, BacktoLibraryMenu=5
	};

	static short _ReadOption()
	{
		cout << "\t\t\tPlease enter your choice from 1 to 5: ";
		short UserOption = clsInputValidate::ReadNumberBetween<short>(1, 5,
			"\n\t\t\tNumber is not within range...\n\t\t\tPlease enter a number between 1 to 4: ");

		return UserOption;
	}

	static void _GoToBorrowReturnMenu()
	{
		cout << "\n\n\nPress any key To go to Borrow and Return Menu";
		system("pause >nul");

		ShowBorrowReturnScreen();
	}


	static void _ShowBorrowBookScreen()
	{
		clsBorrowBookScreen::ShowBorrowBookScreen();

	}

	static void _ShowReturnBookScreen()
	{
		clsReturnBookScreen::ShowReturnBookScreen();
	}

	static void _ShowBorrowedBookByMemberScreen()
	{
		clsBorrowedBookByMemberScreen::ShowBorrowedBookByMemberScreen();
	}

	static void _ShowAllBorrowedBooksScreen()
	{
		clsShowAllBorrowedBooksScreen::ShowAllBorrowedBooksScreen();
	}

	static void _PerformBorrowReturnOption(enBorrowReturnOptions UserOption)
	{
		switch (UserOption)
		{
		case enBorrowReturnOptions::BorrowBook:
			system("cls");
			_ShowBorrowBookScreen();
			_GoToBorrowReturnMenu();
			break;

		case enBorrowReturnOptions::ReturnBook:
			system("cls");
			_ShowReturnBookScreen();
			_GoToBorrowReturnMenu();
			break;

		case enBorrowReturnOptions::ShowBorrowedBookByMember:
			system("cls");
			_ShowBorrowedBookByMemberScreen();
			_GoToBorrowReturnMenu();
			break;

		case enBorrowReturnOptions::ShowAllBorrowedBooks:
			system("cls");
			_ShowAllBorrowedBooksScreen();
			_GoToBorrowReturnMenu();
			break;

		case enBorrowReturnOptions::BacktoLibraryMenu:
			break;
		}
	}


public:

	static void ShowBorrowReturnScreen()
	{
		system("cls");
		_DrawScreenHeader("Borrow Return Screen ");

		cout << "\n\n\t\t\t__________________________________\n";

		cout << "\n\t\t\t\tBorrow Return Menu\n";
		cout << "\n\t\t\t__________________________________\n";


		cout << "\n\t\t\t\t1. Borrow Book\n";
		cout << "\n\t\t\t\t2. Return Book\n";
		cout << "\n\t\t\t\t3. Show Borrowed Book By Member\n";
		cout << "\n\t\t\t\t4. Show All Borrowed Books\n";
		cout << "\n\t\t\t\t5. Back to Library Menu\n";
		cout << "\n\n\t\t\t__________________________________\n\n";

		_PerformBorrowReturnOption((enBorrowReturnOptions)_ReadOption());
	}
};

