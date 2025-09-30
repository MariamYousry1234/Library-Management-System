#pragma once

#include <iostream>
#include"Screens/clsScreen.h"
#include"Libraries/clsInputValidate.h"
#include"Objects/clsMember.h"

using namespace std;
class clsDeleteMemberScreen :protected clsScreen
{
	static string _ReadID()
	{
		cout << "\nEnter Member ID to delete: ";
		string ID = clsInputValidate::ReadString();

		while (!clsMember::IsMemberExist(ID))
		{
			cout << "\nMember ID Not Exist,Enter another ID: ";
			ID = clsInputValidate::ReadString();
		}

		return ID;
	}

	static void _ShowMemberDetails(clsMember Member)
	{

		cout << "\n\nThere is Member Details:\n\n";
		cout << "______________________________\n\n";
		cout << "ID    : " << Member.ID() << endl;
		cout << "Name  : " << Member.GetFullName() << endl;
		cout << "Email : " << Member.Email << endl;
		cout << "Phone : " << Member.PhoneNumber << endl;
		cout << "______________________________\n\n";


	}

public:
	static void  ShowDeleteMemberScreen()
	{
		_DrawScreenHeader("Delete Member Screen");

		string ID = _ReadID();

		clsMember Member = clsMember::SearchByID(ID);

		_ShowMemberDetails(Member);


		cout << "\nAre you sure you want to delete this member?Y/N? ";
		char Confirm = 'y';
		cin >> Confirm;

		if (tolower(Confirm) == 'y')
		{
			if (Member.Delete())
			{
				cout << "\nMember Deleted Successfully..";
			}
			else
			{
				cout << "\nErorr,Member didn't Deleted..";
			}
		}
	}
};

