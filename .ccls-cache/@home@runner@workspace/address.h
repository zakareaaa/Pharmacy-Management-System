#pragma once
#include<iostream>
#include<string.h>
using namespace std;


class Address {
  private:
    //Data Members:
    string email;
    string city;
    string PhoneNum;
    string streetName;

  public:
  //Default Parameterized constructor for initializing data members:
    Address(string email = "Unknown", string city = "Unknown", string PhoneNum = "XXXXXX-XXX", string streetName = "Uknown");

  //Setters and Getters:
    void setEmail(string &email_);
    string getEmail();

    void setCity(string &city_);
    string getCity();

    void setPhoneNum(string &phoneNum_);
    string getPhonenUm();

    void setStreetName(string &streetName_);
    string getStreetName();


    //Display Function
    void Display();
};