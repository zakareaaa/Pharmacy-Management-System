#include "customer.h"
#include <iostream>
#include <string>
using namespace std;

static int uniqueID = 100;
Customer::Customer(string name, const Address &addr) : customerID(++uniqueID) {
  setName(name);
  setAddress(addr);
}

// Getters:
string Customer::getCustomerName() { return customerName; }

Address Customer::getAddress() { return address; }

const int Customer::getCustomerID() { return customerID; }

// Setters:
void Customer::setName(string name) {
  while (name == "") {
    cout << "Enter Valid Name" << endl;
    cin >> name;
  }
  customerName = name;
}

// Display Function:
void Customer::displayCustomerInfo() {
  cout << "Customer Name: " << customerName << endl;
  cout << "Customer ID: " << customerID << endl;
  address.Display();
}
void Customer::setAddress(const Address &addr) { address = addr; }