#include "date.h"
#include <iostream>
#include <string>
using namespace std;
#ifndef MEDICATION_H
#define MEDICATION_H
class Medication {
private:
  int medId;
  string medName;
  string description;
  double price;
  int quantityInStock;
  string barcode;
  static int id;
  Date expDate;

public:
  // Default Parameterized Constructor
  Medication(string Name = "Uknown", string desc = "Uknown", double price_ = 0,
             int quant = 0, string code = "Uknown", Date exp = Date());
  // Setters
  void setMedName(string medName_);
  void setDescription(string description_);
  void setPrice(double price_);
  void setQuantityInStock(int quantityInStock_);
  void setExpiryDate(const Date &);
  void setBarcode(string barcode_);
  // Getters
  string getMedName() const;
  string getDescription() const;
  double getPrice() const;
  int getQuantityInStock() const;
  string getBarcode() const;
  Date getExpiryDate() const;
  int getMedId() const;

  void print();
};
#endif