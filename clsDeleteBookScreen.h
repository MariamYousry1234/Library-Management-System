#pragma once
#include <iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsBook.h"

using namespace std;

class clsDeleteBookScreen :protected clsScreen
{
	static string _ReadID()
	{
		cout << "\nEnter Book ID to delete: ";
		string ID = clsInputValidate::ReadString();

		while (! clsBook::IsBookExist(ID))
		{
			cout << "\nBook ID Not Exist,Enter another ID: ";
			ID = clsInputValidate::ReadString();
		}

		return ID;
	}

	static void _ShowBookDetails(clsBook Book)
	{
		
		cout << "\n\nThere is Book Details:\n\n";
		cout << "______________________________\n\n";
		cout << "ID    : " << Book.ID() << endl;
		cout << "Title : " << Book.Title << endl;
		cout << "Author: " << Book.Author << endl;
		cout << "ISBN  : " << Book.ISBN << endl;
		cout << "Year  : " << Book.PublicationYear << endl;
		cout << "Copies: " << Book.NumberOfCopies << endl;
		cout << "______________________________\n\n";
		
	}

public:
	static void  ShowDeleteBookScreen()
	{
		_DrawScreenHeader("Delete Book Screen");

		string ID = _ReadID();

		clsBook Book = clsBook::SearchByID(ID);

		_ShowBookDetails(Book);


		cout << "\nAre you sure you want to delete [" << Book.Title << "]?Y/N? ";
		char Confirm='y';
		cin >> Confirm;

		if (tolower(Confirm) == 'y')
		{
			if (Book.Delete())
			{
				cout << "\nBook Deleted Successfully..";
			}
			else
			{
				cout << "\nErorr,Book didn't Deleted..";
			}
		}
	}
};

