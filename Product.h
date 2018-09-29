//The Product class is a concrete class that encapsulates the general information for an AMA product. 

#ifndef GMS_PRODUCT_H
#define GMS_PRODUCT_H

#include <iostream>
#include "iProduct.h"
#include "ErrorState.h"

using namespace std;

namespace GMS {

	/*Pre - defined constants :
	Maximum number of characters in a sku(stock keeping unit) – 7.
	Maximum number of characters in the units’ descriptor for a product – 10.
	Maximum number of characters in the user’s name descriptor for a product length – 75.
	The current tax rate – 13 % .*/
	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double TAX_RATE = 0.13;

	class Product : public iProduct {

	//A character that indicates the type of the product – for use in the file record
		char product_type;

	//A character array that holds the product’s sku(stock keeping unit) – the maximum number of characters excluding 
	//the null byte is defined by the namespace constant.
		char psku[max_sku_length+1];

	//A character array that describes the product’s unit – the maximum number of characters excluding the null byte 
	//is defined by the namespace constant.
		char product_unit_descrp[max_unit_length+1];

	//A pointer that holds the address of a C - style string in dynamic memory containing the name of the product.
		char* product_name;

	//An integer that holds the quantity of the product currently on hand; that is, the number of units currently on hand.
		int quantity_on_hand;

	//An integer that holds the quantity of the product needed; that is, the number of units needed.
		int quantity_needed;

	//A double that holds the price of a single unit of the product before any taxes.
		double unit_price_before_tax;

	//A bool that identifies the taxable status of the product; its value is true if the product is taxable.
		bool taxable_product;

	//An ErrorState object that holds the error state of the Product object.
		ErrorState ErrState;

	protected:

		/*This function receives the address of a C - style null - terminated string that holds the name of the product.This function
		stores the name in dynamically allocated memory
		replaces any name previously stored
		If the incoming parameter holds the nullptr address, this function removes the name of the product, if any, from memory.*/
		void name(const char*);

		/*This query returns the address of the C - style string that holds the name of the product.If the product has no name, this 
		query returns nullptr.*/
		const char* name() const;
		
		/*This query returns the address of the C - style string that holds the sku of the product.*/
		const char* sku() const;
		
		/*This query returns the address of the C - style string that holds the unit of the product.*/
		const char* unit() const;
		
		/*This query returns the taxable status of the product.*/
		bool taxed() const;
			
		/*This query returns the price of a single item of the product.*/
		double price() const;
			
		/*This query returns the price of a single item of the product plus any tax that applies to the product.*/
		double cost() const;
			
		/*This function receives the address of a C - style null - terminated string holding an error message and stores that message 
		in the ErrorState object.*/
		void message(const char* err);
			
		/*This query returns true if the ErrorState object is clear; false otherwise.*/
		bool isClear() const;
			
	public:

		/*Zero - One argument Constructor
		This constructor optionally receives a character that identifies the product type.The default value is ‘N’.This function
		stores the character receives in an instance variable
		sets the current object to a safe recognizable empty state.*/
		Product(char pType = 'N');

		/*Seven argument Constructor
		This constructor receives in its seven parameters values in the following order :
		the address of an unmodifiable C - style null terminated string holding the sku of the product
		the address of an unmodifiable C - style null terminated string g holding the name of the product
		the address of an unmodifiable C - style null terminated string holding the unit for the product
		an integer holding the quantity of the product on hand – defaults to zero
		a Boolean value indicating the product’s taxable status – defaults to true
		a double holding the product’s price before taxes – defaults to zero
		an integer holding the quantity of the product needed – defaults to zero
		This constructor allocates enough memory to hold the name of the product.
		Note that a protected function has been declared to perform this task.*/
		Product(const char* sku, const char* name, const char* unit, int qtyOnHand = 0, bool taxStatus = true, double priceBeforeTax = 0.0, int qtyNeeded = 0);

		/*Copy Constructor
		This constructor receives an unmodifiable reference to a Product object and copies the object referenced to the current object.*/
		Product(const Product& product);

		/*Copy Assignment Operator
		This operator receives an unmodifiable reference to a Product object and replaces the current object with a copy of the object referenced.*/
		Product& operator=(const Product& product);

		/*Destructor
		This function deallocates any memory that has been dynamically allocated.*/
		~Product();

		/*This query receives a reference to an fstream object and an optional bool and returns a reference to the fstream object.This function
		inserts into the fstream object the character that identifies the product type as the first field in the record.
		inserts into the fstream object the data for the current object in comma separated fields.
		if the bool parameter is true, inserts a newline at the end of the record.*/
		std::fstream& store(std::fstream& file, bool newLine = true) const;

		/*This modifier receives a reference to an fstream object and returns a reference to that fstream object.This function
		extracts the fields for a single record from the fstream object
		creates a temporary object from the extracted field data
		copy assigns the temporary object to the current object.*/
		std::fstream& load(std::fstream& file);

		/*This query receives a reference to an ostream object and a bool and returns a reference to the ostream object.This 
		function inserts the data fields for the current object into the ostream object in the following order and separates 
		them by a vertical bar character(‘ | ’).If the bool parameter is true, the output is on a single line with the field 
		widths as shown below in parentheses:*/
		/*sku –(maximum number of characters in a sku)
		name –(20)
		cost –(7)
		quantity –(4)
		unit –(10)
		quantity needed –(4)

		If the bool parameter is false, this function inserts the fields on separate lines with the following 
		descriptors(a single space follows each colon) :

		Sku :
		Name(no spaces) :
		Price :
		either of :
		Price after tax :
		N / A
		Quantity on hand :
		Quantity needed :*/
		std::ostream& write(std::ostream& os, bool linear) const;

		/*This modifier receives a reference to an istream object and returns a reference to the istream object.
		This function extracts the data fields for the current object in the following order, line by line.
		This function stops extracting data once it has encountered an error.The error messages are shown in brackets.
		A single space follows each colon :
		Sku : <input value – C - style string>
		Name(no spaces) : <input value – C - style string>
		Unit : <input value – C - style string>
		Taxed ? (y / n) : <input character – y, Y, n, or N>[“Only(Y)es or (N)o are acceptable”]
		Price : <input value – double>[“Invalid Price Entry”]
		Quantity on hand : <input value – integer>[“Invalid Quantity Entry”]
		Quantity needed : <input value – integer>[“Invalid Quantity Needed Entry”]
		If this function encounters an error for the Taxed input option, it sets the failure bit of the istream object
		(calling istream::setstate(std::ios::failbit)) and sets the error object to the error message noted in brackets.
		If the istream object is not in a failed state and this function encounters an error on accepting Price input, 
		it sets the error object to the error message noted in brackets.The member function that reports failure of an 
		istream object is istream::fail().
		If the istream object is not in a failed state and this function encounters an error on the Quantity input, it 
		sets the error object to the error message noted in brackets.
		If the istream object is not in a failed state and this function encounters an error on the Quantity needed input, 
		it sets the error object to the error message noted in brackets.
		If the istream object has accepted all input successfully, this function stores the input values accepted in a 
		temporary object and copy assigns it to the current object.*/
		std::istream& read(std::istream& is);

		/*This query receives the address of an unmodifiable C - style null - terminated string and returns true if 
		the string is identical to the sku of the current object; false otherwise.*/
		bool operator==(const char*) const;

		/*This query that returns the total cost of all items of the product on hand, taxes included.*/
		double total_cost() const;

		//This modifier that receives an integer holding the number of units of the Product that are on hand.This 
		//function resets the number of units that are on hand to the number received.
		void quantity(int);

		/*This query returns true if the object is in a safe empty state; false otherwise.
		int qtyNeeded() const
		This query that returns the number of units of the product that are needed.*/
		bool isEmpty() const;

		//This query that returns the number of units of the product that are needed.
		int qtyNeeded() const;

		//This query returns the number of units of the product that are on hand.
		int quantity() const;
		
		/*This query receives the address of a C - style null - terminated string holding a product sku and returns 
		true if the sku of the current object is greater than the string stored at the received address(according to 
		how the string comparison functions define ‘greater than’); false otherwise.*/
		bool operator>(const char*) const;
		
		/*This query receives an unmodifiable reference to a Product object and returns true if the name of the 
		current object is greater than the name of the referenced Product object(according to how the string comparison 
		functions define ‘greater than’); false otherwise.*/
		bool operator>(const iProduct&) const;
		
		/*This modifier receives an integer identifying the number of units to be added to the Product and returns 
		the updated number of units on hand.If the integer received is positive - valued, this function adds it to 
		the quantity on hand.If the integer is negative - valued or zero, this function does nothing and returns the 
		quantity on hand(without modification).*/
		int operator+=(int);

	};

	//The following helper functions support your Product class :
		
	/*This helper receives a reference to an ostream object and an unmodifiable reference to a Product object 
	and returns a reference to the ostream object.Your implementation of this function will insert a Product record into the ostream.*/
	std::ostream& operator<<(std::ostream& os, const iProduct& product);

	/*This helper receives a reference to an istream object and a reference to a Product object and returns a 
	reference to the istream object.Your implementation of this function extracts the Product record from the istream.*/
	std::istream& operator>>(std::istream& is, iProduct& product);

	/*This helper receives a reference to a double and an unmodifiable reference to a Product object and returns 
	a double.Your implementation of this function adds the total cost of the Product object to the double received and returns the updated double.*/
	double operator+=(double& add, const iProduct& product);

}
#endif // !AMA_Product_H