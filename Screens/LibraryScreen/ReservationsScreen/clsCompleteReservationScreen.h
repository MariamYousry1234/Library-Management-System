#pragma once
#include <iostream>
#include"Screens/clsScreen.h"
#include"Libraries/clsInputValidate.h"
#include"Objects/clsReservations.h"
#include"Objects/clsMember.h"
#include"Objects/clsBook.h"
#include"Objects/clsBorrowReturn.h"
using namespace std;

class clsCompleteReservationScreen :protected clsScreen
{
	static string _ReadReservationID()
	{
		cout << "\nEnter Reservation ID : ";
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
	static void ShowCompleteReservationScreen()
	{
		_DrawScreenHeader("Complete Reservation");

		string ReservationID = _ReadReservationID();

	
		clsReservations Reservation = clsReservations::FindByID(ReservationID);

		_ShowReservationDetails(Reservation);

		cout << "\nDo you want to mark this reservation as Completed?(Y/N): ";
		char ToComplete = 'y';
		cin >> ToComplete;

		if (tolower(ToComplete) == 'y')
		{

			clsReservations::enSave CompleteReservation = Reservation.SaveToFile();

			switch (CompleteReservation)
			{
			case clsReservations::FiledEmptyObject:
			{
				cout << "\n\nError,Reservation not updated";
			}
				break;
			case clsReservations::FailedObjectisCompleted:
			{	
				cout << "\nThis Reservation is already marked as Completed..";
			}
				break;
			case clsReservations::FailedObjectisStillWaiting:
			{
				cout << "\nThis reservation is still in the waiting queue and it's not your turn yet.";
			}
				break;
			case clsReservations::FailedNoCopiedAvailable:
			{
				cout << "\n\nYou can not borrow this book now,there is no Copies Available";
			}
				break;
			case clsReservations::UpdatedSuccessfully:
			{
				cout << "\n\nReservation has been marked as completed Successfully..";

				clsBorrowReturn BorrowBook = clsBorrowReturn::GetBorrowObjectWithAddNewMode(Reservation.MemberID,
					Reservation.BookID);

				BorrowBook.Save();
				cout << "\n\n📚 The book has been added to your borrowed books list...";


				clsBook::DecreaseNumberOfTheBook(Reservation.BookID);

			}
				break;
		
			}


			

		}
	}
};

