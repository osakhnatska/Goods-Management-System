#ifndef GMS_Perishable_H
#define GMS_Perishable_H

#include <iostream>
#include "Product.h"
#include "Date.h"

namespace GMS {

	//Your Perishable class uses a Date object, but does not need its own ErrorState object 
	//(the Product base class handles all error processing).
	class Perishable : public Product {
		
		/*A Date object holds the expiry date for the perishable product.*/
		Date per_prod_exp_date;

	public:

		/*No argument Constructor 
		This constructor passes the file record tag for a perishable product (‘P’) to the base 
		class constructor and sets the current object to a safe empty state.*/
		Perishable();

		/*This query receives a reference to an fstream object and an optional bool and returns a reference 
		to the modified fstream object. This function stores a single file record for the current object. 
		This function
		calls its base class version passing as arguments a reference to the fstream object and a false flag. 
		The base class inserts the common data into the fstream object
		inserts a comma into the file record 
		appends the expiry date to the file record. 
		If newLine is true, this function inserts a newline character (‘\n’) before exiting. 
		In this case, the file record created will look something like:

		P,1234,water,1.5,0,1,liter,5,2018/03/28<NEWLINE> 

		If newLine is false, this function does not insert a newline character (‘\n’) before exiting. 
		In this case, the file record created will look something like:

		P,1234,water,1.5,0,1,liter,5,2018/03/28 
 
		Note that the first field in the file record is ‘P’. This character was passed to the base class at 
		construction time and is inserted by the base class version of this function.*/
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		
		/*This modifier receives a reference to an fstream object and returns a reference to that fstream object. 
		This function extracts the data fields for a single file record from the fstream object. This function 
		calls its base class version passing as an argument a reference to the fstream object
		loads the expiry date from the file record using the read() function of the Date object
		extracts a single character from the fstream object.*/
		std::fstream& load(std::fstream& file);
		
		/*This query receives a reference to an ostream object and a bool flag and returns a reference to the modified ostream object. 
		The flag identifies the output format. This function 
		calls its base class version passing as arguments a reference to the ostream object and the bool flag. 
		if the current object is in an error or safe empty state, does nothing further. 
		if the current object is not in an error or safe empty state, inserts the expiry date into the ostream object. 
		if linear is true, adds the expiry date on the same line for an outcome that looks something like this:
		1234   |water               |   1.50|   1|liter     |   5|2018/03/10
		If linear is false, this function adds a new line character followed by the string “Expiry date: “ 
		and the expiry date for an outcome something like this:
 
		Sku: 1234
		Name (no spaces): water
		Price: 1.50
		Price after tax: N/A
		Quantity on hand: 1 liter
		Quantity needed: 5
		Expiry date: 2018/03/10
		This function does not insert a newline after the expiry date in the case of linear output (linear is true) or 
		the case of line-by-line output (linear is false).*/
		std::ostream& write(std::ostream& os, bool linear) const;
		
		/*This modifier receives a reference to an istream object and returns a reference to the modified istream object. 
		This function populates the current object with the data extracted from the istream object. 

		This function calls its base class version passing as its argument a reference to the istream object. 
		If the base class object extracts data successfully, this function prompts for the expiry date and stores it in a temporary Date object.
		The prompt looks like with a single space after the colon:
		Expiry date (YYYY/MM/DD): 
		If the temporary Date object is in an error state, this function stores the appropriate error message in the 
		base class’ error object and sets the state of the istream object to a failed state. The member function that sets 
		it to a failed state is (istream::setstate(std::ios::failbit)). The messages that correspond to the error codes of a Date object are:
		CIN_FAILED:	Invalid Date Entry
		YEAR_ERROR:	Invalid Year in Date Entry
		MON_ERROR:	Invalid Month in Date Entry
		DAY_ERROR:	Invalid Day in Date Entry
		If the istream object is not in an error state, this function copy assigns the temporary Date object to the 
		instance Date object. The member function that reports failure of an istream object is istream::fail().*/
		std::istream& read(std::istream& is);
		
		//This query returns the expiry date for the perishable product.
		const Date& expiry() const;
	};
}
#endif // !AMA_Perishable_H


