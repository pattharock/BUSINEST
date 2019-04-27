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
    Intro();
    CLEAR_ALL_FILES();
    record * r = new record[size];
    int mc, md, mcc;
    cout << "Please enter threshold for maximum expense incurred by Cash: ";
    cin >> mc;
    cout << "Please enter threshold for maximum expense incurred by Debit Card: ";
    cin >> md;
    cout << "Please enter threshold for maximum expense incurred by Credit Card: ";
    cin >> mcc;
    int opt;
    while(true)
    {
        opt = OPTIONS();
        if(opt==1)
        {
            ADD_RECORD(r, size);
        }
        if(opt==2)
        {
            if(rid==0)
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
            EDIT_RECORD(r,rid);
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
        
        if(opt==0)
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
