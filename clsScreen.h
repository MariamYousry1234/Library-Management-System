#pragma once

#include <iostream>
#include"clsDate.h"

using namespace std;
class clsScreen
{
protected:


    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {

        cout << "\n\t\t\t_________________________________________";
        cout << "\n\n\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t_________________________________________\n\n";
        cout << "\n\t\t\tDate: " << clsDate::DateToString(clsDate()) << endl << endl;
    }


};

