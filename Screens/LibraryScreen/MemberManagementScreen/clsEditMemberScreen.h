#pragma once

#include <iostream>
#include"Screens/clsScreen.h"
#include"Libraries/clsInputValidate.h"
#include"Objects/clsMember.h"
using namespace std;

class clsEditMemberScreen :protected clsScreen
{
	static string _ReadID()
	{
		cout << "\n\nEnter Member ID to edit: ";
		string ID = clsInputValidate::ReadString();

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

	static void _ReadNewMember(clsMember& Member)
	{
		cout << "\nEnter new First Name: ";
		Member.FirstName = clsInputValidate::ReadString();
		cout << "\nEnter new Last Name: ";
		Member.LastName = clsInputValidate::ReadString();
		cout << "\nEnter new Email: ";
		Member.Email = clsInputValidate::ReadString();
		cout << "\nEnter new Phone Number: ";
		Member.PhoneNumber = clsInputValidate::ReadString();

	}


public:
	static void ShowEditMemberScreen()
	{
		_DrawScreenHeader("Edit Member Screen");

		string ID = _ReadID();

		while (!clsMember::IsMemberExist(ID))
		{
			cout << "\nMember ID Not Found-( ";
			ID = _ReadID();
		}

		clsMember Member = clsMember::SearchByID(ID);

		_ShowMemberDetails(Member);

		_ReadNewMember(Member);

		clsMember::enSave Save = Member.Save();

		switch (Save)
		{
		case Member.SavedSuccessfully:
		{
			cout << "\n\nMember Updated Successfully-)";
			break;
		}

		case Member.FailedEmptyObject:
		{
			cout << "\n\nErorr,Member didn't Update -(";
			break;
		}
		}

	}
};

