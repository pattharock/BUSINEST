#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>


// This function is used to prepare an income statement for the current records and also save the income statement in a text file for further reference.
void SHOW_INCOME_STATEMENT( record *&r , int rid){
    cout << endl << endl << endl ;
    cout << "                 INCOME STATEMENT                 "<< endl;
    cout << "          For End of Current Fiscal Year          "<< endl;
    cout << setw(50) << left << "INCOME:- " << endl;
    double ni = 0;
    for( int i=0 ; i < rid ; i++){
        if(r[i].rec_type == "Income"){
            cout << setw(50) << left <<r[i].rec_title << right << r[i].amt <<endl;;
            ni += r[i].amt;
        }
    }
    cout<<endl;
    cout << setw(50) << left << "NET INCOME" << right << ni <<endl;
    cout << endl << endl;
    cout << setw(50) << left << "EXPENSES:- " << endl;
    double ne = 0;
    for( int i=0 ; i < rid ; i++){
        if(r[i].rec_type == "Expense"){
            cout << setw(50) << left <<r[i].rec_title << right << r[i].amt <<endl;;
            ne += r[i].amt;
        }
    }
    cout << endl ;
    cout << setw(50) << left << "NET EXPENSE" << right << ne <<endl;
    cout << endl << endl;
    
    if(ni>=ne){
        cout << setw(50) << left << "NET PROFIT" << right << fabs(ni - ne) << endl;
    }
    else{
        cout << setw(50) << left << "NET LOSS" << right << fabs(ni - ne) << endl;
    }
    
    ofstream f("Income_Statement.txt");
    f << "                 INCOME STATEMENT                 " << endl;
    f << "          For End of Current Fiscal Year          " << endl;
    f << setw(50) << left << "INCOME:- " << endl;
    double nif = 0;
    for( int i=0 ; i < rid ; i++){
        if(r[i].rec_type == "Income"){
            f << setw(50) << left <<r[i].rec_title << right << r[i].amt <<endl;;
            nif += r[i].amt;
        }
    }
    f<<endl;
    f << setw(50) << left << "NET INCOME" << right << nif <<endl;
    f << endl << endl;
    f << setw(50) << left << "EXPENSES:- " << endl;
    double nef = 0;
    for( int i=0 ; i < rid ; i++){
        if(r[i].rec_type == "Expense"){
            f << setw(50) << left <<r[i].rec_title << right << r[i].amt <<endl;;
            nef += r[i].amt;
        }
    }
    f << endl ;
    f << setw(50) << left << "NET EXPENSE" << right << ne <<endl;
    f << endl << endl;
    
    if(ni>=ne){
        f << setw(50) << left << "NET PROFIT" << right << fabs(nif - nef) << endl;
    }
    else{
        f << setw(50) << left << "NET LOSS" << right << fabs(nif - nef) << endl;
    }
    
    f.close();
    
}

// This function is used to compute and display the financial ratios based on the current records.
void FINANCIAL_RATIOS(record *&r,int rid){
    double cf = 0, ti = 0 , te = 0;
    for(int i = 0 ; i < rid ; i++){
        cf += r[i].amt;
        
        if (r[i].rec_type == "Income"){
            ti += r[i].amt;
        }
        
        if (r[i].rec_type == "Expense"){
            te += r[i].amt;
        }
    }
    
    double expenseratio = te/cf;
    double incomeratio = ti/cf;
    
    cout <<endl<<endl<<endl;
    
    cout << "Income Ratio i.e. percentage of Total Cash Flow as Income:  " << fixed << setprecision(2) << incomeratio*100<<endl;
    
    cout<<endl;
    
    cout << "Expense Ratio i.e. percentage of Total Cash Flow as Expense:  " << fixed << setprecision(2) << expenseratio*100<<endl;
    
    
}
