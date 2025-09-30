#pragma once
#include <iostream>
#include"Screens/clsScreen.h"
#include"Libraries/clsInputValidate.h"
#include"Objects/clsReservations.h"
#include<iomanip>
#include<queue>
using namespace std;


class clsShowReservationQueueScreen :protected clsScreen
{
	static string _ReadBookID()
	{
		cout << "\nEnter Book ID: ";
		string ID = clsInputValidate::ReadString();

		return ID;
	}

	static void _ShowReservationRecord(clsReservations::clsQueueLine Reservation)
	{
		string Status = "Waiting";
		if (clsReservations::FirstInBookQueue(Reservation.BookID) == Reservation.MemberID)
		{
			Status = "Active";

		}

		cout << "|" << setw(15) << left << Reservation.QueueID()
			<< "|" << setw(8) << left << Reservation.BookID
			<< "|" << setw(8) << left << Reservation.MemberID
			<< "|" << setw(15) << left << Reservation.ReservationDate
			<< "|" << setw(15) << left << Status;
	}


public:
	static void ShowReservationQueueScreen()
	{
		_DrawScreenHeader("Reservation Queue For A Book");

		string BookID = _ReadBookID();

		if (!clsReservations::IsBookExist(BookID))
		{
			cout << "\n❌ There are no reservations in the queue for this book. ";
			return;
		}

		queue<clsReservations::clsQueueLine>QueueForABook =
			clsReservations::GetQueueForABook(BookID);

		cout << "\n__________________________________________________________________________________\n";
		cout << "|" << setw(15) << left << "QueueNo."
			<< "|" << setw(8) << left << "BookID"
			<< "|" << setw(8) << left << "MemberID"
			<< "|" << setw(15) << left << "Reservation Date"
			<< "|" << setw(15) << left << "Status";
		cout << "\n__________________________________________________________________________________\n";

		while (!QueueForABook.empty())
		{
			_ShowReservationRecord(QueueForABook.front());
			cout << endl;
			QueueForABook.pop();
		}
		
		cout << "\n__________________________________________________________________________________\n";

	}
};

