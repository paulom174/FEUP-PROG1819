#pragma once

#include "agency.h"

#define MAIN_MENU 0
#define EDIT_MENU 1
#define DISPLAY_MENU 2
#define TRANSACTION_MENU 3
#define EXIT 4
#define EDIT_CLIENT 5
#define EDIT_PACKET 6
#define EDIT_CLIENT_NAME 7
#define EDIT_CLIENT_VAT 8
#define EDIT_CLIENT_FS 9
#define EDIT_CLIENT_ADRESS 10
#define EDIT_CLIENT_PACKETS 11
#define EDIT_CLIENT_PURCHASES 12
#define DISPLAY_CLIENT 13
#define DISPLAY_AVAILABLE_PACKETS 14
#define DISPLAY_SOLD_PACKETS 15
#define DISPLAY_GIVEN_CLIENT 16
#define DISPLAY_ALL_CLIENTS 17
#define DISPLAY_MOST_VISITED_PLACES 18
#define DISPLAY_STILL_NOT_VISITED_LOCATION 19


void menu_handler(Agency& agency);