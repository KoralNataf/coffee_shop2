#include "CoffeeShop.h"
#include "functions.h"
#include "Customer.h"
#include "Employee.h"
#include "Shift.h"
#include "Product.h"
#include "Date.h"
#include <ctime>

CoffeeShop::CoffeeShop(const string& name, const Address& address):address(address)
{
	this->name=name;
}

CoffeeShop::CoffeeShop(const string& name, Address&& address):address(address)
{
	this->name = name;
}

CoffeeShop::CoffeeShop(CoffeeShop&& other) : address(std::move(other.address)),
customers(std::move(other.customers)), employees(NULL), products(NULL)
{
	name=std::move(other.name);
	employees = std::move(other.employees);
	shifts = std::move(other.shifts);
	products = std::move(other.products);
}

CoffeeShop::~CoffeeShop()
{
	vector<Employee*>::const_iterator itr = employees.begin();
	vector<Employee*>::const_iterator itrEnd = employees.end();
	for (; itr != itrEnd; ++itr)
		delete* itr;

	vector<Product*>::const_iterator itrP = products.begin();
	vector<Product*>::const_iterator itrEndP = products.end();
	for (; itrP != itrEndP; ++itrP)
		delete* itrP;

	vector<Customer*>::const_iterator itrC = customers.begin();
	vector<Customer*>::const_iterator itrEndC = customers.end();
	for (; itrC != itrEndC; ++itrC)
		delete* itrC;
}

bool CoffeeShop::setAddress(const Address& address)
{
	if (address.getStreetNumber() < 0)
		throw exception("Ilegal input: street number must be positive!\n");
	this->address = address;
	return  true;
}

bool CoffeeShop::addNewEmployee(const Employee& employee)
{
	if (isExsist(employee, employees))
	{
		cout << "Employee already exsist!\n";
		return false;
	}

	employees.push_back(employee.clone());
	return true;
}

bool CoffeeShop::addNewEmployee(Employee&& employee)
{
	if (isExsist(employee, employees))
	{
		cout << "Employee already exsist!\n";
		return false;
	}

	employees.push_back(new Employee(std::move(employee)));
	return true;
}

bool CoffeeShop::addNewProduct(const Product& product)
{
	if (isExsist(product, products))
	{
		cout << "Product already exsist!\n";
		return false;
	}

	products.push_back(product.clone());
	return true;
}

bool CoffeeShop::addNewCustomer(const Customer& customer)
{
	if (isExsist(customer, customers))
	{
		cout << "Customer already exsist!\n";
		return false;
	}

	customers.push_back(new Customer(customer));
	return true;
}

bool CoffeeShop::addNewCustomer(Customer&& customer)
{
	if (isExsist(customer, customers))
	{
		cout << "Customer already exsist!\n";
		return false;
	}

	customers.push_back(new Customer(std::move(customer)));
	return true;
}

bool CoffeeShop::openShift(double clubDiscountPercent, const Date& date)
{
	shifts.add(new Shift(clubDiscountPercent, date));
	return true;
}


Shift* CoffeeShop::getCurrentShift() 
{
	time_t now = time(0);
	tm* dateStruct = localtime(&now);
	Date today(dateStruct->tm_mday, dateStruct->tm_mon + 1, dateStruct->tm_year + 1900);
	
	
	const Node<Shift*>* ptr = shifts.getHead();
	const Node<Shift*>* prev = shifts.getHead();
	while (ptr != NULL)
	{
		
		if (today == *ptr->getData()->getShiftDate())
			return ptr->getData();
		prev = ptr;
		ptr = ptr->getNext();
	}
	cout << "Shist Not Exsist!\nOpen New Shift:\n";

	double discount;
	cout << "Enter club discount: ";
	while (!(cin >> discount) || discount < 0 || discount>100)
	{
		cleanBuffer();
		cout << "ilegal input discount, try again: ";
	}
	discount = discount / 100;

	if (openShift(discount, today))
		if (shifts.getSize() == 1)
			return shifts.getHead()->getData();
		else
			return prev->getData();


	return nullptr;
}

Shift* CoffeeShop::getShiftByChoice()
{
	int choice;
	cout << "Choose option:\n1.get current shift.\n2.get shift by date.\nyour option: ";
	while (!(cin >> choice) || (choice != 1 && choice != 2))
	{
		cleanBuffer();
		cout << "Ilegal input choice!\ntry again: ";
	}

	switch (choice)
	{
	case 1:
		return getCurrentShift();
	case 2:
		return getShiftByDate();
	default:
		return nullptr;
	}
}

Shift* CoffeeShop::getShiftByDate() 
{
	int day, month, year;
	cout << "Enter Date details: " << endl;
	cout << "day: ";
	if (!(cin >> day))
		cleanBuffer();

	cout << "month: ";
	if (!(cin >> month))
		cleanBuffer();

	cout << "year: ";
	if (!(cin >> year))
		cleanBuffer();

	Date date(day, month, year);
	const Node<Shift*>* ptr = shifts.getHead();
	const Node<Shift*>* prev = shifts.getHead();
	while (ptr != NULL)
	{

		if (date == *ptr->getData()->getShiftDate())
			return ptr->getData();
		prev = ptr;
		ptr = ptr->getNext();
	}
	cout << "Shist Not Exsist!\nOpen New Shift:\n";
	
	double discount;
	cout<<"Enter club discount: "; 
	while (!(cin >> discount) || discount < 0 || discount>100)
	{
		cleanBuffer();
		cout << "ilegal input discount, try again: ";
	}
	discount = discount / 100;

	if (openShift(discount, date))
		if (shifts.getSize() == 1)
			return shifts.getHead()->getData();
		else
			return prev->getData();

	return nullptr;
}

template <class T>
bool CoffeeShop:: isExsist(const T& data, vector<T*> arr)
{
	typename vector<T*>::const_iterator itr = arr.begin();
	typename vector<T*>::const_iterator itrEnd = arr.end();
	for (; itr != itrEnd; ++itr)
		if (data == **itr)
			return true;
	return false;
}

ostream& operator<<(ostream& os, const CoffeeShop& coffeeShop)
{
	os << "\n\n*****COFFEE SHOP*****\n" << "Name: " << coffeeShop.name << " , Address: " << coffeeShop.address
		<< "\nCUSTOMERS:\n";
	int i;
	int size = (int)coffeeShop.customers.size();
	for (i = 0; i <size; i++)
		os << *coffeeShop.customers[i];
	if (i == 0)
		cout << "Customers list is empty!\n";

	os << "\nEMPLOYEES:\n";
	size = (int)coffeeShop.employees.size();
	for (i = 0; i < size; i++)
		os << *coffeeShop.employees[i];
	if (i == 0)
		cout << "Employees list is empty!\n";

	os << "\nSHIFTS:\n";
	if (coffeeShop.shifts.getSize() == 0)
		cout << "Shifts list is empty!\n";
	else
		os << coffeeShop.shifts << endl;
	
	os << "\nPRODUCTS:\n";
	size = (int)coffeeShop.products.size();
	for (i = 0; i < size; i++)
		os << *coffeeShop.products[i];
	if (i == 0)
		cout << "Products list is empty!";
	return os;
}
