/***********************************************************
//Name: Gilberto Wagner Miranda da Silva
//Last modification: 12/21/2017
***********************************************************/

//A class for non-perishable products that implements the requirements of the “Product” interface 


#define _CRT_SECURE_NO_WARNINGS
#include<fstream>
#include<iostream>
#include <cstring>
#include <string>
#include "NonPerishable.h"
#include "ErrorMessage.h"


using namespace std;

namespace sict
{
	//PROTECTED MEMBER FUNCTIONS
	void NonPerishable::name(const char* prodName)
	{
		if (prodName != nullptr)
		{
			delete[] this->m_prodName;
			this->m_prodName = new char[strlen(prodName) + 1];
			strcpy(this->m_prodName, prodName);
		}
		else
		{
			delete[] this->m_prodName;
			this->m_prodName = nullptr;
		}
	}


	const char* NonPerishable::name() const
	{
		char* prodName_ptr = nullptr;
		if (this->m_prodName != nullptr)
		{
			prodName_ptr = this->m_prodName;
		}

		return prodName_ptr;
	}


	double NonPerishable::cost() const
	{
		double totalPrice = this->m_prodPrice;
		
		if (this->m_isTaxed)
		{
			totalPrice = this->m_prodPrice + (this->m_prodPrice * tax_rate);
		}
		return totalPrice;
	}


	void NonPerishable::message(const char* errMessage)
	{
		this->m_prodState.message(errMessage);
	}


	bool NonPerishable::isClear() const
	{
		return this->m_prodState.isClear();
	}


	void NonPerishable::setEmpty()
	{
		this->m_prodType = 'N';
		this->m_prodSKU[0] = '\0';
		this->m_prodName = nullptr;
		this->m_unitProd[0] = '\0';
		this->m_prodQty = 0;
		this->m_prodQtyNeeded = 0;
		this->m_prodPrice = 0;
		this->m_isTaxed = false;
		this->m_prodState.clear();
	}


	//PUBLIC MEMBER FUNCTIONS
	NonPerishable::NonPerishable(const char prodType)
	{
		setEmpty();
		this->m_prodType = prodType;
	}


	NonPerishable::NonPerishable(const char* prdSku, const char* prdName, const char* unitProd, int prodQty, bool isTaxed, double prodPrice, int qtyNeeded)
	{
		if (prdSku != nullptr && prdName != nullptr && unitProd != nullptr)
		{
			int len;
			
			len = strlen(prdSku);
			if (len <= max_sku_length)
			{
				strncpy(this->m_prodSKU, prdSku, len);
				this->m_prodSKU[len] = '\0';
			}
			else
			{
				strncpy(this->m_prodSKU, prdSku, max_sku_length);
				this->m_prodSKU[max_sku_length] = '\0';
			}

			this->m_prodName = nullptr;
			this->name(prdName);

			len = strlen(unitProd);
			if (len <= max_unit_lenght)
			{
				strncpy(this->m_unitProd, unitProd, len);
				this->m_unitProd[len] = '\0';
			}
			else
			{
				strncpy(this->m_unitProd, unitProd, max_unit_lenght);
				this->m_unitProd[max_unit_lenght] = '\0';
			}
			this->m_prodType = '\0';
			this->m_prodQty = prodQty;
			this->m_isTaxed = isTaxed;
			this->m_prodPrice = prodPrice;
			this->m_prodQtyNeeded = qtyNeeded;
		}
		else
		{
			setEmpty();
		}
	}

	NonPerishable::NonPerishable(const NonPerishable & other)
	{
		this->setEmpty();
		*this = other;
	}

	NonPerishable& NonPerishable::operator=(const NonPerishable& other)
	{
		if (this != &other)
		{
			if (other.m_prodName != nullptr)
			{
				delete[] this->m_prodName;
				this->m_prodName = nullptr;
				this->name(other.m_prodName);
			
				this->m_prodType = other.m_prodType;
				strcpy(this->m_prodSKU, other.m_prodSKU);
				strcpy(this->m_unitProd, other.m_unitProd);
				this->m_prodQty = other.m_prodQty;
				this->m_isTaxed = other.m_isTaxed;
				this->m_prodPrice = other.m_prodPrice;
				this->m_prodQtyNeeded = other.m_prodQtyNeeded;
			}
			else
			{
				this->setEmpty();
			}
		}
		return *this;
	}

	NonPerishable::~NonPerishable()
	{
		delete[] this->m_prodName;
	}


	std::fstream& NonPerishable::store(std::fstream & file, bool newLine) const
	{
		if (!file.is_open())
		{
			cerr << "File is not open!" << endl;
		}
		else
		{
			file << this->m_prodType << "," << this->m_prodSKU << "," << this->m_prodName << "," << this->m_prodPrice << "," << this->m_isTaxed << "," << this->m_prodQty << "," << this->m_unitProd << "," << this->m_prodQtyNeeded;
			if (newLine == true)
			{
				file << endl;
			}
		}
		return file;
	}


	std::fstream & NonPerishable::load(std::fstream& file)
	{
		NonPerishable temp;
		char tempName[max_name_length + 1];

		if (!file.is_open())
		{
			cerr << "File is not open!" << endl;
		}
		else
		{
			file.getline(temp.m_prodSKU, max_sku_length, ',');
			file.getline(tempName, max_name_length, ',');
			temp.m_prodName = nullptr;
			temp.name(tempName);
			file >> temp.m_prodPrice;
			file.ignore();
			file >> temp.m_isTaxed;
			file.ignore();
			file >> temp.m_prodQty;
			file.ignore();
			file.getline(temp.m_unitProd, max_unit_lenght, ',');
			file >> temp.m_prodQtyNeeded;
	
			if (!temp.isEmpty())
			{
				*this = temp;
			}
		}
		
		return file;
	}
	

	std::ostream& NonPerishable::write(std::ostream & os, bool linear) const
	{
		if (!this->m_prodState.isClear())
		{
			os << this->m_prodState;
		}
		else{
			if (linear)
				{
					os.setf(ios::left);
					os.width(max_sku_length);
					os << this->m_prodSKU << "|";
					os.width(20);
					os <<  this->m_prodName << "|";
					os.unsetf(ios::left);
					os.setf(ios::fixed);
					os.precision(2);
					os.width(7);
					os << this->cost() << "|";
					os.unsetf(ios::fixed);
					os.width(4);
					os << this->m_prodQty << "|";
					os.width(10);
					os.setf(ios::left);
					os << this->m_unitProd << "|";
					os.unsetf(ios::left);
					os.width(4);
					os << this->m_prodQtyNeeded << "|";
				}
				else
				{
					os << "Sku: " << this->m_prodSKU << endl;
					os << "Name: " << this->m_prodName << endl;
					os.setf(ios::fixed);
					os.precision(2);
					os << "Price: " << this->m_prodPrice << endl;
					if (this->m_isTaxed)
					{
						os.setf(ios::fixed);
						os.precision(2);
						os << "Price after tax: " << cost() << endl;
						os.unsetf(ios::fixed);
					}
					else
					{
						os << "Price after tax: N/A" << endl;
					}
					os << "Quantity On Hand: " << this->m_prodQty << " " << this->m_unitProd << endl;
					os << "Quantity Needed: " << this->m_prodQtyNeeded;
				}
			}
		return os;
	}


	std::istream & NonPerishable::read(std::istream& is)
	{
		NonPerishable tmp;
		char tmp_tax;
		char str[max_name_length + 1];
		
		if (this->m_prodType == 'P')
		{
			tmp.m_prodType = 'P';
		}
		else
		{
			tmp.m_prodType = 'N';
		}
		cout << " Sku: ";
		is.getline(tmp.m_prodSKU, max_sku_length);
		cout << " Name: ";
		is >> str;
		tmp.name(str);
		cout << " Unit: ";
		is >> tmp.m_unitProd;
		cout << " Taxed? (y/n): ";
		is >> tmp_tax;
		if (tmp_tax != 'Y' && tmp_tax != 'y' && tmp_tax != 'N' && tmp_tax != 'n')
		{
			is.setstate(std::ios::failbit);
			this->m_prodState.message("Only (Y)es or (N)o are acceptable");
		}
		else
		{
			if (tmp_tax == 'Y' || tmp_tax == 'y') 
			{
				tmp.m_isTaxed = 1;
			}
			else
			{
				tmp.m_isTaxed = 0;
			}
			is.clear();
			cout << " Price: ";
			is >> tmp.m_prodPrice;
			if (is.fail())
			{
				this->m_prodState.message("Invalid Price Entry");
				is.setstate(std::ios::failbit);
			}
			else
			{
				is.clear();
				std::cout << "Quantity On hand: ";
				is >> tmp.m_prodQty;

				if (is.fail())
				{
					this->m_prodState.message("Invalid Quantity Entry");
					is.setstate(std::ios::failbit);
				}
				else
				{
					is.clear();
					std::cout << "Quantity Needed: ";
					is >> tmp.m_prodQtyNeeded;

					if (is.fail())
					{
						this->m_prodState.message("Invalid Quantity Needed Entry");
						is.setstate(std::ios::failbit);
					}
					else
					{
						this->m_prodState.clear();
						*this = tmp;
					}
				}
			}
		}

		return is;
	}


	bool NonPerishable::operator==(const char* sku) const
	{
		if (strcmp(this->m_prodSKU, sku))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	double NonPerishable::total_cost() const
	{
		double total = this->m_prodQty * cost();
		return total;
	}

	void NonPerishable::quantity(int newValue)
	{
		if (newValue >= 0)
		{
			this->m_prodQty = newValue;
		}
		else
		{
			this->m_prodQty = 0;
		}
	}


	bool NonPerishable::isEmpty() const
	{
		bool isErrorState = false;
		if (this->m_prodSKU[0] == '\0')
		{
			isErrorState = true;
		}

		return isErrorState;
	}


	int NonPerishable::qtyNeeded() const
	{
		return this->m_prodQtyNeeded;
	}


	int NonPerishable::quantity() const
	{
		return this->m_prodQty;
	}


	bool NonPerishable::operator>(const char* sku) const
	{
		bool isGreater = false;
		if (strcmp(sku, this->m_prodSKU) > 0)
		{
			isGreater = true;
		}
		return isGreater;
	}


	int NonPerishable::operator+=(int toAdd)
	{
		if (toAdd > 0)
		{
			this->m_prodQty += toAdd;
			return this->m_prodQty;
		}
		else
		{
			return this->m_prodQty;
		}
	}


	bool NonPerishable::operator>(const Product& other) const
	{
		bool greater = false;
		if (strcmp(this->m_prodName, other.name()) > 0)
		{
			greater = true;
		}
		return greater;
	}


	// HELPER FUNCTIONS
	std::ostream & operator<<(std::ostream& os, const Product& NonPerishable)
	{
		NonPerishable.write(os, true);
		return os;
	}
	std::istream & operator >> (std::istream& is, Product& NonPerishable)
	{
			NonPerishable.read(is);
			return is;
	}


	double operator+=(double& toUpdate, const Product &prod)
	{
		toUpdate += prod.total_cost();
		return toUpdate;
	}


	Product * CreateProduct()
	{
		Product* newProduct = nullptr;
		newProduct = new NonPerishable();

		return newProduct;
	}
}
