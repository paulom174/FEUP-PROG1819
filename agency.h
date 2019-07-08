#pragma once

#include <iostream>
#include <string>
#include <vector>


#include "defs.h"
#include "address.h"
#include "client.h"
#include "packet.h"
//#include "menus.h"

using namespace std;

#define CHECK_ALL_DEST 1
#define CHECK_GIVEN_DEST 0
#define CHECK_ALL_DATES 1
#define CHECK_GIVEN_DATES 0

class Agency{
 private:
  string name; // name of the  agency
  unsigned int VATnumber; // VAT number of the agency
  Address address; // address of the agency
  string URL; // URL of the agency Web site
  string packetsPath;
  string clientsPath;
  vector<Client> clients; // vector to store the existing clients
  vector<Packet> packets; // vector to store the existing packets
  vector<string> n_most_visited_sites;
  
  bool clientsInfoHasChanged; // flag that is set to "true" if at least one client has been changed/added/deleted
  bool packetsInfoHasChanged; // flag that is set to "true" if at least one packet has been changed/added/deleted
  unsigned int maxClientsId; // maximum value among all clients identifiers
  unsigned int maxPacketsId; // maximum value among all packets identifiers
  unsigned int lastCreatedPacketId; // id of last packet to be created

 public:
  Agency(string fileName);

  // methods GET
  string getName() const;
  unsigned getVATnumber() const;
  Address getAddress() const;
  string getURL() const;
  string getClientsPath() const;
  string getPacketsPath() const;
  vector<Client> getClients() const;
  vector<Packet> getPackets() const;
  bool getClientsInfoHasChanged() const;
  bool getPacketsInfoHasChanged() const;
  vector<string> getPacketsSites(unsigned id) const;
  vector<string> getN_most_visited_sites() const;


  
  // methods SET
  void setName(string name);
  void setVATnumber(unsigned VATnumber);
  void setAddress(Address address);
  void setURL(string url);
  void setClientsPath(string clientPath);
  void setPacketsPath(string travelPath);
  void setClients(vector<Client> & clients);
  void setPackets(vector<Packet> & packets);
  void setClientsInfoHasChanged(bool clients_changed);
  void setPacketsInfoHasChanged(bool packets_changed);
  void setN_most_visited_sites(vector<string> visited_sites);


  // methods REMOVE
  int removeClient(string name);
  int removePacket(unsigned int id);

  // methods EDIT
  int editClientName(string name, string new_name);
  int editClientVAT(string name, unsigned new_VAT);
  int editClientFamilySize(string name, unsigned new_fs);
  int editClientAdress(string name);
  int editClientPurchases(string name, int value);
  int addPacketToClient(string name, int id);
  int removePacketFromClient(string name, int id);


  // methods ADD
  void addClient();
  void addPacket();

  // methods DISPLAY
  void displayAvailablePackets();
  void displayPacketsAll();
  void displayPacketsDest(string dest);
  void displayPacketsDate(Date d1, Date d2);
  void displayPacketsDateDest(string dest, Date d1, Date d2);
  void displaySoldPackets();
  void displayStillNotVisited();

  // other methods */
  void makePacketUnavailable(int id);
  int checkPacketAvailability(int id);
  void packetTransaction(string name, int id);
  void writeDataIntoFiles(string ag_filePath);
  void PacketsSold();
  void LocationsMostVisited(unsigned n);
  friend void menu_handler(Agency& agency);
  friend ostream& operator<<(ostream& out, const Agency & agency);

  vector<string> formatLocations(string sites);

};
