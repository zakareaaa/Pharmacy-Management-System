#include "prescription.h"
#include <iostream>
#include <limits>
using namespace std;

Prescription::Prescription(const string &Name, const string &desc,
                           double price_, int quant, const string &code,
                           int eday, int emonth, int eyear, int FDA_, int day,
                           int month, int year)
    : Medication(Name, desc, price_, quant, code, Date(eday, emonth, eyear)),
      approvalDate(Date(day, month, year)),
      FDA(FDA_) {}

void Prescription::setFDA(int a) {
  while (a < 0) {
    cout << "Enter Valid Num: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> a;
  }
  FDA = a;
}

void Prescription::setApprovalDate(const Date &d) {
  approvalDate = d; 
}

Date Prescription::getApproval() const { return approvalDate; }

int Prescription::getFDA() const { return FDA; }

void Prescription::printPrescription() {
  print();
  cout << "FDA: " << getFDA() << endl;
  cout << "Approval Date: ";
  getApproval().printDate();
}