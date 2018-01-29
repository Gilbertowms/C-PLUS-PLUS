// Final Project Milestone 4
/**********************************************************
//Name: Gilberto Wagner Miranda da Silva
//Student Number: 139.236.160
//Email: gwmiranda-da-silva@myseneca.ca
//Section: OOPSAB
***********************************************************/


//A class to keep track of the errors occurring during data entry and user interaction.

/* 
The ErrorMessage class encapsulates an error message of client determined length and manages the error state of a client.
A client can create an ErrorMessage object and if the client encounters an error, it can set the object to an appropriate 
message. The object reports whether or not an error has occurred and can display the message. The isClear() query report 
if an error has occurred and the object can be send the error message to an std::ostream.
*/


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "ErrorMessage.h"

using namespace std;

namespace sict {

	ErrorMessage::ErrorMessage(const char* errorMessage) {
		
		if (errorMessage == nullptr)
		{
			this->errMessage = nullptr;
		}
		else
		{
			this->errMessage = nullptr;
			int size = strlen(errorMessage);
			this->errMessage = new char[size + 1];
			strcpy(this->errMessage, errorMessage);
		}
	}


	ErrorMessage::~ErrorMessage() {
		delete[] this->errMessage;
		this->errMessage = nullptr;
	}


	void ErrorMessage::clear() {
		delete[] this->errMessage;
		this->errMessage = nullptr;
	}


	bool ErrorMessage::isClear() const {
	
		if (this->errMessage == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	void ErrorMessage::message(const char* str) {
		delete[] this->errMessage;
			int size = strlen(str);
			this->errMessage = new char[size + 1];
			strcpy(this->errMessage, str);
	}


	const char* ErrorMessage::message()const {
		return errMessage;
	}

	std::ostream& operator<<(std::ostream& ostr, const ErrorMessage& e) {
		if (e.isClear() == false)
		{
			ostr << e.message();
		}
		return ostr;
	}

}
