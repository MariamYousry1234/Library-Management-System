#pragma once
#include <iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsBooksReportsScreen.h"
#include"clsMembersReportsScreen.h"
#include"clsBorrowReturnReportsScreen.h"
#include"clsReservationsReportsScreen.h"
using namespace std;

class clsReportsScreen :protected clsScreen
{
	enum enReportsOptions{ BooksReports =1, MembersReports=2, BorrowReturnReports=3,
		ReservationsReports=4, BackToLibraryMainMenu=5
	};

	static short _ReadReportsOption()
	{
		cout << "\t\t\tPlease enter your choice from 1 to 5: ";
		short UserOption = clsInputValidate::ReadNumberBetween<short>(1, 5,
			"\n\t\t\tNumber is not within range...\n\t\t\tPlease enter a number between 1 to 5: ");

		return UserOption;
	}

	static void _GoToReportsMainMenu()
	{
		cout << "\n\n\nPress any key To go to Reports Main Menu";
		system("pause >nul");

		ShowReportsScreen();
	}

	static void _ShowBooksReportsScreen()
	{
		clsBooksReportsScreen::ShowBooksReportsScreen();
	}

	static void _ShowMembersReportsScreen()
	{
		clsMembersReportsScreen::ShowMembersReportsScreen();
	}

	static void _ShowBorrowReturnReportsScreen()
	{
		clsBorrowReturnReportsScreen::ShowBorrowReturnReportsScreen();
	}

	static void _ShowReservationsReportsScreen()
	{
		clsReservationsReportsScreen::ShowReservationsReportsScreen();
	}


	static void _PerformReportsMainMenuOption(enReportsOptions UserOption)
	{
		switch (UserOption)
		{
		case enReportsOptions::BooksReports:
			system("cls");
			_ShowBooksReportsScreen();
			_GoToReportsMainMenu();
			break;

		case enReportsOptions::MembersReports:
			system("cls");
			_ShowMembersReportsScreen();
			_GoToReportsMainMenu();
			break;

		case enReportsOptions::BorrowReturnReports:
			system("cls");
			_ShowBorrowReturnReportsScreen();
			_GoToReportsMainMenu();
			break;

		case enReportsOptions::ReservationsReports:
			system("cls");
			_ShowReservationsReportsScreen();
			_GoToReportsMainMenu();
			break;

		

		case enReportsOptions::BackToLibraryMainMenu:
			break;
		}
	}

public:
	static void ShowReportsScreen()
	{
		system("cls");
		_DrawScreenHeader("Reports Screen  ");

		cout << "\n\n\t\t\t__________________________________\n";

		cout << "\n\t\t\t\tReports Main Menu\n";
		cout << "\n\t\t\t__________________________________\n";


		cout << "\n\t\t\t\t1. Books Reports\n";
		cout << "\n\t\t\t\t2. Members Reports\n";
		cout << "\n\t\t\t\t3. Borrow/Return Reports\n";
		cout << "\n\t\t\t\t4. Reservations Reports\n";
		cout << "\n\t\t\t\t5. Back to Library Main Menu\n";
		cout << "\n\n\t\t\t__________________________________\n\n";

		_PerformReportsMainMenuOption((enReportsOptions)_ReadReportsOption());
	}
};

