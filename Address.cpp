#include "Address.h"

Address::Address(const string& city, const string& streetName, int streetNumber)
{
	
	this->city = city;
	this->streetName = streetName;
	setStreetNum(streetNumber);
}


bool Address::setStreetNum(int streetNum)
{
	if (streetNum <= 0)							
		throw exception("Street Number must be positive number!\n");

	this->streetNumber = streetNum;
	return true;
}

ostream& operator<<(ostream& os, const Address& address)
{
	os << "City: " << address.city << ", Street: " 
		<< address.streetName << ", Number: " << address.streetNumber << endl;
	return os;
}