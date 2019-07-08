#pragma once

#include <iostream>
#include <string>
#include <vector>


#include "defs.h"
#include "packet.h"
#include "address.h"

using namespace std;

class Client{
 private:
  string name; // name of the client
  unsigned VATnumber; // VAT number of client
  unsigned short familySize;  // number of family members
  Address address; // client's address
  vector<unsigned int> packets = {0}; // vector to store client's bought packets ids
  unsigned totalPurchased; // total value spent by the client

 public:
  Client(string name, unsigned VATnumber, unsigned short familySize, Address address);  // for a new client
  Client(string name, unsigned VATnumber, unsigned short familySize, Address address, vector<unsigned int> packets, unsigned totalPurchased);  // client read from file

  // GET methods
  
  string getName() const;
  unsigned getVATnumber() const;
  unsigned short getFamilySize() const;
  Address getAddress() const;
  vector<unsigned int> getPacketList() const;
  unsigned getTotalPurchased() const;
  
  // SET methods
  
  void setName(string name);
  void setVATnumber(unsigned VATnumber);
  void setFamilySize(unsigned short familySize);
  void setAddress(Address address);
  void setPacketList(vector<unsigned int> packets);
  unsigned setTotalPurchased(unsigned totalPurchased);
  // adress SET methods
  void setClientStreet(string street);
  void setClientDoorNumber(string door_n);
  void setClientFloor(string floor);
  void setClientPostalCode(string postal);
  void setClientLocation(string location);
  
  // other methods

  friend ostream& operator<<(ostream& out, const Client & client);
};
