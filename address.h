#pragma once

#include <iostream>
#include <string>
#include <vector>


#include "defs.h"

using namespace std;

class Address {
 private:
  string street; // street name
  string doorNumber; // doro number
  string floor; // floor number ("-" is not applicable)
  string postalCode; // postal code
  string location; // site

 public:
  Address();
  Address(string str);
  Address(string street, string doorNumber, string floor, string postalCode, string location);

  // metodos GET
  string getStreet() const;
  string getDoorNumber() const;
  string getFloor() const;
  string getPostalCode() const;
  string getLocation() const;
  
  // metodos SET
  void setStreet(string street);
  void setDoorNumber(string doorNumber);
  void setFloor(string floor);
  void setPostalCode(string postalCode);
  void setLocation(string  location);

  // outros */
  
  friend ostream& operator<<(ostream& out, const Address & address);

};
