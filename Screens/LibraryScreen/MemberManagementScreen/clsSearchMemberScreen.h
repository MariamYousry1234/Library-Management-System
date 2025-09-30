#pragma once
#include <iostream>
#include"Screens/clsScreen.h"
#include"Libraries/clsInputValidate.h"
#include"Objects/clsMember.h"
using namespace std;


class clsSearchMemberScreen :protected clsScreen
{
	enum enSearchOptions { ID = 1, Name = 2, Email = 3 };

	static short _ReadOption()
	{
		cout << "\t\t\tPlease enter your choice from 1 to 3: ";
		short UserOption = clsInputValidate::ReadNumberBetween<short>(1, 3,
			"\n\t\t\tNumber is not within range...\n\t\t\tPlease enter a number between 1 to 4: ");

		return UserOption;
	}

	static void _ShowMemberDetails(clsMember Member)
	{
		if (!Member.IsEmpty())
		{
			cout << "\n\n✅ Member Found:\n\n";
			cout << "______________________________\n\n";
			cout << "ID    : " << Member.ID() << endl;
			cout << "Name  : " << Member.GetFullName() << endl;
			cout << "Email : " << Member.Email << endl;
			cout << "Phone  : " << Member.PhoneNumber << endl;
			cout << "______________________________\n\n";
		}

		else
		{
			cout << "\n\nMember Not Found:\n";
		}
	}

	static void _PerformSearchOption(enSearchOptions Option)
	{
		string Text;

		switch (Option)
		{
		case enSearchOptions::ID:
		{
			cout << "\nEnter ID:";
			Text = clsInputValidate::ReadString();
			clsMember Member = clsMember::SearchByID(Text);

			_ShowMemberDetails(Member);

			break;
		}
		case enSearchOptions::Name:
		{
			cout << "\nEnter Name:";
			Text = clsInputValidate::ReadString();
			clsMember Member = clsMember::SearchByName(Text);

			_ShowMemberDetails(Member);

			break;
		}

		case enSearchOptions::Email:
		{
			cout << "\nEnter Email:";
			Text = clsInputValidate::ReadString();
			clsMember Member = clsMember::SearchByEmail(Text);

			_ShowMemberDetails(Member);
			break;
		}
		}
	}

public:
	static void ShowSearchForAMemberScreen()
	{
		_DrawScreenHeader("Search For a Member Screen  ");
		cout << "\n\n\t\t\t__________________________________\n\n";
		cout << "\n\t\t\t\tSearch By:\n";
		cout << "\n\t\t\t\t1. ID\n";
		cout << "\n\t\t\t\t2. Name\n";
		cout << "\n\t\t\t\t3. Email\n";
		cout << "\n\n\t\t\t__________________________________\n\n";

		_PerformSearchOption((enSearchOptions)_ReadOption());

	}
};

