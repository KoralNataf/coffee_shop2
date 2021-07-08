#ifndef __COFFEESHOP_H__
#define __COFFEESHOP_H__

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include "Address.h"
#include "LinkedList.h"
#include <vector>
#include <iterator>

class Customer;
class Employee;
class Shift;
class Product;
class Date;

class CoffeeShop {
private:
	string name;
	Address address;

	vector<Customer*> customers;
	vector <Employee*> employees;
	LinkedList <Shift*> shifts;
	vector <Product*> products;
	
public:
	// ctor
	CoffeeShop(const string& name, const Address& address);
	// copy ctor
	CoffeeShop(const CoffeeShop& other) = delete;
	// move ctor
	CoffeeShop(CoffeeShop&& other) noexcept(false);
	CoffeeShop(const string& name, Address&& address);
	// assignment operator
	const CoffeeShop& operator=(const CoffeeShop& other) = delete;
	// move assignment operator
	const CoffeeShop& operator=(CoffeeShop&& other) = delete;
	// dtor
	~CoffeeShop();

	// getters
	const string& getName() const { return name; }
	const Address* getAddress() const { return &address; }
	const vector <Customer*> getCustomers() const { return customers; }
	const vector <Employee*> getEmployees() const { return employees; }
	const LinkedList<Shift*>& getShifts() const { return shifts; }
	LinkedList<Shift*>& getShifts() { return shifts; }

	const vector <Product*> getProducts() const { return products; }

	// setters
	bool setAddress(const Address& address)noexcept(false);
	
	// functions
	bool addNewEmployee(const Employee& employee);
	bool addNewEmployee(Employee&& employee);	
	bool addNewProduct(const Product& product);
	bool addNewCustomer(const Customer& customer);
	bool addNewCustomer(Customer&& customer);
	bool openShift(double clubDiscountPercent, const Date& date);
	Shift* getCurrentShift() ;
	Shift* getShiftByChoice() noexcept(false);
	Shift* getShiftByDate() noexcept(false);
	template <class T>
	bool isExsist(const T& data, vector<T*> arr);
	friend ostream& operator<<(ostream& os, const CoffeeShop& coffeeShop);
};

#endif