#pragma once

#include <iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsBorrowReturn.h"
#include<iomanip>
using namespace std;

class clsShowAllBorrowedBooksScreen :protected clsScreen
{
	static void _ShowBookRecord(clsBorrowReturn Book)
	{
		cout << "|" << setw(8) << left << Book.BookID
			<< "|" << setw(20) << left << Book.Title
			<< "|" << setw(8) << left << Book.MemberID
			<< "|" << setw(15) << left << Book.MemberName
			<< "|" << setw(13) << left << Book.BorrowedDate
			<< "|" << setw(13) << left << Book.DueDate
			<< "|" << setw(10) << left << Book.Status;
	}

public:
	static void ShowAllBorrowedBooksScreen()
	{
		_DrawScreenHeader("All Borrowed Books");

		vector<clsBorrowReturn> vBorrowedBook =
			clsBorrowReturn::GetAllBorrowedBooks();

		if (vBorrowedBook.size() == 0)
		{
			cout << "\n\nNo Borrow Books Found-(";
			return;
		}

		cout << "\n__________________________________________________________________________________\n";
		cout << "|" << setw(6) << left << "BookID"
			<< "|" << setw(20) << left << "Title"
			<< "|" << setw(8) << left << "MemberID"
			<< "|" << setw(15) << left << "Member Name"
			<< "|" << setw(13) << left << "Borrowed Date"
			<< "|" << setw(13) << left << "Due Date"
			<< "|" << setw(10) << left << "Status";
		cout << "\n__________________________________________________________________________________\n";

		for (clsBorrowReturn B : vBorrowedBook)
		{
			_ShowBookRecord(B);
			cout << endl;
		}
		cout << "\n__________________________________________________________________________________\n";
		cout << "\n\tTotal Borrowed Books= " << vBorrowedBook.size() << endl;

	}
};

