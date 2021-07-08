#ifndef __ADDRESS_H__
#define __ADDRESS_H__

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Address {
private:
	string city;
	string streetName;
	int streetNumber;
public:
	// ctor
	Address(const string& city, const string& streetName, int streetNumber)noexcept(false);
	
	// getters
	const string& getCity() const { return city; }
	const string& getStreetName() const { return streetName; }
	int getStreetNumber() const { return streetNumber; }
	
	//setters
	bool setStreetNum(int streetNum)noexcept(false);
	// functions
	friend ostream& operator<<(ostream& os, const Address& address);
};

#endif