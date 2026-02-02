#include "medication.h"
#include "offtheshelf.h"
#include "prescription.h"
#include "pharmacy.h"
#include <iostream>

using namespace std;

int main() {

  Medication m1("Paracetamol", "Painkiller", 10.5, 100, "123456789", Date(1, 1, 2025));
  Medication m2("Ibuprofen", "Painkiller", 15.5, 100, "123456789", Date(1, 1, 2025));
  Medication m3("Aspirin", "Painkiller", 20.5, 100, "123456789", Date(1, 1, 2025));

  Medication *m = new Medication[3];
  m[0] = m1;
  m[1] = m2;
  m[2] = m3;

  Customer c1("John", Address("john@email.com", "New York", "123-456-789", "123 Main St"));
  Customer c2("Jane", Address("jane@email.com", "New York", "456-789-123", "456 Main St"));
  Customer c3("Jack", Address("jack@email.com", "New York", "789-123-456", "789 Main St"));

  Customer *c = new Customer[3];
  c[0].setName(c1.getCustomerName());
  c[0].setAddress(c1.getAddress());

  c[1].setName(c2.getCustomerName());
  c[1].setAddress(c2.getAddress());

  c[2].setName(c3.getCustomerName());
  c[2].setAddress(c3.getAddress());

  Pharmacy p1("Pharmacy 1", m, 3, c, 3);

  p1.printMedication();
  cout << "-----------------------------" << endl;
  p1.printCustomer();
  
  
  
  return 0; 
}