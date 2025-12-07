#include "Account.h"
#include <fstream>
#include <vector>
#include <unistd.h>
#include <algorithm>
#include <cctype>

bool isValidemail(string email){
    int at = email.find('@');
    int dot = email.find('.', at + 1);

    if (at == string::npos || dot == string::npos || dot < at)
    {
        return false;
    } 

    return true;
}

void deleteaccount(vector<Account> &accounts , Account * signin){
    if(signin == nullptr) return;

    for(auto itr = accounts.begin() ; itr != accounts.end() ; ++itr){
        if(&(*itr) == signin)
        {
            accounts.erase(itr);
            break;
        }
    }
}

bool isValidpassword(string password){
    if(password.length() < 8){
        return false;
    }
    return true;
}

void updatedata(const string & filename , vector<Account> &accounts){
    ofstream outFile(filename);
    
    for(Account &acc : accounts){
        outFile << acc.get_name()<< " " << acc.get_number() << " " << acc.get_amount() <<
                " " << acc.get_email() << " " << acc.get_password() << endl;
    }
    outFile.close();
}

vector<Account> loaddata(const string & filename){
    vector<Account> accounts;
    ifstream inFile(filename);

    if(!inFile)
    {
        return accounts;
    }

    string name,number,email,password;
    double amount;

    while(inFile >> name >> number >> amount >> email >> password){
        accounts.push_back(Account(name,number,amount,email,password));
    }

    inFile.close();

    return accounts;
}

int main(void){
    Account * signin = NULL;
    vector<Account> accounts = loaddata("accounts/account.txt");

    do{
        updatedata("accounts/account.txt",accounts);
        cout << endl << endl;
        cout << "------- L O G I N -------" << endl << endl;
        cout << "1 -- Login ----" << endl;
        cout << "2 -- Sign up ----" << endl;
        cout << "3 -- Exit ----" << endl;
        cout << endl << endl;

        int i = 0;

        cout << "# ";
        cin >> i;

        switch(i){
            case 1:{
                cout << "email : ";
                string email;
                cin >> email;

                int flag = 0;

                for(Account &itr : accounts){
                    if(itr.get_email() == email)
                    {
                        flag = 1;
                        string password;
                        cout << "password : " ;
                        cin >> password;
                        if(itr.get_password() == password)
                        {
                            signin = &itr;
                            cout << "Log in to account...." << endl;
                            sleep(2);
                            break;
                        }
                        cout << "Wrong password" << endl;
                        break;
                    }
                }

                if(!flag)
                {
                    cout << "Account not found" << endl;
                }

                break;
            }
            case 2:{
                string name;
                cout << "name : ";
                cin >> name;

                string number;
                cout << "number : ";
                cin >> number;

                string email;
                string password;

                cout << "email : ";
                cin >> email;

                cout << "password : ";
                cin >> password;

                if(isValidemail(email) && isValidpassword(password)){
                    accounts.push_back(Account(name,number,0.0,email,password));
                }else
                    cout << "Invalid email or password" << endl;

                break;
            }
            case 3:{
                exit(1);
            }
            default:
                cout << "option not found" << endl;
                break;
        }

    
    while(signin){
        updatedata("accounts/account.txt",accounts);

        cout << endl << endl;
        cout << "------- M E N U -------" << endl << endl;
        cout << "1 -- Deposit amount ----" << endl;
        cout << "2 -- withdraw amount ----" << endl;
        cout << "3 -- Apply benefit ----" << endl;
        cout << "4 -- Make transaction ----" << endl;
        cout << "5 -- Display Account ----" << endl;
        cout << "6 -- Settings & pers ----" << endl;

        cout << endl << endl;

        cout << "# ";
        int i = 0;
        cin >> i;

        switch(i){
            case 1:{
                    double amount;
                    cout << "amount : " ;
                    cin >> amount;

                    if(signin->deposit(amount))
                    {
                        cout << "deposit succesfull" << endl;
                    }else{
                        cout << "deposit failed !" << endl;
                    }
                break;
            }
            case 2:{
                    double amount;
                    cout << "amount : " ;
                    cin >> amount;

                    if(signin->withdraw(amount))
                    {
                        cout << "withdraw succesfull" << endl;
                    }else{
                        cout << "withdraw failed !" << endl;
                    }
                break;
            } 
            case 3:{
                    if(signin->get_amount() > 10000 )
                    {
                        signin->benefit(0.1);
                    }else{
                        signin->benefit(0.05);
                    }
                break;
            } 
            case 4:{
                cout << "Recepient number : " ;
                string number;
                cin >> number;

                int flag = 0;

                for(auto &itr : accounts){
                    if(itr.get_number() == number)
                    {
                        flag = 1;
                        double amount;
                        cout << "amount : " ;
                        cin >> amount;

                        if(signin->transaction(itr,amount))
                        {
                            cout << "transaction succesful" << endl;
                            break;
                        }else{
                            cout << "transaction failed !" << endl;
                            break;
                        }
                    }
                }

                if(!flag)
                {
                    cout << "Recepient not found" << endl;
                }
                break;
            }
            case 5:{
                signin->display();
                break;
            }

            case 6:{
                cout << endl << endl;
                cout << "------- Settings & pers -------" << endl << endl;
                cout << "1 -- Update email ----" << endl;
                cout << "2 -- Update password ----" << endl;
                cout << "3 -- Reinitialize account ----" << endl;
                cout << "4 -- Delete account ----" << endl;
                cout << "5 -- Help and faQ ----" << endl;
                cout << "6 -- Sing out ----" << endl;
                cout << endl << endl;

                int i = 0;

                cout << "# " ;
                cin >> i;
                switch(i){
                    case 1:{

                        string newemail;
                        cout << "new email : ";
                        cin >> newemail;
                        if(isValidemail(newemail)){
                            signin->set_email(newemail);
                            cout << "new email set" << endl;
                        }else{
                            cout << "invalid email" << endl;
                        }
                        break;
                    }

                    case 2:{
                        string newpass;
                        cout << "new password : ";
                        cin >> newpass;
                        if(isValidpassword(newpass))
                        {
                            signin->set_password(newpass);
                            cout << "new password set" << endl;
                        }else{
                            cout << "invalid password" << endl;
                        }
                        
                        break;
                    }

                    case 3:{
                        cout << "all your money will be set to 0" << endl
                            << "if you proceed with this option, " << endl
                            << "name and number won't change ." << endl << endl;
                            string decision;
                            do{
                                cout << "are you sure you want to proceed (y,yes / n,no): ";
                                cin >> decision;
                                transform(decision.begin(), decision.end(), decision.begin(), ::tolower);
                            }while( decision != "yes" && decision != "no" && decision != "n" && decision != "y");

                            
                            if(decision == "yes" || decision == "y"){
                                signin->set_amount(0.0);
                                cout << "working on it..." << endl;
                                sleep(2);
                            }else{
                                cout << "Initilizing canceled" << endl;
                            }

                        break;
                    }

                    case 4:{
                        cout << "this option will destroy your" << endl
                            << "account permanently and all the" << endl
                            << "data will disappear, think twice " << endl 
                            << "before you decide ."<< endl;
                        string decision;
                        do{
                            cout << "are you sure you want to proceed (y,yes / n,no): ";
                            cin >> decision;
                            transform(decision.begin(), decision.end(), decision.begin(), ::tolower);
                        }while( decision != "yes" && decision != "no" && decision != "n" && decision != "y");
                        
                        if(decision == "yes" || decision == "y"){
                                string password;
                                cout << "password : ";
                                cin >> password;

                                if(signin->get_password() == password){
                                    deleteaccount(accounts,signin);
                                    signin = NULL;
                                    cout << "working on it..." << endl;
                                    sleep(2);
                                    break;
                                }else{
                                    cout << "password incorrect" << endl;
                                }

                            }else{
                                cout << "Initilizing canceled" << endl;
                            }
                        
                        break;
                    }

                    case 5:{
                        cout << "need help ... we got you " << endl << 
                            "Visit us on https://Account.help.org/faq"<< endl;
                        break;
                    }

                    case 6:{
                        signin = NULL;
                        cout << "Login out...."<< endl;
                        sleep(2);
                        break;
                    }

                    default:
                        cout << "Option not found" << endl;
                }
                break; 
            }
            default:
                cout << "option not found " << endl;
        }
        
    }
    }while(1);
    return 0;
}