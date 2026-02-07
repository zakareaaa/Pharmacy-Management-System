#include "database.h"
#include "date.h"
#include <iostream>
#include <sstream>

using namespace std;

Database::Database(const string& path) : db(nullptr), dbPath(path) {
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc != SQLITE_OK) {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        db = nullptr;
    } else {
        cout << "Database connected successfully!" << endl;
    }
}

Database::~Database() {
    closeConnection();
}

void Database::closeConnection() {
    if (db != nullptr) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool Database::isConnected() {
    return db != nullptr;
}

bool Database::executeSQL(const string& sql) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

bool Database::initializeDatabase() {
    if (!isConnected()) return false;

    // Create Pharmacies table
    string createPharmacies = R"(
        CREATE TABLE IF NOT EXISTS Pharmacies (
            pharmacy_id INTEGER PRIMARY KEY,
            pharmacy_name TEXT NOT NULL
        );
    )";

    // Create Medications table
    string createMedications = R"(
        CREATE TABLE IF NOT EXISTS Medications (
            med_id INTEGER PRIMARY KEY AUTOINCREMENT,
            pharmacy_id INTEGER,
            med_name TEXT NOT NULL,
            description TEXT,
            price REAL,
            quantity INTEGER,
            barcode TEXT,
            expiry_day INTEGER,
            expiry_month INTEGER,
            expiry_year INTEGER,
            FOREIGN KEY (pharmacy_id) REFERENCES Pharmacies(pharmacy_id) ON DELETE CASCADE
        );
    )";

    // Create Customers table
    string createCustomers = R"(
        CREATE TABLE IF NOT EXISTS Customers (
            customer_id INTEGER PRIMARY KEY AUTOINCREMENT,
            pharmacy_id INTEGER,
            customer_name TEXT NOT NULL,
            email TEXT,
            city TEXT,
            phone_number TEXT,
            street_name TEXT,
            FOREIGN KEY (pharmacy_id) REFERENCES Pharmacies(pharmacy_id) ON DELETE CASCADE
        );
    )";

    return executeSQL(createPharmacies) && 
           executeSQL(createMedications) && 
           executeSQL(createCustomers);
}

bool Database::savePharmacy(const Pharmacy& pharmacy) {
    if (!isConnected()) return false;

    stringstream ss;
    ss << "INSERT OR REPLACE INTO Pharmacies (pharmacy_id, pharmacy_name) VALUES ("
       << pharmacy.getPharmacyId() << ", '" 
       << pharmacy.getPharmacyName() << "');";

    return executeSQL(ss.str());
}

bool Database::saveMedication(int pharmacyId, const Medication& med) {
    if (!isConnected()) return false;

    Date expiry = med.getExpiryDate();

    stringstream ss;
    ss << "INSERT INTO Medications (pharmacy_id, med_name, description, price, quantity, barcode, "
       << "expiry_day, expiry_month, expiry_year) VALUES ("
       << pharmacyId << ", '"
       << med.getMedName() << "', '"
       << med.getDescription() << "', "
       << med.getPrice() << ", "
       << med.getQuantityInStock() << ", '"
       << med.getBarcode() << "', "
       << expiry.getDay() << ", "
       << expiry.getMonth() << ", "
       << expiry.getYear() << ");";

    return executeSQL(ss.str());
}

Medication* Database::loadMedications(int pharmacyId, int& count) {
    if (!isConnected()) {
        count = 0;
        return nullptr;
    }

    stringstream ss;
    ss << "SELECT COUNT(*) FROM Medications WHERE pharmacy_id = " << pharmacyId << ";";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, ss.str().c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        count = 0;
        return nullptr;
    }

    sqlite3_step(stmt);
    count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    if (count == 0) return nullptr;

    Medication* medications = new Medication[count];

    ss.str("");
    ss << "SELECT med_name, description, price, quantity, barcode, "
       << "expiry_day, expiry_month, expiry_year FROM Medications WHERE pharmacy_id = " 
       << pharmacyId << ";";

    rc = sqlite3_prepare_v2(db, ss.str().c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        delete[] medications;
        count = 0;
        return nullptr;
    }

    int index = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        string desc = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        double price = sqlite3_column_double(stmt, 2);
        int quantity = sqlite3_column_int(stmt, 3);
        string barcode = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        int day = sqlite3_column_int(stmt, 5);
        int month = sqlite3_column_int(stmt, 6);
        int year = sqlite3_column_int(stmt, 7);

        medications[index] = Medication(name, desc, price, quantity, barcode, Date(day, month, year));
        index++;
    }

    sqlite3_finalize(stmt);
    return medications;
}

bool Database::saveCustomer(int pharmacyId, const Customer& customer) {
    if (!isConnected()) return false;

    Address addr = customer.getAddress();

    stringstream ss;
    ss << "INSERT INTO Customers (pharmacy_id, customer_name, email, city, phone_number, street_name) VALUES ("
       << pharmacyId << ", '"
       << customer.getCustomerName() << "', '"
       << addr.getEmail() << "', '"
       << addr.getCity() << "', '"
       << addr.getPhonenUm() << "', '"
       << addr.getStreetName() << "');";

    return executeSQL(ss.str());
}

Customer* Database::loadCustomers(int pharmacyId, int& count) {
    if (!isConnected()) {
        count = 0;
        return nullptr;
    }

    stringstream ss;
    ss << "SELECT COUNT(*) FROM Customers WHERE pharmacy_id = " << pharmacyId << ";";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, ss.str().c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        count = 0;
        return nullptr;
    }

    sqlite3_step(stmt);
    count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    if (count == 0) return nullptr;

    Customer* customers = new Customer[count];

    ss.str("");
    ss << "SELECT customer_name, email, city, phone_number, street_name FROM Customers WHERE pharmacy_id = " 
       << pharmacyId << ";";

    rc = sqlite3_prepare_v2(db, ss.str().c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        delete[] customers;
        count = 0;
        return nullptr;
    }

    int index = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        string email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string city = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        string phone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        string street = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

        customers[index] = Customer(name, Address(email, city, phone, street));
        index++;
    }

    sqlite3_finalize(stmt);
    return customers;
}

bool Database::deleteMedication(int pharmacyId, const string& medName) {
    if (!isConnected()) return false;

    stringstream ss;
    ss << "DELETE FROM Medications WHERE pharmacy_id = " << pharmacyId 
       << " AND med_name = '" << medName << "';";

    return executeSQL(ss.str());
}

bool Database::deleteCustomer(int pharmacyId, const string& customerName) {
    if (!isConnected()) return false;

    stringstream ss;
    ss << "DELETE FROM Customers WHERE pharmacy_id = " << pharmacyId 
       << " AND customer_name = '" << customerName << "';";

    return executeSQL(ss.str());
}

bool Database::updateMedicationStock(int pharmacyId, const string& medName, int newQuantity) {
    if (!isConnected()) return false;

    stringstream ss;
    ss << "UPDATE Medications SET quantity = " << newQuantity 
       << " WHERE pharmacy_id = " << pharmacyId 
       << " AND med_name = '" << medName << "';";

    return executeSQL(ss.str());
}

int Database::getPharmacyCount() {
    if (!isConnected()) return 0;

    string sql = "SELECT COUNT(*) FROM Pharmacies;";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) return 0;

    sqlite3_step(stmt);
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    return count;
}

bool Database::deletePharmacy(int pharmacyId) {
    if (!isConnected()) return false;

    stringstream ss;
    ss << "DELETE FROM Pharmacies WHERE pharmacy_id = " << pharmacyId << ";";

    return executeSQL(ss.str());
}