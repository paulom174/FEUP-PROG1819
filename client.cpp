#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "client.h"

using namespace std;

Client::Client(string name, unsigned VATnumber, unsigned short familySize, Address address) {
  this->name = name;
  this->VATnumber = VATnumber;
  this->familySize = familySize;
  this->address = address;
  this->totalPurchased = 0;
}

Client::Client(string name, unsigned VATnumber, unsigned short familySize, Address address, vector<unsigned int> packets, unsigned totalPurchased) {
  
  this->name = name;
  this->VATnumber = VATnumber;
  this->familySize = familySize;
  this->address = address;
  this->packets = packets;
  this->totalPurchased = totalPurchased;
}

  // GET methods

string Client::getName() const{
  
  return name;
}
  
unsigned Client::getVATnumber() const{
  
  return VATnumber;
}

unsigned short Client::getFamilySize() const{
  
  return familySize;
}

Address Client::getAddress() const{
  
  return address;
}

vector<unsigned int> Client::getPacketList() const{
  return packets;
}

unsigned Client::getTotalPurchased() const{
  
  return totalPurchased;
}
  
  // metodos SET
	  
void Client::setName(string name){
  
  this->name = name;
}

void Client::setVATnumber(unsigned VATnumber){
  
  this->VATnumber = VATnumber;
}

void Client::setFamilySize(unsigned short familySize){
  
  this->familySize = familySize;
}
void Client::setAddress(Address address){
  
  this->address = address;
}
void Client::setPacketList(vector<unsigned int> packets){
  
  this->packets = packets;
}
unsigned Client::setTotalPurchased(unsigned totalPurchased){
  
  this->totalPurchased = totalPurchased;
}

void Client::setClientStreet(string street) {
  this->address.setStreet(street);
}

void Client::setClientDoorNumber(string door_n) {
  this->address.setDoorNumber(door_n);
}

void Client::setClientFloor(string floor) {
  this->address.setFloor(floor);
}

void Client::setClientPostalCode(string postal) {
  this->address.setPostalCode(postal);
}

void Client::setClientLocation(string location) {
  this->address.setLocation(location);
}
  
  // other methods

ostream& operator<<(ostream& out, const Client & client) {
  out << "Name: " << client.getName() << endl;
  out << "VAT: " << client.getVATnumber() << endl;
  out << "Family Size: " << client.getFamilySize() << endl;
  out << "Adress: " << client.getAddress() << endl;
  out << "Packets: ";
  for(int i=0; i<client.getPacketList().size(); i++) {
    out << client.getPacketList().at(i) << " ";
  }
  out << endl << "Total Spent: " << client.getTotalPurchased() << endl;

  return out;
}
