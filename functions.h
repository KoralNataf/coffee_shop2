#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#include "CoffeeShop.h"
#include <string>

enum class eProductType { COFFEE, COOKIE, SALAD };

// initialize cofeeshop from user input
CoffeeShop initCoffeeShop()noexcept(false);

// coffeeshop menu
void menu(CoffeeShop& shop);


// 1.
void showCoffeeShop(CoffeeShop& shop);
// 2. 3. 4. 5.
template <class T>
void show(vector<T*> arr);

const Product* showProductsByType(CoffeeShop& shop, const type_info& productType);
// 6.
void addProductMenu(CoffeeShop& shop);

bool addProduct(CoffeeShop& shop, const type_info& productType)noexcept(false);

bool addCookieCoffee(CoffeeShop& shop)noexcept(false);
// 7.
void addEmployee(CoffeeShop& shop)noexcept(false);
// 8.
void addCustomer(CoffeeShop& shop);
//9.
void shiftMenu(CoffeeShop& shop);
// 10.
void makeOrder(CoffeeShop& shop, Shift& shift);

void addEmployeesToShift(CoffeeShop& shop, Shift& shift);

void addProductToDailyMenu(CoffeeShop& shop, Shift& shift);

void removeShiftByDate(CoffeeShop& shop);

void cleanBuffer();

#endif