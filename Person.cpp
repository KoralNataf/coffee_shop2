#include "Person.h"

Person:: Person(const string name, const string phoneNumber)
{
	this->name = name;
	setPhoneNumber(phoneNumber);
}

Person::Person(const Person& other)
{
	*this = other;
}

const Person& Person::operator=(const Person& other)
{
	if (this != &other)
	{
		this->name = other.name;
		
		this->phoneNumber = other.phoneNumber;
	}
	return *this;
}

const Person& Person:: operator=(Person&& other)
{
	if (this != &other)
	{
		std::swap(name, other.name);
		std::swap(phoneNumber, other.phoneNumber);
	}
	return *this;
}

bool Person::operator==(const Person& other) const
{
	if ((this->name== other.name) && (this->phoneNumber== other.phoneNumber))
		return true;
	return false;
}

bool Person::setPhoneNumber(const string phoneNumber)
{
	if (phoneNumber.length() != PHONE_SIZE)
		throw exception("Ilegal input: phone must be 10 digits!\n");
	for (int i = 0; i < PHONE_SIZE; i++)
		if (phoneNumber[i] < '0' || phoneNumber[i]>'9')
			throw exception("Ilegal input: phone must be only digits!\n");
	this->phoneNumber = new char[PHONE_SIZE+1];
	this->phoneNumber= phoneNumber;
	return true;
}

void Person::toOs(ostream& os) const
{
}

ostream& operator<<(ostream& os, const Person& person)
{
	os << "Name: " << person.name << ", Phone number: " << person.phoneNumber;
	person.toOs(os);
	os << endl;
	return os;
}
