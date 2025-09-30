#pragma once
#include <iostream>
#include"Screens/clsScreen.h"
#include"Libraries/clsInputValidate.h"
#include"Objects/clsReservations.h"
#include<iomanip>
using namespace std;

class clsViewMyReservationsScreen :protected clsScreen
{
	static void _ShowReservationRecord(clsReservations Reservation)
	{
		cout << "|" << setw(15) << left << Reservation.ReservationID
			<< "|" << setw(8) << left << Reservation.BookID
			<< "|" << setw(8) << left << Reservation.MemberID
			<< "|" << setw(15) << left << Reservation.ReservationDate
			<< "|" << setw(15) << left << clsReservations::GetStringStatus(Reservation.Status);
	}


public:
	static void ShowViewMyReservationsScreen()
	{
		_DrawScreenHeader("View MyReservations");

		vector<clsReservations> vActiveReservation =
			clsReservations::GetReservationsStillActive();

		if (vActiveReservation.size() == 0)
		{
			cout << "\n\n❌ You have no reservations at the moment.";
			return;
		}

		cout << "\n__________________________________________________________________________________\n";
		cout << "|" << setw(15) << left << "ReservationID"
			<< "|" << setw(8) << left << "BookID"
			<< "|" << setw(8) << left << "MemberID"
			<< "|" << setw(15) << left << "Reservation Date"
			<< "|" << setw(15) << left << "Status";
		cout << "\n__________________________________________________________________________________\n";

		for (clsReservations &R : vActiveReservation)
		{
			_ShowReservationRecord(R);
			cout << endl;
		}
		cout << "\n__________________________________________________________________________________\n";
		cout << "\n\tTotal Reservations= " << vActiveReservation.size() << endl;

	}
	

};

