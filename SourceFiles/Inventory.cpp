#include "Inventory.h"
#include<iostream>

// 'ctr
Inventory::Inventory() {}
Inventory::Inventory(std::unordered_map<std::string, int> ingredients) {
	this->ingredients = ingredients;
	std::cout << "\Inventory updated!";
}

// Fetch the quantity of ingredient available in inventory
int Inventory::getQuantity(std::string ingredient) {
	if (ingredients.find(ingredient) != ingredients.end()) {
		return ingredients[ingredient];
	}
	return 0;
}

// Update inventory after taking some ingredients out of it
void Inventory::setQuantity(std::string ingredient, int quantity) {
	if (ingredients.find(ingredient) != ingredients.end()) {
		ingredients[ingredient] = quantity;
	}
}
