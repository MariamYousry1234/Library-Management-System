#pragma once
#include <iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsShowMembersAllScreen.h"
#include"clsSearchMemberScreen.h"
#include"clsRegisterMemberScreen.h"
#include"clsEditMemberScreen.h"
#include"clsDeleteMemberScreen.h"
using namespace std;

class clsMemberManagementScreen :protected clsScreen
{
	enum enMembersScreenOptions {
		ShowAllMembers = 1, SearchMember = 2,
		RegisterMember = 3, EditMember = 4, DeleteMember = 5, ReturntoLibraryMenu = 6
	};

	static short _ReadMembersScreenOption()
	{
		cout << "\t\t\tPlease enter your choice from 1 to 6: ";
		short UserOption = clsInputValidate::ReadNumberBetween<short>(1, 6,
			"\n\t\t\tNumber is not within range...\n\t\t\tPlease enter a number between 1 to 4: ");

		return UserOption;
	}

	static void _GoToMembersManagementScreen()
	{
		cout << "\n\n\nPress any key To go to Members Management Menu";
		system("pause >nul");

		ShowMembersManagementScreen();
	}

	static void	_ShowAllMembersScreen()
	{
		clsShowMembersAllScreen::ShowAllMembersScreen();
	}

	static void	_ShowSearchMemberScreen()
	{
		clsSearchMemberScreen::ShowSearchForAMemberScreen();

	}

	static void	_ShowRegisterMemberScreen()
	{
		clsRegisterMemberScreen::ShowRegisterMemberScreen();
	}

	static void	_ShowEditMemberScreen()
	{
		clsEditMemberScreen::ShowEditMemberScreen();
	}

	static void	_ShowDeleteMemberScreen()
	{
		clsDeleteMemberScreen::ShowDeleteMemberScreen();
	}

	static void _PerformMembersScreenOption(enMembersScreenOptions UserOption)
	{
		switch (UserOption)
		{
		case enMembersScreenOptions::ShowAllMembers:
			system("cls");
			_ShowAllMembersScreen();
			_GoToMembersManagementScreen();
			break;

		case enMembersScreenOptions::SearchMember:
			system("cls");
			_ShowSearchMemberScreen();
			_GoToMembersManagementScreen();
			break;

		case enMembersScreenOptions::RegisterMember:
			system("cls");
			_ShowRegisterMemberScreen();
			_GoToMembersManagementScreen();
			break;

		case enMembersScreenOptions::EditMember:
			system("cls");
			_ShowEditMemberScreen();
			_GoToMembersManagementScreen();
			break;

		case enMembersScreenOptions::DeleteMember:
			system("cls");
			_ShowDeleteMemberScreen();
			_GoToMembersManagementScreen();
			break;

		case enMembersScreenOptions::ReturntoLibraryMenu:
			break;
		}
	}

public:

	static void ShowMembersManagementScreen()
	{
		system("cls");
		_DrawScreenHeader("Members Management Screen  ");

		cout << "\n\n\t\t\t__________________________________\n";

		cout << "\n\t\t\t\tMembers Management Menu\n";
		cout << "\n\t\t\t__________________________________\n";


		cout << "\n\t\t\t\t1. Show All Members\n";
		cout << "\n\t\t\t\t2. Search Member \n";
		cout << "\n\t\t\t\t3. Register Member\n"; 
		cout << "\n\t\t\t\t4. Edit Member\n"; 
		cout << "\n\t\t\t\t5. Delete Member\n"; 
		cout << "\n\t\t\t\t6. Return to Library Menu\n";
		cout << "\n\n\t\t\t__________________________________\n\n";

		_PerformMembersScreenOption((enMembersScreenOptions)_ReadMembersScreenOption());

	}
};

