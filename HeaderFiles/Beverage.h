#include<vector>
#include<iostream>
#include<unordered_map>
using namespace std;

/// Class for requested beverage details 
/// beverage: name of the beverage e.g. "Coffee"/"Tea"
/// ingredients: a list of ingredients required to prepare the beverage
//Ingredients will be shown as name and the quantity required


class Beverage
{
	std::string beverage;
	unordered_map<std::string, int> ingredients;
public:
	Beverage(std::string name, unordered_map<string, int> ingreds);
	std::string getBeverageName();
	////std::vector<Ingredient> getBeverageIngredients();
	//void setBeverageName(std::string name);
	unordered_map<std::string, int> getIngredients();
};

