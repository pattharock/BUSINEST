#include<iostream>
#include<iomanip>
#include<fstream>


//This introduces the program to the user
void Intro()
{
    cout<<endl<<endl<<endl;
    cout << setfill('*');
    cout << setw(27) << "CAP LTD" << setw(21) << "" << endl;
    cout << setw(31) << "Welcome to CAP" << setw(17) << "" << endl;
    cout << setfill(' ');
    cout << setw(38) <<"A place to manage your funds" << setw(10) << "" << endl;
    cout << setw(45) << "A place to make better financial decisions" << setw(3) << endl;
    cout << endl << endl;
    cout << "Please select the options below to get started : " << endl;
}

//This clears all the files
void CLEAR_ALL_FILES(){
    ofstream f1("Records.txt");
    f1.close();

    ofstream f2("Income_Statement.txt");
    f2.close();
}

//this displays all the options
int OPTIONS()
{
    int choice;
    cout<<endl<<endl<<endl;
    cout << "1. ADD A RECORD" << endl;
    cout << "2. DELETE A RECORD" << endl;
    cout << "3. DISPLAY ALL RECORDS" << endl;
    cout << "4. EDIT AN EXISTING RECORD" << endl;
    cout << "5. SEARCH EXISTING RECORD(S)" << endl;
    cout << "6. DISPLAY THE INCOME STATEMENT FOR CURRENT FISCAL PERIOD" << endl;
    cout << "7. VIEW THE CURRENT FINANCIAL RATIOS" <<endl;
    cout << "0. EXIT PROGRAM" << endl;
    cout << "YOUR CHOICE: ";
    cin >> choice;
    return choice;
}
