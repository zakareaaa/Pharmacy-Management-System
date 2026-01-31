#include"address.h"

//initializing constructor
Address::Address(string email_, string city_, string phoneNum_, string streetName_) {
  setEmail(email_);
  setCity(city_);
  setPhoneNum(phoneNum_);
  setStreetName(streetName_);
}
//Setters and getters
void Address::setEmail(string &email_) {
  //checks if email is valid
  while(email_ == ""){
    cout << "Please enter a valid email: ";
    cin >> email_;
  }
  email = email_;
}
void Address::setCity(string &city_) {
  //checks if city is valid
  while(city_ == ""){
    cout << "Please enter a valid city: ";
    cin >> city_;
  }
  city = city_;
}
void Address::setPhoneNum(string &phoneNum_) {
  //checks if phone number is valid
  while(phoneNum_== ""){
    cout << "Please enter a valid phone number: "<<endl;
    cin >> phoneNum_;
  }
  PhoneNum = phoneNum_;
}
void Address::setStreetName(string &streetName_) {
  //checks if street name is valid
  while(streetName_ == ""){
    cout << "Please enter a valid street name: "<<endl;
    cin >> streetName_;
  }
  streetName = streetName_;
}
string Address::getStreetName() {return streetName;}
string Address::getEmail() { return email;}
string Address::getPhonenUm() { return PhoneNum;}
string Address::getCity() { return city;}
//Display Function:
void Address::Display() {
  cout << "Address Information:" << endl;
  cout << "Email: " << email << endl;
  cout << "City: " << city << endl;
  cout << "Phone Number: " << PhoneNum << endl;
  cout << "Street Name: " << streetName << endl;
}




