#pragma once
#include <iostream>
#include"Screens/clsScreen.h"
#include"Objects/clsMember.h"
#include<iomanip>
#include"Objects/clsReservations.h"
#include"Objects/clsBorrowReturn.h"
using namespace std;

class clsTopActiveMembersScreen :protected clsScreen
{
	static void _PrintActiveMemberRecord
	(clsBorrowReturn::stActiveBorrowedMember ActiveMember)
	{
		cout << "|" << setw(10) << left << ActiveMember.MemberID
			<< "|" << setw(30) << left << ActiveMember.MemberName;

	}

	static void _PrintActiveMemberRecord
	(clsReservations::stActiveReservationMember ActiveMember)
	{
		cout << "|" << setw(10) << left << ActiveMember.MemberID
			<< "|" << setw(30) << left << ActiveMember.MemberName;

	}

public:
	static void ShowTopActiveMembersScreen()
	{
		_DrawScreenHeader("Top Active Members ");

		vector< clsBorrowReturn::stActiveBorrowedMember>vActiveBorrowedMember =
			clsBorrowReturn::GetActiveBorrowedMembers();

		vector< clsReservations::stActiveReservationMember>vActiveReservationMember =
			clsReservations::GetActiveReservationMembers();


		if (vActiveBorrowedMember.size() == 0 && vActiveReservationMember.size() == 0)
		{
			cout << "\nNo Active Members yet-(\n\n";
			return;
		}

		cout << "\n__________________________________________________________________\n";
		cout << "|" << setw(10) << left << "MemberID"
			<< "|" << setw(30) << left << "MemberName";

		cout << "\n__________________________________________________________________\n";

		for (clsBorrowReturn::stActiveBorrowedMember& AcM : vActiveBorrowedMember)
		{
			_PrintActiveMemberRecord(AcM);
			cout << endl;
		}

		for (clsReservations::stActiveReservationMember& AcM : vActiveReservationMember)
		{
			_PrintActiveMemberRecord(AcM);
			cout << endl;
		}
		cout << "\n__________________________________________________________________\n";
		cout << "\n\tTotal Active Members: " << vActiveBorrowedMember.size() + vActiveReservationMember.size();
	
	}
};

