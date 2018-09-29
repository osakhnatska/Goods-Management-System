#include <iostream>
#include <cstring>
#include "ErrorState.h"

using namespace std;

namespace GMS {

	//No/One Argument Constructor:
	/*This function receives the address of a C-style null terminated string that holds an error message. 
	If the address is nullptr, this function puts the object in a safe empty state. 
	If the address points to a non-empty message, this function allocates memory for 
	that message and copies the message into the allocated memory.*/
	ErrorState::ErrorState(const char * erM)
	{
		errorMessage = nullptr;

		if (erM == nullptr)
			message('\0');
		else {
			message(erM);
		}
	}

	/*•	This function de-allocates any memory that has been dynamically allocated by the current object.*/
	ErrorState::~ErrorState()
	{
		delete[] errorMessage;
		errorMessage = nullptr;
	}

	/*This function clears any message stored by the current object and initializes the object to a safe empty state.*/
	void ErrorState::clear()
	{
		delete[] errorMessage;
		errorMessage = nullptr;
	}

	/*This query reports returns true if the current object is in a safe empty state.*/
	bool ErrorState::isClear() const
	{
		return errorMessage[0] == '\0';
	}

	/*This function stores a copy of the C-style string pointed to by str:
	de-allocates any memory allocated for a previously stored message
	allocates the dynamic memory needed to store a copy of str (remember to include 1 extra byte for the null terminator)
	copies the string at address str to the allocated memory.*/
	void ErrorState::message(const char * str)
	{
		if (str != nullptr) {
			if (errorMessage != nullptr) {
				errorMessage[0] = '\0';
				delete[] errorMessage;
				errorMessage = nullptr;
			}
			errorMessage = new char[strlen(str) + 1];
			strncpy(errorMessage, str, strlen(str));
			if (errorMessage[strlen(str)] != '\0') errorMessage[strlen(str)] = '\0';
		}
		else {
			errorMessage = new char[1];
			errorMessage[0] = '\0';
		}
		
		/*ErrorState::~ErrorState();
		errorMessage = new char[strlen(str) + 1];
		strncpy(errorMessage, str, strlen(str)+1);
		errorMessage[strlen(str)] = '\0';
		*/
	}

	/*•	This query returns the address of the message stored in the current object.*/
	const char * ErrorState::message() const
	{
		return errorMessage;
	}

	/*Helper operator
	This operator sends an ErrorState message, if one exists, to an std::ostream object and returns a reference to the std::ostream object. 
 	If no message exists, this operator does not send anything to the std::ostream object and returns a reference to the std::ostream object.*/
	std::ostream & operator<<(std::ostream& os, const ErrorState& erSt)
	{
		if (!erSt.isClear())
			os << erSt.message();
		return os;
	}
}