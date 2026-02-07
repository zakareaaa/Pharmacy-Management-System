#include <iostream>
#include <ctime>
using namespace std;
#ifndef DATE_H
#define DATE_H
class Date {
private:
  int day, month, year;

public:
// Default param constructor
  Date(int day = 1, int month = 1, int year = 2000);
//setters
  void setMonth(int);
  void setDay(int);
  void setYear(int);
//getters
  int getMonth() const;
  int getDay() const;
  int getYear() const;
//print function
  void printDate();

  bool operator<(const Date &) const;
};
#endif