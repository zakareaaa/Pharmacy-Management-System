#include "address.h"
#include <iostream>
#include <string>
using namespace std;
#ifndef CUSTOMER_H
#define CUSTOMER_H
class Customer {
private:
  // Data members:
  string customerName;
  const int customerID;
  Address address;

public:
  // Default Parameterized constructor for initializing data members:
  Customer(string name = "Unknown", const Address &addr = Address());
  // Setters and getters:
  string getCustomerName() const;
  int getCustomerID() const;
  Address getAddress() const;
  void setName(string name);
  void displayCustomerInfo();
  void setAddress(const Address &);
};
#endif