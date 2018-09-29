#ifndef GMS_iProduct_H
#define GMS_iProduct_H

#include <iostream>
#include <fstream>

namespace GMS {

	class iProduct {

	public:

		virtual ~iProduct() {};

		//This query will receive a reference to an fstream object and an optional bool and return a reference 
		//to the fstream object.The bool argument will specify whether or not a newline should be inserted 
		//after each iProduct record.Implementations of this function will insert the Product records into the fstream object.
		virtual std::fstream& store(std::fstream& file, bool newLine = true) const = 0;


		/*This modifier will receive a reference to an fstream object and return a reference to that fstream 
		object.Implementations of this function will extract iProduct records from the fstream object.*/
		virtual std::fstream& load(std::fstream& file) = 0;

		/*This query will receive a reference to an ostream object and a bool and return a reference to the 
		ostream object.The bool argument will specify whether or not the records should be listed on a single 
		line or on separate lines.Implementations of this function will insert the iProduct record for the current object into the ostream object.*/
		virtual std::ostream& write(std::ostream& os, bool linear) const = 0;

		//This modifier will receive a reference to an istream object and returns a reference to the 
		//istream object.Implementations of this function will extract the iProduct record for the current object from the istream object.
		virtual std::istream& read(std::istream& is) = 0;

		/*This query will receive the address of an unmodifiable C - style null - terminated string 
		and return true if the string is identical to the stock keeping unit of an iProduct record; false otherwise.*/
		virtual bool operator==(const char*) const = 0;

		//This query will return the cost of a single unit of an iProduct with taxes included.
		virtual double total_cost() const = 0;

		//This query will return the address of a C - style null - terminated string containing the name of an iProduct.
		virtual const char* name() const = 0;

		//This modifier will receive an integer holding the number of units of an iProduct that are currently available.
		//This function will set the number of units available.
		virtual void quantity(int) = 0;

		/*This query will return the number of units of an iProduct that are needed.*/
		virtual int qtyNeeded() const = 0;

		/*This query will return the number of units of an iProduct that are currently available.*/
		virtual int quantity() const = 0;

		/*This modifier will receive an integer identifying the number of units to be added to the iProduct and return
		the updated number of units currently available.*/
		virtual int operator+=(int) = 0;

		/*This query will receive an unmodifiable reference to an iProduct object and return true if the current object is 
		greater than the referenced iProduct object; false otherwise.*/
		virtual bool operator>(const iProduct&) const = 0;

	};
	/*The following helper functions support your interface :*/
		
	/*This helper function will receive a reference to an ostream object and an unmodifiable reference to an iProduct 
	object and return a reference to the ostream object.Implementations of this function will insert the iProduct record 
	for the referenced object into the ostream object.*/
	std::ostream& operator<<(std::ostream&, const iProduct&);

	/*This helper function will receive a reference to an istream object and a reference to an iProduct object and 
	return a reference to the istream object.Implementations of this function will extract the iProduct record for the referenced object from the istream object.*/
	std::istream& operator>>(std::istream&, iProduct&);

	/*This helper function will receive a reference to a double and an unmodifiable reference to an iProduct object 
	and return a double.Implementations of this function will add the total cost of the iProduct object to the double 
	received and return the updated value of the double.*/
	double operator+=(double&, const iProduct&);

	//This helper function will return the address of a Product object.
	iProduct* CreateProduct();

	/*This helper function will return the address of a Perishable object.*/
	iProduct* CreatePerishable();
}

#endif // !GMS_iProduct_H
