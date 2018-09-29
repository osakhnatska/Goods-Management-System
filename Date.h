
#ifndef GMS_DATE_H
#define GMS_DATE_H
//the error state
#define NO_ERROR 0
//istream failed on information entry
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3
#define DAY_ERROR 4

namespace GMS {

	//predefined constraints on the years to be considered acceptable
	const int min_year = 2000;
	const int max_year = 2030;

  class Date {

	  //value between 1 and the number of days in the month 
	  int days;
	  //value between 1 and 12 inclusive
	  int month;
	  //a 4 digit integer between min_year and max_year
	  int year;
	  //value to be used for comparing the date stored in this with the date stored in another Date object
	  int comparator; 
	  
	  //the error state which the client can reference to determine if the object holds a valid date, and if not
	  // in which part is an error
	  int errorState;
	  int mdays(int, int) const;
	  void errCode(int errorCode);
	  bool isEmpty() const;

  public:
 
	  //constructors
	  //default constructor sets an object to a safe empty state
	  Date();
	  //3-argument constructor accepts in its parameters integer values for the year, month and day
	  //checks if each number is in range, in the order of year, month and day. If any of the numbers 
	  //are not within range, this function sets the error state to the appropriate error code and stops further validation.
	  Date(int, int, int);

	  //operators
	  //these comparison operators return the result of comparing this as the left-hand side operand with another Date object 
	  //as the right-hand side operand if the 2 objects are not empty. If one or both of them is empty, these operators return false. 
	  bool operator==(const Date& rhs) const;
	  bool operator!=(const Date& rhs) const;
	  bool operator<(const Date& rhs) const;
	  bool operator>(const Date& rhs) const;
	  bool operator<=(const Date& rhs) const;
	  bool operator>=(const Date& rhs) const;

	  //queries and modifier
	  //this query returns the error state as an error code value
	  int errCode() const;
	  //this query returns true if the error state is not NO_ERROR
	  bool bad() const;

	  //reads the date from console, in the format y/m/d, this f. does not promt user. 
	  //If istr fails at any point (if istr fails, the function istr.fail() returns true), this function sets
	  //the error state to CIN_FAILED and does not clear istr. If read() reads the number successfully, and the 
	  //read values are valid it stores them into the instance variables. Otherwise, your function does not change
	  //the current object. Returns the reference to the std::istream object
	  std::istream& read(std::istream& istr);

	  //this query writes the date to an std::ostream object in the format and then returns a reference to the 
	  //std::ostream object.
	  std::ostream& write(std::ostream& ostr)const;
  };

  //helper functions 
  std::istream& operator>>(std::istream&, Date&);
  std::ostream& operator<<(std::ostream&, const Date&);
}
#endif