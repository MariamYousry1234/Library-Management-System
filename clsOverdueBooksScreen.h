#pragma once
#include <iostream>
#include"clsScreen.h"
#include"clsBorrowReturn.h"
#include<iomanip>
using namespace std;

class clsOverdueBooksScreen :protected clsScreen
{
	static void _PrintBookRecord(clsBorrowReturn BorrowBook)
	{
		cout << "|" << setw(6) << left << BorrowBook.BookID
			<< "|" << setw(25) << left << BorrowBook.Title
			<< "|" << setw(20) << left << BorrowBook.MemberName
			<< "|" << setw(7) << left << BorrowBook.MemberID
			<< "|" << setw(12) << left << BorrowBook.BorrowedDate
			<< "|" << setw(8) << left << BorrowBook.DueDate;
	}

public:
	static void ShowOverdueBooksScreen()
	{
		_DrawScreenHeader("Overdue Books ");

		vector<clsBorrowReturn>vOverdueBooks = clsBorrowReturn::GetOverdueBooks();

		if (vOverdueBooks.size() == 0)
		{
			cout << "\nNo Books Borrowed Overdue-(\n\n";
			return;
		}

		cout << "\n______________________________________________________________________________________________\n";
		cout << "|" << setw(7) << left << "BookID"
			<< "|" << setw(20) << left << "Title"
			<< "|" << setw(6) << left << "MemberID"
			<< "|" << setw(25) << left << "MemberName"
			<< "|" << setw(12) << left << "Borrowed Date"
			<< "|" << setw(8) << left << "Due Date";

		cout << "\n______________________________________________________________________________________________\n";


		for (clsBorrowReturn& B : vOverdueBooks)
		{
			_PrintBookRecord(B);
			cout << endl;
		}
		cout << "\n______________________________________________________________________________________________\n";
		cout << "\n\tTotal Overdue books: " << vOverdueBooks.size();
	}
	
};

