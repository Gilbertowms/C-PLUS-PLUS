/***********************************************************
//Name: Gilberto Wagner Miranda da Silva
//Last modification: 12/21/2017
***********************************************************/


//A class for perishable products that inherits from the “NonPerishable” class and provides an expiry date.


#ifndef SICT_PERISHABLE_H
#define SICT_PERISHABLE_H

#include "NonPerishable.h"
#include "Date.h"

namespace sict
{
	class Perishable : public NonPerishable
	{
		Date m_expiryDate;

	public:
		Perishable();

		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		const Date& expiry() const;
	};

	Product* CreatePerishable();
}
#endif //SICT_PERISHABLE_H
