#pragma once
#include <iostream>
#include"Screens/clsScreen.h"
#include"Objects/clsBorrowReturn.h"
#include<iomanip>
using namespace std;

class clsMostBorrowedBooksScreen :protected clsScreen
{
	static void _PrintBookRecord(clsBorrowReturn::stMostBorrowedBook BorrowBook)
	{
		cout<< "|" << setw(25) << left << BorrowBook.Title
			<< "|" << setw(12) << left << BorrowBook.TimesBorrowed;
		
	}

public:
	static void ShowMostBorrowedBooksScreen()
	{
		_DrawScreenHeader("Most Borrowed Books");


		vector<clsBorrowReturn::stMostBorrowedBook>vMostBorrowedBook = clsBorrowReturn::GetMostBorrowedBooks();

		if (vMostBorrowedBook.size() == 0)
		{
			cout << "\nNo Books Borrowed yet-(\n\n";
			return;
		}

		cout << "\n____________________________________________________________________\n";
		cout << "|" << setw(25) << left << "Title"
			<< "|" << setw(12) << left << "Times Borrowed";
		cout << "\n____________________________________________________________________\n";


		for (clsBorrowReturn::stMostBorrowedBook & B : vMostBorrowedBook)
		{
			_PrintBookRecord(B);
			cout << endl;
		}
		cout << "\n____________________________________________________________________\n";
		
	}
};

