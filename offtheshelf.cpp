#include "offtheshelf.h"
#include <iostream>
using namespace std;

OffTheShelf::OffTheShelf(const string &Name, const string &desc, double price_,
                         int quant, const string &code, int eday, int emonth,
                         int eyear, bool bogof, int day, int month, int year)
    : Medication(Name, desc, price_, quant, code, Date(eday, emonth, eyear)),
      BOGOF(bogof), OfferEnds(day, month, year) {
  // Constructor body empty - everything initialized in initializer list
}

void OffTheShelf::setBOGOF(bool a) { BOGOF = a; }

bool OffTheShelf::getBOGOF() const { return BOGOF; }

void OffTheShelf::setOfferEnds(const Date &a) { OfferEnds = a; }

Date OffTheShelf::getOfferEnds() const { return OfferEnds; }

void OffTheShelf::print() {
  Medication::print(); // Call base class print()
  // Create a copy of OfferEnds to modify for display
  Date displayDate = OfferEnds;

  if (BOGOF) {
    // Add 3 months for BOGOF offers
    if (displayDate.getMonth() + 3 > 12) {
      displayDate.setMonth((displayDate.getMonth() + 3) - 12);
      displayDate.setYear(displayDate.getYear() + 1);
    } else {
      displayDate.setMonth(displayDate.getMonth() + 3);
    }
  } else {
    // Add 2 years for non-BOGOF offers
    displayDate.setYear(displayDate.getYear() + 2);
  }

  cout << "Discount: ";
  if (BOGOF) {
    cout << "Yes (Buy One Get One Free)" << endl;
  } else {
    cout << "No" << endl;
  }

  cout << "Offer Ends: ";
  displayDate.printDate();
}