// Final Project Milestone 4
/**********************************************************
//Name: Gilberto Wagner Miranda da Silva
//Student Number: 139.236.160
//Email: gwmiranda-da-silva@myseneca.ca
//Section: OOPSAB
***********************************************************/


#ifndef SICT_NONPERISHBLE_H
#define SICT_NONPERISHBLE_H

#include "Product.h"
#include "ErrorMessage.h"

namespace sict
{
	const int max_sku_length = 7;
	const int max_unit_lenght = 10;
	const int max_name_length = 75;
	const double tax_rate = 0.13;

	class NonPerishable :	public Product
	{
		char m_prodType;
		char m_prodSKU[max_sku_length + 1];
		char* m_prodName;
		char m_unitProd[max_unit_lenght + 1];
		int m_prodQty;
		int m_prodQtyNeeded;
		double m_prodPrice;
		bool m_isTaxed;
		ErrorMessage m_prodState;

	protected:
		void name(const char*);
		const char* name() const;
		double cost() const;
		void message(const char*);
		bool isClear() const;
		void setEmpty();
	public:
		NonPerishable(const char prodType = 'N');
		NonPerishable(const char* prdSku, const char* prdName, const char* unitProd, int prodQty = 0, bool isTaxed = 1, double prodPrice = 0, int qtyNeeded = 0);
		NonPerishable(const NonPerishable& other);
		NonPerishable& operator=(const NonPerishable& other);
		~NonPerishable();


		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator >(const char*) const;
		int operator+=(int);
		bool operator>(const Product&) const;
		
	};
		std::ostream& operator<<(std::ostream&, const Product&);
		std::istream& operator >> (std::istream&, Product&);
		double operator+=(double&, const Product&);
		Product* CreateProduct();
}
#endif // !SICT_NONPERISHBLE_H