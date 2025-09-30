#pragma once
#include <iostream>
#include"Screens/clsScreen.h"
#include"Libraries/clsInputValidate.h"
#include"Objects/clsBook.h"

using namespace std;
class clsAddNewBookScreen :protected clsScreen
{
	static string _ReadID()
	{
		cout << "\nEnter Book ID : ";
		string ID = clsInputValidate::ReadString();

		while (clsBook::IsBookExist(ID))
		{
			cout << "\nBook ID already Exist,Enter another ID: ";
			ID = clsInputValidate::ReadString();
		}

		return ID;
	}

	static void  _ReadNewBook(clsBook & Book)
	{

		cout << "\nEnter Title : ";
		Book.Title = clsInputValidate::ReadString();
		cout << "\nEnter Author : ";
		Book.Author = clsInputValidate::ReadString();
		cout << "\nEnter ISBN : ";
		Book.ISBN = clsInputValidate::ReadString();
		cout << "\nEnter Publication Year : ";
		Book.PublicationYear = clsInputValidate::ReadNumber<short>();
		cout << "\nEnter Number Of Copies : ";
		Book.NumberOfCopies = clsInputValidate::ReadNumber<short>();

	}

	static void _ShowBookDetails(clsBook Book)
	{
		cout << "\n______________________________\n\n";
		cout << "ID    : " << Book.ID() << endl;
		cout << "Title : " << Book.Title << endl;
		cout << "Author: " << Book.Author << endl;
		cout << "ISBN  : " << Book.ISBN << endl;
		cout << "Year  : " << Book.PublicationYear << endl;
		cout << "Copies: " << Book.NumberOfCopies << endl;
		cout << "______________________________\n\n";

	}
public:

	static void ShowAddNewBookScreen()
	{
		_DrawScreenHeader("Add New Book Screen");
		string ID=  _ReadID();

		clsBook NewBook = clsBook::GetObjectWithModeAddNew(ID);

		_ReadNewBook(NewBook);


		clsBook::enSave Save = NewBook.Save();

		switch (Save)
		{
		case NewBook.SavedSuccessfully:
		{
			cout << "\n\nBook Added Successfully-)";
			_ShowBookDetails(NewBook);
			break;
		}

		case NewBook.FailedObjectExist:
		{
			cout << "\n\nErorr,Book already exist-(";
			break;
		}
		}
	}
};

