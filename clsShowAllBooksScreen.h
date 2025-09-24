#pragma once
#include <iostream>
#include"clsScreen.h"
#include"clsBook.h"
#include<string>
#include<iomanip>
using namespace std;
class clsShowAllBooksScreen :protected clsScreen
{

	static void _PrintBookRecord(clsBook Book)
	{
		cout << "|" << setw(4) << left << Book.ID()
			<< "|" << setw(20) << left << Book.Title
			<< "|" << setw(15) << left << Book.Author
			<< "|" << setw(19) << left << Book.ISBN
			<< "|" << setw(5) << left << Book.PublicationYear
			<< "|" << setw(5) << left << Book.NumberOfCopies;
	}
public:
	static void ShowAllBooksScreen()
	{
		vector< clsBook>vBooks = clsBook::GetBooksList();

		string SubTitle = "(" + to_string(vBooks.size()) + ") Books";

		_DrawScreenHeader("Show All Books Screen", SubTitle);

		if (vBooks.size() == 0)
		{
			cout << "\nNo Books Found-(\n\n";
			return;
		}

		cout << "\n__________________________________________________________________________\n";
		cout << "|" << setw(4) << left << "ID"
			<< "|" << setw(20) << left << "Title"
			<< "|" << setw(15) << left << "Author"
			<< "|" << setw(19) << left << "ISBN"
			<< "|" << setw(5) << left << "Year"
			<< "|" << setw(5) << left << "Copies";
		cout << "\n__________________________________________________________________________\n";


		for (clsBook B : vBooks)
		{
			_PrintBookRecord(B);
			cout << endl;
		}
		cout << "\n__________________________________________________________________________\n";
	}

};

