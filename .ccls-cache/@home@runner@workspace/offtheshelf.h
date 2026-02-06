#ifndef OFFTHESHELF_H
#define OFFTHESHELF_H

#include "date.h"
#include "medication.h"
#include <iostream>
#include <string>
using namespace std;

class OffTheShelf : public Medication {
private:
  bool BOGOF;
  Date OfferEnds;

public:
  // Constructor
  OffTheShelf(const string &Name = "Unknown", const string &desc = "Unknown",
              double price_ = 0, int quant = 0, const string &code = "Unknown",
              int eday = 0, int emonth = 0, int eyear = 0, bool bogof = false,
              int day = 0, int month = 0, int year = 0);

  // Setters
  void setBOGOF(bool a);
  void setOfferEnds(const Date &a);

  // Getters
  bool getBOGOF() const;
  Date getOfferEnds() const;

  // Print
  void print() override;
};

#endif