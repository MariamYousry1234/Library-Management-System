#pragma once


#include <iostream>
#include<string>
#include"clsDate.h"
using namespace std;

class clsUtil
{
public:

    static void Srand()
    {
        srand((unsigned)time(NULL));
    }

    static int RandomNumber(int From, int To)
    {

        int randNum = rand() % (To - From + 1) + From;
        return randNum;
    }

    enum enCharType { SmallLetter = 1, CapitalLetter = 2, SpecialCharacter = 3, Digit = 4, MixChars = 5 };

    static char GetRandomCharacter(enCharType CharType)
    {
        if (CharType == enCharType::MixChars)
        {
            CharType = (enCharType)RandomNumber(1, 4);
        }
        switch (CharType)
        {
        case enCharType::SmallLetter:
            return char(RandomNumber(97, 122));
            break;

        case enCharType::CapitalLetter:
            return char(RandomNumber(65, 90));
            break;

        case enCharType::SpecialCharacter:
            return char(RandomNumber(33, 47));
            break;

        case enCharType::Digit:
            return char(RandomNumber(48, 57));
            break;

        }

    }

    static string GenerateWord(enCharType CharType, short Length)
    {
        string Key = "";
        for (int i = 1; i <= Length; i++)
        {
            Key += GetRandomCharacter(CharType);
        }

        return Key;
    }

    static string GenerateKey(enCharType CharType = CapitalLetter)
    {
        string FullKey = "";

        FullKey += GenerateWord(CharType, 4) + "-";
        FullKey += GenerateWord(CharType, 4) + "-";
        FullKey += GenerateWord(CharType, 4) + "-";
        FullKey += GenerateWord(CharType, 4);

        return FullKey;
    }

    static void GenerateKeys(int Length, enCharType CharType)
    {
        cout << "\n";
        for (int i = 1; i <= Length; i++)
            cout << "Key [" << i << "]:" << GenerateKey(CharType) << endl;
    }

    template<typename T>
    static void  Swap(T& A, T& B)
    {
        T Temp;

        Temp = A;
        A = B;
        B = Temp;
    }


    /*

      static void Swap(double& A, double& B)
{
    double Temp;

    Temp = A;
    A = B;
    B = Temp;
}

static void Swap(string& A, string& B)
{
    string Temp;

    Temp = A;
    A = B;
    B = Temp;
}

static  void Swap(bool& A, bool& B)
{
    bool Temp;

    Temp = A;
    A = B;
    B = Temp;
}
    */


    static void Swap(clsDate& Date1, clsDate& Date2)
    {
        clsDate::SwapDates(Date1, Date2);
    }

    static void ShuffleArray(int arr[100], int arrLength)
    {

        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(i, arrLength - 1)], arr[RandomNumber(i, arrLength - 1)]);
        }
    }

    static void ShuffleArray(string arr[100], int arrLength)
    {

        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(i, arrLength - 1)], arr[RandomNumber(i, arrLength - 1)]);
        }
    }

    static void FillArrayWithRandomNumbers(int arr[100], short Length, short From, short To)
    {
        for (int i = 0; i < Length; i++)
        {
            arr[i] = RandomNumber(From, To);
        }
    }

    static void FillArrayWithRandomWords(string arr[100], short arrLength, enCharType CharType, short WordLength)
    {
        for (int i = 0; i < arrLength; i++)
        {
            arr[i] = GenerateWord(CharType, WordLength);
        }
    }

    static void FillArrayWithRandomKeys(string arr[100], short arrLength, enCharType CharType)
    {
        for (int i = 0; i < arrLength; i++)
        {
            arr[i] = GenerateKey(CharType);
        }
    }

    static string Tabs(short NumberOfTabs)
    {
        string t = "";

        for (int i = 1; i < NumberOfTabs; i++)
        {
            t = t + "\t";
            cout << t;
        }
        return t;
    }

    static string EncryptText(string Text, int EncryptionKey = 2)
    {
        string word = "";
        for (int i = 0; i < Text.length(); i++)
        {
            word += char(Text[i] + EncryptionKey);

        }
        return word;
    }

    static string DecryptText(string Text, int DecryptionKey = 2)
    {
        string word = "";
        for (int i = 0; i < Text.length(); i++)
        {
            word += char(Text[i] - DecryptionKey);

        }
        return word;
    }


    static bool IsPerfect(int Num)
    {
        int Sum = 0;
        for (int i = 1; i < Num; i++)
        {
            if (Num % i == 0)
                Sum += i;
        }


        return Num == Sum;
    }

    static int ReversedNumber(int Num)
    {
        int Number = 0;

        while (Num > 0)
        {
            Number *= 10;
            Number += Num % 10;
            Num = Num / 10;

        }

        return Number;
    }

    static bool IsPalendromeNumber(int Num)
    {
        return ReversedNumber(Num) == Num;

    }

    static bool IsPrime(int Num)
    {
        if (Num < 2)
            return false;

        int Number = round(Num / 2);

        for (int i = 2; i <= Number; i++)
        {
            if (Num % i == 0)
                return false;
        }

        return true;
    }

    static string NumberToText(int Number)
    {

        if (Number == 0)
        {
            return "";
        }

        if (Number >= 1 && Number <= 19)
        {
            string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
        "Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
          "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

            return  arr[Number] + " ";

        }

        if (Number >= 20 && Number <= 99)
        {
            string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
            return  arr[Number / 10] + " " + NumberToText(Number % 10);
        }

        if (Number >= 100 && Number <= 199)
        {
            return  "One Hundred " + NumberToText(Number % 100);
        }

        if (Number >= 200 && Number <= 999)
        {
            return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
        }

        if (Number >= 1000 && Number <= 1999)
        {
            return  "One Thousand " + NumberToText(Number % 1000);
        }

        if (Number >= 2000 && Number <= 999999)
        {
            return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
        }

        if (Number >= 1000000 && Number <= 1999999)
        {
            return  "One Million " + NumberToText(Number % 1000000);
        }

        if (Number >= 2000000 && Number <= 999999999)
        {
            return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
        }

        if (Number >= 1000000000 && Number <= 1999999999)
        {
            return  "One Billion " + NumberToText(Number % 1000000000);
        }
        else
        {
            return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
        }


    }



};






