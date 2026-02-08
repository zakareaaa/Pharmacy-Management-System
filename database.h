#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include "medication.h"
#include "customer.h"
#include "pharmacy.h"

using namespace std;

class Database{
    private:
        sqlite3* db;
        string dbPath;
        bool executeSQL(const string& sql);
    public:
        Database(const string& path = "pharmacy.db");
        ~Database();

        bool initializeDatabase();

        bool savePharmacy(const Pharmacy& pharmacy);
        bool loadPharmacy(const Pharmacy& pharmacy);
        bool deletePharmacy(int pharmacyId);
        int getPharmacyCount();

        bool saveCustomer(int pharmacyId, const Customer& customer);
        Customer* loadCustomers(int pharmacyId, int& count);
        bool deleteCustomer(int pharmacyId, const string& customerName);

        bool saveMedication(int pharmacyId, const Medication& med);
        Medication* loadMedications(int pharmacyId, int& count);
        bool deleteMedication(int pharmacyId, const string& medName);
        bool updateMedicationStock(int pharmacyId, const string& medName, int newQuantity);

        bool isConnected();
        void closeConnection();
  
};

#endif 