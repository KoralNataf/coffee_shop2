#include "Shift.h"
#include "Product.h"
#include "Employee.h"
#include "Order.h"
Shift:: Shift(double clubDiscountPercent, const Date& shiftDate):shiftDate(shiftDate)
{
	setClubDiscountPercent(clubDiscountPercent);
}

Shift::~Shift()
{
	vector<Employee*>::const_iterator itr = employees.begin();
	vector<Employee*>::const_iterator itrEnd = employees.end();
	for (; itr != itrEnd; ++itr)
		delete *itr;

	vector<Product*>::const_iterator itrP = dailyMenu.begin();
	vector<Product*>::const_iterator itrEndP = dailyMenu.end();
	for (; itrP != itrEndP; ++itr)
		delete* itr;

	vector<Order*>::const_iterator itrO = orders.begin();
	vector<Order*>::const_iterator itrEndO = orders.end();
	for (; itrO != itrEndO; ++itr)
		delete* itr;
}

bool Shift::setClubDiscountPercent(double clubDiscountPercent)
{
	if (clubDiscountPercent < 0 || clubDiscountPercent>1)
		throw exception("Ilegal input: discount must be between 0-1!\n");
	this->clubDiscountPercent = clubDiscountPercent;
	return true;
}

bool Shift::addProductToMenu(const Product& product)
{
	if (isExsist(product, dailyMenu))
		return false;
	
	dailyMenu.push_back(product.clone());
	return true;
}

bool Shift::addEmployeeToShift(const Employee& employee)
{
	if (isExsist(employee , employees))
		return false;

	employees.push_back(employee.clone());
	return true;
}

bool Shift::addOrder(const Order& order)
{
	orders.push_back(new Order(order));
	return true;
}

const Employee* Shift::getShiftManger() const
{
	if (employees.size()== 0)
		return nullptr;
	Employee* senior = employees[0];

	vector<Employee*>::const_iterator itr = employees.begin();
	vector<Employee*>::const_iterator itrEnd = employees.end();
	for (; itr != itrEnd; ++itr)
		if ((*itr)->getSeniority() > senior->getSeniority())
			senior = *itr;
	return senior;
}

double Shift::getShiftProfit() const
{
	double sum = 0;
	vector<Order*>::const_iterator itr = orders.begin();
	vector<Order*>::const_iterator itrEnd = orders.end();
	for (; itr != itrEnd; ++itr)
		sum += (*itr)->getOrderTotal();
	return sum;
}

template <class T>
bool Shift::isExsist(const T& data, vector<T*> arr)
{
	typename vector<T*>::const_iterator itr = arr.begin();
	typename vector<T*>::const_iterator itrEnd = arr.end();
	for (; itr != itrEnd; ++itr)
		if (data == **itr)
			return true;
	return false;
}

ostream& operator<<(ostream& os, const Shift& shift)
{
	os << "***SHIFT " << shift.shiftDate << "***\n\tEMPLOYTEES IN SHIFT:\n";
	if (shift.employees.size() != 0)
	{
		vector<Employee*>::const_iterator itr = shift.employees.begin();
		vector<Employee*>::const_iterator itrEnd = shift.employees.end();
		for (; itr != itrEnd; ++itr)
			os << "\t" << **itr;
		os << "\tManager: " << *shift.getShiftManger();
	}
	else
		cout << "\tEmployees List Is Empty!\n";

	os << "\tDAILY MENU:\n";
	if (shift.dailyMenu.size() != 0)
	{
		vector<Product*>::const_iterator itr = shift.dailyMenu.begin();
		vector<Product*>::const_iterator itrEnd = shift.dailyMenu.end();
		for (; itr != itrEnd; ++itr)
			os << "\t" << **itr;
	}
	else
		cout << "\tProducts List Is Empty!\n";
	
	os << "\tSHIFT OEDERS:\n";
	if (shift.orders.size() != 0)
	{
		vector<Order*>::const_iterator itr = shift.orders.begin();
		vector<Order*>::const_iterator itrEnd = shift.orders.end();
		for (int i =1; itr != itrEnd; ++itr, i++)
		{
			cout << "\tOrder Number " << i << ": \n";
			os << "\t" << **itr;
		}
			
	}
	else
		cout << "\tOrders List Is Empty!\n";

	return os;
}