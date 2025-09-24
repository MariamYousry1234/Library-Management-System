#pragma once

#include <iostream>
#include <limits>
#include"clsDate.h"
using namespace std;


class clsInputValidate
{
public:

	template <typename T>
	static	bool IsNumberBetween(T Number, T From, T To)
	{

		return Number >= From && Number <= To;

	}


	static  bool IsDateBetween(clsDate Date, clsDate DateFrom, clsDate DateTo)
	{
		if (clsDate::CompareDates(DateFrom, DateTo) == clsDate::After)
		{
			clsDate::SwapDates(DateFrom, DateTo);
		}

		return ((clsDate::CompareDates(Date, DateFrom) == clsDate::After ||
			clsDate::CompareDates(Date, DateFrom) == clsDate::Equal)
			&&
			(clsDate::CompareDates(Date, DateTo) == clsDate::Before ||
				clsDate::CompareDates(Date, DateTo) == clsDate::Equal));
	}

	template <typename T>

	static  T ReadNumber(string message = "Invalid Number,Enter again:\n")
	{
		T Number = 0;

		while (true)
		{
			cin >> Number;
			if (!cin.fail())
				return Number;

			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << message;
		}


		return Number;
	}

	template<typename T>
	static  T ReadNumberBetween(T From, T To, string message = "Number is not within range, enter again:\n")
	{
		T Number = ReadNumber<T>();

		while (!IsNumberBetween<T>(Number, From, To))
		{
			cout << message;
			Number = ReadNumber<T>();
		}

		return Number;
	}


	static  bool IsValideDate(clsDate Date)
	{
		return clsDate::IsValidDate(Date);
	}

	static string ReadString()
	{
		string  S1 = "";
		// Usage of std::ws will extract allthe whitespace character
		getline(cin >> ws, S1);
		return S1;
	}
};

