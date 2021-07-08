#include "Order.h"
#include "Product.h"
#include "Employee.h"
#include "Customer.h"


Order::Order(const Order& other): employee(other.employee), customer(other.customer)
{
	
	vector<Product*>::const_iterator itr = other.items.begin();
	vector<Product*>::const_iterator itrEnd = other.items.end();
	for (;itr != itrEnd; ++itr)
		items.push_back((**itr).clone());
}

Order::Order(const Employee& employee, const Customer& customer) :employee(employee), customer(customer)
{
}

Order::~Order()
{
	vector<Product*>::iterator itr = items.begin();
	vector<Product*>::iterator itrEnd = items.end();
	for (; itr != itrEnd; ++itr)
		delete *itr;
}    

Product* Order::operator[](int index)
{
	if (index < 0 || index >= items.size())
		throw exception("Ilegal input : operator[] -index out of bounds\n");
	return items[index];
}

const Product* Order::operator[](int index) const
{
	if (index < 0 || index >= items.size())
		throw exception("Ilegal input : operator[] -index out of bounds\n");
	return items[index];
}

Order Order:: operator+(const Order& order)
{
	vector<Product*>::const_iterator itr = order.items.begin();
	vector<Product*>::const_iterator itrEnd = order.items.end();
	for (; itr != itrEnd; ++itr)
		if (!addItem(**itr))
		{
			cout << "failed adding product!" << endl;
			return order;
		}
			
	return *this;
}

bool Order::addItem(const Product& product)
{
	items.push_back(product.clone());
		return true;
}

int Order:: getTotalCalories() const
{
	int sum = 0;
	vector<Product*>::const_iterator itr = items.begin();
	vector<Product*>::const_iterator itrEnd =items.end();
	for (; itr != itrEnd; ++itr)
		sum += (*itr)->getCalories();
	return sum;
}

double Order::getOrderTotal() const
{
	double sum = 0;
	vector<Product*>::const_iterator itr = items.begin();
	vector<Product*>::const_iterator itrEnd =items.end();
	for (; itr != itrEnd; ++itr)
		sum += (*itr)->getPrice();
	return sum;
}

ostream& operator<<(ostream& os, const Order& order)
{
	int size = (int)order.items.size();
	os<<"Number Of Products: " << size << "\n\tProducts In Order:\n";
	if (size != 0)
	{
		for (int i = 0; i < size; i++)
			os << "\t" << *order[i];
		os << "\tTotal Price: " << order.getOrderTotal() << endl;
	}
	else
		os << "Product list is empty!\n";
	os <<"\tCustomer In Order:\n"<<"\t"<<order.customer;
	os << "\tEmployee In Order:\n"<<"\t" << order.employee;
	os << endl;
	return os;
}