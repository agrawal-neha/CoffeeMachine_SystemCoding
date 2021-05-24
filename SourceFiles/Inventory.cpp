#include "Inventory.h"
#include<iostream>

Inventory::Inventory(){}
Inventory::Inventory(std::unordered_map<std::string, int> ingredients) {
	this->ingredients = ingredients;
	std::cout << "\Inventory updated!";
}
bool Inventory::isSufficient(std::string ingredient) {
	return true;
}
bool Inventory::isAvaialable(std::string ingredient) {
	return true;
}

int Inventory::getQuantity(std::string ingredient) {
	if (ingredients.find(ingredient) != ingredients.end()) {
		return ingredients[ingredient];
	}
	return 0;
}

void Inventory::setQuantity(std::string ingredient, int quantity) {
	if (ingredients.find(ingredient) != ingredients.end()) {
		ingredients[ingredient] = quantity;
	}
}
//bool getInventory