#include "CoffeeMachine.h"
#include<string>
#include<mutex>
#include<thread>

std::mutex ingredientMutex;
//CoffeeMachine::CoffeeMachine( int outlets)
//{
//	this->outlets = outlets;
//}
CoffeeMachine::CoffeeMachine() {

}
CoffeeMachine::CoffeeMachine(const CoffeeMachine& cm) {
	outlets = cm.outlets;
	ingred_container = cm.ingred_container;
	inventory = cm.inventory;
}

CoffeeMachine::CoffeeMachine( int outlets, std::unordered_map<std::string, int>containerCapacity,
	std::unordered_map<std::string, int> inv):
	outlets(outlets), ingred_container(containerCapacity), inventory(inv)
{
	//this->outlets = outlets;
	//this->ingred_container = ingred_container;
	fillContainer(inv);
	std::cout << "\nCoffee Machine attributes updated!";
}

void CoffeeMachine::fillContainer(std::unordered_map<std::string, int> inv) {
	auto itr = inv.begin();
	while (itr!= inv.end()) {
		std::string ingredient=itr->first; 
		refillContainer(ingredient);
		itr++;
	}
}

//refills container and set the indicator
void CoffeeMachine::refillContainer( std::string ingred ) {
	//refill ingred container only
	string buffer="\n";
	int invQuantity = inventory.getQuantity(ingred);
	int containerMaxCapacity = ingred_container.getCapacity(ingred);
	int currentQuantity= ingred_container.getCurrentQuantity(ingred);
	int gap = containerMaxCapacity - currentQuantity;
	if (gap <=invQuantity) {
		ingred_container.setCurrentQuantity(ingred, containerMaxCapacity);
		//ingred_container.setIndicator(ingred, false);
		inventory.setQuantity(ingred, invQuantity-gap);
	}
	else {
		ingred_container.setCurrentQuantity(ingred, currentQuantity+invQuantity);
		inventory.setQuantity(ingred, 0);
	}
	ingred_container.setIndicator(ingred);
	buffer.append(ingred + " container is (re)filled!");
	cout << buffer;
}

void CoffeeMachine::prepareBeverage(Beverage bev) {
	
	
	//validate
	
	bool insufficient = false, unavailable = false;
	vector<string> unavailIngreds;
	vector<string> insuffIngreds;
	unordered_map<std::string, int> ingreds = bev.getIngredients();
	string ingred;
	int quantity;
	string beverageName = bev.getBeverageName();
	string buffer="\n";
	std::thread::id id = std::this_thread::get_id();
	cout <<endl<< id;
	//buffer.append((string)id);

	ingredientMutex.lock();
	auto itr = ingreds.begin();

	
	while (itr != ingreds.end()) {
		ingred = itr->first;
		quantity = itr->second;
		if (ingred_container.hasIngredient(ingred)) {
			int containerCurrentQuantity = ingred_container.getCurrentQuantity(ingred);
			int inventoryCurrentQuantity = inventory.getQuantity(ingred);
			int totalAvailable = containerCurrentQuantity + inventoryCurrentQuantity;
			int maxCapacity = ingred_container.getCapacity(ingred);
			if (quantity > totalAvailable)
			{
				insuffIngreds.push_back(ingred);
				insufficient = true;
			}
			else if (quantity > maxCapacity)
			{
				buffer.append(beverageName + " cannot be prepared bacause container in coffee Machine is too small to hold the required ingredients");
				//cout << endl << beverageName << " cannot be prepared bacause ";
				//cout << "container in coffee Machine is too small to hold the required ingredients";
				ingredientMutex.unlock();
				cout << buffer;
				return;

			}
			else if (quantity > containerCurrentQuantity) {
				refillContainer(ingred);
			}
			else
				;
			
		}
		else {
			unavailable = true;
			unavailIngreds.push_back(ingred);

		}
		itr++;
	}
	if (insufficient || unavailable)
		ingredientMutex.unlock();
	//not possible (not available/not sufficient/can be prepared)
	if (insufficient) {
		buffer.append(beverageName + " cannot be prepared bacause ");
		//cout << endl<< beverageName << " cannot be prepared bacause ";
		for (auto i = insuffIngreds.begin(); i != insuffIngreds.end(); i++)
			//cout << *i << " ";
			buffer.append(*i + ", ");
		//cout << "is/are not sufficient";
		buffer.append("is/are not sufficient.");
		if (unavailable) {
			//cout << " and ";
			buffer.append(" Also, ");
			for (auto i = unavailIngreds.begin(); i != unavailIngreds.end(); i++) {
				//cout << *i << ", ";
				buffer.append(*i + ", ");
			}
				
			//cout << "is/are not available";
			buffer.append("is/are not available");

		}
		cout << buffer;
		//ingredientMutex.unlock();
		return;
	}
	else if (unavailable) {
		buffer.append(beverageName+ " cannot be prepared bacause ");
		//cout << endl << beverageName << " cannot be prepared bacause ";
		for (auto i = unavailIngreds.begin(); i != unavailIngreds.end(); i++) {
			buffer.append(*i + ", ");
		}
			//cout << *i << " ";
		//cout << "is/are not available\n";
		buffer.append("is/are not available");
		//ingredientMutex.unlock();
		cout <<buffer;
		return;
	}
	else {
		//prepare
		buffer.append(beverageName + " is prepared!");
		//cout << endl << beverageName << " is prepared";
		cout << buffer;
	}
	//update container 
	//refill if required
	itr = ingreds.begin();
	while (itr != ingreds.end()) {
		ingred = itr->first;
		quantity = itr->second;
		int currentQuantity = ingred_container.getCurrentQuantity(ingred);
		int maxCapacity = ingred_container.getCapacity(ingred);
		int remaining = currentQuantity - quantity;
		int inventoryCurrentQuantity = inventory.getQuantity(ingred);
		ingred_container.setCurrentQuantity(ingred, remaining);
		if (inventoryCurrentQuantity>0 && remaining < (0.2 * maxCapacity)) {
			refillContainer(ingred);
		}
		itr++;
	}
	ingredientMutex.unlock();
	return;
}

//void CoffeeMachine::CoffeeMachine()