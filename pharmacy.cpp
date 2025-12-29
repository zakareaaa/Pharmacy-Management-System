#include "pharmacy.h"
#include <iostream>
#include <string>
using namespace std;
int Pharmacy::id = 100;

//default constructor
Pharmacy::Pharmacy() : pharmacyId(++id) { setPharmacyName("No Name");}
//parameterized constructor
Pharmacy::Pharmacy(string name, Medication *m1, int m_count, Customer *c1,
                   int c_count)
    : pharmacyId(++id), medicationCount(m_count), customerCount(c_count) {
  setPharmacyName(name);
  setMedications(m1, m_count);
  setCustomers(c1, c_count);
}
Pharmacy::~Pharmacy(){
  //to avoid memory leaks
  delete []medications;
  delete []customers;
}
void Pharmacy::setPharmacyName(string name) {
  //cant enter a name that is empty
  while (name == "") {
    cout << "Enter valid Name: " << endl;
    cin >> name;
  }
  pharmacyName = name;
}
void Pharmacy::setMedications(Medication *m1, int count) {
  //medications array setter replaces the old array with a new one
  medicationCount = count;
  delete []medications;
  medications = new Medication[count];
  for (int i = 0; i < medicationCount; i++) {
    medications[i] = m1[i];
  }
}
void Pharmacy::setCustomers(Customer *c1, int count) {
  //customers array setter replaces the old array with a new one
  customerCount = count;
  delete []customers;
  customers = new Customer[count];
  for (int i = 0; i < customerCount; i++) {
    customers[i].setName(c1[i].getCustomerName());
    customers[i].setAddress(c1[i].getAddress());
  }
}
  void Pharmacy::AddMedication(Medication m) {
    //a new array is created with the new medication added to the end replacing the old one
    Medication* newMedications = new Medication[medicationCount + 1];
    for (int i = 0; i < medicationCount; i++) {
      newMedications[i] = medications[i];
    }
    newMedications[medicationCount] = m;
    delete[] medications;
    medications = newMedications;
    //increase the size of the array by one since a medication was added
    medicationCount++;
  }

void Pharmacy::AddCustomer( Customer c1) {
  //a new array is created with the new customer added to the end replacing the old one
  Customer* newCustomers = new Customer[customerCount+1];
  for(int i = 0;i<customerCount;i++){
    newCustomers[i].setName(customers[i].getCustomerName());
    newCustomers[i].setAddress(customers[i].getAddress());
  }
  newCustomers[customerCount].setName(c1.getCustomerName());
  newCustomers[customerCount].setAddress(c1.getAddress());
  delete []customers;
  customers = newCustomers;
  //increase the size of the array by one since a customer was added
  customerCount++;
}
void Pharmacy::printMedication() {
  //prints the medications in the array with a separator between each medication
  for (int i = 0; i < medicationCount; i++) {
    medications[i].print();
    cout<<"-----------------------------"<<endl;
  }
}
void Pharmacy::printCustomer() {
  //prints the customers in the array with a separator between each customer
  for (int i = 0; i < customerCount; i++) {
    customers[i].displayCustomerInfo();
    cout<<"-----------------------------"<<endl;
  }
}
void Pharmacy::removeMedication(string name) {
  //the array is modified with the specified medication removed
  int newSize = 0;
  for(int i = 0; i < medicationCount; i++){
    if(medications[i].getMedName() == name){
      // Found the medication to remove
      continue;
    }
    medications[newSize] = medications[i];
    newSize++;
  }
  medicationCount = newSize;
}
void Pharmacy::removeCustomer(string name) {
  //the array is modified with the specified customer removed
  int newSize = 0;
  for(int i = 0; i < customerCount; i++){
    if(customers[i].getCustomerName() == name){
      // Found the customer to remove
      continue;
    }
    customers[newSize].setName(customers[i].getCustomerName());
    customers[newSize].setAddress(customers[i].getAddress());
    newSize++;
  }
  customerCount = newSize;
}
//getters
Medication * Pharmacy::getMedication(){ return medications;}
Customer * Pharmacy::getCustomer(){ return customers;}
string Pharmacy::getPharmacyName() { return pharmacyName; }
int Pharmacy::getMedicationCount() { return medicationCount; }
int Pharmacy::getCustomerCount() { return customerCount; }