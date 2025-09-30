#pragma once
#include <iostream>
#include"Screens/clsScreen.h"
#include"Objects/clsBorrowReturn.h"
#include<iomanip>
using namespace std;

class clsAllReturnTransactionsScreen :protected clsScreen
{
	static void _PrintBookRecord(clsBorrowReturn BorrowBook)
	{
		cout << "|" << setw(7) << left << BorrowBook.MemberID
			<< "|" << setw(20) << left << BorrowBook.MemberName
			<< "|" << setw(6) << left << BorrowBook.BookID
			<< "|" << setw(25) << left << BorrowBook.Title
			<< "|" << setw(12) << left << BorrowBook.BorrowedDate
			<< "|" << setw(8) << left << BorrowBook.DueDate;
	}

public:
	static void ShowReturnedBooksScreen()
	{
		_DrawScreenHeader("Returned Books");

		vector<clsBorrowReturn>vReturnedBooks = clsBorrowReturn::GetAllReturnedBooks();

		if (vReturnedBooks.size() == 0)
		{
			cout << "\nNo Books Borrowed yet-(\n\n";
			return;
		}

		cout << "\n______________________________________________________________________________________________\n";
		cout << "|" << setw(7) << left << "MemberID"
			<< "|" << setw(20) << left << "MemberName"
			<< "|" << setw(6) << left << "BookID"
			<< "|" << setw(25) << left << "Title"
			<< "|" << setw(12) << left << "Borrowed Date"
			<< "|" << setw(8) << left << "Due Date";

		cout << "\n______________________________________________________________________________________________\n";


		for (clsBorrowReturn& B : vReturnedBooks)
		{
			_PrintBookRecord(B);
			cout << endl;
		}
		cout << "\n______________________________________________________________________________________________\n";
		cout << "\n\tTotal Returned books: " << vReturnedBooks.size();
	}
};

