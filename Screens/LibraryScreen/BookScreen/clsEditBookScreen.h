#pragma once
#include <iostream>
#include"Screens/clsScreen.h"
#include"Libraries/clsInputValidate.h"
#include"Objects/clsBook.h"
using namespace std;

class clsEditBookScreen :protected clsScreen
{
	static string _ReadID()
	{
		cout << "\n\nEnter Book ID to edit: ";
		string ID = clsInputValidate::ReadString();

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

	static void _EditBook(clsBook & Book)
	{
		cout << "\nEnter new Title: ";
		Book.Title= clsInputValidate::ReadString();
		cout << "\nEnter new Author: ";
		Book.Author = clsInputValidate::ReadString();
		cout << "\nEnter new Publication Year: ";
		Book.PublicationYear = clsInputValidate::ReadNumber<int>();
		cout << "\nEnter new Number of Copies: ";
		Book.NumberOfCopies = clsInputValidate::ReadNumber<int>();

	}


public:
	static void ShowEditBookScreen()
	{
		_DrawScreenHeader("Edit Book Screen");
		 
		string ID = _ReadID();

		while (!clsBook::IsBookExist(ID))
		{
			cout << "\nBook ID Not Found-( ";
			ID = _ReadID();
		}

		clsBook Book = clsBook::SearchByID(ID);

		_ShowBookDetails(Book);

		_EditBook(Book);

		clsBook::enSave Save = Book.Save();

		switch (Save)
		{
		case Book.SavedSuccessfully:
		{
			cout << "\n\nBook Updated Successfully-)";
			break;
		}
		
		case Book.FailedEmptyObject:
		{
			cout << "\n\nErorr,Book didn't Update -(";
			break;
		}
		}
		
	}
};

