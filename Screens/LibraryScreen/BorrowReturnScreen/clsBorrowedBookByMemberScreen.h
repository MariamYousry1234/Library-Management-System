#pragma once
#include <iostream>
#include"Screens/clsScreen.h"
#include"Libraries/clsInputValidate.h"
#include"Objects/clsBorrowReturn.h"
#include<iomanip>
using namespace std;
class clsBorrowedBookByMemberScreen :protected clsScreen
{
	static string _ReadMemberID()
	{
		cout << "\nEnter Member ID : ";
		string ID = clsInputValidate::ReadString();

		while (!clsBorrowReturn::IsMemberIDExist(ID))
		{
			cout << "\nMember ID Not Exist,Enter another ID: ";
			ID = clsInputValidate::ReadString();
		}

		return ID;
	}

	static void _ShowBookRecord(clsBorrowReturn Book)
	{
		cout << "|" << setw(8) << left << Book.BookID
			<< "|" << setw(20) << left << Book.Title
			<< "|" << setw(13) << left << Book.BorrowedDate
			<< "|" << setw(13) << left << Book.DueDate
			<< "|" << setw(10) << left << Book.Status;
	}

public:
	static void ShowBorrowedBookByMemberScreen()
	{
		_DrawScreenHeader("Borrowed Book By Member ");

		string MemberID = _ReadMemberID();

		

		cout << "\n\nMember Name: " << 
			clsBorrowReturn::FindMemberID(MemberID).MemberName << endl<<endl;

		vector<clsBorrowReturn> vBorrowedBook =
			clsBorrowReturn::GetBorrowedBooksByMemberID(MemberID);

		if (vBorrowedBook.size() == 0)
		{
			cout << "\n\nNo Borrow Books Found For this member-(";
			return;
		}

		cout << "\n____________________________________________________________________\n";
		cout << "|" << setw(8) << left << "Book ID"
			<< "|" << setw(20) << left << "Title"
			<< "|" << setw(13) << left << "Borrowed Date"
			<< "|" << setw(13) << left << "Due Date"
			<< "|" << setw(10) << left << "Status";
		cout << "\n___________________________________________________________________\n";

		for (clsBorrowReturn B : vBorrowedBook)
		{
			_ShowBookRecord(B);
			cout << endl;
		}
		cout << "\n___________________________________________________________________\n";
		cout << "\n\tTotal Borrowed Books= " << vBorrowedBook.size() << endl;
	}

};

