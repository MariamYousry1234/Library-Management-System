#pragma once
#include <iostream>
#include<fstream>
#include<string>
#include<vector>
#include"Libraries/clsString.h"
using namespace std;


class clsBook
{
	enum enMode{EmptyMode=1,UpdateMode=2,AddNew=3};
	enMode _Mode;

	string _ID;
	string _Title;
	string _Author;
	string _ISBN;
	short _PublicationYear;
	short _NumberOfCopies;

	bool _MarkForDelete = false;

	string _ConvertObjectToLine(clsBook Book,string Separator="#//#")
	{
		string Line;

		Line += Book.ID() + Separator;
		Line += Book.Title + Separator;
		Line += Book.Author + Separator;
		Line += Book.ISBN + Separator;
		Line += to_string(Book.PublicationYear) + Separator;
		Line += to_string(Book.NumberOfCopies);

		return Line;
	}

	static clsBook _ConvertLineToBookObject(string Line,string Separator="#//#")
	{
		vector<string>vBook;

		vBook = clsString::Split(Line, Separator);

		
		return clsBook(enMode::UpdateMode, vBook[0], vBook[1], vBook[2], vBook[3],
			stoi(vBook[4]), stoi(vBook[5]));

	}

	static clsBook _GetEmptyObject()
	{
		return clsBook(enMode::EmptyMode, "", "", "","",0, 0);
	}

	static vector<clsBook>_LoadBooksDataFromFile()
	{
		vector<clsBook>vBooks;

		fstream BooksFile;

		BooksFile.open("Books.txt", ios::in);

		if (BooksFile.is_open())
		{
			string Line;

			while (getline(BooksFile, Line))
			{
				clsBook Book = _ConvertLineToBookObject(Line);

				vBooks.push_back(Book);
			}

			BooksFile.close();
		}

		return vBooks;
	}

	void _SaveBookDataToFile(vector<clsBook>vBooks)
	{
		fstream BooksFile;

		BooksFile.open("Books.txt", ios::out);

		if (BooksFile.is_open())
		{
			for (clsBook B : vBooks)
			{
				if(B.MarkForDelete !=true)
				   BooksFile << _ConvertObjectToLine(B) << endl;
			}

			BooksFile.close();
		}


	}

	void _Update()
	{
		vector<clsBook>vBooks; 
		vBooks = _LoadBooksDataFromFile();

		for (clsBook& B : vBooks)
		{
			if (B.ID() == ID())
			{
				B = *this;
				break;
			}
		}
		_SaveBookDataToFile(vBooks);
	}

	void _AddBookToFile(clsBook Book)
	{
		fstream BooksFile;

		BooksFile.open("Books.txt", ios::out |ios::app);

		if (BooksFile.is_open())
		{
			
		    BooksFile << _ConvertObjectToLine(Book) << endl;
			
			BooksFile.close();
		}

	}

	void _AddNewBook()
	{
		_AddBookToFile(*this);
	}

	void _DeleteBook()
	{
		vector<clsBook>vBooks;
		vBooks = _LoadBooksDataFromFile();

		for (clsBook& B : vBooks)
		{
			if (B.ID() == this->_ID)
			{
				B.MarkForDelete=true;
				break;
			}
		}

		_SaveBookDataToFile(vBooks);
		*this = _GetEmptyObject();
	}

public:
	clsBook(enMode Mode, string ID, string Title, string Author, string ISBN,
		short PublicationYear, short NumberOfCopies)
	{
		_ID = ID;
		_Mode = Mode;
		_Title = Title;
		_Author = Author;
		_ISBN = ISBN;
		_PublicationYear = PublicationYear;
		_NumberOfCopies = NumberOfCopies;
	}

	bool IsEmpty()
	{
		return (_Mode == EmptyMode);
	}

	void SetMarkForDelete(bool MarkForDelete)
	{
		_MarkForDelete = MarkForDelete;
	}

	bool GetMarkForDelete()
	{
		return _MarkForDelete;
	}

	__declspec(property(get = GetMarkForDelete, put = SetMarkForDelete))bool MarkForDelete;

	void SetMode(enMode Mode)
	{
		_Mode = Mode;
	}

	enMode GetMode()
	{
		return _Mode;
	}

	__declspec(property(get = GetMode, put = SetMode))enMode Mode;


	string ID()
	{
		return _ID;
	}

	void SetTitle(string Title)
	{
		_Title = Title;
	}

	string GetTitle()
	{
		return _Title;
	}

	__declspec(property(get= GetTitle, put = SetTitle))string Title;


	void SetAuthor(string Author)
	{
		_Author = Author;
	}

	string GetAuthor()
	{
		return _Author;
	}

	__declspec(property(get = GetAuthor, put = SetAuthor))string Author;

	void SetISBN(string ISBN)
	{
		_ISBN = ISBN;
	}

	string GetISBN()
	{
		return _ISBN;
	}

	__declspec(property(get = GetISBN, put = SetISBN)) string ISBN;

	void SetPublicationYear(short PublicationYear)
	{
		_PublicationYear = PublicationYear;
	}

	short GetPublicationYear()
	{
		return _PublicationYear;
	}

	__declspec(property(get = GetPublicationYear, put = SetPublicationYear))short PublicationYear;

	void SetNumberOfCopies(short NumberOfCopies)
	{
		_NumberOfCopies = NumberOfCopies;
	}

	short GetNumberOfCopies()
	{
		return _NumberOfCopies;
	}

	__declspec(property(get = GetNumberOfCopies, put = SetNumberOfCopies))short NumberOfCopies;

	static clsBook SearchByTitle(string Title)
	{
		fstream BooksFile;

		BooksFile.open("Books.txt", ios::in);

		if (BooksFile.is_open())
		{
			string Line;

			while (getline(BooksFile, Line))
			{
				clsBook Book = _ConvertLineToBookObject(Line);

				if (Book.Title == Title)
				{
					BooksFile.close();
					return Book;
				}
			}

			BooksFile.close();
		}

		return _GetEmptyObject();
	}

	static clsBook SearchByAuthor(string Author)
	{
		fstream BooksFile;

		BooksFile.open("Books.txt", ios::in);

		if (BooksFile.is_open())
		{
			string Line;

			while (getline(BooksFile, Line))
			{
				clsBook Book = _ConvertLineToBookObject(Line);

				if (Book.Author == Author)
				{
					BooksFile.close();
					return Book;
				}
			}

			BooksFile.close();
		}

		return _GetEmptyObject();
	}

	static clsBook SearchByISBN(string ISBN)
	{
		fstream BooksFile;

		BooksFile.open("Books.txt", ios::in);

		if (BooksFile.is_open())
		{
			string Line;

			while (getline(BooksFile, Line))
			{
				clsBook Book = _ConvertLineToBookObject(Line);

				if (Book.ISBN == ISBN)
				{
					BooksFile.close();
					return Book;
				}
			}

			BooksFile.close();
		}

		return _GetEmptyObject();
	}

	static clsBook SearchByID(string ID)
	{
		fstream BooksFile;

		BooksFile.open("Books.txt", ios::in);

		if (BooksFile.is_open())
		{
			string Line;

			while (getline(BooksFile, Line))
			{
				clsBook Book = _ConvertLineToBookObject(Line);

				if (Book.ID() == ID)
				{
					BooksFile.close();
					return Book;
				}
			}

			BooksFile.close();
		}

		return _GetEmptyObject();
	}

	static bool IsBookExist(string ID)
	{
		clsBook Book = SearchByID(ID);

		return (!Book.IsEmpty());
	}

	static vector<clsBook> GetBooksList()
	{
		return _LoadBooksDataFromFile();
	}

	static clsBook GetObjectWithModeAddNew(string ID)
	{
		return clsBook(enMode::AddNew, ID , "", "", "", 0, 0);
	}

	enum enSave{ SavedSuccessfully=1,FailedEmptyObject=2,FailedObjectExist=3};

	enSave Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
			return FailedEmptyObject;
			break;

		case enMode::UpdateMode:
			_Update();
			return SavedSuccessfully;
			break;

		case enMode::AddNew:
		{
			if (IsBookExist(ID()))
				return FailedObjectExist;

			_AddNewBook();
			_Mode = enMode::UpdateMode;
			return SavedSuccessfully;
			break;
		}
		

		}
	}

	bool Delete()
	{
		if (!IsEmpty())
		{
			_DeleteBook();
			return true;
		}
		return false;
	}

	static void DecreaseNumberOfTheBook(string BookID)
	{
		clsBook Book = clsBook::SearchByID(BookID);
		if (Book.NumberOfCopies > 0)
		{
			Book.NumberOfCopies--;
			Book.Save();
		}
	}

	static void IncreaseNumberOfTheBook(string BookID)
	{
		clsBook Book = clsBook::SearchByID(BookID);
		Book.NumberOfCopies++;
		Book.Save();

	}

	static int TotalNumberOfBooks()
	{
		return _LoadBooksDataFromFile().size();
	}

	static vector<clsBook>GetListOfAvailableBooks()
	{
		vector<clsBook>vBooks = _LoadBooksDataFromFile();
		vector<clsBook>vAvilableBooks;

		for (clsBook &B : vBooks)
		{
			if (B.NumberOfCopies > 0)
				vAvilableBooks.push_back(B);
		}
		return vAvilableBooks;
	}


};

