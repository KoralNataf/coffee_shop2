#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Product {
protected:
	string name;
	int calories;
	double cost, price;
public:
	// ctor
	Product(const string name, int calories, double cost, double price);
	
	//dtor
	virtual ~Product(){}
	
	// operators
	bool operator==(const Product& other) const;

	// clone
	virtual Product* clone() const = 0;

	// getters
	const string& getName() const { return name; }
	int getCalories() const { return calories; }
	double getCost() const { return cost; }
	double getPrice() const { return price; }

	// setters
	bool setName(const string name);
	bool setCalories(int calories)noexcept(false);
	bool setCost(double cost)noexcept(false);
	bool setPrice(double price)noexcept(false);

	// functions
	virtual void toOs(ostream& os) const = 0;
	friend ostream& operator<<(ostream& os, const Product& product);
};

#endif