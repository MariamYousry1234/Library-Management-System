#pragma once
#include <iostream>
#include <string>
#include"Objects/clsBook.h"
#include"Objects/clsMember.h"
#include"Libraries/clsDate.h"
#include "Libraries/clsString.h"
#include <queue>
#include<fstream>
#include <vector>
#include "Objects/clsBorrowReturn.h"


using namespace std;

class clsReservations
{

private:

	enum enMode{EmptyMode=1,UpdateMode=2,AddNewMode=3,CancelMode=4};
	enMode _Mode;


	string _ReservationID;
	string _BookID;
	string _MemberID;
	string  _ReservationDate;

	enum enStatus;
	enStatus _Status;

	

	static enStatus GetEnumStatus(string Status)
	{
		string status = clsString::LowerAllString(Status);

		if (status == "active")
			return enStatus::Active;

		if (status == "completed")
			return enStatus::Completed;

		if (status == "waiting")
			return enStatus::Waiting;

		if (status == "cancelled")
			return enStatus::Cancelled;

		return enStatus::Empty;
	}

	static clsReservations _ConvertLineToReservationObject(string Line, string Separator = "|")
	{
		vector<string>vReservation;

		vReservation = clsString::Split(Line, Separator);


		return clsReservations(enMode::UpdateMode,vReservation[0], vReservation[1], vReservation[2],
			vReservation[3], GetEnumStatus(vReservation[4]));

	}

	static vector<clsReservations>_LoadReservationsDataFromFile()
	{
		vector<clsReservations>vReservations;

		fstream MyFile;

		MyFile.open("Reservations.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsReservations Reservation = _ConvertLineToReservationObject(Line);

				vReservations.push_back(Reservation);
			}

			MyFile.close();
		}

		return vReservations;
	}

	static string _ConvertObjectToLine(clsReservations Reservation, string Separator = "|")
	{
		string Line;

		Line += Reservation.ReservationID+ Separator;
		Line += Reservation.BookID + Separator;
		Line += Reservation.MemberID + Separator;
		Line += Reservation.ReservationDate + Separator;
		Line += GetStringStatus(Reservation.Status);

		return Line;
	}

	static void _SaveReservationToFile(clsReservations Reservation)
	{
		fstream MyFile;

		MyFile.open("Reservations.txt", ios::in | ios::app);

		if (MyFile.is_open())
		{

			MyFile << _ConvertObjectToLine(Reservation) << endl;

			MyFile.close();
		}

	}

	static clsReservations _GetEmptyObject()
	{
		return clsReservations(enMode::EmptyMode,"", "", "", "", enStatus::Empty);
	}

	 void _SaveReservationToQueueLine(clsReservations Reservation)
	{
		 clsQueueLine Queue;
		
		 Queue.AddToQueue(Reservation);
	
	}

	static void _UpdateReservations(vector<clsReservations>vReservations)
	{
		fstream MyFile;

		MyFile.open("Reservations.txt", ios::out);

		if (MyFile.is_open())
		{
			for (clsReservations & R : vReservations)
			{
				MyFile << _ConvertObjectToLine(R) << endl;
			}
			

			MyFile.close();
		}
	}

	void _AddReservationToFile()
	{
		this->ReservationDate = clsDate::DateToString(_SystemDate);

		enStatus Status;
		if (IsBookReservedBefore(this->BookID))
			this->Status = enStatus::Waiting;
		else
			this->Status = enStatus::Active;

		_SaveReservationToFile(*this);

		_SaveReservationToQueueLine(*this);

	}

	void _ChangeToComplete()
	{
		vector<clsReservations>vReservations = _LoadReservationsDataFromFile();

		for (clsReservations& R : vReservations)
		{
			if (R.GetReservationID() == this->GetReservationID())
			{
				R.Status = enStatus::Completed;
			}

			//Change Second person for this book to Active status
			if (R.BookID == this->BookID && R.Status == enStatus::Waiting)
			{
				R.Status = enStatus::Active;
				break;
			}
		}

		_UpdateReservations(vReservations);
		

		clsQueueLine Queue;

		Queue.RemoveFromQueueFile(this->BookID, this->MemberID);

	}

	void _ChangeToCancelled()
	{
		vector<clsReservations>vReservations = _LoadReservationsDataFromFile();

		bool IsActive = false;

		for (clsReservations & R : vReservations)
		{
			if (R.GetReservationID() == this->GetReservationID())
			{
				if (R.Status == enStatus::Waiting)
					R.Status = enStatus::Cancelled;


				if (R.Status == enStatus::Active)
				{
					R.Status = enStatus::Cancelled;
					IsActive = true;
				}

				break;
			}
		}

		//Change Second person for this book to Active status
		if (IsActive)
		{
			for (clsReservations& R : vReservations)
			{
				if (R.BookID == this->BookID && R.Status == enStatus::Waiting)
				{
					R.Status = enStatus::Active;
					break;
				}
			}
		}

		_UpdateReservations(vReservations);

		clsQueueLine Queue;

		Queue.RemoveFromQueueFile(this->BookID, this->MemberID);
	}

	clsDate _SystemDate = clsDate::GetSystemDate();

public:

	class clsQueueLine
	{


		enum enMode { EmptyMode = 1, UpdateMode = 2, AddNewMode = 3 };
		enMode _Mode;

		string _QueueID;
		string _BookID;
		string _MemberID;
		string _ReservationDate;
		string _Status;

		static clsQueueLine _ConvertLineToQueueObject(string Line, string Separator = "|")
		{
			vector<string>Queue;

			Queue = clsString::Split(Line, Separator);

			return clsQueueLine(enMode::UpdateMode, Queue[0], Queue[1], Queue[2], Queue[3], Queue[4]);

		}

		static queue<clsQueueLine>_LoadQueueDataFromFile()
		{
			queue<clsQueueLine>QueueLine;

			fstream MyFile;

			MyFile.open("QueueLineReservation.txt", ios::in);

			if (MyFile.is_open())
			{
				string Line;

				while (getline(MyFile, Line))
				{
					clsQueueLine Queue = _ConvertLineToQueueObject(Line);

					QueueLine.push(Queue);
				}

				MyFile.close();
			}

			return QueueLine;
		}

		string _ConvertReservationObjectToQueueLine(clsReservations Reservation, string Separator = "|")
		{
			queue<clsQueueLine>Queue = _LoadQueueDataFromFile();
			string Line;

			Line += to_string(Queue.size() + 1) + Separator;
			Line += Reservation.GetBookID() + Separator;
			Line += Reservation.GetMemberID() + Separator;
			Line += Reservation.GetReservationDate() + Separator;
			Line += "Waiting";

			return Line;
		}

		string  _ConvertQueueObjectToQueueLine(clsQueueLine QueueLine,int Counter, string Separator = "|")
		{
			queue<clsQueueLine>Queue = _LoadQueueDataFromFile();
			string Line;

			Line += to_string(Counter) + Separator;
			Line += QueueLine.GetBookID() + Separator;
			Line += QueueLine.GetMemberID() + Separator;
			Line += QueueLine.GetReservationDate() + Separator;
			Line += "Waiting";

			return Line;
		}

		void _SaveQueueToFile(clsReservations Reservation)
		{
			fstream MyFile;

			MyFile.open("QueueLineReservation.txt", ios::in | ios::app);

			if (MyFile.is_open())
			{

				MyFile << _ConvertReservationObjectToQueueLine(Reservation) << endl;

				MyFile.close();
			}

		}

		static clsQueueLine _GetEmptyObject()
		{
			return clsQueueLine(enMode::EmptyMode, "", "", "", "", "");
		}

	public:
		clsQueueLine()
		{

		}

		clsQueueLine(enMode Mode, string QueueID, string BookID, string MemberID,
			string ReservationDate, string Status)
		{
			_Mode = Mode;
			_QueueID = QueueID;
			_BookID = BookID;
			_MemberID = MemberID;
			_ReservationDate = ReservationDate;
			_Status = Status;
		}

		bool IsEmpty()
		{
			return _Mode == enMode::EmptyMode;
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

		string QueueID()
		{
			return _QueueID;
		}

		void SetBookID(string BookID)
		{
			_BookID = BookID;
		}

		string GetBookID()
		{
			return _BookID;
		}

		__declspec(property(get = GetBookID, put = SetBookID))string BookID;

		void SetMemberID(string MemberID)
		{
			_MemberID = MemberID;
		}

		string GetMemberID()
		{
			return _MemberID;
		}

		__declspec(property(get = GetMemberID, put = SetMemberID))string MemberID;

		void SetReservationDate(string ReservationDate)
		{
			_ReservationDate = ReservationDate;

		}

		string GetReservationDate()
		{
			return _ReservationDate;
		}

		__declspec(property(get = GetReservationDate, put = SetReservationDate))string ReservationDate;

		void SetStatus(string Status)
		{
			_Status = Status;
		}

		string GetStatus()
		{
			return _Status;
		}

		__declspec(property(get = GetStatus, put = SetStatus))string Status;

		static clsQueueLine IsReservationExistBefore(string BookID, string MemberID)
		{
			queue<clsQueueLine>Queue = _LoadQueueDataFromFile();

			if (Queue.empty())
				return _GetEmptyObject();


			while (!Queue.empty())
			{
				if (Queue.front().BookID == BookID && Queue.front().MemberID == MemberID)
					return  Queue.front();
				Queue.pop();
			}

			return _GetEmptyObject();
		}

		void AddToQueue(clsReservations Reservation)
		{
			_SaveQueueToFile(Reservation);
		}

		static queue<clsQueueLine>GetFullQueueForBook(string BookID)
		{
			queue<clsQueueLine>QueueLine;

			fstream MyFile;

			MyFile.open("QueueLineReservation.txt", ios::in);

			if (MyFile.is_open())
			{
				string Line;

				while (getline(MyFile, Line))
				{
					clsQueueLine Queue = _ConvertLineToQueueObject(Line);

					if (Queue.BookID == BookID)
					{
						QueueLine.push(Queue);
					}

				}
				MyFile.close();
			}

			return QueueLine;
		}

		static int GetNumberOfMemberQueue(string MemberID, string BookID)
		{
			queue<clsQueueLine>QueueLine = GetFullQueueForBook(BookID);

			int Counter = 0;

			while (!QueueLine.empty())
			{
				Counter++;
				if (BookID == QueueLine.front().BookID && MemberID == QueueLine.front().MemberID)
					return Counter;
				QueueLine.pop();
			}

			return 0;
		}

		void RemoveFromQueueFile(string BookID, string MemberID)
		{
			queue<clsQueueLine>QueueLine = _LoadQueueDataFromFile();

			fstream MyFile;

			MyFile.open("QueueLineReservation.txt", ios::out);
			int counter = 1;
			if (MyFile.is_open())
			{

				while (!QueueLine.empty())
				{
					if (!(QueueLine.front().BookID == BookID &&
						QueueLine.front().MemberID == MemberID))
					{
						MyFile << _ConvertQueueObjectToQueueLine(QueueLine.front(), counter) << endl;
						counter++;
					}
					QueueLine.pop();
				}
				
				MyFile.close();
			}

		}


	};



public:
	
	clsReservations(enMode Mode,string ReservationID,string BookID,string MemberID,
		string ReservationDate,enStatus Status)
	{
		_Mode = Mode;
		_ReservationID = ReservationID;
		_BookID = BookID;
		_MemberID = MemberID;
		_ReservationDate = ReservationDate;
		_Status = Status;
	}

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	string GetReservationID()
	{
		return _ReservationID;
	}

	__declspec(property(get = GetReservationID)) string ReservationID;

	void SetMode(enMode Mode)
	{
		_Mode = Mode;
	}

	enMode GetMode()
	{
		return _Mode;
	}

	__declspec(property(get = GetMode, put = SetMode))enMode Mode;

	void SetBookID(string BookID)
	{
		_BookID = BookID;
	}

	string GetBookID()
	{
		return _BookID;
	}

	__declspec(property(get = GetBookID, put = SetBookID))string BookID;

	void SetMemberID(string MemberID)
	{
		_MemberID = MemberID;
	}

	string GetMemberID()
	{
		return _MemberID;
	}

	__declspec(property(get = GetMemberID, put = SetMemberID))string MemberID;

	 void SetReservationDate(string ReservationDate)
	{
		_ReservationDate = ReservationDate;
	}

	 string GetReservationDate()
	{
		return _ReservationDate;
	}

	__declspec(property(get = GetReservationDate, put = SetReservationDate))string ReservationDate;

	enum enStatus { Active = 1, Completed = 2, Waiting = 3, Cancelled = 4, Empty = 5 };

	void SetStatus(enStatus Status)
	{
		_Status = Status;
	}

	enStatus GetStatus()
	{
		return _Status;
	}

	__declspec(property(get = GetStatus, put = SetStatus))enStatus Status;

	static string GetStringStatus(enStatus Status)
	{
		switch (Status)
		{
		case enStatus::Active:
			return "Active";
		case enStatus::Completed:
			return "Completed";
		case enStatus::Waiting:
			return "Waiting";
		case enStatus::Cancelled:
			return "Cancelled";
		default:
			return "";
		}
	}

	static bool IsBookAvailable(string BookID)
	{
		clsBook Book = clsBook::SearchByID(BookID);

		return(!Book.IsEmpty() && Book.NumberOfCopies > 0);
	}

	static bool IsReservationExistBefore(string BookID, string MemberID)
	{
		 clsQueueLine queue = clsQueueLine::IsReservationExistBefore(BookID, MemberID);

		return(!queue.IsEmpty());		
	 }

	static bool IsBookReservedBefore(string BookID)
	{
		vector<clsReservations>vReservations=_LoadReservationsDataFromFile();

		for (clsReservations R : vReservations)
		{
			if (R.BookID == BookID && R.Status == enStatus::Active)
				return true;
		}
		return false;
	}

	static clsReservations FindByID(string ReservationID)
	{
		fstream MyFile;

		MyFile.open("Reservations.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsReservations Reservation = _ConvertLineToReservationObject(Line);

				if (Reservation.GetReservationID() == ReservationID)
				{
					MyFile.close();
					return Reservation;
				}
			
			}

			MyFile.close();
		}

		return _GetEmptyObject();
	}

	static bool IsIDExist(string ReservationID)
	{
		clsReservations Reservation = FindByID(ReservationID);

		return (!Reservation.IsEmpty());
	}

	static clsReservations FindByBook(string BookID)
	{
		fstream MyFile;

		MyFile.open("Reservations.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsReservations Reservation = _ConvertLineToReservationObject(Line);

				if (Reservation.BookID == BookID &&
					(Reservation.Status == enStatus::Waiting || Reservation.Status == enStatus::Active))
				{
					MyFile.close();
					return Reservation;
				}

			}

			MyFile.close();
		}

		return _GetEmptyObject();
	}

	static bool IsBookExist(string BookID)
	{
		clsReservations Reservation = FindByBook(BookID);

		return (!Reservation.IsEmpty());
	}

	static clsReservations FindByMember(string MemberID)
	{
		fstream MyFile;

		MyFile.open("Reservations.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsReservations Reservation = _ConvertLineToReservationObject(Line);

				if (Reservation.MemberID == MemberID &&
				(Reservation.Status == enStatus::Waiting || Reservation.Status == enStatus::Active))
				{
					MyFile.close();
					return Reservation;
				}

			}

			MyFile.close();
		}

		return _GetEmptyObject();
	}

	static bool IsMemberExist(string MemberID)
	{
		clsReservations Reservation = FindByMember(MemberID);

		return (!Reservation.IsEmpty());
	}

	static int GetNumberOfMemberQueue(string MemberID, string BookID)
	{
		return clsQueueLine::GetNumberOfMemberQueue(MemberID, BookID);
	}

	static bool IsCompleted(string ReservationID)
	{
		clsReservations Reservation = FindByID(ReservationID);

		return Reservation.Status == enStatus::Completed;
	}

	static bool IsCompleted(clsReservations Reservation)
	{
		return (!IsReservationExistBefore(Reservation.BookID, Reservation.MemberID));
	}

	static bool IsWating(string ReservationID)
	{
		clsReservations Reservation = FindByID(ReservationID);

		return Reservation.Status == enStatus::Waiting;
	}

	static bool IsCancelled(string ReservationID)
	{
		clsReservations Reservation = FindByID(ReservationID);

		return Reservation.Status == enStatus::Cancelled;
	}

	static string FirstInBookQueue(string BookID)
	{
		
		return clsQueueLine::GetFullQueueForBook(BookID).front().MemberID;
	}

	static clsReservations GetObjectWithAddNewMode(string ReservationID,string BookID,string MemberID)
	{
		return clsReservations(enMode::AddNewMode,ReservationID, BookID, MemberID, "", enStatus::Empty);
	}

	static void ChangeObjectToCancelMode(clsReservations &Reservation)
	{
		Reservation.Mode = enMode::CancelMode;
	
	}
	
	enum enSave{FailedMemberStillBorrowThisBook=1,FiledEmptyObject=2,
		FailedReservationExist=3,FailedBookAvailable=4,
		AddedSuccessfully=5,FailedObjectisCompleted=6, 
		FailedObjectisStillWaiting=7,FailedNoCopiedAvailable=8,
	    UpdatedSuccessfully=9, FailedObjectisCancelled=10,CancelledSuccessfully=11
	};

	enSave SaveToFile()
	{
		switch(_Mode)
		{
		case enMode::AddNewMode:
		{
			if (clsBorrowReturn::IsMemberBorrowBookBefore(GetMemberID(), GetBookID()))
			{
				return FailedMemberStillBorrowThisBook;
			}
			if (IsReservationExistBefore(GetBookID(),GetMemberID()))
			{
				return FailedReservationExist;
			}

			if (IsBookAvailable(GetBookID()))
			{
				return FailedBookAvailable;
			}
			_AddReservationToFile();
			_Mode = enMode::UpdateMode;
			return AddedSuccessfully;
		}
	    	break;

		case enMode::UpdateMode:
		{
			if (! IsIDExist(GetReservationID()))
			{
				return FiledEmptyObject;
			}

			if (IsCompleted(GetReservationID()))
			{
				return FailedObjectisCompleted;
			}

			if (IsWating(GetReservationID()))
			{
				return FailedObjectisStillWaiting;
			}

			if (clsBook::SearchByID(GetBookID()).NumberOfCopies == 0)
			{
				return FailedNoCopiedAvailable;	
			}

			_ChangeToComplete();
			return UpdatedSuccessfully;

		}
	    	break;

		case enMode::CancelMode:
		{
			if (!IsIDExist(GetReservationID()))
			{
				return FiledEmptyObject;
			}

			if (IsCancelled(GetReservationID()))
			{
				return FailedObjectisCancelled;
			}

			if (IsCompleted(GetReservationID()))
			{
				return FailedObjectisCompleted;
			}

			_ChangeToCancelled();
			return CancelledSuccessfully;
		}
		   break;

		return FiledEmptyObject;
		}
	}

	static vector<clsReservations>GetReservationsStillActive()
	{
		vector<clsReservations>vReservation = _LoadReservationsDataFromFile();
		vector<clsReservations>vActiveReservation;

		for (clsReservations& R : vReservation)
		{
			if (R.Status == enStatus::Active || R.Status == enStatus::Waiting)
				vActiveReservation.push_back(R);
			
		}
		return vActiveReservation;
	}

	static vector<clsReservations> GetAllReservationsByBook(string BookID)
	{
		vector<clsReservations>vReservation = _LoadReservationsDataFromFile();
		vector<clsReservations>vActiveReservationsByBook;

		for (clsReservations& R : vReservation)
		{
			if (R.BookID == BookID && 
				(R.Status == enStatus::Waiting || R.Status == enStatus::Active) )
				vActiveReservationsByBook.push_back(R);

		}
		return vActiveReservationsByBook;
	}

	static vector<clsReservations> GetAllReservationsByMember(string MemberID)
	{
		vector<clsReservations>vReservation = _LoadReservationsDataFromFile();
		vector<clsReservations>vActiveReservationsByMember;

		for (clsReservations& R : vReservation)
		{
			if (R.MemberID == MemberID &&
				(R.Status == enStatus::Waiting || R.Status == enStatus::Active))
				vActiveReservationsByMember.push_back(R);

		}
		return vActiveReservationsByMember;
	}
		
	static queue <clsQueueLine> GetQueueForABook(string BookID)
	{
		clsQueueLine Queue;
		return Queue.GetFullQueueForBook(BookID);
	}

	struct stActiveReservationMember
	{
		string MemberID;
		string MemberName;
	};

	static vector<stActiveReservationMember>GetActiveReservationMembers()
	{ 
		vector<stActiveReservationMember>vActiveReservationMembers;

		vector<clsReservations>vReservations = clsReservations::GetReservationsStillActive();

		for (clsReservations& R : vReservations)
		{
			stActiveReservationMember Member;

			Member.MemberID = R.MemberID;
			Member.MemberName = clsMember::SearchByID(R.MemberID).GetFullName();

			vActiveReservationMembers.push_back(Member);
		}

		return vActiveReservationMembers;
	}

	static int TotalReservations()
	{
		return _LoadReservationsDataFromFile().size();
	}

	static vector<clsReservations>GetReservationsByStatus(enStatus Status)
	{
		vector<clsReservations>vAllReservation = _LoadReservationsDataFromFile();
		vector<clsReservations>vReservation;

		for (clsReservations& R : vAllReservation)
		{
			if (R.Status == Status)
				vReservation.push_back(R);

		}
		return vReservation;
	}

};

