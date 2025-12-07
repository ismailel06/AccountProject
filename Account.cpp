#include "Account.h"

Account::Account(string name, string number, double amount , string email , string password){
    this->name = name;
    this->number = number;
    this->amount = amount;
    this->email = email;
    this->password = password;

    cout << "Account added " << endl;
}

void Account::set_name(string name){
    if(name == ""){
        return;
    }
    this->name = name;
}

void Account::set_number(string number){
    if(number == ""){
        return;
    }
    this->number = number;
}

void Account::set_amount(double amount){
    if(amount < 0.0){
        return;
    }
    this->amount = amount;
}


void Account::set_email(string email){
     this->email = email;
}

void Account::set_password(string password){
    this->password = password;
}

string Account::get_name(){
    return this->name;
}

string Account::get_number(){
    return this->number;
}

double Account::get_amount(){
    return this->amount;
}

string Account::get_email(){
    return this->email;
}

string Account::get_password(){
    return this->password;
}

void Account::display(){
    cout << "Account Name   : " << this->name << endl;
    cout << "Account Number : " << this->number << endl;
    cout << "Account Amount : " << this->amount << endl;
}

bool Account::deposit(double amount){
    if(amount <= 0){
        return false;
    }
    this->amount += amount;
    return true;
}

bool Account::withdraw(double amount){
    if(amount <= 0 || this->amount < amount){
        return false;
    }
    this->amount -= amount;
    return true;
}

void Account::benefit(double percentage){
    if(percentage > .1 || percentage < 0){
        cout << "Can't perform benefit " << endl;
        return;
    }
    this->amount *= (1 + percentage);
    cout << "benefit performed succesfully" << endl;
}


bool Account::transaction(Account & acc , double amount){
    if(this->get_amount() < 0 ){
        return false;
    }
    if(this->get_amount() < amount || amount <= 0){
        return false;
    }
    this->set_amount(this->get_amount() - amount);
    acc.set_amount(acc.get_amount() + amount);

    return true;
}
