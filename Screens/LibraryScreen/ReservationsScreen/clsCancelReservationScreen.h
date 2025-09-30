#pragma once

#include <iostream>
#include"Screens/clsScreen.h"
#include"Libraries/clsInputValidate.h"
#include"Objects/clsReservations.h"
#include"Objects/clsMember.h"
#include"Objects/clsBook.h"
#include"Objects/clsBorrowReturn.h"
using namespace std;

class clsCancelReservationScreen :protected clsScreen
{
	static string _ReadReservationID()
	{
		cout << "\nEnter Reservation ID to Cancel: ";
		string ID = clsInputValidate::ReadString();

		while (!clsReservations::IsIDExist(ID))
		{
			cout << "\nReservation ID Not Found-(\n\nEnter another ID: ";
			ID = clsInputValidate::ReadString();
		}

		return ID;
	}

	static void _ShowReservationDetails(clsReservations Reservation)
	{
		clsBook Book = clsBook::SearchByID(Reservation.BookID);
		clsMember Member = clsMember::SearchByID(Reservation.MemberID);

		cout << "\n\nReservation Details:\n";
		cout << "_____________________________\n\n";
		cout << "Book Title: " << Book.Title << endl;
		cout << "Member Name: " << Member.GetFullName() << endl;
		cout << "Reservation Date: " << Reservation.ReservationDate << endl;
		cout << "\n_________________________________\n";
	}

public:

	static void ShowCancelReservationScreen()
	{
		_DrawScreenHeader("Cancel Reservation");

		string ReservationID = _ReadReservationID();

		cout << "\n\nAre you sure you want to cancel this reservation? (Y/N):";
		char ToCancel;
		cin >> ToCancel;
	
		clsReservations Reservation = clsReservations::FindByID(ReservationID);

		clsReservations::ChangeObjectToCancelMode(Reservation);

		if (tolower(ToCancel) == 'y')
		{
			clsReservations::enSave CancelReservation = Reservation.SaveToFile();

			switch (CancelReservation)
			{
			case clsReservations::FiledEmptyObject:
			{
				cout << "\n\nError,Reservation not Cancelled";
			}
			break;
			case clsReservations::FailedObjectisCancelled:
			{
				cout << "\n\nThis Reservation already Cancelled ..";
			}
			break;
			case clsReservations::FailedObjectisCompleted:
			{
				cout << "\n\n❌ This reservation is already marked as Completed cannot be cancelled.";
			}
			break;
			case clsReservations::CancelledSuccessfully:
			{
				cout << "\n\n✅ Reservation has been cancelled successfully.";
			}
			break;
		

			}

			
		

		}

	}
};

