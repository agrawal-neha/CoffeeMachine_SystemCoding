#include<vector>
#include<iostream>
#include<unordered_map>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////
/// Beverage class																
/// beverage: name of the beverage e.g. "Coffee"/"Tea"
/// ingredients: a list of ingredients (ingredient name and its quantity) 
/// required to prepare the beverage
////////////////////////////////////////////////////////////////////////////////////

class Beverage
{
	std::string beverage;
	unordered_map<std::string, int> ingredients;
public:
	Beverage(std::string name, unordered_map<string, int> ingreds);
	std::string getBeverageName();
	unordered_map<std::string, int> getIngredients();
};

