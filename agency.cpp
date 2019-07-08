#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <sstream>
#include <cstring>
#include <regex>
#include <limits>
#include "agency.h"
#include "address.h"
#include "macros.h"

using namespace std;

//total purchases, for now, will remain at zero for every client
Agency::Agency(string a_fname) {
  string a_name, a_url, a_addr, p_fname, c_fname;
  ifstream a_file, c_file, p_file;
  string line;
  //reading agency info
  a_file.open(a_fname);
  if(a_file.is_open()) {
    //setting agency name
    getline(a_file,line);
    Agency::setName(line);
    //setting agency VAT
    getline(a_file,line);
    Agency::setVATnumber(stoi(line));
    //setting agency URL
    getline(a_file,line);
    Agency::setURL(line);
    //setting agency address
    getline(a_file,line);
    Address aux(line);
    Agency::setAddress(aux);
    //reading client and packets file name
    getline(a_file,line);
    Agency::setClientsPath(line);
    getline(a_file,line);
    Agency::setPacketsPath(line);
  }
  //reading clients info
  c_file.open("clients.txt", ios::in);
  Client current_c();
  if(c_file.is_open()) {
    vector<Client> a_clients;
    string c_name;
    unsigned VAT_n;
    unsigned short f_size;
    vector<unsigned int> c_packets;
    unsigned c_tPurchases;
    while(1) {
      getline(c_file >> std::ws,line);
      c_name = line;
      getline(c_file,line);
      VAT_n = stoi(line);
      getline(c_file,line);
      f_size = stoi(line);
      getline(c_file,line);
      Address c_adress(line);
      //bough travel pack IDs parsing
      string token;
      string delimiter = "; ";
      size_t pos = 0;
      getline(c_file, line);

      while(pos!=string::npos) {
        pos = line.find(delimiter);
        token = line.substr(0,pos);
        c_packets.push_back(stoi(token));
        line.erase(0,pos+delimiter.length());
      }

      //adding curent client to client list
      a_clients.push_back(Client(c_name, VAT_n, f_size, c_adress, c_packets, 0));
      //resetting current client tp vector for re-use
      c_packets.clear();
      //checking if there's another client or if its EOF
      getline(c_file,line);
      if(c_file.eof()) {
        setClients(a_clients);
        break;
      }
      else if(line=="::::::::::") continue;
    }
  }
  else if(c_file.fail() || !c_file.is_open()){
    std::cerr << strerror(errno) << std::endl;
  }
 
  //parsing travel packs info
  p_file.open(packetsPath);
  if(p_file.is_open()) {
    //variables to fill constructor with
    int p_id;
    vector<string> p_sites;
    //Date p_begin;
    //Date p_end;
    double p_ppp;
    unsigned p_maxPersons;
    unsigned p_reserved;
    //
    string token;
    getline(p_file,line);
    lastCreatedPacketId = stoi(line);
    while(1) {
      getline(p_file,line);
      p_id = stoi(line);
      //turistic spots parsing
      size_t pos = 0;
      string delimiter = ", ";
      getline(p_file,line);
      while(pos!=string::npos) {
        pos = line.find(delimiter);
        string token = line.substr(0,pos);
        token = line.substr(0,pos);
        p_sites.push_back(token);
        line.erase(0,pos+delimiter.length());
        //delimiter = ", ";
      }
      //reading begin date 
      getline(p_file,line);
      Date p_begin(line);
      //reading end date
      getline(p_file,line);
      Date p_end(line);
      //reading price per person
      getline(p_file,line);
      p_ppp = stoi(line);
      //reading max capacity
      getline(p_file,line);
      p_maxPersons = stoi(line);
      //reading sold packets
      getline(p_file,line);
      p_reserved = stoi(line);
      //adding current travel pack to agency vector
      packets.push_back(Packet(p_id,p_sites,p_begin,p_end,p_ppp,(double)p_maxPersons,p_reserved));
      //resetting p_sites vecgor for re-use
      p_sites.clear();
      //checking if theres another packet or if its EOF
      getline(p_file,line);
      if(p_file.eof()) break;
      else if (line=="::::::::::") continue;
    }
  }
  LocationsMostVisited(10);
}

  // metodos GET
string Agency::getName() const {
  return name;
}

unsigned Agency::getVATnumber() const {
  return VATnumber;
}

Address Agency::getAddress() const {
  return address;
}

string Agency::getURL() const {
  return URL;
}

string Agency::getClientsPath() const { 
  return clientsPath;
}

string Agency::getPacketsPath() const { 
  return packetsPath;
}

vector<Client> Agency::getClients() const {
  return clients;
}

vector<Packet> Agency::getPackets() const {
  return packets;
}

bool Agency::getClientsInfoHasChanged() const {
  return clientsInfoHasChanged;
}

bool Agency::getPacketsInfoHasChanged() const {
  return packetsInfoHasChanged;
}

vector<string> Agency::getN_most_visited_sites() const{
  return n_most_visited_sites;
}

vector<string> Agency::getPacketsSites(unsigned id) const{
  for(int i = 0; i < packets.size(); i++){
    if(id == packets.at(i).getId()){
      return packets.at(i).getSites();
    }
  }
}



  
  // SET Methods

void Agency::setName(string name) {
  this->name = name;
}

void Agency::setVATnumber(unsigned VATnumber) {
  this->VATnumber = VATnumber;
}

void Agency::setAddress(Address address) {
  this->address = address;
}

void Agency::setURL(string url) {
  this->URL = url;
}

void Agency::setClientsPath(string clientPath) {
  this->clientsPath = clientPath;
}

void Agency::setPacketsPath(string travelPath) {
  this->packetsPath = travelPath;
}

void Agency::setClients(vector<Client> & clients) {
  this->clients  = clients;
}
  
void Agency::setPackets(vector<Packet> & packets){
  this->packets = packets;
}

void Agency::setClientsInfoHasChanged(bool clients_changed){
  this->clientsInfoHasChanged = clients_changed;
}

void Agency::setPacketsInfoHasChanged(bool clients_changed){
  this->packetsInfoHasChanged = clients_changed;
}

void Agency::setN_most_visited_sites(vector<string> visited_sites){
  this->n_most_visited_sites = visited_sites;
}

// REMOVE methods

//Returns 0 if given client is removed successfuly, -1 otherwise
int Agency::removeClient(string name) {
  for(int i=0; i<clients.size(); i++) {
    if(clients.at(i).getName()==name) {
      clients.erase(clients.begin() + i);
      return 0;
    }
  }
  return -1;
}


//unnecessary since packets never really get deleted. only made unavailable
int Agency::removePacket(unsigned int id) {
  for(int i=0; i<packets.size(); i++) {
    if(packets.at(i).getId()==id) {
      packets.erase(packets.begin() + i);
      return 0;
    }
  }
  return -1;
}

// EDIT methods
int Agency::editClientName(string name, string new_name) {
  for(int i=0; i<clients.size(); i++) {
    if(clients.at(i).getName().compare(name)==0) {
      clients.at(i).setName(new_name);
      return 0;
    }
  }
  return -1;
}

int Agency::editClientVAT(string name, unsigned new_VAT) {
  for(int i=0; i<clients.size(); i++) {
    if(clients.at(i).getName()==name) {
      clients.at(i).setVATnumber(new_VAT);
      return 0;
    }
  }
  return -1;
}

int Agency::editClientFamilySize(string name, unsigned new_fs) {
  for(int i=0; i<clients.size(); i++) {
    if(clients.at(i).getName()==name) {
      clients.at(i).setFamilySize(new_fs);
      return 0;
    }
  }
  return -1;
}

int Agency::editClientAdress(string name) {
  int input = 0;
  string new_info;
  for(int i=0; i<clients.size(); i++) {
    if(clients.at(i).getName()==name) {
      cout << "What member of adress you want to change?" << endl;
      cout << "1: Street\n";
      cout << "2: Door Number\n";
      cout << "3: Floor\n";
      cout << "4: Postal Code\n";
      cout << "5: Location\n";
      cin >> input;

      while(input < 1 && input >5) {
      cout << "Input valid option: ";
      cin >> input;
      cout << endl;
      }

      switch(input) {
        case(1):
          cout << "Input new street: ";
          cin.ignore(1000, '\n');
          getline(cin, new_info);
          clients.at(i).setClientStreet(new_info);
          cout << endl;
          return 0;
        case(2):
          cout << "Input door number: ";
          cin.ignore(1000, '\n');           
          getline(cin, new_info);
          clients.at(i).setClientDoorNumber(new_info);
          cout << endl;
          return 0;
        case(3):
          cout << "Input floor number: ";
          cin.ignore(1000, '\n');
          getline(cin, new_info);
          clients.at(i).setClientFloor(new_info);
          cout << endl;
          return 0;
        case(4):
          cout << "Input postal code: ";
          cin.ignore(1000, '\n');           
          getline(cin, new_info);
          clients.at(i).setClientPostalCode(new_info);
          cout << endl;
          return 0;
        case(5):
          cout << "Input location: ";
          cin.ignore(1000, '\n');           
          getline(cin, new_info);
          clients.at(i).setClientLocation(new_info);
          cout << endl;
          return 0;
        default:
          break;
      }
    }
  }
  cout << "No valid option was chosen" << endl;
  return -1;
}

int Agency::editClientPurchases(string name, int value) {
  for(int i=0; i<clients.size(); i++) {
    if(clients.at(i).getName()==name) {
      clients.at(i).setTotalPurchased(value);
      return 0;
    }
  }
  return -1;
}

int Agency::addPacketToClient(string name, int id) {
  int availability = checkPacketAvailability(id);
  if(availability==-2) {
    cout << "Specified packet was not found." << endl;
    return -1;
  }
  for(int i=0; i<clients.size(); i++) {
    if(clients.at(i).getName()==name) {
      vector<unsigned> packets = clients.at(i).getPacketList();
      packets.push_back(id);
      clients.at(i).setPacketList(packets);
    }
  }
  return 0;
}

int Agency::removePacketFromClient(string name, int id) {
  int availability = checkPacketAvailability(id);
  if(availability==-2) {
    cout << "Specified packet was not found." << endl;
    return -1;
  }

  for(int i=0; i<clients.size(); i++) {
    if(clients.at(i).getName()==name) {
      vector<unsigned> packets = clients.at(i).getPacketList();
      packets.erase(remove(packets.begin(), packets.end(), id), packets.end());
      clients.at(i).setPacketList(packets);
    }
  }
  
  return 0;
}

// ADD methods

void Agency::addClient() {
  string name, street, door, floor, postal, location;
  unsigned short family;
  unsigned vat;

  cout<<"Input client name: ";
  cin>>name;
  cout<<"Input client vat number: ";
  cin>>vat;
  while(!cin.good()){
    cout<<" >  ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin>>vat;
  }
  
  cout<<"Input client family size: ";
  cin>>family;
  while(!cin.good()){
    cout<<" >  ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin>>family;
  }
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout<<"Input client address street: ";
  getline(cin, street);
  while(!cin.good()){
    cout<<" >  ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, street);
  }
  cout<<"Input client door number: ";
  getline(cin, door);
  while(!cin.good()){
    cout<<" >  ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, door);
  }
  cout<<"Input client floor number: ";
  getline(cin, floor);
  while(!cin.good()){
    cout<<" >  ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, floor);
  }
  cout << "Input client postal code: ";
  getline(cin, postal);
  while(!cin.good()){
    cout<<" >  ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, postal);
  }
  cout << "Input client location: ";
  getline(cin, location);
  while(!cin.good()){
    cout<<" >  ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, location);
  }
  cout << endl;

  clients.push_back(Client(name, vat, family, Address(street, door, floor, postal, location)));
}

void Agency::addPacket() {
  int id;
  vector<string> sites;
  string begin_date, end_date, string_sites;
  double price;
  unsigned max, reserved;

  cout<<"Input packet id: ";
  cin>>id;
  while(!cin.good()){
    cout<<" >  ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin>>id;
  }

  cout<<"Site: ";
  cin>>string_sites;
  sites = formatLocations(string_sites);

  cout<<"Input date of begin: ";
  cin>>begin_date;
  cout<<"Input date of end: ";
  cin>>end_date;

  cout<<"Input price per person: ";
  cin>>price;
  while(!cin.good()){
    cout<<" >  ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin>>price;
  }

  cout<<"Input max persons: ";
  cin>>max;
  while(!cin.good()){
    cout<<" >  ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin>>max;
  }

  cout<<"Input places reserved: ";
  cin>>reserved;
  while(!cin.good()){
    cout<<" >  ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin>>reserved;
  }

  packets.push_back(Packet(id, sites, Date(begin_date), Date(end_date), price, max, reserved));
}

// OTHER methods
void Agency::makePacketUnavailable(int id) {
  for(int i=0; i<packets.size(); i++) {
    if(packets.at(i).getId()==abs(id)) {
      packets.at(i).setId(-abs(id));
    }
  }
}

void Agency::packetTransaction(string name, int id) {
  int availability = checkPacketAvailability(id);
  if(availability==-2) {
    cout << "Specified packet was not found." << endl;
    return;
  }
  else if(availability==-1) {
    cout << "Specified packet is unavailable." << endl;
    return;
  }
  //addPacketToClient(name, id);
  for(int i=0; i<clients.size(); i++) {
    if(clients.at(i).getName()==name) {
      vector<unsigned> packets = clients.at(i).getPacketList();
      packets.push_back(id);
      clients.at(i).setPacketList(packets);
      float total = clients.at(i).getTotalPurchased();
      for(int j=0; j<packets.size(); j++) {
        if(abs(getPackets().at(j).getId())==id) {
          total += getPackets().at(j).getPricePerPerson();
          this->clients.at(i).setTotalPurchased(total);
          this->packets.at(j).setReserved(getPackets().at(j).getReserved()+1);
          if(getPackets().at(j).getReserved()==getPackets().at(j).getMaxPersons()) {
            makePacketUnavailable(id);
          }
        }
      }
    }
  }
  return;
}

//returns -1 if unavailable, -2 if it doesnt exist
int Agency::checkPacketAvailability(int id) {
  for(int i=0; i<packets.size(); i++) {
    if(abs(packets.at(i).getId())==abs(id)) {
      if(packets.at(i).getId() < 0) return -1;
      else return 0;
    }
  }
  return -2;
}

// DISPLAY methods

void Agency::displayAvailablePackets() {
  string dest_input;
  string date_input;
  int dest_input_f;
  int date_input_f;
  Date d1;
  Date d2;

  cout << "1: Search for any destination." << endl;
  cout << "2: Search for specific destination." << endl;
  cin >> dest_input;
  while(dest_input!="1" && dest_input!="2") {
    cout << "\nInput valid option: ";
    cin >> dest_input;
    cout << endl;
  }
  if(dest_input=="1") dest_input_f = CHECK_ALL_DEST;
  else {
    dest_input_f = CHECK_GIVEN_DEST;
    cout << "\nInput destination to be searched for: ";
    cin >> dest_input;
  }

  cout << "1: Search for any date." << endl;
  cout << "2: Search for specific interval." << endl;
  cin >> date_input;
  while(date_input!="1" && date_input!="2") {
    cout << "\nInput valid option: ";
    cin >> date_input;
    cout << endl;
  }
  if(date_input=="1") date_input_f = CHECK_ALL_DATES;
  else {
    date_input_f = CHECK_GIVEN_DATES;
    cout << "\nInput earlier date (yyyy/mm/dd): ";
    cin >> date_input;
    d1.setDate(date_input);
    cout << "\nInput later date (yyyy/mm/dd): ";
    cin >> date_input;
    d2.setDate(date_input);
    cout << d1 << endl << d2;
  }

  if(date_input_f==CHECK_ALL_DATES&&dest_input_f==CHECK_ALL_DATES) {
    displayPacketsAll();
  }
  else if(date_input_f==CHECK_ALL_DATES&&dest_input_f==CHECK_GIVEN_DEST) {
    displayPacketsDest(dest_input);
  }
  else if(date_input_f==CHECK_GIVEN_DATES&&dest_input_f==CHECK_ALL_DEST) {
    displayPacketsDate(d1, d2);
  }
  else displayPacketsDateDest(dest_input, d1, d2);

  return;
}

void Agency::displayPacketsAll() {
  for(int i=0; i<getPackets().size(); i++) {
    cout << "\n\n" << getPackets().at(i);
  }
  cout << endl;
  return;
}

void Agency::displayPacketsDest(string dest) {
  for(int i=0; i<getPackets().size(); i++) {
    for(int j=0; j<getPackets().at(i).getSites().size(); j++) {
      if(getPackets().at(i).getSites().at(j)==dest   
      && getPackets().at(i).getId()>0) {
        cout << "\n\n" << getPackets().at(i);
        break;
      }
    }
  }
  cout << endl;
  return;
}

void Agency::displayPacketsDate(Date d1, Date d2) {
  for(int i=0; i<getPackets().size(); i++) {
    if(getPackets().at(i).getBeginDate()>=d1) {
      if(getPackets().at(i).getEndDate()<=d2 
      && getPackets().at(i).getId()>0) {
        cout << "\n\n" << getPackets().at(i);
      }
    }
  }
  cout << endl;
  return;
}

void Agency::displayPacketsDateDest(string dest, Date d1, Date d2) {
  for(int i=0; i<getPackets().size(); i++) {
    if(getPackets().at(i).getBeginDate()>=d1) {
      if(getPackets().at(i).getEndDate()<=d2
      && getPackets().at(i).getId()>0) {
        for(int j=0; j<getPackets().at(i).getSites().size(); j++) {
          if(getPackets().at(i).getSites().at(j)==dest) {
            cout << "\n\n" << getPackets().at(i);
            break;
          }
        }
      }
    }
  }
  cout << endl;
  return;
}

void Agency::displaySoldPackets() {
  int input;
  string name;
  cout << "1: Display all sold packets.\n";
  cout << "2: Display packets sold to specific client.\n";
  cin.ignore(1000,'\n');
  cin >> input;
  if(input==1) {
      for(int i=0; i<getPackets().size(); i++) {
      cout << getPackets().at(i) << endl;
      cout << "Packet sold to: ";
      for(int j=0; j<getClients().size(); j++) {
        for(int k=0; k<getClients().at(j).getPacketList().size(); k++) {
          if(getClients().at(j).getPacketList().at(k)==abs(getPackets().at(i).getId())) {
            cout << getClients().at(j).getName() << "; ";
          }
        }
      }
      cout << "\n\n";
    }
  }
  if(input==2) {
    cout << "Input the client's name you want to show the packets of: ";
    cin.ignore(1000,'\n');
    getline(cin, name);
    for(int i=0; i<getClients().size(); i++) {
      if(getClients().at(i).getName()==name) {
        for(int j=0; j<getClients().at(i).getPacketList().size(); j++) {
          for(int k=0; k<getPackets().size(); k++) {
            if(abs(getPackets().at(k).getId())==getClients().at(i).getPacketList().at(j)) {
              cout << getPackets().at(k);
              cout << "\n\n";
            }
          }
        }
        cout << "\n\n";
      }
    }
  }
  cout << "\n\n";
  return;
}

void Agency::writeDataIntoFiles(string ag_filePath){
  ofstream ag_file, c_file, p_file;
  unsigned last_packet_created = packets.at(packets.size()-1).getId();
  //variables FOR
  int i, j;

  ag_file.open(ag_filePath, ios::out | ios::trunc);
  // Escrever os dados da agency para o ficheiro respetivo
  ag_file << name << endl;
  ag_file << VATnumber << endl;
  ag_file << URL << endl;
  ag_file << address.getStreet() << " / " << address.getDoorNumber()<<" / "<<address.getFloor()<<" / "<<address.getPostalCode()<<" / "<<address.getLocation()<<endl;
  ag_file << clientsPath << endl;
  ag_file << packetsPath;
  

  // Escrever os dados do vetor de clientes para o respetivo ficheiro
  c_file.open("clients.txt", ios::out | ios::trunc);
  for(i = 0; i < clients.size(); i++){
    c_file << clients.at(i).getName() << endl;
    c_file << clients.at(i).getVATnumber() << endl;
    c_file << clients.at(i).getFamilySize() << endl;
    c_file << clients.at(i).getAddress().getStreet()<<" / "<<clients.at(i).getAddress().getDoorNumber()<<" / "<<clients.at(i).getAddress().getFloor()<<" / "<<clients.at(i).getAddress().getPostalCode()<<" / "<<clients.at(i).getAddress().getLocation()<<endl;
    for(j = 0; j < (clients.at(i).getPacketList().size()); j++){
      if(j == clients.at(i).getPacketList().size()-1){
        if(i == clients.size() -1){
          c_file << clients.at(i).getPacketList().at(j);
          break;
        }
        c_file << clients.at(i).getPacketList().at(j)<<endl;
        break;
      }
      c_file << clients.at(i).getPacketList().at(j)<<" ; ";
    }
    if(i != clients.size()-1)
      c_file << "::::::::::" <<endl;
  }

  
  // Escrever os dados do vetor de pacotes para o respetivo ficheiro
  p_file.open("packets.txt", ios::out | ios::trunc);
  p_file << last_packet_created <<endl;
  for(i = 0; i < packets.size(); i++){
    p_file << packets.at(i).getId() << endl;
    for(j = 0; j < packets.at(i).getSites().size(); j++){
      if(j == packets.at(i).getSites().size()-1){
        p_file << packets.at(i).getSites().at(j)<<endl;
        break;
      }
      p_file << packets.at(i).getSites().at(j)<<", ";
    }
    p_file<<packets.at(i).getBeginDate().getYear()<<"/"<<packets.at(i).getBeginDate().getMonth()<<"/"<<packets.at(i).getBeginDate().getDay()<<endl;
    p_file<<packets.at(i).getEndDate().getYear()<<"/"<<packets.at(i).getEndDate().getMonth()<<"/"<<packets.at(i).getEndDate().getDay()<<endl;
    p_file << packets.at(i).getPricePerPerson()<<endl;
    p_file << packets.at(i).getMaxPersons()<<endl;
    p_file << packets.at(i).getReserved()<<endl;
    if(i != packets.size()-1)
      p_file << "::::::::::" <<endl;
  }
}

void Agency::PacketsSold(){

  unsigned num_packets = 0;
  double price_packets = 0;

  for(int i = 0; i < packets.size(); i++){
    num_packets += packets.at(i).getReserved();
    price_packets += num_packets * packets.at(i).getPricePerPerson();
  }

  cout<<"Total number of packets sold: "<<num_packets<<endl;
  cout<<"Total value of the packets sold: "<<price_packets<<" euros"<<endl;
}

void Agency::LocationsMostVisited(unsigned n){
  vector<Packet> pac = packets;
  int k = 0;
  unsigned most_sold_packet = 0;

  while(n_most_visited_sites.size() < n){
    for(int i = 0; i < pac.size(); i++){
      if(pac.at(i).getReserved() > most_sold_packet){
        most_sold_packet = pac.at(i).getReserved();
        k = i;
      }
    }
    for(int i = 0; i < pac.size(); i++){
      if(most_sold_packet == pac.at(i).getReserved()){
        for(int j = 0; j <  pac.at(i).getSites().size(); j++){
          if(n_most_visited_sites.size() < n){
            n_most_visited_sites.push_back(pac.at(i).getSites().at(j));
          }
        }
      }
    }
    pac.at(k).setReserved(0);
    most_sold_packet = 0;
  }
}

void Agency::displayStillNotVisited(){
  int found_not_visited = 0;

  for(int k = 0; k < clients.size(); k++){
    vector<string> sites_visited;
    for(int j = 0; j < clients.at(k).getPacketList().size(); j++){
      for(int i = 0; i < getPacketsSites(clients.at(k).getPacketList().at(j)).size(); i++){
        sites_visited.push_back(getPacketsSites(clients.at(k).getPacketList().at(j)).at(i));
      }
    }
    for(int i = 0; i < n_most_visited_sites.size(); i++){
      for(int j = 0; j <sites_visited.size(); j++){
        if(n_most_visited_sites.at(i).compare(sites_visited.at(j)) == 0){
          break;
        }
        if(j == sites_visited.size()-1){
          cout << clients.at(k).getName() << " still didn't visit "<< n_most_visited_sites.at(i)<<"!"<<endl;
          found_not_visited = 1;
        }
      }
      if(found_not_visited == 1){
          break;
      }
      if(i == n_most_visited_sites.size()-1){
        cout << clients.at(k).getName() << " already visited all sites!"<<endl;
      }
    }
    found_not_visited = 0;
  }
}



/*********************************
 * Mostrar Loja
 ********************************/  

// mostra o conteudo de uma agencia
ostream& operator<<(ostream& out, const Agency & agency){

  // A IMPLEMENTATION REQUIRED 
}

vector<string> Agency:: formatLocations(string sites){
    
    vector<string> temp;

    cout<<sites<<endl;

    int pos = 0, i = 0;
    int slash = sites.find(",", pos);

    while(pos < slash){
            temp.push_back(sites.substr(pos, slash-pos));
            
            pos = slash +1;
            slash = sites.find(",", pos);
    }

    temp.push_back(sites.substr(pos, slash-pos));

    return temp;
}
