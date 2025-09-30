#pragma once
#include <iostream>
#include"Screens/clsScreen.h"
#include"Libraries/clsInputValidate.h"
#include"Screens/LibraryScreen/ReportsScreen/ReservationsReportsScreen/clsTotalReservationsScreen.h"
#include"Screens/LibraryScreen/ReportsScreen/ReservationsReportsScreen/clsActiveReservationsScreen.h"
#include"Screens/LibraryScreen/ReportsScreen/ReservationsReportsScreen/clsWaitingReservationsScreen.h"
#include"Screens/LibraryScreen/ReportsScreen/ReservationsReportsScreen/clsCompletedReservationsScreen.h"
#include"Screens/LibraryScreen/ReportsScreen/ReservationsReportsScreen/clsCancelledReservationsScreen.h"
using namespace std;

class clsReservationsReportsScreen :protected clsScreen
{
	enum enReservationsReportsOptions {
		ShowTotalReservations = 1, ShowActiveReservations = 2,
		ShowWaitingReservations = 3,ShowCompletedReservations=4,
		ShowCancelledReservations = 5, BackToReportsMenu = 6
	};

	static short _ReadReservationsReportsOption()
	{
		cout << "\t\t\tPlease enter your choice from 1 to 6: ";
		short UserOption = clsInputValidate::ReadNumberBetween<short>(1, 6,
			"\n\t\t\tNumber is not within range...\n\t\t\tPlease enter a number between 1 to 6: ");

		return UserOption;
	}

	static void _GoToReservationsReportsMainMenu()
	{
		cout << "\n\n\nPress any key To go to Reservations Reports Menu";
		system("pause >nul");

		ShowReservationsReportsScreen();
	}

	static void _ShowTotalReservationsScreen()
	{
		clsTotalReservationsScreen::ShowTotalReservationsScreen();
	}

	static void _ShowActiveReservationsScreen()
	{
		clsActiveReservationsScreen::ShowActiveReservationsScreen();
	}

	static void _ShowWaitingReservationsScreen()
	{
		clsWaitingReservationsScreen::ShowWaitingReservationsScreen();
	}

	static void _ShowCompletedReservationsScreen()
	{
		clsCompletedReservationsScreen::ShowCompletedReservationsScreen();
	}

	static void _ShowCancelledReservationsScreen()
	{
		clsCancelledReservationsScreen::ShowCancelledReservationsScreen();
	}

	static void _PerformReservationsReportsOption(enReservationsReportsOptions UserOption)
	{
		switch (UserOption)
		{
		case enReservationsReportsOptions::ShowTotalReservations:
			system("cls");
			_ShowTotalReservationsScreen();
			_GoToReservationsReportsMainMenu();
			break;

		case enReservationsReportsOptions::ShowActiveReservations:
			system("cls");
			_ShowActiveReservationsScreen();
			_GoToReservationsReportsMainMenu();
			break;

		case enReservationsReportsOptions::ShowWaitingReservations:
			system("cls");
			_ShowWaitingReservationsScreen();
			_GoToReservationsReportsMainMenu();
			break;

		case enReservationsReportsOptions::ShowCompletedReservations:
			system("cls");
			_ShowCompletedReservationsScreen();
			_GoToReservationsReportsMainMenu();
			break;

		case enReservationsReportsOptions::ShowCancelledReservations:
			system("cls");
			_ShowCancelledReservationsScreen();
			_GoToReservationsReportsMainMenu();
			break;



		case enReservationsReportsOptions::BackToReportsMenu:
			break;
		}
	}
public:
	static void ShowReservationsReportsScreen()
	{
		system("cls");
		cout << "\n\n\t\t\t_________________________________________\n";

		cout << "\n\t\t\t\t   Reservations Reports \n";
		cout << "\n\t\t\t_________________________________________\n";


		cout << "\n\t\t\t\t1. Show Total Reservations\n";
		cout << "\n\t\t\t\t2. Show Active Reservations\n";
		cout << "\n\t\t\t\t3. Show Waiting Reservations\n";
		cout << "\n\t\t\t\t4. Show Completed Reservations\n";
		cout << "\n\t\t\t\t5. Show Cancelled Reservations\n";
		cout << "\n\t\t\t\t6. Back To Reports Menu\n";
		cout << "\n\t\t\t_________________________________________\n\n";

		_PerformReservationsReportsOption((enReservationsReportsOptions)_ReadReservationsReportsOption());
	}
};

