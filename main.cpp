#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"
#include "CoffeeShop.h"
#include "Employee.h"
#include "Date.h"
#include "Customer.h"
#include "Coffee.h"
#include"Cookie.h"

int main()
{
	while (true)
	{
		try
		{
			CoffeeShop shop = initCoffeeShop();

			// For Debug :
			//CoffeeShop shop("aroma", Address("holon", "golda", 7));
			//shop.addNewEmployee(Employee("gal", "0526756660",1000, Date(12,12,2020)));
			//shop.addNewCustomer(Customer("koral", "0526745552", true));
			//shop.addNewProduct(Coffee("coffee", 10, 12, 10));
			//shop.addNewProduct(Cookie("kookoko", 55, 12, 10));
			
			menu(shop);
			break;

		}
		catch (exception & e)
		{
			cleanBuffer();
			cout << e.what() << "try again: ";
			
		}
	}
	
	return 0;
}