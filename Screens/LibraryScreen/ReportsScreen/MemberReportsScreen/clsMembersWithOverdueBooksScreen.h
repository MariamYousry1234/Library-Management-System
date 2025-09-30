#pragma once
#include <iostream>
#include"Screens/clsScreen.h"
#include"Objects/clsBorrowReturn.h"
#include<iomanip>
using namespace std;

class clsMembersWithOverdueBooksScreen :protected clsScreen
{
	static void _PrintBookRecord(clsBorrowReturn BorrowMember)
	{
		cout << "|" << setw(7) << left << BorrowMember.MemberID
			<< "|" << setw(20) << left << BorrowMember.MemberName
			<< "|" << setw(6) << left << BorrowMember.BookID
			<< "|" << setw(25) << left << BorrowMember.Title
			<< "|" << setw(12) << left << BorrowMember.BorrowedDate
			<< "|" << setw(8) << left << BorrowMember.DueDate;
	}

public:
	static void ShowOverdueMembersScreen()
	{
		_DrawScreenHeader("Overdue Members ");

		vector<clsBorrowReturn>vOverdueMembers = clsBorrowReturn::GetOverdueBooks();

		if (vOverdueMembers.size() == 0)
		{
			cout << "\nNo Members Overdue-(\n\n";
			return;
		}

		cout << "\n______________________________________________________________________________________________\n";
		cout << "|" << setw(7) << left << "MemberID"
			<< "|" << setw(20) << left << "MemberName"
			<< "|" << setw(6) << left << "BookID"
			<< "|" << setw(25) << left << "Title"
			<< "|" << setw(12) << left << "Borrowed Date"
			<< "|" << setw(8) << left << "Due Date";

		cout << "\n______________________________________________________________________________________________\n";


		for (clsBorrowReturn& M : vOverdueMembers)
		{
			_PrintBookRecord(M);
			cout << endl;
		}
		cout << "\n______________________________________________________________________________________________\n";
		cout << "\n\tTotal Overdue Members: " << vOverdueMembers.size();
	}
};

