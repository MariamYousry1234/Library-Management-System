#pragma once
#include <iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsTotalNumberOfMembersScreen.h"
#include"clsMembersWithBorrowedBooksScreen.h"
#include"clsMembersWithOverdueBooksScreen.h"
#include"clsTopActiveMembersScreen.h"
using namespace std;

class clsMembersReportsScreen :protected clsScreen
{
	enum enMembersReportsOptions {
		ShowTotalNumberOfMembers = 1, ShowMembersWithBorrowedBooks=2, ShowMembersWithOverdueBooks = 3,
		ShowTopActiveMembers = 4,  BackToReportsMenu = 5
	};


	static short _ReadMembersReportsOption()
	{
		cout << "\t\t\tPlease enter your choice from 1 to 5: ";
		short UserOption = clsInputValidate::ReadNumberBetween<short>(1, 5,
			"\n\t\t\tNumber is not within range...\n\t\t\tPlease enter a number between 1 to 5: ");

		return UserOption;
	}

	static void _GoToMembersReportsMainMenu()
	{
		cout << "\n\n\nPress any key To go to Members Reports Menu";
		system("pause >nul");

		ShowMembersReportsScreen();
	}


	static void _ShowTotalNumberOfMembersScreen()
	{
		clsTotalNumberOfMembersScreen::ShowTotalNumberOfMembersScreen();
	}

	static void _ShowMembersWithBorrowedBooksScreen()
	{
		clsMembersWithBorrowedBooksScreen::ShowMembersWithBorrowedBooksScreen();
	}

	static void _ShowMembersWithOverdueBooksScreen()
	{
		clsMembersWithOverdueBooksScreen::ShowOverdueMembersScreen();
	}

	static void _ShowTopActiveMembersScreen()
	{
		clsTopActiveMembersScreen::ShowTopActiveMembersScreen();
	}

	static void _PerformMembersReportsOption(enMembersReportsOptions UserOption)
	{
		switch (UserOption)
		{
		case enMembersReportsOptions::ShowTotalNumberOfMembers:
			system("cls");
			_ShowTotalNumberOfMembersScreen();
			_GoToMembersReportsMainMenu();
			break;

		case enMembersReportsOptions::ShowMembersWithBorrowedBooks:
			system("cls");
			_ShowMembersWithBorrowedBooksScreen();
			_GoToMembersReportsMainMenu();
			break;

		case enMembersReportsOptions::ShowMembersWithOverdueBooks:
			system("cls");
			_ShowMembersWithOverdueBooksScreen();
			_GoToMembersReportsMainMenu();
			break;

		case enMembersReportsOptions::ShowTopActiveMembers:
			system("cls");
			_ShowTopActiveMembersScreen();
			_GoToMembersReportsMainMenu();
			break;

		case enMembersReportsOptions::BackToReportsMenu:
			break;
		}
	}
public:
	static void ShowMembersReportsScreen()
	{
		system("cls");
		cout << "\n\n\t\t\t_________________________________________\n";

		cout << "\n\t\t\t\t    Members Reports \n";
		cout << "\n\t\t\t_________________________________________\n";


		cout << "\n\t\t\t\t1. Show Total Number Of Members\n";
		cout << "\n\t\t\t\t2. Show Members With Borrowed Books\n";
		cout << "\n\t\t\t\t3. Show Members With Overdue Books\n";
		cout << "\n\t\t\t\t4. Show Top Active Members\n";
		cout << "\n\t\t\t\t5. Back To Reports Menu\n";
		cout << "\n\t\t\t_________________________________________\n\n";

		_PerformMembersReportsOption((enMembersReportsOptions)_ReadMembersReportsOption());
	}
};

