/***********************************************************
//Name: Gilberto Wagner Miranda da Silva
//Last modification: 12/21/2017
***********************************************************/

//A class to keep track of the errors occurring during data entry and user interaction.

/* 
The ErrorMessage class encapsulates an error message of client determined length and manages the error state of a client.
A client can create an ErrorMessage object and if the client encounters an error, it can set the object to an appropriate 
message. The object reports whether or not an error has occurred and can display the message. The isClear() query report 
if an error has occurred and the object can be send the error message to an std::ostream.
*/

#include<iostream>

#ifndef SICT_ERRORMESSAGE_H
#define SICT_ERRORMESSAGE_H



namespace sict {

	class ErrorMessage
	{
		char* errMessage;

	public:
		explicit ErrorMessage(const char* errorMessage = nullptr);
		ErrorMessage(const ErrorMessage& em) = delete;
		ErrorMessage& operator=(const ErrorMessage& em) = delete;
		virtual ~ErrorMessage();
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message()const;

	};

	std::ostream& operator<<(std::ostream& ostr, const ErrorMessage& e);



}







#endif // !1


