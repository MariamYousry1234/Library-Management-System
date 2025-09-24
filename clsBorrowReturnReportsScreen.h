#pragma once

#include <iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsAllBorrowTransactionsScreen.h"
#include"clsAllReturnTransactionsScreen.h"
#include"clsMostBorrowedBooksScreen.h"
using namespace std;

class clsBorrowReturnReportsScreen :protected clsScreen
{
	enum enBorrowReturnReportsOptions {
		ShowAllBorrowTransactions = 1, ShowAllReturnTransactions = 2,
		ShowMostBorrowedBooks = 3,BackToReportsMenu = 4
	};

	static short _ReadBorrowReturnReportsOption()
	{
		cout << "\t\t\tPlease enter your choice from 1 to 4: ";
		short UserOption = clsInputValidate::ReadNumberBetween<short>(1, 4,
			"\n\t\t\tNumber is not within range...\n\t\t\tPlease enter a number between 1 to 4: ");

		return UserOption;
	}

	static void _GoToBorrowReturnReportsMainMenu()
	{
		cout << "\n\n\nPress any key To go to Borrow/Return Reports Menu";
		system("pause >nul");

		ShowBorrowReturnReportsScreen();
	}


	static void _ShowAllBorrowTransactionsScreen()
	{
		clsAllBorrowTransactionsScreen::ShowBorrowedBooksScreen();
	}

	static void _ShowAllReturnTransactionsScreen()
	{
		clsAllReturnTransactionsScreen::ShowReturnedBooksScreen();
	}

	static void _ShowMostBorrowedBooksScreen()
	{
		clsMostBorrowedBooksScreen::ShowMostBorrowedBooksScreen();
	}

	static void _PerformBorrowReturnReportsOption(enBorrowReturnReportsOptions UserOption)
	{
		switch (UserOption)
		{
		case enBorrowReturnReportsOptions::ShowAllBorrowTransactions:
			system("cls");
			_ShowAllBorrowTransactionsScreen();
			_GoToBorrowReturnReportsMainMenu();
			break;

		case enBorrowReturnReportsOptions::ShowAllReturnTransactions:
			system("cls");
			_ShowAllReturnTransactionsScreen();
			_GoToBorrowReturnReportsMainMenu();
			break;

		case enBorrowReturnReportsOptions::ShowMostBorrowedBooks:
			system("cls");
			_ShowMostBorrowedBooksScreen();
			_GoToBorrowReturnReportsMainMenu();
			break;

		case enBorrowReturnReportsOptions::BackToReportsMenu:
			break;
		}
	}

public:
	static void ShowBorrowReturnReportsScreen()
	{
		system("cls");
		cout << "\n\n\t\t\t_________________________________________\n";

		cout << "\n\t\t\t\t  Borrow/Return Reports \n";
		cout << "\n\t\t\t_________________________________________\n";


		cout << "\n\t\t\t\t1. Show All Borrow Transactions\n";
		cout << "\n\t\t\t\t2. Show All Return Transactions\n";
		cout << "\n\t\t\t\t3. Show Most Borrowed Books\n";
		cout << "\n\t\t\t\t4. Back To Reports Menu\n";
		cout << "\n\t\t\t_________________________________________\n\n";

		_PerformBorrowReturnReportsOption((enBorrowReturnReportsOptions)_ReadBorrowReturnReportsOption());
	}
};

