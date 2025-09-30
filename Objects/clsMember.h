#pragma once

#include <iostream>
#include"Objects/clsPerson.h"
#include<fstream>
#include<string>
#include<vector>
#include"Libraries/clsString.h"

using namespace std;

class clsMember :public clsPerson
{
	enum enMode { EmptyMode = 1, UpdateMode = 2, AddNew = 3 };
	enMode _Mode;


	string _ID;

	bool _MarkForDelete = false;

	string _ConvertObjectToLine(clsMember Member, string Separator = "###")
	{
		string Line;

		Line += Member.ID() + Separator;
		Line += Member.FirstName + Separator;
		Line += Member.LastName + Separator;
		Line += Member.Email+ Separator;
		Line += Member.PhoneNumber ;

		return Line;
	}

	static clsMember _ConvertLineToMemberObject(string Line, string Separator = "###")
	{
		vector<string>vMember;

		vMember = clsString::Split(Line, Separator);


		return clsMember(enMode::UpdateMode, vMember[0], vMember[1], vMember[2], vMember[3], vMember[4]);

	}

	static vector<clsMember>_LoadMembersDataFromFile()
	{
		vector<clsMember>vMembers;

		fstream MembersFile;

		MembersFile.open("Members.txt", ios::in);

		if (MembersFile.is_open())
		{
			string Line;

			while (getline(MembersFile, Line))
			{
				clsMember Member = _ConvertLineToMemberObject(Line);

				vMembers.push_back(Member);
			}

			MembersFile.close();
		}

		return vMembers;
	}

	static clsMember _GetEmptyObject()
	{
		return clsMember(enMode::EmptyMode, "", "", "", "", "");
	}

	void _SaveMemberDataToFile(vector<clsMember>vMembers)
	{
		fstream MembersFile;

		MembersFile.open("Members.txt", ios::out);

		if (MembersFile.is_open())
		{
			for (clsMember M : vMembers)
			{
				if (M.MarkForDelete != true)
					MembersFile << _ConvertObjectToLine(M) << endl;
			}

			MembersFile.close();
		}


	}

	void _Update()
	{
		vector<clsMember>vMembers;
		vMembers = _LoadMembersDataFromFile();

		for (clsMember& M : vMembers)
		{
			if (M.ID() == this->_ID)
			{
				M = *this;
				break;
			}
		}
		_SaveMemberDataToFile(vMembers);
	}

	void _AddMemberToFile(clsMember Member)
	{
		fstream MembersFile;

		MembersFile.open("Members.txt", ios::out | ios::app);

		if (MembersFile.is_open())
		{

			MembersFile << _ConvertObjectToLine(Member) << endl;

			MembersFile.close();
		}

	}

	void _AddNewMember()
	{
		_AddMemberToFile(*this);
	}

	void _DeleteMember()
	{
		vector<clsMember>vMembers;
		vMembers = _LoadMembersDataFromFile();

		for (clsMember& M : vMembers)
		{
			if (M.ID() == this->_ID)
			{
				M.MarkForDelete = true;
				break;
			}
		}

		_SaveMemberDataToFile(vMembers);
		*this = _GetEmptyObject();
	}
public:
	clsMember(enMode Mode,string ID, string FirstName, string LastName, string Email,
		string PhoneNumber) :clsPerson(FirstName, LastName, Email, PhoneNumber)
	{
		_Mode = Mode;
		_ID = ID;
	}

	string ID()
	{
		return _ID;
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

	void SetMarkForDelete(bool MarkForDelete)
	{
		_MarkForDelete = MarkForDelete;
	}

	bool GetMarkForDelete()
	{
		return _MarkForDelete;
	}

	__declspec(property(get = GetMarkForDelete, put = SetMarkForDelete))bool MarkForDelete;

	static vector<clsMember> GetMembersList()
	{
		return _LoadMembersDataFromFile();
	}

	static clsMember SearchByID(string ID)
	{
		fstream MembersFile;

		MembersFile.open("Members.txt", ios::in);

		if (MembersFile.is_open())
		{
			string Line;

			while (getline(MembersFile, Line))
			{
				
					clsMember Member = _ConvertLineToMemberObject(Line);

					if (Member.ID() == ID)
					{
						MembersFile.close();
						return Member;
					}
				
				
			}

			MembersFile.close();
		}

		return _GetEmptyObject();
	}

	static clsMember SearchByName(string Name)
	{
		string UserName = clsString::LowerAllString(Name);

		fstream MembersFile;

		MembersFile.open("Members.txt", ios::in);

		if (MembersFile.is_open())
		{
			string Line;

			while (getline(MembersFile, Line))
			{
				clsMember Member = _ConvertLineToMemberObject(Line);

				if (clsString::LowerAllString(Member.GetFullName()) == UserName)
				{
					MembersFile.close();
					return Member;
				}
			}

			MembersFile.close();
		}

		return _GetEmptyObject();
	}

	static clsMember SearchByEmail(string Email)
	{
		fstream MembersFile;

		MembersFile.open("Members.txt", ios::in);

		if (MembersFile.is_open())
		{
			string Line;

			while (getline(MembersFile, Line))
			{
				clsMember Member = _ConvertLineToMemberObject(Line);

				if (Member.Email == Email)
				{
					MembersFile.close();
					return Member;
				}
			}

			MembersFile.close();
		}

		return _GetEmptyObject();
	}

	static bool IsMemberExist(string ID)
	{
		clsMember Member = SearchByID(ID);

		return (!Member.IsEmpty());
	}

	static clsMember GetObjectWithModeAddNew(string ID)
	{
		return clsMember(enMode::AddNew, ID, "", "", "", "");
	}

	enum enSave { SavedSuccessfully = 1, FailedEmptyObject = 2, FailedObjectExist = 3 };

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
			if (IsMemberExist(ID()))
				return FailedObjectExist;

			_AddNewMember();
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
			_DeleteMember();
			return true;
		}
		return false;
	}

	static int TotalNumbersOfMembers()
	{
		return _LoadMembersDataFromFile().size();
	}

	
};

