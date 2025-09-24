#pragma once

#include <iostream>
#include"clsScreen.h"
#include"clsMember.h"
#include"clsBook.h"
#include"clsInputValidate.h"
#include"clsDate.h"
#include"clsBorrowReturn.h"

using namespace std;

class clsBorrowBookScreen :protected clsScreen
{
	static string _ReadMemberID()
	{
		cout << "\nEnter Member ID : ";
		string ID = clsInputValidate::ReadString();

		while (!clsMember::IsMemberExist(ID))
		{
			cout << "\nMember ID Not Exist,Enter another ID: ";
			ID = clsInputValidate::ReadString();
		}

		return ID;
	}

	static string _ReadBookID()
	{
		cout << "\nEnter Book ID : ";
		string ID = clsInputValidate::ReadString();

		while (!clsBook::IsBookExist(ID))
		{
			cout << "\nBook ID Not Exist,Enter another ID: ";
			ID = clsInputValidate::ReadString();
		}

		return ID;
	}

	static void _ShowBookInfo(string BookID)
	{
		clsBook Book = clsBook::SearchByID(BookID);

		if (!Book.IsEmpty())
		{
			cout << "______________________________\n\n";
			cout << "Book Info:\n\n";
			cout << "______________________________\n\n";
			cout << "ID    : " << Book.ID() << endl;
			cout << "Title : " << Book.Title << endl;
			cout << "Author: " << Book.Author << endl;
			cout << "ISBN  : " << Book.ISBN << endl;
			cout << "Year  : " << Book.PublicationYear << endl;
			cout << "Copies: " << Book.NumberOfCopies << endl;
			cout << "______________________________\n\n";
		}
		else
		{
			cout << "\n\nBook Not Found-(";
			return;
		}

	}

public:
	static void ShowBorrowBookScreen()
	{
		_DrawScreenHeader("Borrow Book Screen");

		
		string MemberID = _ReadMemberID();
		string BookID = _ReadBookID();

		clsBorrowReturn	BorrowObject= clsBorrowReturn::GetBorrowObjectWithAddNewMode(MemberID, BookID);
		
		if (BorrowObject.IsEmpty())
		{
			cout << "\n\nYou borrow this Book Before Or There is any books available for this book now ";
			return;
		}

		_ShowBookInfo(BorrowObject.BookID);

		cout << "\n\nBorrow Date: " << BorrowObject.BorrowedDate << endl;
		cout << "Due Date: " << BorrowObject.DueDate<< endl;
		

		cout << "\nConfirm Borrow?(Y/N)? ";
		char Confirm = 'y';
		cin >> Confirm;

		
		if (tolower(Confirm) == 'y')
		{
			clsBorrowReturn::enSave Save = BorrowObject.Save();

			switch (Save)
			{
			case clsBorrowReturn::SavedSuccessfully:
			{
				cout << "\nBorrow Successfully!\nBook [" <<
					BorrowObject.Title << "] assigned to Member [" <<
					BorrowObject.MemberID << "]\n";

				clsBook::DecreaseNumberOfTheBook(BorrowObject.BookID);

				/*clsBook Book= clsBook::SearchByID(BorrowObject.BookID);
				if (Book.NumberOfCopies > 0)
				{
					Book.NumberOfCopies--;
					Book.Save();
				}*/
				
			}
				break;
			case clsBorrowReturn::FailedEmptyObject:
			{
				cout << "\nErorr,Borrow Failed\n";
			}
				break;
			
			}

		}
	}
};

