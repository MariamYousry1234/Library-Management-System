#pragma once

#include <iostream>
#include"Screens/clsScreen.h"
#include"Libraries/clsInputValidate.h"
#include"Objects/clsBook.h"
using namespace std;

class clsSearchForABookScreen :protected clsScreen
{
	enum enSearchOptions{ ID=1,Title =2, Author=3, ISBN=4};

	static short _ReadOption()
	{
		cout << "\t\t\tPlease enter your choice from 1 to 4: ";
		short UserOption = clsInputValidate::ReadNumberBetween<short>(1, 4,
			"\n\t\t\tNumber is not within range...\n\t\t\tPlease enter a number between 1 to 4: ");

		return UserOption;
	}

	static void _ShowBookDetails(clsBook Book)
	{
		if (!Book.IsEmpty())
		{
			cout << "\n\n✅ Book Found:\n\n";
			cout << "______________________________\n\n";
			cout << "ID    : " << Book.ID() << endl;
			cout << "Title : " << Book.Title<< endl;
			cout << "Author: " << Book.Author << endl;
			cout << "ISBN  : " << Book.ISBN << endl;
			cout << "Year  : " << Book.PublicationYear << endl;
			cout << "Copies: " << Book.NumberOfCopies << endl;
			cout << "______________________________\n\n";
		}

		else
		{
			cout << "\n\nBook Not Found:\n";
		}
	}

	static void _PerformSearchOption(enSearchOptions Option)
	{
		string Text;

		switch (Option)
		{
		case enSearchOptions::ID:
		{
			cout << "\nEnter ID:";
			Text = clsInputValidate::ReadString();
			clsBook Book = clsBook::SearchByID(Text);

			_ShowBookDetails(Book);

			break;
		}
		case enSearchOptions::Title:
		{
			cout << "\nEnter Title:";
			Text= clsInputValidate::ReadString();
			clsBook Book = clsBook::SearchByTitle(Text);

			_ShowBookDetails(Book);

			break;
		}
			
		case enSearchOptions::Author:
		{
			cout << "\nEnter Author:";
			Text = clsInputValidate::ReadString();
			clsBook Book = clsBook::SearchByAuthor(Text);

			_ShowBookDetails(Book);
			break;
		}

		case enSearchOptions::ISBN:
		{
			cout << "\nEnter ISBN:";
			Text = clsInputValidate::ReadString();
			clsBook Book = clsBook::SearchByISBN(Text);

			_ShowBookDetails(Book);
			break;
		}
		}
	}

public:
	static void ShowSearchForABookScreen()
	{ 
		_DrawScreenHeader("Search For a Book Screen  ");
		cout << "\n\n\t\t\t__________________________________\n\n";
		cout << "\n\t\t\t\tSearch By:\n";
		cout << "\n\t\t\t\t1. ID\n";
		cout << "\n\t\t\t\t2. Title\n";
		cout << "\n\t\t\t\t3. Author\n";
		cout << "\n\t\t\t\t4. ISBN\n";
		cout << "\n\n\t\t\t__________________________________\n\n";

		_PerformSearchOption((enSearchOptions)_ReadOption());

	}
};

