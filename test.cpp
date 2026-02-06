#include "medication.h"
#include "offtheshelf.h"
#include "pharmacy.h"
#include "prescription.h"
#include <iostream>

using namespace std;

int test() {
  cout << "Step 1: Creating Medication array..." << endl;
  Medication *m =
      new Medication[3]{Medication("Paracetamol", "Painkiller", 10.5, 100,
                                   "123456789", Date(1, 1, 2025)),
                        Medication("Ibuprofen", "Painkiller", 15.5, 100,
                                   "123456789", Date(1, 1, 2025)),
                        Medication("Aspirin", "Painkiller", 20.5, 100,
                                   "123456789", Date(1, 1, 2025))};
  cout << "Step 1: SUCCESS" << endl;

  cout << "Step 2: Creating Customer c1..." << endl;
  Customer c1("John",
              Address("zak@gmail.com", "New York", "10001", "Main st."));
  cout << "Step 2: SUCCESS" << endl;

  cout << "Step 3: Creating Customer c2..." << endl;
  Customer c2("Jane",
              Address("f.hotmail.com", "New York", "10002", "Main st."));
  cout << "Step 3: SUCCESS" << endl;

  cout << "Step 4: Creating Customer c3..." << endl;
  Customer c3("Jack",
              Address("jdjd@dhhd.com", "New York", "10003", "Main st."));
  cout << "Step 4: SUCCESS" << endl;

  cout << "Step 5: Creating Customer array..." << endl;
  Customer *c = new Customer[3]{c1, c2, c3};
  cout << "Step 5: SUCCESS" << endl;

  cout << "Step 6: Creating Pharmacy object..." << endl;
  Pharmacy p("Life", m, 3, c, 3);
  cout << "Step 6: SUCCESS" << endl;

  cout << "Step 7: Cleaning up..." << endl;
  delete[] m;
  delete[] c;
  cout << "Step 7: SUCCESS" << endl;

  cout << "Step 8: Program ending (Pharmacy destructor will run)..." << endl;
  return 0;
}