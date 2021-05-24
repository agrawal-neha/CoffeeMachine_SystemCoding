#pragma once
#include"IngredientContainer.h"
#include "Inventory.h"
#include "Beverage.h"
//////////////////////////////////////////////////////////////////////////////
/// CoffeeMachine class
/// outlets: number of outlets to serve beverages in parallel
/// ingred_container: ingredient container which will contain the ingredients. 
/// is_low_indicator: To show if any ingredient level is running low
///////////////////////////////////////////////////////////////////////
/// This is the class the user will be interacting with for their beverage requests
/// This will serve user with their beverages or indicate if some ingredient is 
/// insufficient or unavailble to prepare the requested beverage.
/// ///////////////////////////////////////////////////////////////////////////////

class CoffeeMachine
{
	 int outlets;
	IngredientContainer ingred_container;
	Inventory inventory;
	//std::map<std::string, bool> is_low_indicator;
	
public:
	//CoffeeMachine(unsigned int outlets);
	CoffeeMachine( int outlets, std::unordered_map<std::string, int>containerCapacity, std::unordered_map<std::string, int> inv);
	CoffeeMachine(const CoffeeMachine& cm);
	CoffeeMachine();
	//container and inventory related
	void fillContainer(std::unordered_map<std::string, int> inv);
	void refillContainer(std::string ingred);
	void prepareBeverage(Beverage bev);

};

