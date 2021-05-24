#include<iostream>
#include<unordered_map>
#include<string>

////////////////////////////////////////////////////////////////////////////////////
/// IngredientContainer class																
/// containerCapacity: It is list of containers for diff ingredients and 
/// their capacity (max ingredient that it can hold)
/// currentQuantitity: Ingredient container current quantity
/// isLowIndicators: indiactors to show if any container is running low of ingredients
/// (true means low)
////////////////////////////////////////////////////////////////////////////////////

class IngredientContainer
{
	std::unordered_map<std::string, int> containerCapacity;
	std::unordered_map<std::string, int> currentQuantitity;
	std::unordered_map<std::string, bool> isLowIndicators;

public:
	IngredientContainer();
	IngredientContainer(std::unordered_map<std::string, int>containerCapacity);
	int getCapacity(std::string ingred);
	int getCurrentQuantity(std::string ingred);
	void setCurrentQuantity(std::string ingredient, int quantity);
	bool isLow(std::string ingred);
	void setIndicator(std::string ingredient);
	bool hasIngredient(std::string ingredient);
};

