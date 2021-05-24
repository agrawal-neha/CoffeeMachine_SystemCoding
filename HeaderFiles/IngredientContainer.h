#include<iostream>
#include<unordered_map>
#include<string>

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

