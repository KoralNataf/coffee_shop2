#ifndef __SHIFT_H__
#define __SHIFT_H__

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;
#include <vector>
#include <iterator>

#include "Date.h"
class Order;
class Employee;
class Product;

class Shift {
private:

	double clubDiscountPercent;
	Date shiftDate;

	vector<Employee*> employees;
	vector<Product*> dailyMenu;
	vector<Order*> orders;
	
public:
	// ctor
	Shift(double clubDiscountPercent, const Date& shiftDate); 
	// copy ctor
	Shift(const Shift& other) = delete;
	//dtor
	~Shift();
	// assignment operator
	const Shift& operator=(const Shift& other) = delete;
	// move assignment operator
	const Shift& operator=(Shift&& other) = delete;

	// getters

	double getClubDiscountPercent() const { return clubDiscountPercent; }
	const Date* getShiftDate() const { return &shiftDate; }
	const vector<Employee*> getEmployees() const { return employees; }
	const vector<Product*> getDailyMenu() const { return dailyMenu; }
	const vector<Order*> getOrders() const { return orders; }

	// setters
	bool setClubDiscountPercent(double clubDiscountPercent)noexcept(false);

	// functions
	bool addProductToMenu(const Product& product);
	bool addEmployeeToShift(const Employee& employee);
	bool addOrder(const Order& order);
	const Employee* getShiftManger() const;
	double getShiftProfit() const;
	template <class T>
	bool isExsist(const T& data, vector<T*> arr);
	friend ostream& operator<<(ostream& os, const Shift& shift);
};

#endif