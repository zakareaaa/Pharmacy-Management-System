#include "medication.h"
#include <iostream>
#include <string>
using namespace std;
int Medication::id = 100;
// each medication has a unique id
Medication::Medication(string Name, string desc, double price_, int quant,
                       string code, Date exp)
    : medId(++id), expDate(exp) {
  setMedName(Name);
  setDescription(desc);
  setPrice(price_);
  setQuantityInStock(quant);
  setBarcode(code);
}
void Medication::setMedName(string medName_) {
  while (medName_ == "") {
    // if the name is not empty
    cout << "Enter Valid Medication Name" << endl;
    cin>>medName_;
  }
  medName = medName_;
}
void Medication::setDescription(string description_) {
  // if the description is not empty
  while (description_ == "") {
    cout << "Enter Valid Description" << endl;
    cin >> description_;
  }
  description = description_;
}
void Medication::setPrice(double price_) {
  // Price cant be negative
  while (price_ < 0) {
    cout << "Please enter a valid price: ";
    cin >> price_;
  }
  price = price_;
}
void Medication::setQuantityInStock(int quantity_) {
  // Quantity cant be negative
  while (quantity_ < 0) {
    cout << "Please enter a valid quantity: ";
    cin >> quantity_;
  }
  quantityInStock = quantity_;
}
void Medication::setExpiryDate(const Date &exp) { expDate = exp; }
void Medication::setBarcode(string code_) {
  // Barcode cant be empty
  while (code_ == "") {
    cout << "Please enter a valid barcode: ";
    cin >> code_;
  }
  barcode = code_;
}
void Medication::print() {
  // print medication details
  cout << "Medication Id: " << medId << endl;
  cout << "Medication name: " << medName << endl;
  cout << "Description: " << description << endl;
  cout << "Price: " << price << endl;
  cout << "Quantity in stock: " << quantityInStock << endl;
  cout << "Date: ";
  // print expiry date(composition)
  expDate.printDate();
  cout << "Barcode: " << barcode << endl;
}
// getters
string Medication::getDescription() const { return description; }
string Medication::getMedName() const { return medName; }
double Medication::getPrice() const { return price; }
int Medication::getQuantityInStock() const { return quantityInStock; }
string Medication::getBarcode() const { return barcode; }
Date Medication::getExpiryDate() const { return expDate; }
int Medication::getMedId() const { return medId; }