#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

class account
{
    int acno;
    char name[50];
    int deposit;
    char type;

public:
    void create_account();
    void show_account() const;
    void modify();
    void dep(int);
    void draw(int);
    int retacno() const;
    void report() const;
    int retdeposit() const;
    char rettype() const;
};

void account::create_account()
{
    system("CLS");
    cout << "\n\t\t\tEnter The Account Number : ";
    cin >> acno;
    cout << "\n\t\t\tEnter The Name Of The Account Holder : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\n\t\t\tEnter The Type Of Account (C / S) : ";
    cin >> type;
    type = toupper(type);
    cout << "\n\t\t\tEnter The Initial Amount : ";
    cin >> deposit;
    cout << "\n\t\t\tAccount Created....";
}

void account::show_account() const
{
    cout << "\n\t\t\tAccount No : " << acno;
    cout << "\n\t\t\tAccount Holder Name : " << name;
    cout << "\n\t\t\tType Of Account : " << type;
    cout << "\n\t\t\tBalance Amount : " << deposit;
}

void account::modify()
{
    cout << "\n\t\t\tAccount No : " << acno;
    cout << "\n\t\t\tModify Account Holder Name : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\n\t\t\tModify Type Of Account : ";
    cin >> type;
    type = toupper(type);
    cout << "\n\t\t\tModify Balance Amount : ";
    cin >> deposit;
}

void account::dep(int x)
{
    deposit += x;
}

void account::draw(int x)
{
    deposit -= x;
}

void account::report() const
{
    cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
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

void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);

int main()
{
    char ch;
    int num;

    do
    {
        system("CLS");
        cout << "\n\n\t\t\t\t----------------------------------------------------\n";
        cout << "\t\t\t\t               BANK MANAGEMENT SYSTEM";
        cout << "\n\n\t\t\t\t----------------------------------------------------\n";
        cout << "\t\t\t\t **MAIN MENU**\n";
        cout << "\n\t\t\t\t1> _NEW ACCOUNT_";
        cout << "\n\t\t\t\t2> _DEPOSIT AMOUNT_";
        cout << "\n\t\t\t\t3> _WITHDRAW AMOUNT_";
        cout << "\n\t\t\t\t4> _BALANCE CHECK_";
        cout << "\n\t\t\t\t5> _ALL ACCOUNT HOLDER LIST_";
        cout << "\n\t\t\t\t6> _CLOSE AN ACCOUNT_";
        cout << "\n\t\t\t\t7> _MODIFY AN ACCOUNT_";
        cout << "\n\t\t\t\t8> _EXIT_";
        cout << "\n\t\t\t\tSelect Your Option (1-8): ";
        cin >> ch;

        switch (ch)
        {
            case '1':
                write_account();
                break;

            case '2':
                system("CLS");
                cout << "\n\t\t\t\tEnter The Account Number : ";
                cin >> num;
                deposit_withdraw(num, 1);
                break;

            case '3':
                system("CLS");
                cout << "\n\t\t\t\tEnter The Account Number : ";
                cin >> num;
                deposit_withdraw(num, 2);
                break;

            case '4':
                system("CLS");
                cout << "\n\t\t\t\tEnter The Account Number : ";
                cin >> num;
                display_sp(num);
                break;

            case '5':
                display_all();
                break;

            case '6':
                system("CLS");
                cout << "\n\t\t\t\tEnter The Account Number : ";
                cin >> num;
                delete_account(num);
                break;

            case '7':
                system("CLS");
                cout << "\n\t\t\t\tEnter The Account Number : ";
                cin >> num;
                modify_account(num);
                break;

            case '8':
                cout << "\n\t\t\t\tExiting the system...\n";
                break;

            default:
                cout << "\a";
        }
        cin.ignore();
        cin.get();

    } while (ch != '8');
    return 0;
}

void write_account()
{
    account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char*>(&ac), sizeof(account));
    outFile.close();
}

void display_sp(int n)
{
    account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File Could Not Be Opened !! Press Any Key...";
        return;
    }
    cout << "\n\t\t\t\tBALANCE DETAILS\n";
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(account)))
    {
        if (ac.retacno() == n)
        {
            ac.show_account();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\t\t\t\tAccount Number Does Not Exist";
}

void modify_account(int n)
{
    account ac;
    fstream File;
    bool found = false;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File Could Not Be Opened !! Press Any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char*>(&ac), sizeof(account));
        if (ac.retacno() == n)
        {
            ac.show_account();
            cout << "\n\n\t\t\tEnter The New Details of Account" << endl;
            ac.modify();
            int pos = (-1) * static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*>(&ac), sizeof(account));
            cout << "\n\t\t\tRecord Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\t\t\tRecord Not Found";
}

void delete_account(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File Could Not Be Opened !! Press Any Key...";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(account)))
    {
        if (ac.retacno() != n)
        {
            outFile.write(reinterpret_cast<char*>(&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat", "account.dat");
    cout << "\n\t\t\tRecord Deleted...";
}

void display_all()
{
    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File Could Not Be Opened !! Press Any Key...";
        return;
    }
    cout << "\n\n\t\t\tACCOUNT HOLDER LIST\n\n";
    cout << "====================================================\n";
    cout << "A/c No.      NAME           Type  Balance\n";
    cout << "====================================================\n";
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
}

void deposit_withdraw(int n, int option)
{
    int amt;
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File Could Not Be Opened !! Press Any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char*>(&ac), sizeof(account));
        if (ac.retacno() == n)
        {
            ac.show_account();
            if (option == 1)
            {
                cout << "\n\n\t\t\tTO DEPOSIT AMOUNT";
                cout << "\n\n\t\t\tEnter The Amount To Be Deposited: ";
                cin >> amt;
                ac.dep(amt);
            }
            else if (option == 2)
            {
                cout << "\n\n\t\t\tTO WITHDRAW AMOUNT";
                cout << "\n\n\t\t\tEnter The Amount To Be Withdrawn: ";
                cin >> amt;
                int bal = ac.retdeposit() - amt;
                if (bal < 0)
                    cout << "Insufficient Balance";
                else
                    ac.draw(amt);
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*>(&ac), sizeof(account));
            cout << "\n\t\t\tRecord Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\t\t\tRecord Not Found";
}
