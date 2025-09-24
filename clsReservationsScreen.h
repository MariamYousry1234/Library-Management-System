#pragma once
#include <iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsMakeAReservationScreen.h"
#include"clsCompleteReservationScreen.h"
#include"clsCancelReservationScreen.h"
#include"clsViewMyReservationsScreen.h"
#include"clsSearchReservationByBookScreen.h"
#include"clsSearchReservationByMemberScreen.h"
#include"clsShowReservationQueueScreen.h"
using namespace std;

class clsReservationsScreen :protected clsScreen
{

	enum enReservationMainMenuOptions {
		MakeAReservation = 1,  CompleteReservation=2, CancelReservation = 3,
		ViewMyReservations = 4, SearchReservationByBook = 5, 
		SearchReservationByMember = 6, ReservationQueue = 7,
		BackToLibraryMenu=8
	};

	static short _ReadOption()
	{
		cout << "\t\t\tPlease enter your choice from 1 to 8: ";
		short UserOption = clsInputValidate::ReadNumberBetween<short>(1, 8,
			"\n\t\t\tNumber is not within range...\n\t\t\tPlease enter a number between 1 to 8: ");

		return UserOption;
	}

	static void _GoToReservationMainMenu()
	{
		cout << "\n\n\nPress any key To go to Reservation Menu";
		system("pause >nul");

		ShowReservationScreen();
	}

	static void _ShowMakeAReservationScreen()
	{
		clsMakeAReservationScreen::ShowMakeAReservationScreen();
	}

	static void _ShowCompleteReservationScreen()
	{
		clsCompleteReservationScreen::ShowCompleteReservationScreen();
	}

	static void _ShowCancelReservationScreen()
	{
		clsCancelReservationScreen::ShowCancelReservationScreen();
	}

	static void _ShowViewMyReservationsScreen()
	{
		clsViewMyReservationsScreen::ShowViewMyReservationsScreen();
	}

	static void _ShowSearchReservationByBookScreen()
	{
		clsSearchReservationByBookScreen::ShowSearchReservationByBookScreen();
	}

	static void _ShowSearchReservationByMemberScreen()
	{
		clsSearchReservationByMemberScreen::ShowSearchReservationByBookScreen();
	}

	static void _ShowReservationQueueScreen()
	{
		clsShowReservationQueueScreen::ShowReservationQueueScreen();
	}


	static void _PerformReservationMainMenuOption(enReservationMainMenuOptions UserOption)
	{
		switch (UserOption)
		{
		case enReservationMainMenuOptions::MakeAReservation:
			system("cls");
			_ShowMakeAReservationScreen();
			_GoToReservationMainMenu();
			break;

		case enReservationMainMenuOptions::CompleteReservation:
			system("cls");
			_ShowCompleteReservationScreen();
			_GoToReservationMainMenu();
			break;


		case enReservationMainMenuOptions::CancelReservation:
			system("cls");
			_ShowCancelReservationScreen();
			_GoToReservationMainMenu();
			break;

		case enReservationMainMenuOptions::ViewMyReservations:
			system("cls");
			_ShowViewMyReservationsScreen();
			_GoToReservationMainMenu();
			break;

		case enReservationMainMenuOptions::SearchReservationByBook:
			system("cls");
			_ShowSearchReservationByBookScreen();
			_GoToReservationMainMenu();
			break;

		case enReservationMainMenuOptions::SearchReservationByMember:
			system("cls");
			_ShowSearchReservationByMemberScreen();
			_GoToReservationMainMenu();
			break;

		case enReservationMainMenuOptions::ReservationQueue:
			system("cls");
			_ShowReservationQueueScreen();
			_GoToReservationMainMenu();
			break;


		case enReservationMainMenuOptions::BackToLibraryMenu:
			break;
		}
	}

public:

	static void ShowReservationScreen()
	{
		system("cls");
		_DrawScreenHeader("Reservation Screen ");

		cout << "\n\n\t\t\t__________________________________\n";

		cout << "\n\t\t\t\tReservation Main Menu\n";
		cout << "\n\t\t\t__________________________________\n";


		cout << "\n\t\t\t\t1. Make a Reservation\n";
		cout << "\n\t\t\t\t2. Complete Reservation\n";
		cout << "\n\t\t\t\t3. Cancel Reservation\n";
		cout << "\n\t\t\t\t4. View My Reservations\n";
		cout << "\n\t\t\t\t5. Search Reservation By Book\n";
		cout << "\n\t\t\t\t6. Search Reservation By Member\n";
		cout << "\n\t\t\t\t7. Reservation Queue For A Book\n";
		cout << "\n\t\t\t\t8. Back To Library Menu";
		cout << "\n\n\t\t\t__________________________________\n\n";

		_PerformReservationMainMenuOption((enReservationMainMenuOptions)_ReadOption());
	}
};

