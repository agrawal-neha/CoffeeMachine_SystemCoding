#include "IngredientContainer.h"

// Default constructor
IngredientContainer::IngredientContainer() {
	// ctr
}

// Constructor to instantiate IngredientContainer
IngredientContainer::IngredientContainer(std::unordered_map<std::string, int>containerCapacity) {
	this->containerCapacity = containerCapacity;
	auto itr = containerCapacity.begin();
	while (itr != containerCapacity.end()) {
		currentQuantitity[itr->first] = 0;
		isLowIndicators[itr->first] = true;
		itr++;
	}

}

// Method to fetch capacity
int IngredientContainer::getCapacity(std::string ingredient) {
	if (containerCapacity.find(ingredient) != containerCapacity.end()) {
		return containerCapacity[ingredient];
	}
	return 0;
}

// Method to fetch current quantity of the container for given ingredient
int IngredientContainer::getCurrentQuantity(std::string ingredient) {
	if (currentQuantitity.find(ingredient) != currentQuantitity.end()) {
		return currentQuantitity[ingredient];
	}
	return 0;
}


// Method to set current quantity of the container for given ingredient
void IngredientContainer::setCurrentQuantity(std::string ingredient, int quantity) {
	currentQuantitity[ingredient] = quantity;
}


// Method to check if the container is running low of ingredient
bool IngredientContainer::isLow(std::string ingredient) {
	if (isLowIndicators.find(ingredient) != isLowIndicators.end()) {
		return isLowIndicators[ingredient];
	}
	return 0;
}

// Method to set the low indicator if the container is running low of ingredient
void IngredientContainer::setIndicator(std::string ingredient) {
	if (isLowIndicators.find(ingredient) != isLowIndicators.end()) {

		int currQuantity = getCurrentQuantity(ingredient);
		if (currQuantity == 0) {
			isLowIndicators[ingredient] = true;
		}
		else {
			isLowIndicators[ingredient] = false;
		}
	}

}

// Method to check if a container for given ingredient is available
bool IngredientContainer::hasIngredient(std::string ingredient) {
	if (currentQuantitity.find(ingredient) != currentQuantitity.end()) {
		return true;
	}
	return false;
}