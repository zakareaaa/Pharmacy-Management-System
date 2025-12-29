#include "customer.h"
#include "medication.h"
#include <iostream>
#include <string>
using namespace std;

class Pharmacy {
private:
  const int pharmacyId;
  string pharmacyName;
  static int id;
  Medication *medications;
  int medicationCount;
  int customerCount;
  Customer *customers;
public:
//constructors
  Pharmacy();
  Pharmacy(string name, Medication*, int, Customer*, int);
//destructor
  ~Pharmacy();
//setters
  void setPharmacyName(string);
  void setMedications(Medication *, int);
  void setCustomers(Customer *, int);
//getters
  string getPharmacyName();
  Medication *getMedication();
  Customer *getCustomer();
  int getMedicationCount();
  int getCustomerCount();
//functions
  void AddMedication( Medication);
  void AddCustomer(Customer);
  void removeMedication(string);
  void printMedication();
  void printCustomer();
  void removeCustomer(string);
};
