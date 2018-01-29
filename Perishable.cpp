#include <fstream>
#include<cstring>
#include "Perishable.h"
#include "NonPerishable.h"


using namespace std;

namespace sict
{
	Perishable::Perishable() : NonPerishable('P')
	{
		this->m_expiryDate.setEmpty();
	}

	std::fstream& Perishable::store(std::fstream& file, bool newLine) const
	{
		if (!file.is_open())
		{
			cerr << "File is not open!" << endl;
		}
		else
		{
			NonPerishable::store(file, false);
			file	<< "," << this->m_expiryDate;
			if (newLine == true)
			{
				file << endl;
			}
		}
		return file;
	}


	std::fstream& Perishable::load(std::fstream& file)
	{
		if (!file.is_open())
		{
			cerr << "File is not open!" << endl;
		}
		else
		{
		char c;
		NonPerishable::load(file);
		file.ignore();
		this->m_expiryDate.read(file);
		file.get(c);
		}
		return file;
	}


	std::ostream & Perishable::write(std::ostream& os, bool linear) const
	{
		os.fill(' ');
		NonPerishable::write(os, linear);
		if (this->m_expiryDate.bad() || !this->m_expiryDate.isEmpty() )
		{
			if (linear)
			{
				this->m_expiryDate.write(os);
			}
			else
			{
				os << endl;
				os << "Expiry date: ";
				this->m_expiryDate.write(os);
			}
		}
		return os;
	}


	std::istream & Perishable::read(std::istream & is)
	{
		Date temp;

		NonPerishable::read(is);
		if (!is.fail())
		{
			cout << "Expiry date (YYYY/MM/DD): ";
			temp.read(is);
			if (!temp.bad())
			{
				char str[28];
				if (temp.errCode() == 1)
				{
					strcpy(str, "Invalid Date Entry");
					this->message(str);
				}
				else if (temp.errCode() == 2)
				{
					strcpy(str, "Invalid Year in Date Entry");
					this->message(str);
				}
				else if (temp.errCode() == 3)
				{
					strcpy(str, "Invalid Month in Date Entry");
					this->message(str);
				}
				else if (temp.errCode() == 2)
				{
					strcpy(str, "Invalid Day in Date Entry");
					this->message(str);
				}
				is.setstate(std::ios::failbit);
			}
			else
			{
				this->m_expiryDate = temp;
			}
		}


		return is;
	}


	const Date & Perishable::expiry() const
	{
		return this->m_expiryDate;
	}


	Product* CreatePerishable()
	{
		Product* newProduct = nullptr;
		newProduct = new Perishable();

		return newProduct;
	}
}