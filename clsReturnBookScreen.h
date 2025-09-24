#pragma once
#include <iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsBorrowReturn.h"
#include"clsMember.h"
#include"clsBook.h"
#include"clsDate.h"
using namespace std;

class clsReturnBookScreen :protected clsScreen
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

	static string _ReadBookID()
	{
		cout << "\nEnter Book ID : ";
		string ID = clsInputValidate::ReadString();

		while (!clsBorrowReturn::IsBookIDExist(ID))
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
			cout << "\n\nBook Info:\n\n";
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
	static void ShowReturnBookScreen()
	{
		_DrawScreenHeader("Return Book Screen");


		string MemberID = _ReadMemberID();//

		string BookID = _ReadBookID();//


		clsBorrowReturn BorrowReturnObject = clsBorrowReturn::FindBookID(BookID);
		_ShowBookInfo(BookID);

		
		cout << "\n\nBorrow Date: " << BorrowReturnObject.BorrowedDate << endl;
		cout << "Due Date: " << BorrowReturnObject.DueDate << endl;
		
		cout << "Return Date: "<< clsBorrowReturn::GetReturnDate();

		if (clsBorrowReturn::IsOverdue(BorrowReturnObject.DueDate,
			clsBorrowReturn::GetReturnDate()))
		{
			int Overdue = clsBorrowReturn::CalculateOverdue(BorrowReturnObject.DueDate,
				clsBorrowReturn::GetReturnDate()) ;

			cout << "\n\nBook returned " << Overdue << " Day (s) Late!";
			cout << "\nFine Amount : " << clsBorrowReturn::FineAmount(Overdue) <<
				" EGP (10 EGP Per Day)";
				
		}
	


		BorrowReturnObject.SetStatus("Returned");

		clsBorrowReturn::enSave Save = BorrowReturnObject.Save();

		switch (Save)
		{
		case clsBorrowReturn::SavedSuccessfully:
		{
			cout << "\n\nReturned Successfully!\nBook [" <<
				BorrowReturnObject.Title << "] received from Member [" <<
				BorrowReturnObject.MemberID << "]\n";
			

			clsBook::IncreaseNumberOfTheBook(BorrowReturnObject.BookID);

			/*clsBook Book = clsBook::SearchByID(BorrowReturnObject.BookID);
			Book.NumberOfCopies++;
			Book.Save();*/
			
		}
		break;

		case clsBorrowReturn::FailedEmptyObject:
		{
			cout << "\nErorr,Reurned Failed\n";
		}
		break;

		}

		}
	
};

