#pragma once
#include <iostream>
#include"Screens/clsScreen.h"
#include"Objects/clsReservations.h"
#include"Objects/clsBook.h"
#include"Objects/clsMember.h"
#include<iomanip>
using namespace std;

class clsCompletedReservationsScreen :protected clsScreen
{
	static void _PrintReservationRecord(clsReservations Reservation)
	{
		cout << "|" << setw(7) << left << Reservation.ReservationID
			<< "|" << setw(7) << left << Reservation.BookID
			<< "|" << setw(20) << left << clsBook::SearchByID(Reservation.BookID).Title
			<< "|" << setw(8) << left << Reservation.MemberID
			<< "|" << setw(20) << left << clsMember::SearchByID(Reservation.MemberID).GetFullName()
			<< "|" << setw(12) << left << Reservation.ReservationDate;
	}

public:
	static void ShowCompletedReservationsScreen()
	{
		_DrawScreenHeader("Completed Reservations");

		vector<clsReservations>vCompletedReservations = clsReservations::GetReservationsByStatus(clsReservations::enStatus::Completed);

		if (vCompletedReservations.size() == 0)
		{
			cout << "\nNo Completed Reservations Found-(\n\n";
			return;
		}

		cout << "\n______________________________________________________________________________________________\n";
		cout << "|" << setw(7) << left << "R.ID"
			<< "|" << setw(7) << left << "Bo.ID"
			<< "|" << setw(20) << left << "Title"
			<< "|" << setw(8) << left << "MemberID"
			<< "|" << setw(20) << left << "MemberName"
			<< "|" << setw(12) << left << "R.Date";
		cout << "\n______________________________________________________________________________________________\n";


		for (clsReservations& R : vCompletedReservations)
		{
			_PrintReservationRecord(R);
			cout << endl;
		}
		cout << "\n______________________________________________________________________________________________\n";
		cout << "\n\tTotal Completed Reservations: " << vCompletedReservations.size();
	}
};

