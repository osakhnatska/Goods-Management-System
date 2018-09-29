#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include "Product.h"

using namespace std;

namespace GMS {

	/*This function receives the address of a C - style null - terminated string that holds the name of the product.This function
	stores the name in dynamically allocated memory
	replaces any name previously stored
	If the incoming parameter holds the nullptr address, this function removes the name of the product, if any, from memory.*/
	void GMS::Product::name(const char *name)
	{
		if (name != nullptr) { 
			int len = (int)strlen(name);
				product_name = new char[len + 1];
			for(int i=0; i < len; ++i){
				product_name[i] = name[i];
			}
			product_name[len] = '\0';
		}
		else if (name == nullptr) {
			delete[] product_name;
			product_name = nullptr;
		}
	}

	/*This query returns the address of the C - style string that holds the name of the product.
	If the product has no name, this query returns nullptr.*/
	const char * Product::name() const
	{
		if (product_name == nullptr || product_name[0] == '\0')
			return nullptr;
		else
			return product_name;
	}

	/*This query returns the address of the C - style string that holds the sku of the product.*/
	const char * Product::sku() const
	{
		return psku;
	}

	/*This query returns the address of the C - style string that holds the unit of the product.*/
	const char * Product::unit() const
	{
		return product_unit_descrp;
	}

	/*This query returns the taxable status of the product.*/
	bool Product::taxed() const
	{
		return taxable_product;
	}

	/*This query returns the price of a single item of the product.*/
	double Product::price() const
	{
		return unit_price_before_tax;
	}

	/*This query returns the price of a single item of the product plus any tax that applies to the product.*/
	double Product::cost() const
	{
		if (taxable_product)
			return unit_price_before_tax * TAX_RATE + unit_price_before_tax;
		else
			return unit_price_before_tax;
	}

	/*This function receives the address of a C - style null - terminated string holding an error message and 
	stores that message in the ErrorState object.*/
	void Product::message(const char * err)
	{
		ErrState.message(err);
	}

	/*This query returns true if the ErrorState object is clear; false otherwise.*/
	bool Product::isClear() const
	{
		return ErrState.isClear();
	}

	//Zero or One Argument Constructor
	Product::Product(char pType)
	{
		product_type = pType;
		psku[0] = '\0';
		product_unit_descrp[0] = '\0';
		product_name = nullptr;
		quantity_on_hand = 0;
		quantity_needed = 0;
		unit_price_before_tax = 0;
		taxable_product = true;
		ErrState.clear();
	}

	//7 Argument Constructor
	Product::Product(const char * sku, const char * pname, const char * unit, int qtyOnHand, bool taxStatus, double priceBeforeTax, int qtyNeeded)
	{
		strncpy(psku, sku, max_sku_length);
		psku[max_sku_length] = '\0';
		name(pname);
		strncpy(product_unit_descrp, unit, max_unit_length);
		product_unit_descrp[max_sku_length] = '\0';
		quantity_on_hand = qtyOnHand;
		taxable_product = taxStatus;
		unit_price_before_tax = priceBeforeTax;
		quantity_needed = qtyNeeded;
	}

	//Copy Constructor
	Product::Product(const Product & product)
	{
		if (!product.isEmpty()) {
			product_name = nullptr;
			*this = product;
		}
	}

	//Copy Assignment Operator
	Product & Product::operator=(const Product & product)
	{
		if (this != &product) {
			product_type = product.product_type;
			strcpy(psku, product.psku);
			name(product.product_name);
			strcpy(product_unit_descrp, product.product_unit_descrp);
			quantity_on_hand = product.quantity_on_hand;
			quantity_needed = product.quantity_needed;
			taxable_product = product.taxable_product;
			unit_price_before_tax = product.unit_price_before_tax;
			ErrState.message(product.ErrState.message()); 
		}
		return *this;
	}

	//Destructor
	Product::~Product()
	{
		delete[] product_name;
		product_name = nullptr;
	}

	/*This query receives a reference to an fstream object and an optional bool and returns a reference to the fstream object.This function
	inserts into the fstream object the character that identifies the product type as the first field in the record.
	inserts into the fstream object the data for the current object in comma separated fields.
	if the bool parameter is true, inserts a newline at the end of the record.*/
	std::fstream & Product::store(std::fstream & file, bool newLine) const
	{
		file << product_type << "," << psku << "," << product_name << "," << product_unit_descrp << "," << taxable_product << "," << unit_price_before_tax << "," << quantity_on_hand << "," << quantity_needed;
		if (newLine)
			file << std::endl;
		return file;
	}

	/*This modifier receives a reference to an fstream object and returns a reference to that fstream object.This function
	extracts the fields for a single record from the fstream object
	creates a temporary object from the extracted field data
	copy assigns the temporary object to the current object.*/
	std::fstream & Product::load(std::fstream & file)
	{
		//char product_type_;
		char psku_[max_sku_length+1];
		char product_name_[max_name_length+1];
		char product_unit_descrp_[max_unit_length+1];
		bool taxable_product_;
		double unit_price_before_tax_;
		int quantity_on_hand_;
		int quantity_needed_;

		//file >> product_type_;
		file.getline(psku_, max_sku_length, ',');
		file.getline(product_name_, max_name_length, ',');
		file.getline(product_unit_descrp_, max_unit_length, ',');
		file >> taxable_product_;
		file.ignore(); // get rid of the ','
		file >> unit_price_before_tax_;
		file.ignore();
		file >> quantity_on_hand_;
		file.ignore();
		file >> quantity_needed_;
		file.ignore();

		Product temp = Product(psku_, product_name_, product_unit_descrp_, quantity_on_hand_, taxable_product_, unit_price_before_tax_, quantity_needed_);
		*this = temp; 
		return file;
	}

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

	If the bool parameter is false, this function inserts the fields on separate lines with the following descriptors(a 
	single space follows each colon) :

	Sku :
	Name(no spaces) :
	Price :
	either of :
	Price after tax :
	N / A
	Quantity on hand :
	Quantity needed :*/
	std::ostream & Product::write(std::ostream & os, bool linear) const
	{
		if (ErrState.isClear()) {
			if (linear) {
				os << std::left << std::setw(max_sku_length) << psku << "|";
				os << std::left << std::setw(20) << product_name << "|";
				os << std::fixed << std::setprecision(2) << std::right << std::setw(7) << cost() << "|";
				os << std::right << std::setw(4) << quantity_on_hand << "|";
				os << std::left << std::setw(10) << product_unit_descrp << "|";
				os << std::right << std::setw(4) << quantity_needed << "|";
			}
			else {
				os << " Sku: " << psku << std::endl;
				os << " Name (no space): " << product_name << std::endl;
				os << " Price: " << price() << std::endl;
				os << " Price after tax: ";
				if (taxed())
					os << cost() << std::endl;
				else
					os << "N/A" << std::endl;
				os << " Quantity on hand: " << quantity_on_hand << " " << product_unit_descrp << std::endl;
				os << " Quantity needed: " << quantity_needed;
			}
		}
		else {
			os << ErrState;
		}
		return os;
	}

	/*This modifier receives a reference to an istream object and returns a reference to the istream object.This function 
	extracts the data fields for the current object in the following order, line by line.This function stops extracting 
	data once it has encountered an error.The error messages are shown in brackets.A single space follows each colon :
	Sku : <input value – C - style string>
	Name(no spaces) : <input value – C - style string>
	Unit : <input value – C - style string>
	Taxed ? (y / n) : <input character – y, Y, n, or N>[“Only(Y)es or (N)o are acceptable”]
	Price : <input value – double>[“Invalid Price Entry”]
	Quantity on hand : <input value – integer>[“Invalid Quantity Entry”]
	Quantity needed : <input value – integer>[“Invalid Quantity Needed Entry”]
	If this function encounters an error for the Taxed input option, it sets the failure bit of the istream object(calling 
	istream::setstate(std::ios::failbit)) and sets the error object to the error message noted in brackets.
	If the istream object is not in a failed state and this function encounters an error on accepting Price input, it sets 
	the error object to the error message noted in brackets.The member function that reports failure of an istream object is istream::fail().
	If the istream object is not in a failed state and this function encounters an error on the Quantity input, it sets the 
	error object to the error message noted in brackets.
	If the istream object is not in a failed state and this function encounters an error on the Quantity needed input, it sets 
	the error object to the error message noted in brackets.
	If the istream object has accepted all input successfully, this function stores the input values accepted in a temporary 
	object and copy assigns it to the current object.*/
	std::istream & Product::read(std::istream & is)
	{
		char sku[max_sku_length + 1];
		char name[max_name_length + 1];
		char unit[max_unit_length + 1];
		int  qtyh, qtyn;
		double price;
		char taxed;
		bool taxable;

		std::cout << " Sku: ";
		is >> sku;
		std::cout << " Name (no spaces): ";
		is >> name;
		std::cout << " Unit: ";
		is >> unit;
		std::cout << " Taxed ? (y/n): ";
		is >> taxed;

		if (taxed != 'Y' && taxed != 'y' &&  taxed != 'N' && taxed != 'n') {
			is.setstate(std::ios::failbit);
			ErrState.message("Only (Y)es or (N)o are acceptable");
		}
		else if (taxed == 'y' || taxed == 'Y')
			taxable = true;
		else
			taxable = false;

		if (!is.fail()) {
			std::cout << " Price: ";
			is >> price;
			if (is.fail())
				ErrState.message("Invalid Price Entry");
		}

		if (!is.fail()) {
			std::cout << " Quantity on hand: ";
			is >> qtyh;
			if (is.fail())
				ErrState.message("Invalid Quantity Entry");
		}

		if (!is.fail()) {
			std::cout << " Quantity needed: ";
			is >> qtyn;
			if (is.fail())
				ErrState.message("Invalid Quantity Needed Entry");
		}

		if (!is.fail()) {
			Product temp = Product(product_type);
			delete[] temp.product_name;
			temp.product_name = new char[strlen(name) + 1];
			strcpy(temp.product_name, name);
			strcpy(temp.psku, sku);
			strcpy(temp.product_unit_descrp, unit);
			temp.quantity_on_hand = qtyh;
			temp.taxable_product = taxable;
			temp.unit_price_before_tax = price;
			temp.quantity_needed = qtyn;
			*this = temp;
		}
		is.ignore(2000, '\n'); //ignores anything left in the input stream
		return is;
	}

	/*This query receives the address of an unmodifiable C - style null - terminated string and returns true 
	if the string is identical to the sku of the current object; false otherwise.*/
	bool Product::operator==(const char *sku) const
	{
		return strcmp(psku, sku) == 0;
	}

	/*This query that returns the total cost of all items of the product on hand, taxes included.*/
	double Product::total_cost() const
	{
		return cost()*quantity_on_hand;
	}

	//This modifier that receives an integer holding the number of units of the Product that are on hand.This 
	//function resets the number of units that are on hand to the number received.
	void Product::quantity(int qtyOnHand)
	{
		quantity_on_hand = qtyOnHand;
	}

	/*This query returns true if the object is in a safe empty state; false otherwise.
	int qtyNeeded() const
	This query that returns the number of units of the product that are needed.*/
	bool Product::isEmpty() const
	{
		return (product_type == 'N'&& psku[0] == '\0'&& product_unit_descrp[0] == '\0'&& quantity_on_hand == 0 && quantity_needed == 0 && product_unit_descrp == 0 && taxable_product == true && product_name == nullptr);
	}
	
	//This query that returns the number of units of the product that are needed.
	int Product::qtyNeeded() const
	{
		return quantity_needed;
	}

	//This query returns the number of units of the product that are on hand.
	int Product::quantity() const
	{
		return quantity_on_hand;
	}

	/*This query receives the address of a C - style null - terminated string holding a product sku and 
	returns true if the sku of the current object is greater than the string stored at the received address
	(according to how the string comparison functions define ‘greater than’); false otherwise.*/
	bool Product::operator>(const char * sku) const
	{
		return (psku > sku);
	}

	/*This query receives an unmodifiable reference to a Product object and returns true if the name of the 
	current object is greater than the name of the referenced Product object(according to how the string 
	comparison functions define ‘greater than’); false otherwise.*/
	bool Product::operator>(const iProduct & product) const
	{
		bool temp = false;
		if (strcmp((*this).product_name, product.name())){
			temp = true;
		}
		return temp;
	}

	/*This modifier receives an integer identifying the number of units to be added to the Product and 
	returns the updated number of units on hand.If the integer received is positive - valued, this function 
	adds it to the quantity on hand.If the integer is negative - valued or zero, this function does nothing 
	and returns the quantity on hand(without modification).*/
	int Product::operator+=(int units)
	{
		if (units > 0) {
			quantity_on_hand += units;
		}
		return quantity_on_hand;
	}

	//The following helper functions support your Product class :

	/*This helper receives a reference to an ostream object and an unmodifiable reference to a Product 
	object and returns a reference to the ostream object.Your implementation of this function will insert a Product record into the ostream.*/
	std::ostream & operator<<(std::ostream &os, const iProduct &product)
	{
		product.write(os, true); 
		return os;
	}

	/*This helper receives a reference to an istream object and a reference to a Product object and returns a 
	reference to the istream object.Your implementation of this function extracts the Product record from the istream.*/
	std::istream & operator>>(std::istream & is, iProduct & product)
	{
		product.read(is);
		return is;
	}
	/*This helper receives a reference to a double and an unmodifiable reference to a Product object and returns 
	a double.Your implementation of this function adds the total cost of the Product object to the double received and returns the updated double.*/
	double operator+=(double & total_cost, const iProduct & product)
	{
		return total_cost += product.total_cost();
	}

}
