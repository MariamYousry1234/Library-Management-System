#pragma once
#include <iostream>
#include"clsScreen.h"
#include"clsMember.h"
#include<string>
#include<iomanip>
using namespace std;

class clsShowMembersAllScreen :protected clsScreen
{
	static void _PrintMemberRecord(clsMember Member)
	{
		cout << "|" << setw(5) << left << Member.ID()
			<< "|" << setw(15) << left << Member.GetFullName()
			<< "|" << setw(20) << left << Member.Email
			<< "|" << setw(10) << left << Member.PhoneNumber;
	}
public:
	static void ShowAllMembersScreen()
	{
		vector< clsMember>vMembers = clsMember::GetMembersList();

		string SubTitle = "(" + to_string(vMembers.size()) + ") Members";

		_DrawScreenHeader("Show All Members Screen", SubTitle);

		if (vMembers.size() == 0)
		{
			cout << "\nNo Members Found-(\n\n";
			return;
		}

		cout << "\n_______________________________________________________________________\n";
		cout << "|" << setw(5) << left << "ID"
			<< "|" << setw(15) << left << "Name"
			<< "|" << setw(20) << left << "Email"
			<< "|" << setw(10) << left << "Phone";
		
		cout << "\n_______________________________________________________________________\n";


		for (clsMember M : vMembers)
		{
			_PrintMemberRecord(M);
			cout << endl;
		}
		cout << "\n__________________________________________________________________________\n";
	}

};

