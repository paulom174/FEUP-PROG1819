#include <iostream>
#include <string>
#include <vector>

#include "agency.h"
#include "menus.h"
// #include "utils.h"


int main(){
  Agency agency("agency.txt");   // create the agency
  menu_handler(agency);
  return 0;
}
