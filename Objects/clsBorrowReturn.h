#pragma once

#include <iostream>
#include"Libraries/clsDate.h"
#include"Libraries/clsString.h"
#include<fstream>
#include<string>
#include"Objects/clsMember.h"
#include"Libraries/clsUtil.h"
using namespace std;

class clsBorrowReturn
{
	enum enMode { EmptyMode = 1, UpdateMode = 2,AddNew=3 };
	enMode _Mode;


	string _MemberID;
	string _MemberName;
	string _BookID;
	string _Title;
	string _BorrowedDate;
	string _DueDate;
	string _Status;

	struct stMostBorrowedBook;
	clsDate _SystemDate = clsDate::GetSystemDate();

	string _ConvertBorrowReturnBooksObjectToLine(clsBorrowReturn BorrowReturnBook,
		string Separator="#//#")
	{
		string Line;

		Line += BorrowReturnBook.MemberID + Separator;
		Line += BorrowReturnBook.MemberName + Separator;
		Line += BorrowReturnBook.BookID + Separator;
		Line += BorrowReturnBook.Title + Separator;
		Line += BorrowReturnBook.BorrowedDate+ Separator;
		Line += BorrowReturnBook.DueDate + Separator;
		Line += BorrowReturnBook.Status;

		return Line;
	}

	static clsBorrowReturn _ConvertBorrowReturnBooksLineToObject(string Line, string Separator = "#//#")
	{
		vector<string>vBorrowReturnBooks;
		vBorrowReturnBooks = clsString::Split(Line, Separator);


		return clsBorrowReturn(enMode::UpdateMode, vBorrowReturnBooks[0], vBorrowReturnBooks[1], vBorrowReturnBooks[2]
			, vBorrowReturnBooks[3], vBorrowReturnBooks[4],
			vBorrowReturnBooks[5], vBorrowReturnBooks[6]);
	}

	static vector< clsBorrowReturn> _LoadBorrowReturnBooksFromFile()
	{
		vector<clsBorrowReturn>vBorrowReturnBooks;
		fstream MyFile;

		MyFile.open("BorrowReturnBooks.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				if (Line !="")
				{
					clsBorrowReturn BorrowReturnObject =
						_ConvertBorrowReturnBooksLineToObject(Line);

					vBorrowReturnBooks.push_back(BorrowReturnObject);
				}
			}


			MyFile.close();
		}

		return vBorrowReturnBooks;
	}

	static clsBorrowReturn _GetEmptyObject()
	{
		return clsBorrowReturn(enMode::EmptyMode, "", "", "", "", "", "", "");
	}

	void _SaveDataToFile()
	{
		fstream MyFile;

		MyFile.open("BorrowReturnBooks.txt", ios::out|ios::app);

		if (MyFile.is_open())
		{
			if (!this->IsEmpty())
			{
				MyFile << _ConvertBorrowReturnBooksObjectToLine(*this) << endl;
			}
		
			MyFile.close();
		}
		
	}

	void _SaveUpdateToFile(vector< clsBorrowReturn>vBorrowReturnBooks)
	{
		fstream MyFile;

		MyFile.open("BorrowReturnBooks.txt", ios::out );

		if (MyFile.is_open())
		{
			for (clsBorrowReturn & B : vBorrowReturnBooks)
			{
				if (!this->IsEmpty())
				{
					MyFile << _ConvertBorrowReturnBooksObjectToLine(B) << endl;
				}
			}
		
			MyFile.close();
		}

	}

	void _UpdateToReturned()
	{
		vector< clsBorrowReturn>vBorrowReturnBooks = _LoadBorrowReturnBooksFromFile();

		for (clsBorrowReturn &B : vBorrowReturnBooks)
		{

			if (B.BookID == this->BookID && B.MemberID ==this->MemberID)
			{
				B.Status = "Returned";
				break;
			}
		}

		_SaveUpdateToFile(vBorrowReturnBooks);
	}

	static int TheNumberOfBorrowTheBook(string BookID, vector< clsBorrowReturn>vBooks)
	{
		int Counter = 0;

		for (clsBorrowReturn& B : vBooks)
		{
			if (BookID == B.BookID)
				Counter++;
		}
		return Counter;
	}

	static void RerangeMostBorrowedBooks(vector<stMostBorrowedBook>& vMostBorrowedBook)
	{
		for (int i = 0; i < vMostBorrowedBook.size()-1; i++)
		{
			if (vMostBorrowedBook[i].TimesBorrowed < vMostBorrowedBook[i + 1].TimesBorrowed)
				clsUtil::Swap(vMostBorrowedBook[i], vMostBorrowedBook[i + 1]);
		}
		
	}

public:

	clsBorrowReturn(enMode Mode, string MemberID, string MemberName, string BookID, string Title,
		string BorrowedDate, string DueDate, string Status)
	{
		_Mode = Mode;
		_MemberID = MemberID;
		_MemberName = MemberName;
		_BookID = BookID;
		_Title = Title;
		_BorrowedDate = BorrowedDate;
		_DueDate = DueDate;
		_Status = Status;
	}

	bool IsEmpty()
	{
		return (_Mode == EmptyMode);
	}

	void SetMode(enMode Mode)
	{
		_Mode = Mode;
	}

	enMode GetMode()
	{
		return _Mode;
	}

	__declspec(property(get = GetMode, put = SetMode))enMode Mode;

	void SetMemberID(string MemberID)
	{
		_MemberID = MemberID;
	}

	string GetMemberID()
	{
		return _MemberID;
	}

	__declspec(property(get = GetMemberID, put = SetMemberID))string MemberID;

	void SetMemberName(string MemberName)
	{
		_MemberName = MemberName;
	}

	string GetMemberName()
	{
		return _MemberName;
	}

	__declspec(property(get = GetMemberName, put = SetMemberName))string MemberName;

	void SetBookID(string BookID)
	{
		_BookID = BookID;
	}

	string GetBookID()
	{
		return _BookID;
	}

	__declspec(property(get = GetBookID, put = SetBookID))string BookID;


	void SetTitle(string Title)
	{
		_Title = Title;
	}

	string GetTitle()
	{
		return _Title;
	}

	__declspec(property(get = GetTitle, put = SetTitle))string Title;

	void SetBorrowedDate()
	{
		_BorrowedDate = clsDate::DateToString(_SystemDate);
	}

	string GetBorrowedDate()
	{
		return _BorrowedDate;
	}

	__declspec(property(get = GetBorrowedDate, put = SetBorrowedDate))string BorrowedDate;

	void SetDueDate()
	{
		_DueDate = clsDate::DateToString(_SystemDate.IncreaseDateByXDays(14, _SystemDate));
	}

	string GetDueDate()
	{
		return _DueDate;
	}

	__declspec(property(get = GetDueDate, put = SetDueDate))string DueDate;


	void SetStatus(string Status)
	{
		_Status = Status;
	}

	string GetStatus()
	{
		return _Status;
	}

	__declspec(property(get = GetStatus, put = SetStatus))string Status;


	static clsBorrowReturn FindBookID(string BookID)
	{
		vector< clsBorrowReturn>vBorrowReturnBooks = _LoadBorrowReturnBooksFromFile();

		for (clsBorrowReturn B : vBorrowReturnBooks)
		{
			if (B.BookID == BookID)
			{
				return B;
			}
		}

		return _GetEmptyObject();
	}

	static clsBorrowReturn FindMemberID(string MemberID)
	{
		vector< clsBorrowReturn>vBorrowReturnBooks = _LoadBorrowReturnBooksFromFile();

		for (clsBorrowReturn& B : vBorrowReturnBooks)
		{

			if (B.MemberID == MemberID)
			{
				return B;
			}
		}

		return _GetEmptyObject();
	}

	static bool IsBookIDExist(string BookID)
	{
		clsBorrowReturn BorrowReturnObject = FindBookID(BookID);

		return (!BorrowReturnObject.IsEmpty());

	}

	static bool IsMemberIDExist(string MemberID)
	{
		clsBorrowReturn BorrowReturnObject = FindMemberID(MemberID);

		return (!BorrowReturnObject.IsEmpty());
	}

	static bool IsMemberBorrowBookBefore(string MemberID, string BookID)
	{
		vector< clsBorrowReturn>vBorrowReturnBooks = _LoadBorrowReturnBooksFromFile();

		for (clsBorrowReturn &B : vBorrowReturnBooks)
		{

			if (B.MemberID == MemberID &&B.BookID==BookID && B.Status=="Borrowed")
			{
				return true;
			}
		}

		return false;
	}

	static clsBorrowReturn GetBorrowObjectWithAddNewMode(string MemberID,
		string BookID)
	{
		clsBorrowReturn	BorrowObject = _GetEmptyObject();
		clsBook Book = clsBook::SearchByID(BookID);

		if (IsMemberBorrowBookBefore(MemberID, BookID) ||Book.NumberOfCopies== 0)
		{
			return BorrowObject;
		}

		BorrowObject.Title = Book.Title;

		clsMember Member = clsMember::SearchByID(MemberID);
		if (Member.IsEmpty())
			return BorrowObject;

		string MemberName = Member.GetFullName();

		
		BorrowObject.SetBorrowedDate();
		BorrowObject.SetDueDate();

		return clsBorrowReturn(enMode::AddNew, MemberID, MemberName, 
			BookID, BorrowObject.Title, BorrowObject.BorrowedDate, BorrowObject.DueDate, "Borrowed");
	}

	enum enSave { FailedEmptyObject = 1, SavedSuccessfully = 2 };

	enSave Save()
	{
		switch (_Mode)
		{
		case clsBorrowReturn::EmptyMode:
		{
			return FailedEmptyObject;
		    break;

		}
		case clsBorrowReturn::UpdateMode:
		{
			if (!IsBookIDExist(GetBookID()))
			{
				return FailedEmptyObject;
			}

			_UpdateToReturned();
			return SavedSuccessfully;
			break;
		}
		case clsBorrowReturn::AddNew:
		{
			_SaveDataToFile();
			_Mode = enMode::UpdateMode;

			return SavedSuccessfully;
			break;
		}
			
		
		}
	}

	static string GetReturnDate()
	{
		return clsDate::DateToString(clsDate::GetSystemDate());
	}

	static short CalculateOverdue(string DueDate,string ReturnDate)
	{
		if (clsDate::IsDate1BeforeDate2(clsDate(DueDate), clsDate(ReturnDate)))
		{
			return clsDate::GetDifferenceInDays(clsDate(DueDate), clsDate(ReturnDate));
		}
		return 0;
	}

	static bool IsOverdue(string DueDate, string ReturnDate)
	{
		return CalculateOverdue(DueDate, ReturnDate) > 0 ;
	}

	static float FineAmount(int Overdue)
	{
		return Overdue * 10;

	}

	static vector< clsBorrowReturn> GetBorrowedBooksByMemberID(string MemberID)
	{
		vector< clsBorrowReturn>vBorrowReturnBooks = _LoadBorrowReturnBooksFromFile();
		vector< clsBorrowReturn>vBorrowed;

		for (clsBorrowReturn B : vBorrowReturnBooks)
		{

			if (B.MemberID == MemberID && B.Status=="Borrowed")
			{
				vBorrowed.push_back(B);
			}
		}
		return vBorrowed;

	}

	static vector< clsBorrowReturn>GetAllBorrowedBooks()
	{
		vector< clsBorrowReturn>vBorrowReturnBooks = _LoadBorrowReturnBooksFromFile();
		vector< clsBorrowReturn>vBorrowed;

		for (clsBorrowReturn B : vBorrowReturnBooks)
		{
			if (B.Status == "Borrowed")
			{
				vBorrowed.push_back(B);
			}
		}

		return vBorrowed;
	}

	static vector<clsBorrowReturn>GetOverdueBooks()
	{
		clsDate SystemDate = clsDate::GetSystemDate();

		vector< clsBorrowReturn>vBorrowedBooks= GetAllBorrowedBooks();
		vector< clsBorrowReturn>vOverdue;

		for (clsBorrowReturn B : vBorrowedBooks)
		{
			if (clsDate::IsDate1AfterDate2(SystemDate, B.DueDate))
			{
				vOverdue.push_back(B);
			}
		}

		return vOverdue;
	}

	struct stActiveBorrowedMember
	{
		string MemberID;
		string MemberName;
	};

	static vector<stActiveBorrowedMember>GetActiveBorrowedMembers()
	{
		vector<stActiveBorrowedMember>vActiveBorrowedMembers;

		vector<clsBorrowReturn>vBorrowedBooks = GetAllBorrowedBooks();

		for (clsBorrowReturn& B : vBorrowedBooks)
		{
			stActiveBorrowedMember Member;
			Member.MemberID = B.MemberID;
			Member.MemberName = B.MemberName;

			vActiveBorrowedMembers.push_back(Member);
		}

		return vActiveBorrowedMembers;
	}

	static vector< clsBorrowReturn>GetAllReturnedBooks()
	{
		vector< clsBorrowReturn>vBorrowReturnBooks = _LoadBorrowReturnBooksFromFile();
		vector< clsBorrowReturn>vReturned;

		for (clsBorrowReturn B : vBorrowReturnBooks)
		{
			if (B.Status == "Returned")
			{
				vReturned.push_back(B);
			}
		}

		return vReturned;
	}

	struct stMostBorrowedBook
	{
		string Title;
		int TimesBorrowed;
	};

	static vector<stMostBorrowedBook>GetMostBorrowedBooks()
	{
		vector< clsBorrowReturn>vBooks= _LoadBorrowReturnBooksFromFile();
		vector<stMostBorrowedBook>vMostBorrowedBook;

		
		for (clsBorrowReturn& B : vBooks)
		{
			bool IsExist = false;

			for (stMostBorrowedBook& MBB : vMostBorrowedBook)
			{
				if (MBB.Title == B.Title)
				{
					IsExist = true;
					break;
				}	
			}

			if (!IsExist)
			{
				stMostBorrowedBook Book;

				Book.Title = B.Title;
				Book.TimesBorrowed = TheNumberOfBorrowTheBook(B.BookID, vBooks);
				vMostBorrowedBook.push_back(Book);
			}
			
		}

		RerangeMostBorrowedBooks(vMostBorrowedBook);

		return vMostBorrowedBook;
	}
};

