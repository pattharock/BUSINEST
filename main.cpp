#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "RecordDefinition.hpp"
#include "SecondaryFunctions.hpp"
#include "RecordOperations.hpp"
#include "IncomeStatement_and_Ratios.hpp"


int main()
{
    Intro();  //This function introduces the program to the user
    CLEAR_ALL_FILES();   //Empties the ratio file and the record file
    record * r = new record[size];   //dynamic array for storing the records
    int mc, md, mcc;
    cout << "Please enter threshold for maximum expense incurred by Cash: ";
    cin >> mc;    //threshold for cash expense
    cout << "Please enter threshold for maximum expense incurred by Debit Card: ";
    cin >> md;     //threshold for debit card expense
    cout << "Please enter threshold for maximum expense incurred by Credit Card: ";
    cin >> mcc;    //threshold for credit card expense
    int opt;

    //this will run until the user decides to end the program. The options menu as a result will tend to keep on appearing.
    while(true)
    {
        opt = OPTIONS();    //displays the options to the user
        if(opt==1)
        {
            ADD_RECORD(r, size);
        }
        if(opt==2)
        {
            if(rid==0)  //this is true if no records are added
            {
                cout <<"No records have been added!" << endl;
            }
            else
            {
                DELETE_RECORD(r, rid, size);
            }
        }
        if(opt==3)
        {
            if(rid==0)
            {
                cout <<"No records have been added!" << endl;
            }
            else
            {
                DISPLAY_RECORDS();
            }
        }
        if(opt==4)
        {   
            if(rid==0)
            {
                cout <<"No records have been added!" << endl;
            }
            else
            {    
                EDIT_RECORD(r,rid);
            }
        }
        if(opt==5)
        {
            if(rid==0)
            {
                cout <<"No records have been added!" << endl;
            }
            else
            {
                SEARCH_RECORD(r,rid);
            }
        }
        if (opt == 6){
            if(rid == 0)
            {
                cout <<"No records have been added!" << endl;
            }
            else
            {
                SHOW_INCOME_STATEMENT(r,rid);
            }
        }

        if(opt == 7){
            FINANCIAL_RATIOS(r,rid);
        }

        if(opt==0)   //This is a parting message if user decides to end the program
        {
            cout<<endl<<endl<<endl;
            cout<<"Thanks for using our program !!"<<endl;
            cout<<"See You Again !!"<<endl;
            break;
            exit(1);
        }
        BALANCE_CHECK(r,rid,mc,md,mcc);

    }
}
