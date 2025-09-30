#pragma once


#include <iostream>
#include"Screens/clsScreen.h"
#include"Libraries/clsInputValidate.h"
#include"Screens/LibraryScreen/BookScreen/clsBookManagementScreen.h"
#include"Screens/LibraryScreen/MemberManagementScreen/clsMemberManagementScreen.h"
#include"Screens/LibraryScreen/BorrowReturnScreen/clsBorrowReturnBooksScreen.h"
#include"Screens/LibraryScreen/ReservationsScreen/clsReservationsScreen.h"
#include"Screens/LibraryScreen/ReportsScreen/clsReportsScreen.h"
using namespace std;

class clsLibraryMainScreen:protected clsScreen
{
	enum enLibraryMainMenuOptions{ BookManagement =1, MembersManagement=2,
		BorrowReturnBooks=3, Reservations=4, Reports=5, Logout=6
	};

	static short _ReadLibraryOption()
	{
		cout << "\t\t\tPlease enter your choice from 1 to 6: ";
		short UserOption =clsInputValidate::ReadNumberBetween<short>(1, 6,
				"\n\t\t\tNumber is not within range...\n\t\t\tPlease enter a number between 1 to 6: ");

		return UserOption;
	}

	static void _GoToLibraryMainMenu()
	{
		cout << "\n\n\nPress any key To go to Library Menu";
		system("pause >nul");

		ShowLibraryMainScreen();
	}

	static void _ShowBookManagementScreen()
	{
		clsBookManagementScreen::ShowBookManagementScreen();
	}

	static void _ShowMembersManagementScreen()
	{
		clsMemberManagementScreen::ShowMembersManagementScreen();
	}

	static void _ShowBorrowReturnBooksScreen()
	{
		clsBorrowReturnBooksScreen::ShowBorrowReturnScreen();
	}

	static void _ShowReservationsScreen()
	{
		clsReservationsScreen::ShowReservationScreen();	
	}

	static void _ShowReportsScreen()
	{
		clsReportsScreen::ShowReportsScreen();
	}

	static void _PerformLibraryMainMenuOption(enLibraryMainMenuOptions UserOption)
	{
		switch (UserOption)
		{
		case enLibraryMainMenuOptions::BookManagement:
			system("cls");
			_ShowBookManagementScreen();
			_GoToLibraryMainMenu();
			break;

		case enLibraryMainMenuOptions::MembersManagement:
			system("cls");
			_ShowMembersManagementScreen();
			_GoToLibraryMainMenu();
			break;

		case enLibraryMainMenuOptions::BorrowReturnBooks:
			system("cls");
			_ShowBorrowReturnBooksScreen();
			_GoToLibraryMainMenu();
			break;

		case enLibraryMainMenuOptions::Reservations:
			system("cls");
			_ShowReservationsScreen();
			_GoToLibraryMainMenu();
			break;

		case enLibraryMainMenuOptions::Reports:
			system("cls");
			_ShowReportsScreen();
			_GoToLibraryMainMenu();
			break;

		case enLibraryMainMenuOptions::Logout:
			break;
		}
	}

public:

	static void ShowLibraryMainScreen()
	{
		system("cls");
		_DrawScreenHeader("Library Management System  ");

		cout << "\n\n\t\t\t__________________________________\n";
		
		cout << "\n\t\t\t\tLibrary Main Menu\n";
		cout << "\n\t\t\t__________________________________\n";
		

		cout << "\n\t\t\t\t1. Book Management\n";
		cout << "\n\t\t\t\t2. Member Management\n";
		cout << "\n\t\t\t\t3. Borrow/Return Books\n";
		cout << "\n\t\t\t\t4. Reservations\n";
		cout << "\n\t\t\t\t5. Reports\n";
		cout << "\n\t\t\t\t6. Logout";
		cout << "\n\n\t\t\t__________________________________\n\n";

		_PerformLibraryMainMenuOption((enLibraryMainMenuOptions)_ReadLibraryOption());
	}
};

