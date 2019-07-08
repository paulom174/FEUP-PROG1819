#include "menus.h"

void menu_handler(Agency& agency){
  string new_name;
  unsigned new_vat;
  unsigned new_fs;
  unsigned id;
  unsigned num_places;
  string name;
  int exit_f;
  int menu_state = MAIN_MENU;
  int input = MAIN_MENU;
  while(menu_state!=EXIT) {
    switch(menu_state) {
      case MAIN_MENU:
        cout << agency.getClients().at(1).getPacketList().at(agency.getClients().at(1).getPacketList().size()-1) << endl;

        cout << "1: Edit data." << endl;
        cout << "2: Display data." << endl;
        cout << "3: Make transaction." << endl;
        cout << "4: Exit program." << endl;
        cout << "\nEnter your choice and press return: ";
        cin >> input;
        //fazer catch te expepções e o crlh
        break;

      case EDIT_MENU:
        cout << "1: Edit clients." << endl;
        cout << "2: Edit packets." << endl;
        cout << "\nEnter your choice and press return: ";
        cin >> input;
        if(input==1) input = EDIT_CLIENT;
        if(input==2) input = EDIT_PACKET;
        //preciso interpretar input
        //fazer catch te expepções e o crlh
        break;

      case EDIT_CLIENT:
        cout << "Input the name of the client you want to edit the data of: ";
        cin.ignore(1000, '\n');
        getline(cin, name);
        cout << "\n\nWhat parameter of the client data you want to change?" << endl;
        cout << "1: Name.\n" << "2: VAT.\n" << "3: Family Size.\n" <<
        "4: Adress.\n" << "5: Bought Packets.\n" << "6: Total Purchases Amount.\n";
        cin >> input;
        if(input==1) input = 7;
        else if(input==2) input = 8;
        else if(input==3) input = 9;
        else if(input==4) input = 10;
        else if(input==5) input = 11;
        else if(input==6) input = 12;
        break;

      case EDIT_CLIENT_NAME:
        cout << "Input the new name of the given client: ";
        cin.ignore(1000, '\n');
        getline(cin, new_name);
        agency.editClientName(name, new_name);
        input=MAIN_MENU;
        break;
      case EDIT_CLIENT_VAT:
        cout << "Input new VAT number of the given client: ";
        cin.ignore(1000, '\n');
        cin >> new_vat;
        agency.editClientVAT(name, new_vat);
        input=MAIN_MENU;
        break;
      case EDIT_CLIENT_FS:
        cout << "Input new family size of the given client: ";
        cin.ignore(1000, '\n');
        cin >> new_vat;
        agency.editClientFamilySize(name,new_fs);
        input=MAIN_MENU;
        break;
      case EDIT_CLIENT_ADRESS:
        agency.editClientAdress(name);
        input=MAIN_MENU;
        break;
      case EDIT_CLIENT_PACKETS:
        cout << "1: Add packet.\n" << "2: Remove packet.\n";
        cout << "Enter your choice and press return: ";
        cin.ignore(1000, '\n');
        cin >> input;
        cout << "\nEnter packet ID to be added/removed: ";
        cin.ignore(1000, '\n');
        cin >> id;
        if(input==1) agency.addPacketToClient(name,id);
        if(input==2) agency.removePacketFromClient(name,id);
        input=MAIN_MENU;
        break;
      case EDIT_CLIENT_PURCHASES:
        cout << "Enter new client purchases total: ";
        cin.ignore(1000, '\n');
        cin >> input;
        agency.editClientPurchases(name, input);
        input=MAIN_MENU;
        break;

      case DISPLAY_MENU:
        cout << "1: Display client.\n";
        cout << "2: Display available packets.\n";
        cout << "3: Display sold packets.\n";
        cout << "4: Display most visited locations.\n";
        cin.ignore(1000, '\n');
        cin >> input;
        if(input==1) input = DISPLAY_CLIENT;
        if(input==2) input = DISPLAY_AVAILABLE_PACKETS;
        if(input==3) input = DISPLAY_SOLD_PACKETS;
        if(input == 4)input = DISPLAY_MOST_VISITED_PLACES;
        break;

      case DISPLAY_CLIENT:
        cout << "1: Display specific client.\n";
        cout << "2: Display all clients.\n";
        cout << "3: Display most common locations that clients didn't visit yet.\n";
        cin.ignore(1000, '\n');
        cin >> input;
        if(input==1) input = DISPLAY_GIVEN_CLIENT;
        if(input==2) input = DISPLAY_ALL_CLIENTS;
        if(input==3) input = DISPLAY_STILL_NOT_VISITED_LOCATION;
        break;
      case DISPLAY_ALL_CLIENTS:
        for(int i=0; i<agency.getClients().size(); i++) {
          cout << agency.getClients().at(i) << endl;
        }
        input = MAIN_MENU;
        break;
      case DISPLAY_GIVEN_CLIENT:
        cout << "Input client to be displayed name: ";
        cin.ignore(1000, '\n');
        getline(cin, name);
        for(int i=0; i<agency.getClients().size(); i++) {
          if(agency.getClients().at(i).getName()==name) {
            cout << agency.getClients().at(i);
          }
        }
        input = MAIN_MENU;
        break;
      case DISPLAY_STILL_NOT_VISITED_LOCATION:
        agency.displayStillNotVisited();
        input = MAIN_MENU;
        break;

      case DISPLAY_AVAILABLE_PACKETS:
        agency.displayAvailablePackets();
        input = MAIN_MENU;
        break;
      case DISPLAY_SOLD_PACKETS:
        agency.displaySoldPackets();
        agency.PacketsSold();
        input = MAIN_MENU;
        break;
      case DISPLAY_MOST_VISITED_PLACES:
        cout <<"Input the number of locations: ";
        cin.ignore(1000, '\n');
        cin >> num_places;
        agency.LocationsMostVisited(num_places);
        for(int i = 0; i < agency.getN_most_visited_sites().size(); i++){
          cout << i+1 << " - " << agency.getN_most_visited_sites().at(i) << endl;
        }
        input=MAIN_MENU;
        break;
      case TRANSACTION_MENU:
        cout << "Input client's name involved in the transaction: ";
        cin.ignore(1000, '\n');
        getline(cin, name);
        cout << "\nInput packet's ID involved in the transaction: ";
        cin.ignore(1000, '\n');
        cin >> id;
        agency.packetTransaction(name,id);
        input=MAIN_MENU;
        break;

    }
    menu_state = input;
    cout <<"\n\n\n\n~~~~~~~~~~~~~~~~~~~~~\n\n\n\n";
  }
  agency.writeDataIntoFiles("agency.txt");
  return;
}
    
