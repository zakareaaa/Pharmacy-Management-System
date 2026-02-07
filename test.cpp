#include "medication.h"
#include "offtheshelf.h"
#include "pharmacy.h"
#include "prescription.h"
#include <iostream>

using namespace std;

int main() {
  Medication *m =
      new Medication[3]{Medication("Paracetamol", "Painkiller", 10.5, 9,
                                   "123456789", Date(1, 1, 2025)),
                        Medication("Ibuprofen", "Painkiller", 15.5, 100,
                                   "123456789", Date(1, 1, 2025)),
                        Medication("Aspirin", "Painkiller", 20.5, 100,
                                   "123456789", Date(1, 1, 2025))};

  Customer c1("John",
              Address("zak@gmail.com", "New York", "10001", "Main st."));

  Customer c2("Jane",
              Address("f.hotmail.com", "New York", "10002", "Main st."));

  Customer c3("Jack",
              Address("jdjd@dhhd.com", "New York", "10003", "Main st."));

  Customer *c = new Customer[3]{c1, c2, c3};

  Pharmacy p("Life", m, 3, c, 3);

  p.checkExpiredMedication();
            

  return 0;
}