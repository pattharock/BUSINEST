#include<iostream>
#include<string>

using namespace std;

int rid = 0;
int size = 5;

struct date
{
    int dd;        //day
    int mm;        //month
    int yy;        //year
};

struct record
{
    date d;            //date of transcation
    int rec_id;        //unique id of transaction
    string rec_title;  //name of the record
    string rec_type;     // income or expense
    string acc;        // Cash Accounts / Debit Card Account / Credit Card Account
    double amt;        //Transaction amount
    void transaction();
};

//This function is part of the structure of record where the user inputs all the data inside the record. After each function call, the record is incremented by one
void record::transaction()
{
    ++rid;
    cout<<endl<<endl<<endl;
    cout<<"Enter the date in dd/mm/yy format: ";
    cin>>d.dd>>d.mm>>d.yy;
    cout<<"The record id is : "<< rid <<endl;
    rec_id = rid;
    cin.ignore();
    cout<<"Enter the record title: " ;
    getline(cin,rec_title);
    cout<<"Enter the record type (Income / Expense): ";
    getline(cin,rec_type);
    cout<<"Enter the Account Name(Cash/Debit Card/Credit Card): ";
    getline(cin,acc);
    cout<<"Enter the amount: ";
    cin>>amt;
}
