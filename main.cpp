#include "database.h"
#include "pharmacy.h"
#include "medication.h"
#include "customer.h"
#include "address.h"
#include "date.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    Database db("pharmacy.db");

    if (!db.initializeDatabase()) {
        cout << "Failed to initialize database!" << endl;
        return 1;
    }

    cout << "Welcome to the Pharmacy Management System!" << endl;
    int choice = -1;

    while (choice != 0) {
        cout << "\nMenu:\n";
        cout << "1. Add a new pharmacy\n";
        cout << "2. Add medication to a pharmacy\n";
        cout << "3. Add customer to a pharmacy\n";
        cout << "4. Remove medication\n";
        cout << "5. Remove customer\n";
        cout << "6. Display medication inventory\n";
        cout << "7. Display customers\n";
        cout << "8. Check low stock\n";
        cout << "9. Restock medication\n";
        cout << "10. Check expired medications\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // remove leftover newline

        if (choice == 1) {
            // Add Pharmacy
            string name;
            cout << "Enter Pharmacy Name: ";
            getline(cin, name);

            Pharmacy p;
            p.setPharmacyName(name);

            if (db.savePharmacy(p)) {
                cout << "Pharmacy added successfully with ID: " << p.getPharmacyId() << endl;
            } else {
                cout << "Error saving pharmacy." << endl;
            }
        }

        else if (choice == 2) {
            // Add Medication
            int pharmacyId;
            cout << "Enter Pharmacy ID: ";
            cin >> pharmacyId;
            cin.ignore();

            string medName, desc, barcode;
            double price;
            int quantity, day, month, year;

            cout << "Medication Name: ";
            getline(cin, medName);
            cout << "Description: ";
            getline(cin, desc);
            cout << "Price: ";
            cin >> price;
            cout << "Quantity: ";
            cin >> quantity;
            cin.ignore();
            cout << "Barcode: ";
            getline(cin, barcode);
            cout << "Expiry Day Month Year: ";
            cin >> day >> month >> year;
            cin.ignore();

            Medication med(medName, desc, price, quantity, barcode, Date(day, month, year));
            if (db.saveMedication(pharmacyId, med)) {
                cout << "Medication saved successfully!" << endl;
            } else {
                cout << "Error saving medication." << endl;
            }
        }

        else if (choice == 3) {
            // Add Customer
            int pharmacyId;
            cout << "Enter Pharmacy ID: ";
            cin >> pharmacyId;
            cin.ignore();

            string custName, city, street, email, phone;
            cout << "Customer Name: ";
            getline(cin, custName);
            cout << "City: ";
            getline(cin, city);
            cout << "Street: ";
            getline(cin, street);
            cout << "Email: ";
            getline(cin, email);
            cout << "Phone: ";
            getline(cin, phone);

            Customer cust(custName, Address(email, city, phone, street));
            if (db.saveCustomer(pharmacyId, cust)) {
                cout << "Customer saved successfully!" << endl;
            } else {
                cout << "Error saving customer." << endl;
            }
        }

        else if (choice == 4) {
            // Remove Medication
            int pharmacyId;
            string medName;
            cout << "Enter Pharmacy ID: ";
            cin >> pharmacyId;
            cin.ignore();
            cout << "Enter Medication Name to remove: ";
            getline(cin, medName);

            if (db.deleteMedication(pharmacyId, medName)) {
                cout << "Medication removed successfully!" << endl;
            } else {
                cout << "Error removing medication." << endl;
            }
        }

        else if (choice == 5) {
            // Remove Customer
            int pharmacyId;
            string custName;
            cout << "Enter Pharmacy ID: ";
            cin >> pharmacyId;
            cin.ignore();
            cout << "Enter Customer Name to remove: ";
            getline(cin, custName);

            if (db.deleteCustomer(pharmacyId, custName)) {
                cout << "Customer removed successfully!" << endl;
            } else {
                cout << "Error removing customer." << endl;
            }
        }

        else if (choice == 6) {
            // Display Medication
            int pharmacyId;
            cout << "Enter Pharmacy ID: ";
            cin >> pharmacyId;
            cin.ignore();

            int medCount;
            Medication* meds = db.loadMedications(pharmacyId, medCount);
            if (!meds || medCount == 0) {
                cout << "No medications found." << endl;
            } else {
                cout << "Medications for Pharmacy ID " << pharmacyId << ":\n";
                for (int i = 0; i < medCount; i++) {
                    cout << meds[i].getMedName() << " | Qty: " << meds[i].getQuantityInStock()
                         << " | Price: " << meds[i].getPrice() << endl;
                }
                delete[] meds;
            }
        }

        else if (choice == 7) {
            // Display Customers
            int pharmacyId;
            cout << "Enter Pharmacy ID: ";
            cin >> pharmacyId;
            cin.ignore();

            int custCount;
            Customer* custs = db.loadCustomers(pharmacyId, custCount);
            if (!custs || custCount == 0) {
                cout << "No customers found." << endl;
            } else {
                cout << "Customers for Pharmacy ID " << pharmacyId << ":\n";
                for (int i = 0; i < custCount; i++) {
                    cout << custs[i].getCustomerName() << " | " << custs[i].getAddress().getCity() << endl;
                }
                delete[] custs;
            }
        }

        else if (choice == 8) {
            // Check Low Stock
            int pharmacyId;
            cout << "Enter Pharmacy ID: ";
            cin >> pharmacyId;
            cin.ignore();

            int medCount;
            Medication* meds = db.loadMedications(pharmacyId, medCount);
            if (!meds) continue;

            cout << "Low stock medications (<5 units):\n";
            for (int i = 0; i < medCount; i++) {
                if (meds[i].getQuantityInStock() < 5) {
                    cout << meds[i].getMedName() << " | Qty: " << meds[i].getQuantityInStock() << endl;
                }
            }
            delete[] meds;
        }

        else if (choice == 9) {
            // Restock Medication
            int pharmacyId;
            string medName;
            int quantity;
            cout << "Enter Pharmacy ID: ";
            cin >> pharmacyId;
            cin.ignore();
            cout << "Medication Name: ";
            getline(cin, medName);
            cout << "Quantity to add: ";
            cin >> quantity;
            cin.ignore();

            // Load meds, find the one to restock
            int medCount;
            Medication* meds = db.loadMedications(pharmacyId, medCount);
            if (!meds) continue;

            int currentQty = -1;
            for (int i = 0; i < medCount; i++) {
                if (meds[i].getMedName() == medName) {
                    currentQty = meds[i].getQuantityInStock() + quantity;
                    break;
                }
            }
            delete[] meds;

            if (currentQty != -1 && db.updateMedicationStock(pharmacyId, medName, currentQty)) {
                cout << "Medication restocked successfully!" << endl;
            } else {
                cout << "Error restocking medication." << endl;
            }
        }

        else if (choice == 10) {
            // Check Expired Medications
            int pharmacyId;
            cout << "Enter Pharmacy ID: ";
            cin >> pharmacyId;
            cin.ignore();

            int medCount;
            Medication* meds = db.loadMedications(pharmacyId, medCount);
            if (!meds) continue;

            Date today; // Assuming default constructor gives current date
            cout << "Expired medications:\n";
            for (int i = 0; i < medCount; i++) {
                if (meds[i].getExpiryDate() < today) {
                    cout << meds[i].getMedName() << " | Exp: "
                         << meds[i].getExpiryDate().getDay() << "/"
                         << meds[i].getExpiryDate().getMonth() << "/"
                         << meds[i].getExpiryDate().getYear() << endl;
                }
            }
            delete[] meds;
        }
    }

    cout << "Exiting program. Goodbye!" << endl;
    return 0;
}
