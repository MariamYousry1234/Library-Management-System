#pragma once
#include <iostream>
#include"Screens/clsScreen.h"
#include"Libraries/clsInputValidate.h"
#include"Objects/clsReservations.h"
#include<iomanip>

using namespace std;

class clsSearchReservationByBookScreen :protected clsScreen
{
	static string _ReadBookID()
	{
		cout << "\nEnter Book ID: ";
		string ID = clsInputValidate::ReadString();

		return ID;
	}


	static void _ShowReservationRecord(clsReservations Reservation)
	{
		cout << "|" << setw(15) << left << Reservation.ReservationID
			<< "|" << setw(8) << left << Reservation.BookID
			<< "|" << setw(8) << left << Reservation.MemberID
			<< "|" << setw(15) << left << Reservation.ReservationDate
			<< "|" << setw(15) << left << clsReservations::GetStringStatus(Reservation.Status);
	}

public:
	static void ShowSearchReservationByBookScreen()
	{
		_DrawScreenHeader("Search Reservation By Book ");
		string BookID = _ReadBookID();

		if (!clsReservations::IsBookExist(BookID))
		{
			cout << "\n❌ No reservations found for this book. ";
			return;
		}
		vector<clsReservations>vActiveReservationsByBook=
			clsReservations::GetAllReservationsByBook(BookID);

		cout << "\n__________________________________________________________________________________\n";
		cout << "|" << setw(15) << left << "ReservationID"
			<< "|" << setw(8) << left << "BookID"
			<< "|" << setw(8) << left << "MemberID"
			<< "|" << setw(15) << left << "Reservation Date"
			<< "|" << setw(15) << left << "Status";
		cout << "\n__________________________________________________________________________________\n";

		for (clsReservations& R : vActiveReservationsByBook)
		{
			_ShowReservationRecord(R);
			cout << endl;
		}
		cout << "\n__________________________________________________________________________________\n";
	}
	

};

