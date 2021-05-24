#include "Beverage.h"
#include<string>
#include<unordered_map>
#include<iostream>
using namespace std;

Beverage::Beverage(std::string name, unordered_map<string, int> ingreds)
{
	beverage = name;
	auto i = ingreds.begin();
	while (i!=ingreds.end()) {
		this->ingredients[i->first] =  i->second;
		i++;
	}
}
//void Beverage::setBeverageName(std::string name) {
//	beverage = name;
//}
//
//void Beverage::setBeverageIngredients(std::vector<Ingredient> ingreds) {
//	//ingredients = ingreds;
//}
//
std::string Beverage::getBeverageName() {
	return beverage;
}
 
// 
unordered_map<std::string, int> Beverage::getIngredients() {
	return this->ingredients;
}
