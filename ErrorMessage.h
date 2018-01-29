// Final Project Milestone 4
/**********************************************************
//Name: Gilberto Wagner Miranda da Silva
//Student Number: 139.236.160
//Email: gwmiranda-da-silva@myseneca.ca
//Section: OOPSAB
***********************************************************/


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


