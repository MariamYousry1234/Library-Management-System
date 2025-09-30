#pragma once
#include <iostream>
#include"Screens/clsScreen.h"
#include"Objects/clsMember.h"
using namespace std;

class clsTotalNumberOfMembersScreen :protected clsScreen
{
public:
	static void ShowTotalNumberOfMembersScreen()
	{
		_DrawScreenHeader("Total Number Of Members ");

		cout << "\n\nTotal number of Members in the library: [" << clsMember::TotalNumbersOfMembers()<< "]";
	}
};

