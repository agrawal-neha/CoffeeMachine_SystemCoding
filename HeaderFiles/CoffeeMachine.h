#pragma once
#include"IngredientContainer.h"
#include "Inventory.h"
#include "Beverage.h"

////////////////////////////////////////////////////////////////////////////////////
/// CoffeeMachine class																
/// outlets: number of outlets to serve beverages in parallel
/// ingred_container: ingredient container which will contain the ingredients.
/// inventory: total ingredients available in the inventory 
////////////////////////////////////////////////////////////////////////////////////
/// This is the class the user will be interacting with for their beverage requests
/// This will serve user with their beverages or indicate if some ingredient is 
/// insufficient or unavailble to prepare the requested beverage.
/// ///////////////////////////////////////////////////////////////////////////////

class CoffeeMachine
{
	int outlets;
	IngredientContainer ingred_container;
	Inventory inventory;
public:
	CoffeeMachine();
	CoffeeMachine(int outlets, std::unordered_map<std::string, int>containerCapacity, std::unordered_map<std::string, int> inv);
	CoffeeMachine(const CoffeeMachine& cm);

	void fillContainer(std::unordered_map<std::string, int> inv);
	void refillContainer(std::string ingred);
	void prepareBeverage(Beverage bev);
};

