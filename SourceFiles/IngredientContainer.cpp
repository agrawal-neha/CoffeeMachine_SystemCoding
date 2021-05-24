#include "IngredientContainer.h"
IngredientContainer::IngredientContainer() {

}
IngredientContainer::IngredientContainer(std::unordered_map<std::string, int>containerCapacity) {
	this->containerCapacity = containerCapacity;
	/*auto itr = containerCapacity.begin();
	while (itr!= containerCapacity.end()) {
		currentQuantitity[itr->first] = (itr->second);
		if (itr->second > 0) {
			isLowIndicators[itr->first] = false;
		}
		else
		{
			isLowIndicators[itr->first] = true;
		}
		itr++;
	}*/

	auto itr = containerCapacity.begin();
	while (itr!= containerCapacity.end()) {
		currentQuantitity[itr->first] = 0;
		isLowIndicators[itr->first] = true;
		itr++;
	}
	
}

int IngredientContainer::getCapacity(std::string ingredient) {
	if (containerCapacity.find(ingredient) != containerCapacity.end()) {
		return containerCapacity[ingredient];
	}
	return 0;
}
int IngredientContainer::getCurrentQuantity(std::string ingredient) {
	if (currentQuantitity.find(ingredient) != currentQuantitity.end()) {
		return currentQuantitity[ingredient];
	}
	return 0;
}
void IngredientContainer::setCurrentQuantity(std::string ingredient, int quantity) {
	currentQuantitity[ingredient] = quantity;
}

bool IngredientContainer::isLow(std::string ingredient) {
	if (isLowIndicators.find(ingredient) != isLowIndicators.end()) {
		return isLowIndicators[ingredient];
	}
	return 0;
}

void IngredientContainer::setIndicator(std::string ingredient) {
	if (isLowIndicators.find(ingredient) != isLowIndicators.end()) {
		
		int currQuantity = getCurrentQuantity(ingredient);
			 if(currQuantity==0){
				 isLowIndicators[ingredient] = true;
		}
			 else {
				 isLowIndicators[ingredient] = false;
			 }
	}

}

bool IngredientContainer::hasIngredient(std::string ingredient) {
	if (currentQuantitity.find(ingredient) != currentQuantitity.end()) {
		return true;
	}
	return false;
}