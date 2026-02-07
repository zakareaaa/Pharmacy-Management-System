#include "address.h"
#include "customer.h"
#include "date.h"
#include "medication.h"
#include "offtheshelf.h"
#include "pharmacy.h"
#include "prescription.h"
#include <iostream>
#include <string>

using namespace std;
int main() {

  int pNum = 0; // keeps track of the number of pharmacies added
  cout << "Welcome to the Pharmacy Management System" << endl;
  int pharmacySize = 0;
  // setting the size of the pharmacy array
  cout << "Enter Number Of Pharmacies: ";
  // input validation
  while (pharmacySize <= 0)
    cin >> pharmacySize;
  cout << endl;

  Pharmacy *p = new Pharmacy[pharmacySize];
  int choice = -1;
  while (choice != 0) {
    // menu
    cout << "\n╔════════════════════════════════════╗" << endl;
    cout << "║  PHARMACY MANAGEMENT SYSTEM        ║" << endl;
    cout << "╚════════════════════════════════════╝" << endl;
    cout << "1. Add a new pharmacy" << endl;
    cout << "2. Add Medication To A Pharmacy" << endl;
    cout << "3. Add Customer To A Pharmacy" << endl;
    cout << "4. Remove Medication From A Pharmacy" << endl;
    cout << "5. Remove Customer From A Pharmacy" << endl;
    cout << "6. Display Medication Inventory" << endl;
    cout << "7. Display Customer List" << endl;
    cout << "8. Check Low Stock" << endl;            // ✅ NEW
    cout << "9. Restock Medication" << endl;         // ✅ NEW
    cout << "10. Check Expired Medications" << endl; // ✅ NEW
    cout << "0. Exit" << endl;
    cout << "════════════════════════════════════" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
      // keep track of the number of pharmacies added (making sure it doesn't
      // exceed the size of the array)
      if (pNum < pharmacySize) {
        string Pname;
        int medicationNum = 0, customerNum = 0;
        cout << "Enter Pharmacy Name: ";
        cin >> Pname;
        cout << "Enter Number Of Medications: ";
        while (medicationNum <= 0)
          cin >> medicationNum;
        Medication *m1 = new Medication[medicationNum];
        for (int i = 0; i < medicationNum; i++) {
          string medName, desc, bar;
          double price;
          int quantity, day, month, year;
          cout << "Medication NO." << i + 1 << " Info" << endl;
          cout << "Enter Medication Name: ";
          cin >> medName;
          cout << "Enter Medication Description: ";
          cin >> desc;
          cout << "Enter Medication Price: ";
          cin >> price;
          cout << "Enter Medication Quantity: ";
          cin >> quantity;
          cout << "Enter Barcode: ";
          cin >> bar;
          cout << "Enter Expiry Date" << endl;
          cout << "Day: ";
          cin >> day;
          cout << "Month: ";
          cin >> month;
          cout << "Year: ";
          cin >> year;
          cout << endl;
          m1[i] = Medication(medName, desc, price, quantity, bar,
                             Date(day, month, year));
        }
        cout << "Medications Added!" << endl;
        cout << endl;
        cout << "Enter Number Of Customers: ";
        while (customerNum <= 0)
          cin >> customerNum;
        Customer *c1 = new Customer[customerNum];
        for (int i = 0; i < customerNum; i++) {
          string cName, city, street, email, phoneNum;
          cout << endl;
          cout << "Customer NO." << i + 1 << " Info" << endl;
          cout << "Enter Customer Name: ";
          cin >> cName;
          cout << "City: ";
          cin >> city;
          cout << "Street: ";
          cin >> street;
          cout << "Email: ";
          cin >> email;
          cout << "Phone Number: ";
          cin >> phoneNum;
          c1[i].setName(cName);
          c1[i].setAddress(Address(email, city, phoneNum, street));
        }
        cout << endl;
        cout << "Customers Added!" << endl;
        p[pNum].setCustomers(c1, customerNum);
        p[pNum].setMedications(m1, medicationNum);
        p[pNum].setPharmacyName(Pname);

        delete[] m1;
        delete[] c1;

        cout << "Pharmacy Added!" << endl;
        cout << endl;
        pNum++;
      } else {
        // if the pharmacy array is full
        int choice2 = -1;
        // resize the array
        cout << "Maximum Number Of Pharmacies Reached" << endl;
        cout << "1.Increase Size" << endl;
        cout << "0.Return To Menu" << endl;
        cin >> choice2;
        cout << endl;
        while (choice2 != 0) {
          if (choice2 == 1) {
            int newSize;
            cout << "Enter New Size: ";
            cin >> newSize;
            if (newSize < pNum) {
              newSize = pNum;
            }
            Pharmacy *p2 = new Pharmacy[newSize];
            for (int i = 0; i < pharmacySize; i++) {
              p2[i].setMedications(p[i].getMedication(),
                                   p[i].getMedicationCount());
              p2[i].setCustomers(p[i].getCustomer(), p[i].getCustomerCount());
              p2[i].setPharmacyName(p[i].getPharmacyName());
            }
            delete[] p;
            p = p2;
            pharmacySize = newSize;
            cout << "Pharmacies Resized!" << endl;
            cout << endl;
            break;
          }
        }
      }
    }
    if (choice == 2) {
      string Pname;
      int index, count = 0;
      cout << "Enter Pharmacy Name: ";
      cin >> Pname;
      cout << endl;
      for (int i = 0; i < pharmacySize; i++) {
        if (p[i].getPharmacyName() == Pname) {
          count++;
          index = i;
        }
      }
      if (count == 0) {
        cout << endl << "Pharmacy Not Found" << endl;
      } else {
        string medName, desc, bar;
        int quantity, day, month, year;
        double price;
        cout << "Enter Medication name: ";
        cin >> medName;
        cout << "Enter Description: ";
        cin >> desc;
        cout << "Enter Price: ";
        cin >> price;
        cout << "Enter Quantity: ";
        cin >> quantity;
        cout << "Enter Barcode: ";
        cin >> bar;
        cout << "Enter Expiry Date" << endl;
        cout << "Day: ";
        cin >> day;
        cout << "Month: ";
        cin >> month;
        cout << "Year: ";
        cin >> year;
        p[index].AddMedication(Medication(medName, desc, price, quantity, bar,
                                          Date(day, month, year)));
        cout << endl << "Medication Added!" << endl;
        cout << endl;
      }
    }
    if (choice == 3) {
      string Pname;
      int index, count = 0;
      cout << "Enter Pharmacy Name: ";
      cin >> Pname;
      for (int i = 0; i < pNum; i++) {
        if (p[i].getPharmacyName() == Pname) {
          count++;
          index = i;
        }
      }
      if (count == 0) {
        cout << endl << "Pharmacy Not Found" << endl;
      } else {
        string cName, city, email, phoneNum, street;
        cout << "Enter Customer Name: ";
        cin >> cName;
        cout << "City: ";
        cin >> city;
        cout << "Street: ";
        cin >> street;
        cout << "Email: ";
        cin >> email;
        cout << "Phone number: ";
        cin >> phoneNum;
        p[index].AddCustomer(
            Customer(cName, Address(email, city, phoneNum, street)));
        cout << "Customer Added!" << endl;
        cout << endl;
      }
    }
    if (choice == 4) {
      string Pname, medName;
      int index, count = 0;
      cout << "Enter Pharmacy Name: ";
      cin >> Pname;
      for (int i = 0; i < pNum; i++) {
        if (p[i].getPharmacyName() == Pname) {
          count++;
          index = i;
        }
      }
      if (count == 0) {
        cout << "Pharmacy Not Found" << endl;
      } else {
        string medName;
        cout << "Enter Name Of Medication You Want To Remove: ";
        cin >> medName;
        p[index].removeMedication(medName);
        cout << endl;
        cout << "Medication Removed Successfuly!" << endl;
        cout << endl;
      }
    }
    if (choice == 5) {
      string Pname, cName;
      int index, count = 0;
      cout << "Enter Pharmacy Name: ";
      cin >> Pname;
      for (int i = 0; i < pNum; i++) {
        if (p[i].getPharmacyName() == Pname) {
          count++;
          index = i;
        }
      }
      if (count == 0) {
        cout << "Pharmacy Not Found" << endl;
      } else {
        string cName;
        cout << "Enter Name Of Customer You Want To Remove: ";
        cin >> cName;
        p[index].removeCustomer(cName);
        cout << endl;
        cout << "Customer Removed Successfuly!" << endl;
        cout << endl;
      }
    }
    if (choice == 6) {
      string Pname;
      int index, count = 0;
      cout << "Enter Pharmacy Name: ";
      cin >> Pname;
      cout << endl;
      for (int i = 0; i < pNum; i++) {
        if (p[i].getPharmacyName() == Pname) {
          count++;
          index = i;
        }
      }
      if (count == 0) {
        cout << "Pharmacy Not Found" << endl;
      } else {
        p[index].printMedication();
        cout << endl;
      }
    }
    if (choice == 7) {
      string Pname;
      int index, count = 0;
      cout << "Enter Pharmacy Name: ";
      cin >> Pname;
      cout << endl;
      for (int i = 0; i < pNum; i++) {
        if (p[i].getPharmacyName() == Pname) {
          count++;
          index = i;
        }
      }
      if (count == 0) {
        cout << "Pharmacy Not Found" << endl;
      } else {
        p[index].printCustomer();
        cout << endl;
      }
    }

    if (choice == 8) {
      string Pname;
      int index, count = 0;
      cout << "Enter Pharmacy Name: ";
      cin >> Pname;
      cout << endl;

      for (int i = 0; i < pNum; i++) {
        if (p[i].getPharmacyName() == Pname) {
          count++;
          index = i;
        }
      }

      if (count == 0) {
        cout << "Pharmacy Not Found" << endl;
      } else {
        p[index].checkLowStock();
        cout << endl;
      }
    }

    if (choice == 9) {
      string Pname;
      int index, count = 0;
      cout << "Enter Pharmacy Name: ";
      cin >> Pname;
      cout << endl;

      for (int i = 0; i < pNum; i++) {
        if (p[i].getPharmacyName() == Pname) {
          count++;
          index = i;
        }
      }

      if (count == 0) {
        cout << "Pharmacy Not Found" << endl;
      } else {
        string medName;
        int quantity;
        cout << "Enter Medication Name to Restock: ";
        cin >> medName;
        cout << "Enter Quantity to Add: ";
        cin >> quantity;

        p[index].restockMedication(medName, quantity);
        cout << endl;
      }
    }

    if (choice == 10) {
      string Pname;
      int index, count = 0;
      cout << "Enter Pharmacy Name: ";
      cin >> Pname;
      cout << endl;

      for (int i = 0; i < pNum; i++) {
        if (p[i].getPharmacyName() == Pname) {
          count++;
          index = i;
        }
      }

      if (count == 0) {
        cout << "Pharmacy Not Found" << endl;
      } else {
        p[index].checkExpiredMedication();
        cout << endl;
      }
    }
  }

  cout << "Thank you for using our program!" << endl;
  delete[] p;

  return 0;
}turn 0;
}
