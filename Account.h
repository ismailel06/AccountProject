#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
#include <string.h>

using namespace std;


class Account{
    private:
        string name;
        string number;
        double amount;
        string email;
        string password;
    public:
        Account(string,string,double,string,string);

        void set_name(string);
        void set_number(string);
        void set_amount(double);
        void set_email(string);
        void set_password(string);

        string get_name();
        string get_number();
        double get_amount();
        string get_email();
        string get_password();

        void display();

        bool deposit(double);
        bool withdraw(double);

        void benefit(double);

        bool transaction(Account &, double);
};
#endif