#include "date.h"
#include <iostream>
#include <string>
using namespace std;
#ifndef MEDICATION_H
#define MEDICATION_H
class Medication {
private:
  int medId;
  string medName;
  string description;
  double price;
  int quantityInStock;
  string barcode;
  static int id;
  Date expDate;
public:
  // Default Parameterized Constructor
  Medication(string Name = "Uknown", string desc = "Uknown", double price_ = 0,
             int quant = 0, string code = "Uknown", Date exp = Date());
  // Setters
  void setMedName(string medName_);
  void setDescription(string description_);
  void setPrice(double price_);
  void setQuantityInStock(int quantityInStock_);
  void setExpiryDate(const Date&);
  void setBarcode(string barcode_);
  // Getters
  string getMedName() const;
  string getDescription() const;
  double getPrice() const;
  int getQuantityInStock() const;
  string getBarcode() const;
  Date getExpiryDate() const;
  int getMedId()const;

  void print();
};

class Prescription:public Medication{
  private:
  int FDA;
  Date approvalDate;
  public:
  Prescription(string Name = "Uknown",string desc = "Uknown",double price_ = 0,int quant = 0,string code = "Uknown",int eday = 0,int emonth = 0,int eyear = 0,int FDA_ = 0,int day=1,int month=1,int year=2000):approvalDate(Date(day,month,year)){
    FDA = FDA_;
    setMedName(Name);
    setDescription(desc);
    setPrice(price_);
    setQuantityInStock(quant);
    setBarcode(code);
    setExpiryDate(Date(eday,emonth,eyear));
  }
  void setFDA(int a){
    while(a<0){
      cout<<"Enter Valid Num: ";
      cin>>a;
    }
    cout<<endl;
    FDA = a;
  }
  void setApprovalDate(const Date &d){
    approvalDate.setDay(d.getDay());
    approvalDate.setMonth(d.getMonth());
    approvalDate.setYear(d.getYear());
  }
  Date getApproval(){ return approvalDate;}
  int getFDA(){ return FDA;}
  void printPrescription(){
  print();
  cout<<"FDA: "<<getFDA()<<endl;
  getApproval().printDate();
  }
};
class OffTheShelf:public Medication{
private:
bool BOGOF;
Date OfferEnds;
public:
OffTheShelf(string Name = "Uknown",string desc = "Uknown",double price_ = 0,int quant = 0,string code = "Uknown",int eday = 0,int emonth = 0,int eyear = 0,bool bogof = false, int day = 0, int month = 0, int year = 0):OfferEnds(day,month,year){
  BOGOF = bogof;
  setMedName(Name);
  setDescription(desc);
  setPrice(price_);
  setQuantityInStock(quant);
  setBarcode(code);
  setExpiryDate(Date(eday,emonth,eyear));
}
void setBOGOF(bool a){
  BOGOF = a;
}
bool getBOGOF(){ return BOGOF;}
void setOfferEnds(Date a){
  OfferEnds.setDay(a.getDay());
  OfferEnds.setMonth(a.getMonth());
  OfferEnds.setYear(a.getYear());
}
void printOfftheshelf(){
  print();
  if(BOGOF){
    if(OfferEnds.getMonth()+3>12){
      OfferEnds.setMonth((OfferEnds.getMonth()+3)-12);
      OfferEnds.setYear(OfferEnds.getYear()+1);
    }
    else{
      OfferEnds.setMonth(OfferEnds.getMonth()+3);
    }
  }
  else{
    OfferEnds.setYear(OfferEnds.getYear()+2);
  }
  cout<<"Discount: ";
  if(BOGOF){
    cout<<"Yes"<<endl;
  }
  else{
    cout<<"No"<<endl;
  }
  OfferEnds.printDate();
}
};
#endif