#include "date.h"
#include <iostream>
using namespace std;
//default param constructor
Date::Date(int day, int month, int year) {
  setDay(day);
  setMonth(month);
  setYear(year);
}
void Date::setDay(int day) {
//only days between 1 and 31 is valid
  while(day<=0||day>31){
    cout<<"Enter Valid Day"<<endl;
    cin>>day;
  }
  day_ = day;
}
void Date::setMonth(int month) {
//only months between 1 and 12 is valid
  while(month<=0||month>12){
    cout<<"Enter Valid Month"<<endl;
    cin>>month;
  }
  month_ = month;
}
void Date::setYear(int year) {
//only years between 1900 and 2099 is valid
  while(year<1900||year>3000){
    cout<<"Enter Valid year"<<endl;
    cin>>year;
  }
  year_ = year;
}
//getters
int Date::getDay() const { return day_; }
int Date::getMonth() const { return month_; }
int Date::getYear() const { return year_; }
//print the date with format d/m/yyyy
void Date::printDate() {
  cout << day_ << "/" << month_ << "/" << year_ << endl;
}