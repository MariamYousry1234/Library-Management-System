#pragma once
#include <iostream>
#include"clsScreen.h"
#include"clsReservations.h"
using namespace std;

class clsTotalReservationsScreen :protected clsScreen
{
public:
	static void ShowTotalReservationsScreen()
	{
		_DrawScreenHeader("Total Reservations ");

		cout << "\n\nTotal Reservations: [" << clsReservations::TotalReservations() << "]";
	}

};

