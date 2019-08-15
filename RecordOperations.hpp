#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


// This function increases the size of the dynamic array by 2 times
void ENLARGE(record *&r, int &n)
{
    record * r_new = new record[n*2];
    for (int i = 0; i < n; i++)
    {
        r_new[i] = r[i];
    }
    delete [] r;
    r = r_new;
    n+=n;
}


//This function is used to add a record to the dynamic array
void ADD_RECORD(record *&r, int &n)
{
    if(rid>=n)  //enlarges the size of the array if number of records are greater than the arrray size
    {
        ENLARGE(r, n);
    }
    r[rid].transaction();  
    ofstream fout ("Records.txt", ios::app); //appends new records to the file
    if(fout.fail())
    {
        cout << "Error in opening file!" << endl;
        exit(1);
    }
    int ind = rid-1;
    fout << fixed << setprecision(2) << r[ind].d.dd << "/" <<fixed << setprecision(2) << r[ind].d.mm << "/" << r[ind].d.yy << " " << rid << " " << r[ind].rec_title << " " << r[ind].rec_type << " " << r[ind].acc << " " << r[ind].amt << endl;
    fout.close();
}


//This function is used to delete a record from the array by reducing array size by 1 and using pointers for deletion.
void DELETE_RECORD(record *&r, int &id, int &n)
{
    int rid_num;
    cout << endl << endl << endl;
    cout << "Please enter the id of the record you want to delete: ";
    cin >> rid_num;
    record * r_new = new record[n-1]; //since we are deleting a record, the array size decreases.
    for (int i = 0; i < id; i++)
    {
        if(i+1>=rid_num) 
        {
            if(i==id-1)
            {
                break;
            }
            r_new[i] = r[i+1];
            r_new[i].rec_id = i+1; //We keep on building the new array until it reaches the position of the deleted element. Afterwards, i-th element of the new array is equal to the (i+1)th of the old array since the new array has one less element.
        }
        else
        {
            r_new[i] = r[i];
        }
    }
    delete [] r;
    r = r_new;
    n-=1;
    id-=1;    //id and array size decreases by 1 since we are deleting an element.
    ofstream fout ("Records.txt");
    if (fout.fail())
    {
        cout << "Error in opening file!" << endl;
        exit(1);
    }
    for(int i = 0; i<id; ++i)
    {
        fout << fixed << setprecision(2) << r[i].d.dd << "/" << fixed << setprecision(2) << r[i].d.mm << "/" << r[i].d.yy << " " << i+1 << " " << r[i].rec_title << " " << r[i].rec_type << " " << r[i].acc << " " << r[i].amt << endl;
    }
    fout.close();
}


// This function is used to Display all the records in the array.
void DISPLAY_RECORDS()
{
    cout << endl << endl << endl;
    ifstream fin("Records.txt");
    string line;
    while(getline(fin,line))
    {
        cout<<line<<endl;
    }
    fin.close();
}

//This function is used to edit a previously entered record by searching for the RECORD ID of a particular record.
void EDIT_RECORD(record *&r,int &rid)
{
    cout << endl << endl << endl;
    cout << "Enter the RECORD ID of the record to edit: ";
    int recid, original = rid;
    cin>>recid;  //input the record id we want to edit.
    for(int i=0;i<rid;i++)
    {
        if(r[i].rec_id == recid)
        {
            cout<< "Record Found !" <<endl;
            rid = recid-1;  //we decrease rid by 1 in order to match the array index
            r[i].transaction();
            rid = original;
        }
    }
    ofstream fout ("Records.txt");  //since we updated the records, we update the record.txt file
    for(int i=0;i<rid;i++)
    {
        fout << r[i].d.dd << "/" << r[i].d.mm << "/" << r[i].d.yy << " " << i+1 << " " << r[i].rec_title << " " << r[i].rec_type << " " << r[i].acc << " " << r[i].amt << endl;
    }
    fout.close();
}

//Using this function records can be searched accourding to one field, and then multiple searches can be carried out within the previously searched records based on other fields, so that the user can narrow down to a single record or a group of records.
void MULTIPLE_SEARCH(record *&r, int rid)
{
    cout << endl << endl << endl;
    int dat, mon, year, choice, count=0;
    string title, type, acc;
    double amount;       //these are all the various parameters of our choices.
    vector<record>ls;
    cout << "1. Search by date" << endl;
    cout << "2. Search by title" << endl;
    cout << "3. Search by type" << endl;
    cout << "4. Search by acc" << endl;
    cout << "5. Search by amount" << endl;
    cout << "6. Start search again" << endl;
    cout << "To exit, enter -1" << endl;
    cout << "Choice: ";
    cin >> choice;
    cout << endl << endl << endl;
    while (true)   //count==1 is the first search. It scans the entire array and when the parameters match, the matching records are stored in the vector.
    {
        ++count;
        if(choice==1)
        {
            cout<<"Enter the date in dd/mm/yy format: ";
            cin >> dat >> mon >> year;
            cout << endl << endl << endl;
            if(count>1)   //When count is greater than 1, we are searching from the pool of records which matched the first search and were stored in the vectors. Hence, by this searching mechanism, we can isolate specific records by one parameter and search furthur using other parameters.
            {
                int c=ls.size(),d=0;
                for(int i=0;d<c;++i)
                {
                    if((ls[i].d.dd==dat) && (ls[i].d.mm==mon))
                    {
                        cout << ls[i].d.dd << "/" << ls[i].d.mm << "/" << ls[i].d.yy << " " << ls[i].rec_id << " " << ls[i].rec_title << " " << ls[i].rec_type << " " << ls[i].acc << " " << ls[i].amt << endl;
                    }
                    else
                    {
                        --i;
                        ls.erase(ls.begin()+d);
                        if(ls.empty())
                        {
                            cout << "No matching results!";
                        }
                    }
                    ++d;
                }
            }
            else if(count==1)  
            {
                int j = 0;
                for(int i=0;i<rid;++i)
                {
                    if((r[i].d.dd==dat) && (r[i].d.mm==mon)){
                        ++j;
                        ls.push_back(r[i]);
                        cout << r[i].d.dd << "/" << r[i].d.mm << "/" << r[i].d.yy << " " << i+1 << " " << r[i].rec_title << " " << r[i].rec_type << " " << r[i].acc << " " << r[i].amt << endl;
                    }
                }
                if(j==0)
                {
                    cout << "No matching results!" << endl;
                }
            }
        }
        else if(choice==2)
        {
            cout<<"Enter the record title: " ;
            cin >> title;
            if(count>1)
            {
                int c=ls.size(),d=0;
                for(int i=0;d<c;++i)
                {
                    if(ls[i].rec_title==title)
                    {
                        cout << ls[i].d.dd << "/" << ls[i].d.mm << "/" << ls[i].d.yy << " " << i+1 << " " << ls[i].rec_title << " " << ls[i].rec_type << " " << ls[i].acc << " " << ls[i].amt << endl;
                    }
                    else
                    {
                        --i;
                        ls.erase(ls.begin()+d);
                        if(ls.empty())
                        {
                            cout << "No matching results!";
                        }
                    }
                    ++d;
                }
            }
            else if(count==1)
            {
                int j=0;
                for(int i=0;i<rid;++i)
                {
                    if(r[i].rec_title==title)
                    {
                        ++j;
                        ls.push_back(r[i]);
                        cout << r[i].d.dd << "/" << r[i].d.mm << "/" << r[i].d.yy << " " << i+1 << " " << r[i].rec_title << " " << r[i].rec_type << " " << r[i].acc << " " << r[i].amt << endl;
                    }
                }
                if(j==0)
                {
                    cout << "No matching results" << endl;
                }
            }
        }
        else if(choice==3)
        {
            cout<<"Enter the record type (Income / Expense): ";
            cin >> type;
            if(count>1)
            {
                int c=ls.size(),d=0;
                for(int i=0;d<c;++i)
                {
                    
                    if(ls[i].rec_type==type)
                    {
                        cout << ls[i].d.dd << "/" << ls[i].d.mm << "/" << ls[i].d.yy << " " << ls[i].rec_id << " " << ls[i].rec_title << " " << ls[i].rec_type << " " << ls[i].acc << " " << ls[i].amt << endl;
                    }
                    else
                    {
                        --i;
                        ls.erase(ls.begin()+d);
                        if(ls.empty())
                        {
                            cout << "No matching results!";
                        }
                    }
                    ++d;
                }
            }
            else if(count==1)
            {
                int j=0;
                for(int i=0;i<rid;++i)
                {
                    if(r[i].rec_type==type)
                    {
                        ++j;
                        ls.push_back(r[i]);
                        cout << r[i].d.dd << "/" << r[i].d.mm << "/" << r[i].d.yy << " " << i+1 << " " << r[i].rec_title << " " << r[i].rec_type << " " << r[i].acc << " " << r[i].amt << endl;
                    }
                }
                if(j==0)
                {
                    cout << "No matching results!" << endl;
                }
            }
        }
        else if(choice==4)
        {
            cout<<"Enter the Account Name(Cash/Debit Card/Credit Card): ";
            cin >> acc;
            if(count>1)
            {
                int c=ls.size(),d=0;
                for(int i=0;d<c;++i)
                {
                    if(ls[i].acc==acc)
                    {
                        cout << ls[i].d.dd << "/" << ls[i].d.mm << "/" << ls[i].d.yy << " " << ls[i].rec_id << " " << ls[i].rec_title << " " << ls[i].rec_type << " " << ls[i].acc << " " << ls[i].amt << endl;
                    }
                    else
                    {
                        --i;
                        ls.erase(ls.begin()+d);
                        if(ls.empty())
                        {
                            cout << "No matching results!";
                        }
                    }
                }
                ++d;
            }
            else if(count==1)
            {
                int j=0;
                for(int i=0;i<rid;++i)
                {
                    if(r[i].acc==acc)
                    {
                        ++j;
                        ls.push_back(r[i]);
                        cout << r[i].d.dd << "/" << r[i].d.mm << "/" << r[i].d.yy << " " << i+1 << " " << r[i].rec_title << " " << r[i].rec_type << " " << r[i].acc << " " << r[i].amt << endl;
                    }
                }
                if(j==0)
                {
                    cout << "No matching results!" << endl;
                }
            }
        }
        else if(choice==5)
        {
            cout<<"Enter the amount: ";
            cin >> amount;
            if(count>1)
            {
                int c=ls.size(),d=0;
                for(int i=0;d<c;++i)
                {
                    if(ls[i].amt==amount)
                    {
                        cout << ls[i].d.dd << "/" << ls[i].d.mm << "/" << ls[i].d.yy << " " << ls[i].rec_id << " " << ls[i].rec_title << " " << ls[i].rec_type << " " << ls[i].acc << " " << ls[i].amt << endl;
                    }
                    else
                    {
                        --i;
                        ls.erase(ls.begin()+d);
                        if(ls.empty())
                        {
                            cout << "No matching results!";
                        }
                    }
                    ++d;
                }
            }
            else if(count==1)
            {
                int j=0;
                for(int i=0;i<rid;++i)
                {
                    if(r[i].amt==amount)
                    {
                        ++j;
                        ls.push_back(r[i]);
                        cout << r[i].d.dd << "/" << r[i].d.mm << "/" << r[i].d.yy << " " << i+1 << " " << r[i].rec_title << " " << r[i].rec_type << " " << r[i].acc << " " << r[i].amt << endl;
                    }
                }
                if(j==0)
                {
                    cout << "No matching results!" << endl;
                }
            }
        }
        else if(choice==6)
        {
            MULTIPLE_SEARCH(r,rid);   //recursion which repeats the process creating a new vector and restarting the search
        }
        else if(choice==-1)
        {
            ls.clear();  //clears the vector
            break;
        }
        cout << endl << endl << endl;
        cout << "1. Search by date" << endl;
        cout << "2. Search by title" << endl;
        cout << "3. Search by type" << endl;
        cout << "4. Search by acc" << endl;
        cout << "5. Search by amount" << endl;
        cout << "6. Start search again" << endl;
        cout << "To exit, enter -1" << endl;
        cout << "Choice: ";
        cin >> choice;
        cout << endl << endl << endl;
    }
}


//This functions either searches a single record by its RECORD ID or calls the previous funtion to implement multiple search
void SEARCH_RECORD(record *&r, int rid)
{
    int choice;
    cout << endl << endl << endl;
    cout << "Enter 1 to search a particular record through its record id." << endl;
    cout << "Enter 2 to search multiple records(or narrow down to one record)." << endl;
    cout << "Choice: ";
    cin >> choice;
    if(choice==1)
    {
        int sid;
        cout << endl << endl << endl;
        cout << "Enter record id: ";
        cin >> sid;
        for(int i=0;i<rid;++i)
        {
            if(r[i].rec_id==sid)
            {
                cout << r[i].d.dd << "/" << r[i].d.mm << "/" << r[i].d.yy << " " << i+1 << " " << r[i].rec_title << " " << r[i].rec_type << " " << r[i].acc << " " << r[i].amt << endl;
                break;
            }
        }
    }
    else if(choice==2)
    {
        MULTIPLE_SEARCH(r, rid);
    }
}

// This funtion is used to check the threshold limit and prompt user to either increase threshhold or continue.
void BALANCE_CHECK(record *&r, int rid, int &mc, int &md, int &mcc)
{
    int mc0=0, md0=0, mcc0=0;
    for(int i = 0;i<rid;++i)  //After every transaction, this function continuously checks whether the balances exceeded the giving limit or not.
    {
        if (r[i].rec_type=="Expense" && r[i].acc=="Cash")
        {
            mc0+=r[i].amt;
        }
        if (r[i].rec_type=="Expense" && r[i].acc=="Debit Card")
        {
            md0+=r[i].amt;
        }
        if (r[i].rec_type=="Expense" && r[i].acc=="Credit Card")
        {
            mcc0+=r[i].amt;
        }
    }
    if(mc0>mc)
    {
        int choice,inc;
        cout << "*WARNING!*" << endl;
        cout << "Limit crossed for maximum expense incurred by Cash!" << endl;
        cout << "Enter 1 to increase cash threshold or enter 2 to continue: " << endl;
        cout << "Choice: ";
        cin >> choice;
        if(choice==1)
        {
            cout << "Enter the amount by which you want to increase the threshold: ";
            cin >> inc;
            mc+=inc;
        }
        else
        {
            cout << "REMINDER: No warnings will be generated no matter how much cash expense increases" << endl;
        }
        
    }
    if(md0>md)
    {
        int choice, inc;
        cout << "*WARNING!*" << endl;
        cout << "Limit crossed for maximum expense incurred by Debit Card!" << endl;
        cout << "Enter 1 to increase debit card threshold or enter 2 to continue: " << endl;
        cout << "Choice: ";
        cin >> choice;
        if(choice==1)
        {
            cout << "Enter the amount by which you want to increase the threshold: ";
            cin >> inc;
            md+=inc;
        }
        else
        {
            cout << "REMINDER: No warnings will be generated no matter how much debit card expense increases" << endl;
        }
    }
    if(mcc0>mcc)
    {
        int choice,inc;
        cout << "*WARNING!*" << endl;
        cout << "Limit crossed for maximum expense incurred by Credit Card!" << endl;
        cout << "Enter 1 to increase credit card threshold or enter 2 to continue: " << endl;
        cout << "Choice: ";
        cin >> choice;
        if(choice==1)
        {
            cout << "Enter the amount by which you want to increase the threshold: ";
            cin >> inc;
            mcc+=inc;
        }
        else
        {
            cout << "REMINDER: No warnings will be generated no matter how much credit card expense increases" << endl;
        }
    }
}
