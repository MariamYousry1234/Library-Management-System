#pragma once

#include <iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsMember.h"
#include"clsBook.h"
#include"clsReservations.h"
using namespace std;


class clsMakeAReservationScreen :protected clsScreen
{

	static string _ReadReservationID()
	{
		cout << "\nEnter Reservation ID : ";
		string ID = clsInputValidate::ReadString();

		while (clsReservations::IsIDExist(ID))
		{
			cout << "\nReservation ID already Exist,Enter another ID: ";
			ID = clsInputValidate::ReadString();
		}

		return ID;
	}

	static string _ReadBookID()
	{
		cout << "\nEnter Book ID : ";
		string ID = clsInputValidate::ReadString();

		while (!clsBook::IsBookExist(ID))
		{
			cout << "\nBook ID Not Exist,Enter another ID: ";
			ID = clsInputValidate::ReadString();
		}

		return ID;
	}

	static string _ReadMemberID()
	{
		cout << "\nEnter Member ID : ";
		string ID = clsInputValidate::ReadString();

		while (!clsMember::IsMemberExist(ID))
		{
			cout << "\nMember ID Not Exist,Enter another ID: ";
			ID = clsInputValidate::ReadString();
		}

		return ID;
	}

	static void _ShowBookInfo(string BookID)
	{
		clsBook Book = clsBook::SearchByID(BookID);

		if (!Book.IsEmpty())
		{
			cout << "______________________________\n\n";
			cout << "Book Info:\n\n";
			cout << "______________________________\n\n";
			cout << "ID    : " << Book.ID() << endl;
			cout << "Title : " << Book.Title << endl;
			cout << "Author: " << Book.Author << endl;
			cout << "ISBN  : " << Book.ISBN << endl;
			cout << "Year  : " << Book.PublicationYear << endl;
			cout << "Copies: " << Book.NumberOfCopies << endl;
			cout << "______________________________\n\n";
		}
		else
		{
			cout << "\n\nBook Not Found-(";
			return;
		}

	}

	static void _ShowMemberDetails(string MemberID)
	{
		clsMember Member = clsMember::SearchByID(MemberID);

		cout << "\n\nThere is Member Details:\n\n";
		cout << "______________________________\n\n";
		cout << "ID    : " << Member.ID() << endl;
		cout << "Name  : " << Member.GetFullName() << endl;
		cout << "Email : " << Member.Email << endl;
		cout << "Phone : " << Member.PhoneNumber << endl;
		cout << "______________________________\n\n";


	}

public:
	static void ShowMakeAReservationScreen()
	{
		_DrawScreenHeader("Make a Reservation");

		cout << "\nPlease enter the following details :\n\n";
		string ReservationID = _ReadReservationID();
		string BookID = _ReadBookID();

		_ShowBookInfo(BookID);

		string MemberID = _ReadMemberID();

		_ShowMemberDetails(MemberID);

		clsReservations Reservation = clsReservations::GetObjectWithAddNewMode(
			ReservationID, BookID, MemberID);

		cout << "\n\nConfirm Reservation Y/N?";
		char Confirm = 'y';
		cin >> Confirm;

		if (tolower(Confirm) == 'y')
		{

			clsReservations::enSave SaveReservation = Reservation.SaveToFile();


			switch (SaveReservation)
			{
			case clsReservations::FailedMemberStillBorrowThisBook:
			{
				cout << "\n\nThis member borrowed this book until now";
			}
			break;

			case clsReservations::FailedReservationExist:
			{
				cout << "\n\nThis reservation already exists for the same member";
			}
			break;

			case clsReservations::FailedBookAvailable:
			{
				cout << "\n\n📢 This book is currently available. Please go to the Borrow screen to borrow it directly. ";
			}
			break;

			case clsReservations::AddedSuccessfully:
			{
				cout << "\n\n✅ Reservation created successfully.";

				cout << "\n\nYou are number " <<
					clsReservations::GetNumberOfMemberQueue(MemberID, BookID)
					<< " in the waiting queue for this book";

			}
			break;

			default:
			{
				cout << "\n\nError,Reservation not created";
			}
			break;

			}


		}

	}

};

