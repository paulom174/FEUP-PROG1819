#include <iostream>
#include <vector>

#include "address.h"

using namespace std;


Address::Address(){
  //default constructor
}

Address::Address(string str){

     vector<string>temp;
    int pos = 0, i = 0, pos_final = 0;

    //Dividing the string in different address members
    int slash = str.find("/", pos);

    while(pos < slash){
            temp.push_back(str.substr(pos, slash-pos));
            
            pos = slash +1;
            slash = str.find("/", pos);
    }

    temp.push_back(str.substr(pos, slash-pos));

    //Removing spaces from strings
    for(int i = 0; i < temp.size(); i++){
      pos = temp[i].find_first_not_of(' ', 0);
      pos_final = temp[i].find_last_not_of(' ', temp[i].back());
      temp[i] = temp[i].substr(pos, pos_final - pos +1);
    }


    this->street = temp[0];
    this->doorNumber = temp[1];
    this->floor = temp[2];
    this->postalCode = temp[3];
    this->location = temp[4];
}

Address::Address(string street, string doorNumber, string floor, string postalCode, string location){

  this->street = street;
  this->doorNumber = doorNumber;
  this->floor = floor;
  this->postalCode = postalCode;
  this->location = location;
}

  // metodos GET


string Address::getStreet() const{

  return street;
}

string Address::getDoorNumber() const{

  return doorNumber;
}

string Address::getFloor() const{
  
  return floor;
}

string Address::getPostalCode() const{

  return postalCode;
}

string Address::getLocation() const{

  return location;
}


  // metodos SET

void Address::setStreet(string street){

  this->street = street;
}

void Address::setDoorNumber(string doorNumber){

  this->doorNumber = doorNumber;
}

void Address::setFloor(string floor){

  this->floor = floor;
}

void Address::setPostalCode(string postalCode){

  this->postalCode = postalCode;
}

void Address::setLocation(string  location){

  this->location = location;
}


/*********************************
 * Mostrar Address
 ********************************/  

// discplyes an address in a nice format
ostream& operator<<(ostream& out, const Address & address){
  out << address.getStreet() << ", " << address.getDoorNumber();
  if(address.getFloor()!=" - ") cout << ", " << address.getFloor();
  out << ", " << address.getPostalCode() << " " << address.getLocation();

  return out;
}
