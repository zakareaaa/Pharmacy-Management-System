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
  this->day = day;
}
void Date::setMonth(int month) {
//only months between 1 and 12 is valid
  while(month<=0||month>12){
    cout<<"Enter Valid Month"<<endl;
    cin>>month;
  }
  this->month = month;
}
void Date::setYear(int year) {
//only years between 1900 and 2099 is valid
  while(year<1900||year>3000){
    cout<<"Enter Valid year"<<endl;
    cin>>year;
  }
  this->year = year;
}
//getters
int Date::getDay() const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear() const { return year; }
//print the date with format d/m/yyyy
void Date::printDate() {
  cout << day << "/" << month << "/" << year << endl;
}
bool Date::operator<(const Date &other) const {
  if (year != other.year)
    return year < other.year;

  if (month != other.month)
    return month < other.month;

  return day < other.day;
}
