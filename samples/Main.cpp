#include <iostream>

#include "Polynomial.h"
#include "TablesManager.h"



int main() {
	std::cout << "Commands:" << std::endl;
	std::cout << "1 (Insert polynom in all tables)" << std::endl;
	std::cout << "2 (Remove polynom in all tables)" << std::endl;
	std::cout << "3 (Set active table)" << std::endl;
	std::cout << "4 (Print active table)" << std::endl;
	std::cout << "5 (Search polynom and mult it by number)" << std::endl;
	std::cout << "6 (Search polynom and differentiate it)" << std::endl;
	std::cout << "7 (Search polynom and integrate it)" << std::endl;
	std::cout << "8 (Search polynom and calculate it in point)" << std::endl;
	std::cout << "9 (Exit)" << std::endl;

	size_t command = 0, active = 0;
	double kf;
	char var;
	Polynomial polynom;
	Polynomial* pPolynom;
	std::string strPol, strKey;
	TablesManager<std::string, Polynomial> tablesManager;

	while (command != 9) {
		command = 0;
		while ((command < 1) || (command > 10)) {
			std::cout << std::endl << "Your command: ";
			std::cin >> command;
		}
		std::cout << std::endl;

		if (command == 1) {
			std::cout << "You should enter polynom as follows: 1.0x1y2z3+2.0x2y1z0+-3.0x3y2z1" << std::endl;
			std::cout << "Enter your polynom: ";
			strPol = "";
			std::cin >> strPol;
			std::cout << "Enter key (name) for this polynom: ";
			strKey = "";
			std::cin >> strKey;
			polynom.ParsePolynom(strPol);
			tablesManager.InsertInAll(strKey, polynom);
			continue;
		}
		
		if (command == 2) {
			std::cout << "Enter key (name) of polynom to remove: ";
			strKey = "";
			std::cin >> strKey;
			tablesManager.RemoveInAll(strKey);
			continue;
		}
		
		if (command == 3) {
			std::cout << "Tables: " << std::endl;
			std::cout << "0. Unordered Array Table " << std::endl;
			std::cout << "1. Unordered List Table " << std::endl;
			std::cout << "2. Ordered Array Table " << std::endl;
			std::cout << "3. AVL Tree Table " << std::endl;
			std::cout << "4. Repeated Hash Table " << std::endl;
			std::cout << "5. Chained Hash Table " << std::endl;
			std::cout << "Enter number of table to print: ";
			std::cin >> active;
			tablesManager.ChangeActive(active);
			continue;
		}
		
		if (command == 4) {
			tablesManager.PrintActive();
			continue;
		}
		
		if (command == 5) {
			std::cout << "Enter key (name) of polynom to mult: ";
			strKey = "";
			std::cin >> strKey;
			pPolynom = tablesManager.SearchInActive(strKey);
			std::cout << "Enter double number to mult: ";
			std::cin >> kf;
			*pPolynom = *pPolynom * kf;
			continue;
		}
		
		if (command == 6) {
			std::cout << "Enter key (name) of polynom to differentiate: ";
			strKey = "";
			std::cin >> strKey;
			pPolynom = tablesManager.SearchInActive(strKey);
			std::cout << "Differentiation variable? x, y or z: ";
			std::cin >> var;
			*pPolynom = (*pPolynom).Differentiate(var);
			continue;
		}
		
		if (command == 7) {
			std::cout << "Enter key (name) of polynom to integrate: ";
			strKey = "";
			std::cin >> strKey;
			pPolynom = tablesManager.SearchInActive(strKey);
			std::cout << "Integration variable? x, y or z: ";
			std::cin >> var;
			*pPolynom = (*pPolynom).Integrate(var);
			continue;
		}
		
		if (command == 8) {
			std::cout << "Enter key (name) of polynom to calculate in point: ";
			strKey = "";
			std::cin >> strKey;
			pPolynom = tablesManager.SearchInActive(strKey);
			double x, y, z;
			std::cout << "Enter x double value: ";
			std::cin >> x;
			std::cout << "Enter y double value: ";
			std::cin >> y;
			std::cout << "Enter z double value: ";
			std::cin >> z;
			std::cout << "Result: ";
			std::cout << (*pPolynom).CalculateInPoint(x, y, z);
			continue;
		}
	}
	std::cout << "EXIT";
	return 0;
}
