#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#include "date.h"
#include "medication.h"
#include <iostream>
#include <string>
using namespace std;

class Prescription : public Medication {
private:
  int FDA;//change to boolean
  Date approvalDate;

public:
  Prescription(const string &Name = "Unknown", const string &desc = "Unknown",
               double price_ = 0, int quant = 0, const string &code = "Unknown",
               int eday = 0, int emonth = 0, int eyear = 0, int FDA_ = 0,
               int day = 1, int month = 1, int year = 2000);

  void setFDA(int a);
  void setApprovalDate(const Date &d);

  Date getApproval() const;
  int getFDA() const;

  void printPrescription();
};

#endif