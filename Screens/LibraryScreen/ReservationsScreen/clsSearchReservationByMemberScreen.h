#pragma once

#include <iostream>
#include"Screens/clsScreen.h"
#include"Libraries/clsInputValidate.h"
#include"Objects/clsReservations.h"
#include<iomanip>

using namespace std;


class clsSearchReservationByMemberScreen :protected clsScreen
{
	static string _ReadMemberID()
	{
		cout << "\nEnter Member ID: ";
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
		string MemberID = _ReadMemberID();

		if (!clsReservations::IsMemberExist(MemberID))
		{
			cout << "\n❌ This member has no reservations. ";
			return;
		}
		vector<clsReservations>vActiveReservationsByMember =
			clsReservations::GetAllReservationsByMember(MemberID);

		cout << "\n__________________________________________________________________________________\n";
		cout << "|" << setw(15) << left << "ReservationID"
			<< "|" << setw(8) << left << "BookID"
			<< "|" << setw(8) << left << "MemberID"
			<< "|" << setw(15) << left << "Reservation Date"
			<< "|" << setw(15) << left << "Status";
		cout << "\n__________________________________________________________________________________\n";

		for (clsReservations& R : vActiveReservationsByMember)
		{
			_ShowReservationRecord(R);
			cout << endl;
		}
		cout << "\n__________________________________________________________________________________\n";
	}

};

