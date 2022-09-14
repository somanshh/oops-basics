#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

class Bank // Base class named bank
{
private:
    string Bank_name;
    string Bank_branch;

protected:
    int idOfEmp[5] = {568, 584, 555, 695, 595}; // Assinging Id's of employee's , "you have to enter exact id to perform the action of an employee"

public:
    Bank() {}
    Bank(string name, string branch)
    {
        Bank_name = name;
        Bank_branch = branch;
    }
    void showBankDetails()
    {
        cout << "\nName of the Bank is : " << Bank_name;
        cout << "\nBranch is : " << Bank_branch << endl;
    }

    friend void intro(); // an introductry function
};

class customer : public Bank // Customer class inheriting properties from bank class
{
protected:
    int accNumber;
    char name[20];
    int balance;
    char type;

public:
    void create_account(); // initializing funcitons
    void show_account() const;
    void modify();
    void deposit(int);
    void withdraw(int);
    void report() const;
    int retAccNumber() const;
    int retBalance() const;
    char retAccType() const;
};

class employee : private customer // employee class inheriting the properties of customer class
{
private:
    int emp_id;

public:
    employee() {}
    employee(int emp_id)
    {
        this->emp_id = emp_id;
    }
    void showEmpId()
    {
        cout << "Employee ID : " << emp_id << endl;
    }
    void write_account();            // function to write record in binary file
    void display_sp(int);            // function to display account details given by user
    void modify_account(int);        // function to modify record of file
    void delete_account(int);        // function to delete record of file
    void display_all();              // function to display all account details
    void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
};

//Defining Functions for Customer class

void customer::create_account() // function to get data from user
{
    cout << "Please verify your Employee id to continue : ";          // verifing the employee by ID
    int id;
    cin >> id;
    bool flag = false;
    for (int i = 0; i < 5; i++)
    {
        if (id == idOfEmp[i])                       //if employee id entered is correct then , only you can access ahead
        {
            flag = true;
            break;
        }
    }
    if (flag == false)
        cout << "\nPlease enter the correct ID to continue \n";
    else
    {
        cout << "\nEnter The account No. : ";                       //steps for creating account
        cin >> accNumber;
        cout << "\n\nEnter The Name of The account Holder : ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "\nEnter Type of The account (C/S) : ";
        cin >> type;
        type = toupper(type);
        cout << "\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
        cin >> balance;
        cout << "\n\n\nAccount Created..";
    }
}

void customer::show_account() const // function to show data on screen
{
    cout << "\nAccount No. : " << accNumber;
    cout << "\nAccount Holder Name : ";
    cout << name;
    cout << "\nType of Account : " << type << "  ";
    cout << "\nBalance amount : " << balance << endl;
}

void customer::modify() // function to add new data
{
    cout << "\nPlease verify your Employee id to continue : ";
    int id;
    cin >> id;
    bool flag = false;
    for (int i = 0; i < 5; i++)                     
    {
        if (id == idOfEmp[i])
        {
            flag = true;
            break;
        }
    }
    if (flag == false)
        cout << "\nPlease enter the correct ID to continue \n";
    else
    {
        cout << "\nAccount No. : " << accNumber;                    // steps for modifying an account
        cout << "\nModify Account Holder Name : ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "\nModify Type of Account : ";
        cin >> type;
        type = toupper(type);
        cout << "\nModify Balance amount : ";
        cin >> balance;
    }
}

void customer::deposit(int x) // function to accept amount and add to balance amount
{
    balance += x;
    cout<<"\nUpdated Account Balance is : "<<balance <<endl;
}

void customer::withdraw(int x) // function to accept amount and subtract from balance amount
{
    balance -= x;
}

void customer::report() const // function to show data
{
    cout << accNumber << setw(5) << " " << name << setw(10) << " " << type << setw(6) << balance << endl;
}

int customer::retAccNumber() const // function to return account number
{
    return accNumber;
}

int customer::retBalance() const // function to return balance amount
{
    return balance;
}

char customer::retAccType() const // function to return type of account
{
    return type;
}



//******************  Defining Functions for employee class   *********************/



void employee::write_account() // function to write in file
{
    customer ac;                        //creating an customer class object
    ofstream outFile;                                           //object of ofstream to write data into an file named "account.dat"
    outFile.open("account.dat", ios::binary | ios::app);
    ac.create_account();                                     //calling the create account function for creating an account
    outFile.write(reinterpret_cast<char *>(&ac), sizeof(customer));         //wrinting data
    outFile.close();
}


void employee::display_sp(int n) //    	function to read specific record from file
{
    customer ac;
    bool flag = false;
    ifstream inFile;                                           //object of ifstream to read data from a file named "account.dat"
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\nBALANCE DETAILS\n";

    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(customer)))
    {
        if (ac.retAccNumber() == n)
        {
            ac.show_account();                      //calling the show_account function for showing details of an account
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\nAccount number does not exist";
}

void employee::modify_account(int n) //    	function to modify record of file
{
    bool found = false;
    customer ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(customer));             // calling all functions needed to modify an account
        if (ac.retAccNumber() == n)
        {
            ac.show_account();              
            cout << "\n\nEnter The New Details of account" << endl;
            ac.modify();
            int pos = (-1) * static_cast<int>(sizeof(customer));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(customer));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n Record Not Found ";
}

void employee::delete_account(int n) //    	function to delete record of file
{
    cout << "Please verify your Employee id to continue : ";
    int id;
    cin >> id;
    bool flag = false;
    for (int i = 0; i < 5; i++)
    {
        if (id == idOfEmp[i])
        {
            flag = true;
            break;
        }
    }
    if (flag == false)
        cout << "\nPlease enter the correct ID to continue \n";
    else
    {
        customer ac;
        ifstream inFile;
        ofstream outFile;
        inFile.open("account.dat", ios::binary);
        if (!inFile)
        {
            cout << "File could not be open !! Press any Key...";
            return;
        }
        outFile.open("Temp.dat", ios::binary);                              //steps for deleting the data of an particular account
        inFile.seekg(0, ios::beg);
        while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(customer)))
        {
            if (ac.retAccNumber() != n)
            {
                outFile.write(reinterpret_cast<char *>(&ac), sizeof(customer));
            }
        }
        inFile.close();
        outFile.close();
        remove("account.dat");
        rename("Temp.dat", "account.dat");                  // removing data from the file itself
        cout << "\n\n\tRecord Deleted ..";
    }
}

void employee::display_all() //    	function to display all accounts deposit list
{
    customer ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << "========================================================\n";
    cout << "A/c no.          NAME         Type       Balance\n";
    cout << "========================================================\n";
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(customer)))
    {
        ac.report();                         //calling the report function for showing details of all accounts
        cout << endl;
    }
    inFile.close();
}

void employee::deposit_withdraw(int n, int option) //    	function to deposit and withdraw amounts
{
    int amt;
    bool found = false;
    customer ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(customer));
        if (ac.retAccNumber() == n)
        {
            ac.show_account();
            if (option == 1)
            {
                cout << "\n\n\tTO DEPOSITE AMOUNT ";
                cout << "\n\nEnter The amount to be deposited : ";
                cin >> amt;
                ac.deposit(amt);                    //calling deposit func. for depositing an given amount
                cin.get();
            }
            if (option == 2)
            {
                cout << "\n\n\tTO WITHDRAW AMOUNT ";
                cout << "\n\nEnter The amount to be withdraw : ";
                cin >> amt;
                int bal = ac.retBalance() - amt;
                if ((bal < 500 && ac.retAccType() == 'S') || (bal < 1000 && ac.retAccType() == 'C'))
                    cout << "Insufficience balance\n";
                else
                    ac.withdraw(amt);           //calling withdraw func. for withdrawing an given amount
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(customer));
            cout << "\n\n\t Record Updated\n";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n Record Not Found \n";
}

void intro();


//******************        MAIN FUNCTION           ***********************/
 
 
int main()
{
    intro();                    //calling intro funciton for displaying some info

    employee emp(1);

    char ch;
    int num;

    do
    {
        system("cls");                      //giving choice and calling the particular funciton based on the choice entered
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. NEW ACCOUNT";
        cout << "\n\n\t02. DEPOSIT AMOUNT";
        cout << "\n\n\t03. WITHDRAW AMOUNT";
        cout << "\n\n\t04. BALANCE ENQUIRY";
        cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
        cout << "\n\n\t06. CLOSE AN ACCOUNT";
        cout << "\n\n\t07. MODIFY AN ACCOUNT";
        cout << "\n\n\t08. EXIT";
        cout << "\n\n\tSelect Your Option (1-8) ";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case '1':
            emp.write_account();
            break;

        case '2':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            emp.deposit_withdraw(num, 1);
            break;

        case '3':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            emp.deposit_withdraw(num, 2);
            break;

        case '4':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            emp.display_sp(num);
            break;

        case '5':
            emp.display_all();
            break;

        case '6':

            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            emp.delete_account(num);
            break;

        case '7':

            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            emp.modify_account(num);
            break;

        case '8':
            cout << "\n\n\tThanks for using bank managemnt system";
            break;
        default:
            cout << "\a";
        }
        cin.ignore();
        cin.get();
    } while (ch != '8');
    return 0;
}

//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
    cout << "\n\n\n\t\t  BANK";
    cout << "\n\n\t\tMANAGEMENT";
    cout << "\n\n\t\t  SYSTEM";

    cout << "\n\n\n\n\tWelcome to our online Banking Interface \n\t      Hope You Will Enjoy\n\n\n Please press enter to continue : ";

    cin.get();


}