#include "packet.h"

Packet::Packet(int id, vector<string> sites, Date inicio, Date fim, double precoPessoa, unsigned maxPessoas, unsigned reserved){

  this->id = id;
  this->sites = sites;
  this->begin = inicio;
  this->end = fim;
  this->pricePerPerson = precoPessoa;
  this->maxPersons = maxPersons;
  this->reserved = reserved;
}

  // metodos GET

int Packet::getId() const{

  return id;
}

vector<string> Packet::getSites() const{

  return sites;
}

Date Packet::getBeginDate() const{

  return begin;
}

Date Packet::getEndDate() const{

  return end;
}

double Packet::getPricePerPerson() const{

  return pricePerPerson;
}

unsigned Packet::getMaxPersons() const{

  return maxPersons;
}

unsigned Packet::getReserved() const{

  return reserved;
}

  // metodos SET

void Packet::setId(int id){

  this->id = id;
}

void Packet::setSites(vector<string> sites){

  this->sites = sites;
}

void Packet::setBeginDate(Date begin){

  this->begin = begin;
}

void Packet::setEndDate(Date end){

  this->end = end;
}

void Packet::setPricePerPerson(double pricePerPerson){

  this->pricePerPerson = pricePerPerson;
}

void Packet::setMaxPersons(unsigned maxPersons){

  this->maxPersons = maxPersons;
}

void Packet::setReserved(unsigned reserved){

  this->reserved = reserved;
}


/*********************************
 * Show Packet information
 ********************************/  

// shows a packet content 
ostream& operator<<(ostream& out, const Packet & packet){
  out << "ID: " << packet.getId() << endl;
  cout << "Sites: ";
  for(int i=0; i<packet.getSites().size(); i++) {
    if(i==0) cout << packet.getSites().at(i) << " - ";
    else if(i==1) cout << packet.getSites().at(i);
    else cout << ", " << packet.getSites().at(i);
  }
  out << endl << "Begin date: " << packet.getBeginDate() << endl;
  out << "End date: " << packet.getEndDate() << endl;
  out << "Price per person: " << packet.getPricePerPerson() << endl;
  out << "Max capacity: " << packet.getMaxPersons() << endl;
  out << "Reserved: " << packet.getReserved();

  return cout;
}


