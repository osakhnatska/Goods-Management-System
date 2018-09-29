#include <iostream>

#include "Date.h"

namespace GMS {

  // number of days in month mon_ and year year_
  int Date::mdays(int mon, int year)const {
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int month = mon >= 1 && mon <= 12 ? mon : 13;
    month--;
    return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
  }

  //the error state which the client can reference to determine if the object holds a valid date, and if not
  // in which part is an error
  void Date::errCode(int errorCode)
  {
	  errorState = errorCode;
  }

  bool Date::isEmpty() const
  {
	  return year == 0;
  }

  //0arg constructor
  Date::Date()
  {
	  days = 0;
	  month = 0;
	  year = 0;
	  comparator = 0;
	  errorState = NO_ERROR;
  }

  //3arg constructor
  Date::Date(int year_, int month_, int days_)
  {
	  if(min_year <= year_ && year_ <= max_year && month_ > 0 && month < 13 && days_ > 0 && days_ <= mdays(month_, year_))
	  {
		  year = year_;
		  month = month_;
		  days = days_;
		  comparator = year * 372 + month * 13 + days;
		  errorState = NO_ERROR;
	  }
	  else {
		  *this = Date();
	  }
  }

  //operators
  //these comparison operators return the result of comparing this as the left-hand side operand with another Date object 
  //as the right-hand side operand if the 2 objects are not empty. If one or both of them is empty, these operators return false. 
  bool Date::operator==(const Date & rhs) const
  {	
	  if (isEmpty() || rhs.isEmpty()) {
		  return false;
	  }
	  else if (this->comparator == rhs.comparator) {
		  return true;
	  }
	  else {
		  return false;
	  }
  }

  bool Date::operator!=(const Date & rhs) const
  {
	  if (isEmpty() || rhs.isEmpty())
		  return false;
	  else
		  return comparator != rhs.comparator;
  }

  bool Date::operator<(const Date & rhs) const
  {
	  if (isEmpty() || rhs.isEmpty())
		  return false;
	  else
		  return comparator < rhs.comparator;
  }

  bool Date::operator>(const Date & rhs) const
  {
	  if (isEmpty() || rhs.isEmpty())
		  return false;
	  else
		  return comparator > rhs.comparator;
  }

  bool Date::operator<=(const Date & rhs) const
  {
	  if (isEmpty() || rhs.isEmpty())
		  return false;
	  else
		  return comparator <= rhs.comparator;
  }

  bool Date::operator>=(const Date & rhs) const
  {
	  if (isEmpty() || rhs.isEmpty())
		  return false;
	  else
		  return comparator >= rhs.comparator;
  }

  //queries and modifier
  //this query returns the error state as an error code value
  int Date::errCode() const
  {
	  return errorState;
  }

  //this query returns true if the error state is not NO_ERROR
  bool Date::bad() const
  {
	  if (errorState != NO_ERROR)
		  return true;
	  else
		  return false;
  }

  //reads the date from console, in the format y/m/d, this f. does not promt user. 
  //If istr fails at any point (if istr fails, the function istr.fail() returns true), this function sets
  //the error state to CIN_FAILED and does not clear istr. If read() reads the number successfully, and the 
  //read values are valid it stores them into the instance variables. Otherwise, your function does not change
  //the current object. Returns the reference to the std::istream object
  std::istream & Date::read(std::istream & istr)
  {
	  char data;
	  int tempError = 0;
	  istr.clear();
	  istr >> year >> data >> month >> data >> days;
	  if (istr.fail()) {
		  tempError = CIN_FAILED;
		  errorState = CIN_FAILED;
	  }
	  else if (year < min_year || year > max_year) {
		  *this = Date();
		  tempError =YEAR_ERROR;
		  errorState =YEAR_ERROR;
	  }
	  else if (1 > month || month > 12) {
		  *this = Date();
		  tempError = MON_ERROR;
		  errorState = MON_ERROR;
	  }
	  else if (days < 1 || days > mdays(month, year)) {
		  *this = Date();
		  tempError = DAY_ERROR;
		  errorState = DAY_ERROR;
	  }
	  else {
		  istr.clear();
		  Date date(year, month, days);
		  date.errCode(tempError);
		  *this = date;
	  }
	  return istr;
  }

  //this query writes the date to an std::ostream object in the format and then returns a reference to the 
  //std::ostream object.
  std::ostream & Date::write(std::ostream & ostr) const
  {
	  ostr << year << "/";
	  if (month < 10)
	  {
		  ostr << "0" << month << "/";
		  if (days < 10) {
			  ostr << "0" << days;
		  }
		  else {
			  ostr << days;
		  }
	  }
	  else {
		  ostr << month << "/";
		  if (days < 10) {
			  ostr << "0" << days;
		  }
		  else {
			  ostr << days;
		  }
	  }
	  return ostr; 
  }

  //helper functions 
  std::istream & operator>>(std::istream & istr, Date & date)
  {
	  return date.read(istr);   
  }

  std::ostream & operator<<(std::ostream & ostr, const Date & date)
  {
	  return date.write(ostr);
  }
}