#include "functions.h"
#include "Salad.h"
#include "Coffee.h"
#include "Cookie.h"
#include "CookieCoffee.h"
#include "Shift.h"
#include "Customer.h"
#include "Employee.h"
#include "Order.h"
#include "CoffeeShop.h"
#include "LinkedList.h"
#include <iostream>
using namespace std;
#include <exception>


CoffeeShop initCoffeeShop()
{
	string name,city, streetName;
	int streetNum;

	// enter coffeeshop details
	cout << "Enter Coffee-Shop name: ";
	getline(cin, name);

	cout << "Enter Address details: \n";
	cout << "Enter City: " ;
	getline(cin, city);

	cout << "Enter Street name: " ;
	getline(cin, streetName);

	cout << "Enter Street number: ";
	cin >> streetNum;

	
	return CoffeeShop(name, Address(city, streetName, streetNum));
}

// coffeeshop menu
void menu(CoffeeShop& shop)
{
	int choice = -1;
	while (choice)
	{
		// get choice from user
		cout << "\nSHOP MENU:" << endl;
		cout << "===============" << endl;

		cout << "Enter your choice:" << endl;
		cout << "1 - Show coffee shop details" << endl;
		cout << "2 - Show employees details" << endl;
		cout << "3 - Show customers details" << endl;
		cout << "4 - Show products details" << endl;
		cout << "5 - Show shifts details" << endl;
		cout << "6 - Add new product to coffee shop" << endl;
		cout << "7 - Add new employee to coffee shop" << endl;
		cout << "8 - Add new customer to coffee shop" << endl;
		cout << "9 - Shift menu" << endl;
		cout << "10- Remove Shift By Date" << endl;
		cout << "0 - Quit" << endl;
		cout << "Your choice: ";
		if (!(cin >> choice))
		{
			choice = -1;
			cleanBuffer();
		}

		try
		{
			
			switch (choice)
			{
			case 1:
				// 1. show coffeeshop details
				showCoffeeShop(shop);
				break;
			case 2:
				// 2. show employees details
					show(shop.getEmployees());
				break;
			case 3:
				// 3. show customers details
				show(shop.getCustomers());
				break;
			case 4:
				// 4. show products details
					show(shop.getProducts());
				break;
			case 5:
				// 5. show shifts details
				cout << shop.getShifts() << endl;
				break;
			case 6:
				// 6. add new product to coffee shop
				addProductMenu(shop);
				break;
			case 7:
				// 7. add new employee to coffee shop
				addEmployee(shop);
				break;
			case 8:
				// 8. add new customer to coffee shop
				addCustomer(shop);
				break;
			case 9:
				//9. creat/show shifts
				shiftMenu(shop);
				break;
			case 10:
				//10. remove shift
				removeShiftByDate(shop);
				break;
			case 0:
				// exit menu
				cout << "Thank you for using the Coffee Shop System, goodbye." << endl;
				return;
			default:
				// show unknown choice msg
				cout << "Invalid choice, try again: ";
				break;
			}
		}
		catch (exception &e)
		{
			cout << e.what() << "try again! \n";
		}
		
	}
}

// return true if shift is still open
void shiftMenu(CoffeeShop& shop)
{
	int choice = -1;

	// get current shift
	Shift* shift = shop.getShiftByChoice();
	while (choice)
	{
		// get choice from user
		cout << "\nSHIFT MENU: " <<*shift->getShiftDate()<< endl;
		cout << "===============" << endl;

		cout << "Enter your choice:" << endl;
		cout << "1 - Show daily menu" << endl;
		cout << "2 - Make order" << endl;
		cout << "3 - Add employee to shift" << endl;
		cout << "4 - Add product to dailyMenu" << endl;
		cout << "5 - Close shift" << endl;
		cout << "0 - Quit" << endl;
		cout << "Your choice: ";

		if (!(cin >> choice))
			choice = -1;

		switch (choice)
		{
		case 1:
			// 1. show daily menu
				show(shift->getDailyMenu());
			break;
		case 2:
			// 2. make order
			makeOrder(shop, *shift);
			break;
		case 3:
			// 3. add employee to shift
			addEmployeesToShift(shop, *shift);
			break;
		case 4:
			// 4. add product to dailyMenu
			addProductToDailyMenu(shop, *shift);
			break;
		case 5:
			// 5. close shift
			return;
		case 0:
			// exit shift menu
			return;
		default:
			// show unknown choice msg
			cout << "Invalid choice, try again." << endl;
			break;
		}
	}
}

void showCoffeeShop(CoffeeShop& shop)
{
	cout << "The coffee shop details are:" << shop << endl;
}

template <class T>
void show(vector<T*> arr)
{
	cout << "The " << (typeid(T).name())+6  << "s " << "are: " << endl;
	if (arr.size() != 0)
	{
		typename vector<T*>::const_iterator itr = arr.begin();
		typename vector<T*>::const_iterator itrEnd = arr.end();


		for (int i = 1; itr != itrEnd ; i++, ++itr)
			cout << i << ". " << **itr;
	}
	else
		cout << (typeid(T).name()) + 6 << "s list is empty!\n";

}

const Product* showProductsByType(CoffeeShop& shop, const type_info& productType)
{
	int choice;
	const vector<Product*> products = shop.getProducts();
 
	int index = 0;
	vector<Product*>::const_iterator itr = products.begin();
	vector<Product*>::const_iterator itrEnd = products.end();
	for (int i=0; itr != itrEnd; ++itr , i++)
		if (typeid(**itr) == productType)
		{
			cout << i + 1 << ". " << **itr;
			index++;
		}
	if (index == 0)
	{
		cout << "Cannot Make CookieCoffee - there is no " << productType.name() << endl;
		return nullptr;
	}
	int size = (int)shop.getProducts().size();
	while(!(cin >> choice) || choice <= 0 || choice > size||
		typeid(*products[choice - 1]) != productType)
		{
			cleanBuffer();
			cout<<"Ilegal input choice!\ntry again : ";
		}
	return products[choice - 1];
}

void addProductMenu(CoffeeShop& shop)
{
	int choice = -1;

	while (choice)
	{
		// get choice from user
		cout << "Choose product type to add:" << endl;
		cout << "1 - Coffee" << endl;
		cout << "2 - Cookie" << endl;
		cout << "3 - Salad" << endl;
		cout << "4 - CookieCoffee" << endl;
		cout << "0 - Quit" << endl;
		cout << "Your choice: ";

		if (!(cin >> choice))
		{
			choice = -1;
			cleanBuffer();
		}
			
			switch (choice)
			{
			case 1:
				// 1. add coffee product to coffee shop
				addProduct(shop, typeid(Coffee));
				break;
			case 2:
				// 2. add cookie product to coffee shop
				addProduct(shop, typeid(Cookie));
				break;
			case 3:
				// 3. add salad product to coffee shop
				addProduct(shop, typeid(Salad));
				break;
			case 4:
				// 4. add CookieCoffee product to coffee shop
				addCookieCoffee(shop);
				break;
			case 0:
				// exit menu
				return;
			default:
				// show unknown choice msg
				cout << "Invalid choice, try again." << endl;
				break;
			}
	}
}

bool addProduct(CoffeeShop& shop, const type_info& productType)
{
	string name;
	int calories;
	double cost, price;
	int choice;

	cout << "Enter product's name: ";
	cleanBuffer();
	getline(cin, name);

	cout << "Enter product's calories: ";
	if (!(cin >> calories))
	{
		cout << "Ilegal input calories! try again.\n" << endl;
		cleanBuffer();
		return false;
	}

	cout << "Enter product's cost: ";
	if (!(cin >> cost))
	{
		cout << "Ilegal input cost! try again.\n"<<endl;
		cleanBuffer();
		return false;
	}

	cout << "Enter product's price: ";
	if (!(cin >> price))
	{
		cout << "Ilegal input price! try again.\n" << endl;
		cleanBuffer();
		return false;
	}

	if (productType == typeid(Coffee))
		shop.addNewProduct(Coffee(name, calories, cost, price));
	else if (productType == typeid(Salad))
		shop.addNewProduct(Salad(name, calories, cost, price));
	else if (productType == typeid(Cookie))
	{
		cout << "Select cookie flour type index" << endl;

		while (true)
		{
			for (int i = 0; i < (int)Cookie::eFlourType::enumTypeEnd; i++)
				cout << i + 1 << ". " <<sFlourType[i] << endl;

			while(!(cin >> choice))
			{
				cleanBuffer();
				cout<<"Ilegal input choice\ntry again: ";
			}
				
					

			if (choice < 1 || choice > (int)Cookie::eFlourType::enumTypeEnd)
				cout << "Invalid choice" << endl;
			else break;
		}

		shop.addNewProduct(Cookie(name, calories, cost, price, (Cookie::eFlourType)(choice - 1)));
	}

	return true;
}

bool addCookieCoffee(CoffeeShop& shop)
{
	const Product* p1, * p2;
	int tmp;
	double discountPercent;
	char choice;
	
		cout << "Enter product's discount percent:" << endl;
		while(!(cin >> tmp))
		{
			cleanBuffer();
			cout<<"Ilegal input: descount must be double type!\ntry again: ";
		}
		discountPercent = (double)tmp / 100;

		cout << "Choose from existing Cookie product:" << endl;
		p1 = showProductsByType(shop, typeid(Cookie));
		if (p1 == nullptr)
			return false;
		cout << "Choose from existing Coffee product:" << endl;
		p2 = showProductsByType(shop, typeid(Coffee));
		if (p2 == nullptr)
			return false;
		cout << "Would you like to grind the cookie in the coffee? Y/N" << endl;
		if (!(cin >> choice))
			throw exception("Ilegal input choice!\n");
		const Cookie* c1 = dynamic_cast<const Cookie*>(p1);
		const Coffee* c2 = dynamic_cast<const Coffee*>(p2);
		shop.addNewProduct(
			CookieCoffee(*c1, *c2, discountPercent,
			(choice == 'Y' || choice == 'y') ? true : false));

	return true;
}

void addEmployee(CoffeeShop& shop)
{
	string name,phoneNumber;
	double shiftSalary;
	int day, month, year;

	cleanBuffer();
	cout << "Enter employee's name: ";
	getline(cin, name);

	cout << "Enter employee's phone number: ";
	getline(cin, phoneNumber);

	cout << "Enter employee's shift salary: ";
	if (!(cin >> shiftSalary))
	{
		cleanBuffer();
		cout << "Ilegal input salary - must be double type!\n";
		return;
	}

	cout << "Enter employee's hire date details: \n";
	cout << "day: ";
	if (!(cin >> day))
	{
		cleanBuffer();
		cout << "Ilegal input day - must be integer type!\n";
		return;
	}
	cout << "month: ";
	if (!(cin >> month))
	{
		cleanBuffer();
		cout << "Ilegal input month - must be integer type!\n";
		return;
	}
	cout << "year: ";
	if (!(cin >> year))
	{
		cleanBuffer();
		cout << "Ilegal input year - must be integer type!\n";
		return;
	}

	shop.addNewEmployee(Employee(name, phoneNumber, shiftSalary, Date(day, month, year)));
}

void addCustomer(CoffeeShop& shop)
{
	string name, phoneNumber;
	char clubMember;

	cleanBuffer();
	cout << "Enter customer's name: ";
	getline(cin, name);

	cout << "Enter customer's phone number: ";
	getline(cin, phoneNumber);
	
	cout << "Is club member? (y/Y -for yes ,any other char for no): ";
	while (!(cin >> clubMember))
	{
		cleanBuffer();
		cout << "Ilegal input : try again!\n";
	}

	shop.addNewCustomer(Customer(name, phoneNumber, 
		(clubMember=='y' || clubMember == 'Y')? true:false));

}

void makeOrder(CoffeeShop& shop, Shift& shift)
{
	Product* p;
	const Employee* theEmployee;
	const Customer* theCustomer;
	int choice;
	char withMilk;
	int numOfSugar;
	int size = (int)shift.getEmployees().size();
	
	cout << "Enter employee to be incharge of the order" << endl;
	if(size !=0)
		show(shift.getEmployees());
	else
	{
		cout << "Employees list is empty!\n";
		return;
	}
		
	
	while(!(cin >> choice) || choice<1 || choice>size)
	{
		cleanBuffer();
		cout << "Ilegal input choice!\ntry again: ";	
	}

	theEmployee = shift.getEmployees()[choice - 1];
	
	int numCustomers = (int)shop.getCustomers().size();
	
		cout << "Enter customer making the order" << endl;
		if(numCustomers !=0)
			show(shop.getCustomers());
		else
		{
			cout << "Customers list is empty!\n";
			return;
		}
	
	
	while(!(cin >> choice) || choice <0 || choice >numCustomers)
	{
		cleanBuffer();
		cout<<"Ilegal input choice!\ntry again: ";
	}
	theCustomer = shop.getCustomers()[choice - 1];
	// create order
	Order theOrder(*theEmployee, *theCustomer);

	size = (int)shift.getDailyMenu().size();
	cout << "The daily menu items" << endl;
	if(size != 0 )
		show(shift.getDailyMenu());
	else
	{
		cout << "Product list is empty!\n";
		return;
	}
	while (choice != -1)
	{
		cout << "choose items indice you wish to order, -1 to stop" << endl;
		while(!(cin >> choice)|| choice<-1 || choice >size)
		{
			cleanBuffer();
			cout << "Ilegal input choice!\n";
		}

		if (choice != -1)
		{
			p = shift.getDailyMenu()[choice - 1]->clone();
			if (typeid(*p) == typeid(Coffee))
			{
				cout << "With milk? (y/Y -for yes ,any other char for no): ";
				cin >> withMilk;
				cout << "How many sugar spoons? ";
				while (!(cin >> numOfSugar)|| numOfSugar<0 )
				{
					cleanBuffer();
					cout << "Ilegal input try again: ";
				}
				Coffee* temp = dynamic_cast<Coffee*>(p);
				temp->setMilk((withMilk=='y' || withMilk=='Y')? true : false);
				*temp += numOfSugar;
				p = temp;
				
			}
			else if (typeid(*p) == typeid(Salad))
			{
				cout << "Select salad dressing type index" << endl;

				while (true)
				{
					for (int i = 0; i < (int)Salad::eDressingType::enumTypeEnd; i++)
						cout << i + 1 << ". " << sDressingType[i] << endl;

					while(!(cin >> choice))
					{
						cleanBuffer();
						cout<<"Ilegal input choice!\ntry again: ";
					}
					

					if (choice < 1 || choice > (int)Salad::eDressingType::enumTypeEnd)
						cout << "Invalid choice" << endl;
							else break;
				}

				Salad* temp = dynamic_cast<Salad*>(p);
				temp->addDressing(Salad::eDressingType(choice - 1));

				p = temp;
			}
			else if (typeid(*p) == typeid(CookieCoffee))
			{
				cout << "With milk? (y/Y -for yes ,any other char for no): ";
				cin >> withMilk;
				cout << "How many sugar spoons? ";
				while (!(cin >> numOfSugar) || numOfSugar < 0)
				{
					cleanBuffer();
					cout << "Ilegal input try again: ";
				}
				CookieCoffee* temp = dynamic_cast<CookieCoffee*>(p);
				temp->setMilk((withMilk == 'y' || withMilk == 'Y') ? true : false);
				*temp += numOfSugar;
				p = temp;
			}
			else {} // its a cookie

			theOrder.addItem(*p);
			
		}
	}

	shift.addOrder(theOrder);
}

void addEmployeesToShift(CoffeeShop& shop, Shift& shift)
{
	int choice = 1;

	// show all Employees in the coffeeshop
	if((int)shop.getEmployees().size() !=0)
		show(shop.getEmployees());
	else
	{
		cout << "Employees list is empty!\n";
		return;
	}

	// choose employees to add
	while (choice != -1)
	{
		try
		{
			cout << "choose employee indice you wish to add, -1 to stop" << endl;
			while (!(cin >> choice))
			{
				cleanBuffer();
				cout<<"Ilegal input choice!\ntry again:";
			}
		

			if (choice<-1 || choice > shop.getEmployees().size()) {
				cout << "Invalid employee index" << endl;
				continue;
			}

			if (choice != -1)
			{
				if (shift.addEmployeeToShift(*shop.getEmployees()[choice - 1]))
				{
					cout << shop.getEmployees()[choice - 1]->getName() << " added to shift! " << endl;
				}
				else
				{
					cout << "Employee already exists in shift!" << endl;
				}
			}
		}
		catch (char* msg)
		{
			cout << msg << " , try again!" << endl;
		}
	}
	
}

void addProductToDailyMenu(CoffeeShop& shop, Shift& shift)
{
	int choice = 1;

	// show all products in the coffeeshop
	int numOfProducts = (int)shop.getProducts().size();
	if(numOfProducts!=0)
		show(shop.getProducts());
	else
	{
	cout << "Products list is empty!\n";
	return;
	}

	// choose products to add
	while (choice != -1)
	{
		try
		{
			cout << "choose product indice you wish to add, -1 to stop" << endl;
			while (!(cin >> choice))
			{
				cleanBuffer();
				cout << "Ilegal input choice!\ntry again:";
			}

			if (choice<-1 || choice > numOfProducts) {
				cout << "Invalid product index" << endl;
				continue;
			}

			if (choice != -1)
			{
				if (shift.addProductToMenu(*shop.getProducts()[choice - 1]))
				{
					cout << shop.getProducts()[choice - 1]->getName() << " added to daily menu! " << endl;
				}
				else
				{
					cout << "Product already exists in daily menu!" << endl;
				}
			}
		}
		catch (char* msg)
		{
			cout << msg << "try again!" << endl;
		}
		
	}
}

void removeShiftByDate(CoffeeShop& shop)
{

	int day, month, year;
	cout << "Enter Date details: " << endl;
	cout << "day: ";
	if (!(cin >> day))
		cleanBuffer();

	cout << "month: ";
	if (!(cin >> month))
		cleanBuffer();

	cout << "year: ";
	if (!(cin >> year))
		cleanBuffer();

	Date date(day, month, year);
	const Node<Shift*>* ptr = shop.getShifts().getHead();
	while (ptr != NULL)
	{

		if (date == *ptr->getData()->getShiftDate())
		{
			shop.getShifts().remove(ptr->getData());
			cout << "Shift Removed!\n";
			return;
		}
		ptr = ptr->getNext();
	}
	cout << "Shist Not Exsist!\n";

}


void cleanBuffer()
{
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

