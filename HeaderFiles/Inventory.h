#pragma once
#include<unordered_map>
#include<string>
class Inventory
{
	std::unordered_map<std::string, int> ingredients;
public:
	Inventory();
	Inventory(std::unordered_map<std::string, int> ingredients);
	int getQuantity(std::string ingredient);
	void setQuantity(std::string ingred, int quantity);
	bool isSufficient(std::string ingredient);
	bool isAvaialable(std::string ingredient);
};

