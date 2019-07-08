#include "date.h"

Date::Date(){
}

Date::Date(string date){
    size_t sz;
    int pos = 0, i = 0;
    int slash = date.find("/", pos);

    this->year = stoi(date.substr(pos, slash-pos), &sz, 10);
    pos = slash +1;
    slash = date.find("/", pos);

    this->month = stoi(date.substr(pos, slash-pos), &sz, 10);
    pos = slash +1;
    slash = date.find("/", pos);

    this->day = stoi(date.substr(pos, slash-pos), &sz, 10);
}


Date::Date(unsigned short day, unsigned short month, unsigned year){

  this->day = day;
  this->month = month;
  this->year = year;
}

/*********************************
 * GET Methods
 ********************************/
unsigned short Date::getDay() const{

  return day;

}

  
unsigned short Date::getMonth() const{

  return month;

}
    
unsigned Date::getYear() const{

  return year;

}

/*********************************
 * SET Methods
 ********************************/

void Date::setDay(unsigned short day){
  
  this->day = day;

}
void Date::setMonth(unsigned short month){
  
  this->month = month;

}

void Date::setYear(unsigned year){

  this->year = year;

}

void Date::setDate(string date) {
    size_t sz;
    int pos = 0, i = 0;
    int slash = date.find("/", pos);

    this->year = stoi(date.substr(pos, slash-pos), &sz, 10);
    pos = slash +1;
    slash = date.find("/", pos);

    this->month = stoi(date.substr(pos, slash-pos), &sz, 10);
    pos = slash +1;
    slash = date.find("/", pos);

    this->day = stoi(date.substr(pos, slash-pos), &sz, 10);
}


/*********************************
 * Show Date
 ********************************/  

// disply a Date in a nice format
ostream& operator<<(ostream& out, const Date & date){
  out << date.year << "/" << date.month << "/" << date.day;
  return out;
}

bool operator>(const Date date1, const Date date2) {
  unsigned d1 = date1.year*10000 + date1.month*100 + date1.day;
  unsigned d2 = date2.year*10000 + date2.month*100 + date2.day;
  if(d1>d2) return true;
  else return false;
}

bool operator<(const Date date1, const Date date2) {
  unsigned d1 = date1.year*10000 + date1.month*100 + date1.day;
  unsigned d2 = date2.year*10000 + date2.month*100 + date2.day;
  if(d1>d2) return false;
  else return true;
}

bool operator>=(const Date date1, const Date date2) {
  unsigned d1 = date1.year*10000 + date1.month*100 + date1.day;
  unsigned d2 = date2.year*10000 + date2.month*100 + date2.day;
  if(d1>=d2) return true;
  else return false;
}

bool operator<=(const Date date1, const Date date2) {
  unsigned d1 = date1.year*10000 + date1.month*100 + date1.day;
  unsigned d2 = date2.year*10000 + date2.month*100 + date2.day;
  if(d1>=d2) return false;
  else return true;
}
