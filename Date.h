// Final Project Milestone 1
/***********************************************************
//Name: Gilberto Wagner Miranda da Silva
//Student Number: 139.236.160
//Email: gwmiranda-da-silva@myseneca.ca
//Section: OOPSAB
***********************************************************/

// A class to be used to hold the expiry date of the perishable items. 

/*
The Date class encapsulates a date that is readable by an std::istream 
and printable by an std::ostream using the following format for both reading and writing: YYYY/MM/DD  
*/


#include <iostream>
#include <cstring>

#ifndef SICT_DATE_H
#define SICT_DATE_H

#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3
#define DAY_ERROR 4

namespace sict {
	
	int const min_year = 2000;
	int const max_year = 2030;

	class Date {

		int m_year;
		int m_month;
		int m_day;
		int m_comparator;
		int m_errorState;

		int mdays(int, int)const;
		void errCode(int errorCode);
	public:
		Date();
		Date(int, int, int);
		bool isEmpty() const;
		void setEmpty();

		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;

		int errCode() const;
		bool bad()const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;
	};
	std::istream& operator>>(std::istream&, Date&);
	std::ostream& operator<<(std::ostream&, const Date&);
}
#endif
