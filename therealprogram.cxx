#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <string>
using namespace std;
//Class used in project
class account
{
    int acno;
    char name[50];
    int deposit;
    char type;
public:
void create_account();
void show_account()const;
void modify();
void dep(int);
void draw(int);
void report() const;
int retacno() const;
int retdeposit() const;
char rettype() const;
};
void account::create_account()
{
    cout<<"\nEnter The account No. :";
	cin>>acno;
	cout<<"\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;
	cout<<"\n\n\nAccount Created..";
}

void account::show_account() const
{
    cout<<"\nAccount No. : "<<acno;
    cout<<"\nAccount holder name : ";
    cout<<name;
    cout<<"\nType of account:"<<type;
    cout<<"\nBalanced Ammount"<<deposit;
} 
void account::modify()
{
    cout<<"\nAccount No.:"<<acno;
    cout<<"\nModify account holder name:";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\nModify type of account:";
    cin>>type;
    type=toupper(type);
    cout<<"\nModify balanced amount:";
    cin>>deposit;
}
void account::dep(int x)
{
    deposit+=x;
}
void account::draw(int x)
{
    deposit-=x;
}
void account::report() const
{
    cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}
int account::retacno() const
{
    return acno;
}
int account::retdeposit() const
{
    return deposit;
}
char account::rettype() const
{
    return type;
}
//this is the function declaration
void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw (int,int);
void intro();
int main()
{
    char ch;
    int num;
    intro();
    do
    {
        system("cls");
        cout<<"\n\n\n\tMain Menu";
        cout<<"\n\n\t01.New account";
        cout<<"\n\n\t02.Deposit amount";
        cout<<"\n\n\t03.withdraw ammount";
        cout<<"\n\n\t04.Balanced enquiry";
        cout<<"\n\n\t05.All account holder list";
        cout<<"\n\n\t06.Close an account";
        cout<<"\n\n\t07.modify an account";
        cout<<"\n\n\t08.Exit";
        cout<<"\n\n\tSelect your option (1-8)";
        cin>>ch;
        switch(ch)
        {
            case '1': write_account(); break;
            case '2':cout<<"\n\n\tEnter The account No. : "; cin>>num;
            deposit_withdraw(num,1);
            break;
            case '3':cout<<"\n\n\tEnter the account No.:  "; cin>>num;
            deposit_withdraw(num,2); break;
            case '4':cout<<"\n\n\tEnter the account No.:";cin>>num;
            display_sp(num); break;
            case '5':display_all(); break;
            case '6':cout<<"\n\n\tEnter the account No.:";cin>>num;
            delete_account(num); break;
            case '7':cout<<"\n\n\tEnter the account No.:";cin>>num;
            modify_account(num); break;
            case '8':cout<<"\n\n\tThanks for using bank managment:";
            break; default:cout<<"\a";
        }
        cin.ignore();
        cin.get();
    }while(ch!='8');
    return 0;   
}
//Now its the function to write in file
void write_account()
{
    account ac;
    ofstream outfile;
    outfile.open("account.dat",ios::binary|ios::app);
    ac.create_account();
    outfile.write(reinterpret_cast<char*>(&ac), sizeof(account));
    outfile.close();
}
//function to read specify record from file
void display_sp (int n)
{
    account ac;
    bool flag=false;
    ifstream infile;
    infile.open("account.dat",ios::binary);
    if(!infile)
    {
       cout<<"File could not be open, press any key";
       return; 
    }
    cout<<"\nBalanced detail\n";
    while(infile.read(reinterpret_cast<char*>(&ac),sizeof(account)))
    {
        if(ac.retacno()==n)
        {
            ac.show_account();
            flag=true;
        }
    }
    infile.close();
    if(flag==false)
    cout<<"\n\nAccount number does not exist";
}
//to modify the record of the file
void modify_account (int n)
{
    bool found=false;
    account ac;
    fstream file;
    file.open("account.dat",ios::binary|ios::in|ios::out);
    if(!file)
    {
        cout<<"File could not open, press any key.";
        return;
    }
    while(file.eof()&&found==false)
    {
        file.read(reinterpret_cast<char*>(&ac),sizeof(account));
        if(ac.retacno()==n)
        {
            ac.show_account();
            cout<<"\n\nEnter the details of the account!";
            ac.modify();
            int pos=(-1)*static_cast<int>(sizeof(account));
            file.seekp (pos,ios::cur);
            file.write(reinterpret_cast<char*>(&ac), sizeof(account));
            cout<<"\n\n\tRecord updated";
            found=true;
        }
    }
    file.close();
    if(found==false)
    cout<<"\n\nRecord not found";
}
//Deletes record of the file
void delete_account(int n)
{
    account ac;
    ifstream infile;
    ofstream outfile;
    infile.open("account.dat",ios::binary);
    if(!infile)
    {
        cout<<"file could not be open, press any key";
        return;
    }
    outfile.open("tempt.dat", ios::binary);
    infile.seekg(0,ios::beg);
    while(infile.read(reinterpret_cast<char*>(&ac),sizeof (account)))
    {
        if(ac.retacno()!=n)
        {
            outfile.write(reinterpret_cast<char*>(&ac),sizeof(account));
        }
    }
    infile.close();
    outfile.close();
    remove("account.dat");
    rename("temp.dat","account.dat");
    cout<<"\n\n\tRecord deleted";
}
//To display all account deposit list
void display_all()
{
    account ac;
    ifstream infile;
    infile.open("amount.dat",ios::binary);
    if(!infile)
    {
        cout<<"File could not open, press anykey";
        return;
    }
    cout<<"\n\n\t\tAccount holder list\n\n";
    cout<<"=============================================\n";
    cout<<"A/c No.        Name           type balanced\n";
    cout<<"=============================================\n";
    while (infile.read(reinterpret_cast<char*>(&ac),sizeof(account)))
    {
        ac.report();
    }
    infile.close();
}
//This function is for deposit and withdraw the ammounts
void deposit_withdraw(int n, int option)
{
    int amt;
    bool found=false;
    account ac;
    fstream file;
    file.open("account.dat",ios::binary|ios::in|ios::out);
    if(!file)
    {
        cout<<"file could not open, press any key";
        return;
    }
    while(!file.eof()&&found==false)
    {
        file.read(reinterpret_cast<char*>(&ac),sizeof(account));
        if(ac.retacno()==n)
        {
            ac.show_account();
            if(option==1)
            {
                cout<<"\n\n\tDeposit amount";
                cout<<"\n\nEnter the amount to be deposited";
                cin>>amt;
                ac.dep(amt);
            }
            if(option==2)
            {
                cout<<"\n\n\tTo withdraw amount";
                cout<<"\n\nEnter the amount to be withdraw";
                cin>>amt;
                int bal=ac.retdeposit()-amt;
                if((bal<500&&ac.rettype()=='s')||(bal<1000&&ac.rettype()=='c'))
                cout<<"insufficience balance";
                else ac.draw(amt);
            }
            int pos=(-1)*static_cast<int>(sizeof(ac));
            file.seekp(pos,ios::cur);
            file.write(reinterpret_cast<char*>(&ac),sizeof(account));
            cout<<"\n\n\tRecord updated";
            found=true;
        }
    }
    file.close();
    if(found==false)
    cout<<"\n\nRecord not found";
}
//introduction function
void intro()
{
    cout<<"\n\n\n\tBank";
    cout<<"\n\n\tManagement";
    cout<<"\n\n\tSystem";
    cout<<"\n\n\n\nMade by: Literly me";
    cout<<"\n\nNew to this";
    cin.get();
}
//Yup thats all