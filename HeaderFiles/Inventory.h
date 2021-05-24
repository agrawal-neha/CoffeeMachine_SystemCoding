#pragma once
#include<unordered_map>
#include<string>

////////////////////////////////////////////////////////////////////////////////////
/// Inventory class																
/// ingredients: the available ingredients and their quantity
////////////////////////////////////////////////////////////////////////////////////
class Inventory
{
	std::unordered_map<std::string, int> ingredients;
public:
	Inventory();
	Inventory(std::unordered_map<std::string, int> ingredients);
	int getQuantity(std::string ingredient);
	void setQuantity(std::string ingred, int quantity);
};

