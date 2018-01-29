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

#include "Date.h"

namespace sict {

	Date::Date() {
		setEmpty();
	}
	
	Date::Date(int year, int month, int day) {
		if (year >= min_year && year <= max_year && month > 0 && month < 13 && day <= mdays(month, year))
		{
			this->m_year = year;
			this->m_month = month;
			this->m_day = day;
			this->m_errorState = NO_ERROR;
			this->m_comparator = year * 372 + month * 13 + day;
		}
		else
		{
			setEmpty();
		}
	}


	bool Date::operator==(const Date& rhs) const {
		bool flag;
		if (this->isEmpty() == true || rhs.isEmpty() == true)
		{
			flag = false;
		}
		else
		{
			if (this->m_comparator == rhs.m_comparator)
			{
				flag = true;
			}
		}
		return flag;
	}


	bool Date::operator!=(const Date& rhs) const {
		bool flag;
		if (this->isEmpty() == true || rhs.isEmpty() == true)
		{
			flag = false;
		}
		else
		{
			if (this->m_comparator != rhs.m_comparator)
			{
				flag = true;
			}
		}
		return flag;
	}

	bool Date::operator < (const Date& rhs) const {
		bool flag;
		if (this->isEmpty() == true || rhs.isEmpty() == true)
		{
			flag = false;
		}
		else
		{
			if (this->m_comparator < rhs.m_comparator)
			{
				flag = true;
			}
		}
		return flag;
	}


	bool Date::operator > (const Date& rhs) const {
		bool flag;
		if (this->isEmpty() == true || rhs.isEmpty() == true)
		{
			flag = false;
		}
		else
		{
			if (this->m_comparator > rhs.m_comparator)
			{
				flag = true;
			}
		}
		return flag;
	}


	bool Date::operator <= (const Date& rhs) const {
		bool flag;
		if (this->isEmpty() == true || rhs.isEmpty() == true)
		{
			flag = false;
		}
		else
		{
			if (this->m_comparator <= rhs.m_comparator)
			{
				flag = true;
			}
		}
		return flag;
	}


	bool Date::operator >= (const Date& rhs) const {
		bool flag;
		if (this->isEmpty() == true || rhs.isEmpty() == true)
		{
			flag = false;
		}
		else
		{
			if (this->m_comparator >= rhs.m_comparator)
			{
				flag = true;
			}
		}
		return flag;
	}


	int Date::errCode() const {
		return this->m_errorState;
	}


	bool Date::bad()const {
		if (this->m_errorState == NO_ERROR)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	std::istream& Date::read(std::istream& istr) {
		char temp;

		istr >> this->m_year >> temp >> this->m_month >> temp >> this->m_day;
		if (istr.fail() == true)
		{
			this->m_errorState = CIN_FAILED;
			return istr;
		}
		else
		{
			if (m_year >= min_year && m_year <= max_year && m_month > 0 && m_month < 13 && m_day <= mdays(m_month, m_year))
			{
				this->m_errorState = NO_ERROR;
			}
			else
			{
				if (m_year < min_year || m_year > max_year)
				{
					this->m_errorState = YEAR_ERROR;
				}
				else if (m_month < 1 || m_month > 12)
				{
					this->m_errorState = MON_ERROR;
				}
				else
				{
					this->m_errorState = DAY_ERROR;
				}
				this->m_year = 0;
				this->m_month = 0;
				this->m_day = 0;
				this->m_comparator = 0;
			}
			return istr;
		}
	}

	std::ostream& Date::write(std::ostream& ostr) const {
		if (!isEmpty())
		{
		ostr << this->m_year << "/";
		ostr.fill('0');
		ostr.width(2);
		ostr << this->m_month << "/";
		ostr.fill('0');
		ostr.width(2);
		ostr << this->m_day;
		}

		return ostr;
	}

	std::istream& operator >> (std::istream& istr, Date& date) {
		date.read(istr);
		return istr;
	}

	std::ostream& operator<<(std::ostream& ostr, const Date& date) {
		date.write(ostr);
		return ostr;
	}

	//Private member functions
	void Date::setEmpty() {
		this->m_year = 0;
		this->m_month = 0;
		this->m_day = 0;
		this->m_errorState = NO_ERROR;
		this->m_comparator = 0;
	}

	bool Date::isEmpty() const {
		
		if (this->m_year == 0 && this->m_month == 0 && this->m_day == 0 && this->m_errorState == NO_ERROR && this->m_comparator == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// number of days in month mon_ and year year_
	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}


	void Date::errCode(int errorCode) {
		this->m_errorState = errorCode;
	}
}


