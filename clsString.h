#pragma once

#include <iostream>
#include<vector>

using namespace std;

class clsString
{

private:
    string _Value;


public:
    clsString()
    {
        _Value = "";

    }

    clsString(string Value)
    {
        _Value = Value;

    }

    void SetValue(string Value)
    {
        _Value = Value;
    }

    string GetValue()
    {
        return _Value;
    }

    __declspec(property(get = GetValue, put = SetValue)) string Value;


    static short Length(string S1)
    {
        return S1.length();
    }

    short Length()
    {
        return _Value.length();
    }

    static short CountWords(string S1)
    {
        string delim = " "; // delimiter
        short Counter = 0;
        short pos = 0;
        string sWord; // define a string variable

        // use find() function to get the position of the delimiters
        while ((pos = S1.find(delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos); // store the word

            if (sWord != "")
            {
                Counter++;
            }

            // erase() until position and move to next word
            S1.erase(0, pos + delim.length());
        }

        if (S1 != "")
        {
            Counter++; // counts the last word of the string
        }

        return Counter;
    }

    short CountWords()
    {
        return CountWords(_Value);
    }

    static string  UpperFirstLetterOfEachWord(string S1)
    {
        bool isFirstLetter = true;
        for (short i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ' && isFirstLetter)
            {
                S1[i] = toupper(S1[i]);
            }

            isFirstLetter = (S1[i] == ' ' ? true : false);
        }
        return S1;
    }

    void  UpperFirstLetterOfEachWord()
    {
        _Value = UpperFirstLetterOfEachWord(_Value);
    }

    static string  LowerFirstLetterOfEachWord(string S1)
    {
        bool isFirstLetter = true;
        for (short i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ' && isFirstLetter)
            {
                S1[i] = tolower(S1[i]);
            }

            isFirstLetter = (S1[i] == ' ' ? true : false);
        }
        return S1;
    }

    void  LowerFirstLetterOfEachWord()
    {
        _Value = LowerFirstLetterOfEachWord(_Value);
    }

    static string LowerAllString(string S1)
    {
        for (short i = 0; i < S1.length(); i++)
        {

            S1[i] = tolower(S1[i]);

        }

        return S1;
    }

    void LowerAllString()
    {
        _Value = LowerAllString(_Value);
    }

    static string UpperAllString(string S1)
    {

        for (short i = 0; i < S1.length(); i++)
        {

            S1[i] = toupper(S1[i]);

        }

        return S1;
    }

    void UpperAllString()
    {
        _Value = UpperAllString(_Value);
    }

    static char InvertLetterCase(char Char)
    {
        return isupper(Char) ? tolower(Char) : toupper(Char);

    }

    static string InvertAllLettersCase(string S1)
    {
        for (short i = 0; i < S1.length(); i++)
        {
            S1[i] = InvertLetterCase(S1[i]);
        }
        return S1;
    }

    void InvertAllLettersCase()
    {
        _Value = InvertAllLettersCase(_Value);
    }

    static short CountCapitalLetters(string S1)
    {
        int Counter = 0;
        for (short i = 0; i < S1.length(); i++)
        {

            if (isupper(S1[i]))
                Counter++;

        }
        return Counter;
    }

    short CountCapitalLetters()
    {
        return CountCapitalLetters(_Value);
    }

    static int CountSmallLetters(string S1)
    {
        int Counter = 0;
        for (short i = 0; i < S1.length(); i++)
        {

            if (islower(S1[i]))
                Counter++;

        }
        return Counter;
    }

    int CountSmallLetters()
    {
        return CountSmallLetters(_Value);
    }

    static int CountSpecificLetter(char Letter, string S1, bool MatchCase)
    {
        short Counter = 0;

        for (short i = 0; i < S1.length(); i++)
        {

            if (MatchCase)
            {
                if (S1[i] == Letter)
                    Counter++;
            }
            else
            {
                if (tolower(S1[i]) == tolower(Letter))
                    Counter++;
            }

        }

        return Counter;
    }

    int CountSpecificLetter(char Letter, bool MatchCase)
    {
        return CountSpecificLetter(Letter, _Value, MatchCase);
    }

    static bool IsVowel(char Char)
    {
        Char = tolower(Char);
        return (Char == 'a' || Char == 'o' ||
            Char == 'u' || Char == 'i' || Char == 'e');

    }

    static int CountVowels(string S1)
    {
        int Counter = 0;
        for (short i = 0; i < S1.length(); i++)
        {
            if (IsVowel(S1[i]))
                Counter++;
        }
        return Counter;
    }

    int CountVowels()
    {
        return CountVowels(_Value);
    }

    static vector<string> Split(string S1, string delim)
    {
        vector<string> vSplit;

        int pos = 0;
        string word;

        while ((pos = S1.find(delim)) != std::string::npos)
        {
            word = S1.substr(0, pos);

            if (word != "")
            {
                vSplit.push_back(word);
            }

            S1.erase(0, pos + delim.length());

        }

        if (S1 != "")
        {
            vSplit.push_back(S1);
        }

        return vSplit;

    }

    vector<string> Split(string delim)
    {
        return Split(_Value, delim);
    }

    static string TrimLeft(string S1)
    {

        for (int i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ')
            {
                return S1.substr(i);

            }

        }

        return "";
    }

    void TrimLeft()
    {
        _Value = TrimLeft(_Value);
    }

    static string TrimRight(string S1)
    {

        for (int i = S1.length() - 1; i > 0; i--)
        {
            if (S1[i] != ' ')
            {
                return S1.substr(0, i + 1);

            }

        }

        return "";
    }

    void TrimRight()
    {
        _Value = TrimRight(_Value);
    }

    static string Trim(string S1)
    {
        return TrimRight(TrimLeft(S1));
    }

    void Trim()
    {
        _Value = Trim(_Value);
    }

    static string JoinString(vector<string>vString, string delim)
    {
        string joinstring;

        for (string& element : vString)
        {
            joinstring += element + delim;

        }

        return joinstring.substr(0, joinstring.length() - delim.length());
    }

    static string JoinString(string arr[4], int length, string delim)
    {
        string joinstring;

        for (int i = 0; i < length; i++)
        {

            joinstring += arr[i] + delim;


        }

        return joinstring.substr(0, joinstring.length() - delim.length());


    }

    static string ReverseWordsInString(string S1)
    {
        vector<string>vString;

        vString = Split(S1, " ");

        string ReversedString = "";


        vector<string>::iterator iter = vString.end();

        while (iter != vString.begin())
        {
            --iter;
            ReversedString += *iter + " ";

        }

        return ReversedString.substr(0, ReversedString.length() - 1);

    }

    void ReverseWordsInString()
    {
        _Value = ReverseWordsInString(_Value);
    }

    static string ReplaceWord(string S1, string word, string otherword, bool MatchCase = true)
    {
        vector<string>vString;

        vString = Split(S1, " ");


        for (string& s : vString)
        {
            if (MatchCase == false)
            {
                if (LowerAllString(s) == LowerAllString(word))
                    s = otherword;

            }
            else
            {
                if (s == word)
                    s = otherword;

            }


        }

        return JoinString(vString, " ");
    }

    void ReplaceWord(string wordReplace, string ToReplace)
    {
        _Value = ReplaceWord(_Value, wordReplace, ToReplace);
    }

    static string RemovePunctuations(string S1)
    {
        string S;
        for (int i = 0; i < S1.length(); i++)
        {
            if (!ispunct(S1[i]))
                S += S[i];

        }
        return S;
    }

    void RemovePunctuations()
    {
        _Value = RemovePunctuations(_Value);
    }

};

;

