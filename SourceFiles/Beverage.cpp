#include "Beverage.h"
#include<string>
#include<unordered_map>
#include<iostream>
using namespace std;

// Constructor to instantiate Beverage when name and ingredient details are provided
Beverage::Beverage(std::string name, unordered_map<string, int> ingreds)
{
	beverage = name;
	auto i = ingreds.begin();
	while (i != ingreds.end()) {
		this->ingredients[i->first] = i->second;
		i++;
	}
}

// Method to get beverage name
std::string Beverage::getBeverageName() {
	return beverage;
}

// Method to get ingredient details
unordered_map<std::string, int> Beverage::getIngredients() {
	return this->ingredients;
}
