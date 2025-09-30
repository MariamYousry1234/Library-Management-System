#pragma once

#include <iostream>
#include"Screens/clsScreen.h"
#include"Libraries/clsInputValidate.h"
#include"Objects/clsMember.h"

using namespace std;


class clsRegisterMemberScreen :protected clsScreen
{

	static string _ReadID()
	{
		cout << "\nEnter Book ID : ";
		string ID = clsInputValidate::ReadString();

		while (clsMember::IsMemberExist(ID))
		{
			cout << "\nMember ID already Exist,Enter another ID: ";
			ID = clsInputValidate::ReadString();
		}

		return ID;
	}

	static void  _ReadNewMember(clsMember& Member)
	{

		cout << "\nEnter First Name : ";
		Member.FirstName = clsInputValidate::ReadString();
		cout << "\nEnter Last Name : ";
		Member.LastName = clsInputValidate::ReadString();
		cout << "\nEnter Email : ";
		Member.Email = clsInputValidate::ReadString();
		cout << "\nEnter Phone : ";
		Member.PhoneNumber = clsInputValidate::ReadString();
		

	}

	static void _ShowMemberDetails(clsMember Book)
	{
		cout << "\n______________________________\n\n";
		cout << "ID    : " << Book.ID() << endl;
		cout << "Name : " << Book.GetFullName() << endl;
		cout << "Email: " << Book.Email << endl;
		cout << "Phone  : " << Book.PhoneNumber << endl;
		cout << "______________________________\n\n";

	}
public:

	static void ShowRegisterMemberScreen()
	{
		_DrawScreenHeader("Register Member Screen");
		string ID = _ReadID();

		clsMember NewMember = clsMember::GetObjectWithModeAddNew(ID);

		_ReadNewMember(NewMember);


		clsMember::enSave Save = NewMember.Save();

		switch (Save)
		{
		case NewMember.SavedSuccessfully:
		{
			cout << "\n\nMember Added Successfully-)";
			_ShowMemberDetails(NewMember);
			break;
		}

		case NewMember.FailedObjectExist:
		{
			cout << "\n\nErorr,Member already exist-(";
			break;
		}
		}
	}

};

