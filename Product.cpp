#include "Product.h"

Product::Product(const string name, int calories, double cost, double price)
{
	setName(name);
	setCalories(calories);
	setCost(cost);
	setPrice(price);
}



bool Product::operator==(const Product& other) const
{
	if ((this->name == other.name) && calories == other.calories && cost == other.cost && price == other.price)
		return true;
	return false;
}

bool Product::setName(const string name)
{
	this->name = name;
	return true;
	
}

bool Product::setCalories(int calories)
{
	if (calories <= 0)
		throw exception("Ilegal input: calories must be positive number!\n");
	this->calories = calories;
	return true;
}

bool Product::setCost(double cost)
{
	if (cost <= 0)
		throw exception("Ilegal input: cost must be positive number!\n");
	this->cost = cost;
	return true;
}

bool Product::setPrice(double price)
{
	if (price <= 0)
		throw exception("Ilegal input: price must be positive number!\n");
	this->price = price;
	return true;
}

ostream& operator<<(ostream& os, const Product& product)
{
	os << "Name: " << product.name << " , Calories: " << product.calories << " , Cost: " << product.cost << " , Price: " << product.price;
	product.toOs(os);
	os << endl;
	return os;
}