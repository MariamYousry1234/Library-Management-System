#pragma once
#include <iostream>
#include"Screens/clsScreen.h"
#include"Objects/clsBook.h"
#include<iomanip>
using namespace std;

class clsAvailableBooksScreen :protected clsScreen
{
	static void _PrintBookRecord(clsBook Book)
	{
		cout << "|" << setw(7) << left << Book.ID()
			<< "|" << setw(30) << left << Book.Title
			<< "|" << setw(10) << left << Book.NumberOfCopies;
	}

public:
	static void ShowAvailableBooksScreen()
	{
		vector<clsBook>vAvailableBooks = clsBook::GetListOfAvailableBooks();

		_DrawScreenHeader("Available Books ");


		if (vAvailableBooks.size() == 0)
		{
			cout << "\nNo Books Available-(\n\n";
			return;
		}

		cout << "\n_________________________________________________________________\n";
		cout << "|" << setw(7) << left << "ID"
			<< "|" << setw(30) << left << "Title"
		    << "|" << setw(10) << left << "Number Of Copies";

		cout << "\n_________________________________________________________________\n";


		for (clsBook & B : vAvailableBooks)
		{
			_PrintBookRecord(B);
			cout << endl;
		}
		cout << "\n_________________________________________________________________\n";
		cout << "\n\tTotal available books: " << vAvailableBooks.size();
	}
};

