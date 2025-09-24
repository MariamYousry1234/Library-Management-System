#pragma once
#include <iostream>
#include"clsScreen.h"
#include"clsBook.h"
using namespace std;

class clsTotalNumberOfBooksScreen :protected clsScreen
{
public :
	static void ShowTotalNumberOfBooksScreen()
	{
		_DrawScreenHeader("Total Number Of Books ");

		cout << "\n\nTotal number of books in the library: [" << clsBook::TotalNumberOfBooks()<<"]";
	}
};

