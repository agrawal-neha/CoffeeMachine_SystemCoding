#include "CoffeeMachine.h"
#include<string>
#include<mutex>
#include<thread>

std::mutex ingredientMutex;

// Default constructor
CoffeeMachine::CoffeeMachine() {
	//default 'ctr
}

// Copy constructor
CoffeeMachine::CoffeeMachine(const CoffeeMachine& cm) {
	outlets = cm.outlets;
	ingred_container = cm.ingred_container;
	inventory = cm.inventory;
}

// Constructor for coffee machine
CoffeeMachine::CoffeeMachine(int outlets, std::unordered_map<std::string, int>containerCapacity,
	std::unordered_map<std::string, int> inv) :
	outlets(outlets), ingred_container(containerCapacity), inventory(inv)
{
	// This will fill the coffee machine ingredient container for the first time
	// Also, will update the inventory based on what quantity is filled into container
	fillContainer(inv);
	std::cout << "\nCoffee Machine attributes updated!";
}

// This is called only once when the coffee machine is instantiated to update the coffee
// machine container and inventory. This uses refillContainer method internally to fill each ingredient
// in the container.
void CoffeeMachine::fillContainer(std::unordered_map<std::string, int> inv) {
	auto itr = inv.begin();
	while (itr != inv.end()) {
		std::string ingredient = itr->first;
		refillContainer(ingredient);
		itr++;
	}
}

// Refills container and set the indicator
void CoffeeMachine::refillContainer(std::string ingred) {
	string buffer = "\n";
	int invQuantity = inventory.getQuantity(ingred);
	int containerMaxCapacity = ingred_container.getCapacity(ingred);
	int currentQuantity = ingred_container.getCurrentQuantity(ingred);
	int gap = containerMaxCapacity - currentQuantity;

	if (gap <= invQuantity) {
		ingred_container.setCurrentQuantity(ingred, containerMaxCapacity);
		inventory.setQuantity(ingred, invQuantity - gap);
	}
	else {
		ingred_container.setCurrentQuantity(ingred, currentQuantity + invQuantity);
		inventory.setQuantity(ingred, 0);
	}
	ingred_container.setIndicator(ingred);
	buffer.append(ingred + " container is (re)filled!");
	cout << buffer;
}


// Method to serve beverage requests.
// Multiple threads will access this method in parallel, mutex is used
// to handle race condition for the common resources.
void CoffeeMachine::prepareBeverage(Beverage bev) {
	
	bool insufficient = false, unavailable = false;
	vector<string> unavailIngreds;
	vector<string> insuffIngreds;
	unordered_map<std::string, int> ingreds = bev.getIngredients();
	string ingred;
	int quantity;
	string beverageName = bev.getBeverageName();
	string buffer = "\n";
	std::thread::id id = std::this_thread::get_id();
	//cout <<endl<< id;
	
	ingredientMutex.lock();
	auto itr = ingreds.begin();
	

	// Iterate through the ingredients that are required to prepare beverage
	while (itr != ingreds.end()) {
		ingred = itr->first;
		quantity = itr->second;

		// Check if the ingredient is available, if yes, check if it is sufficient
		if (ingred_container.hasIngredient(ingred)) {
			int containerCurrentQuantity = ingred_container.getCurrentQuantity(ingred);
			int inventoryCurrentQuantity = inventory.getQuantity(ingred);
			int totalAvailable = containerCurrentQuantity + inventoryCurrentQuantity;
			int maxCapacity = ingred_container.getCapacity(ingred);
			if (quantity > totalAvailable)
			{
				insuffIngreds.push_back(ingred);
				// Set insufficient flag is any ingredient is not sufficient
				insufficient = true;
			}
			// Check if the container can hold the quantity of ingredient that is requested for a beverage
			else if (quantity > maxCapacity)
			{
				buffer.append(beverageName + " cannot be prepared bacause container in coffee Machine is too small to hold the required ingredients");
				//cout << endl << beverageName << " cannot be prepared bacause ";
				//cout << "container in coffee Machine is too small to hold the required ingredients";
				ingredientMutex.unlock();
				cout << buffer;
				return;

			}
			// Refill the conatiner if the ingredient is sufficient, but need to take from inventory
			else if (quantity > containerCurrentQuantity) {
				refillContainer(ingred);
			}
			else
				;

		}
		// Set unavailable flag is the ingredient is not available
		else {
			unavailable = true;
			unavailIngreds.push_back(ingred);

		}
		itr++;
	}

	// Leave the lock if the ingredients are insufficient/ unavailable as no write is required 
	if (insufficient || unavailable)
		ingredientMutex.unlock();


	if (insufficient) {
		buffer.append(beverageName + " cannot be prepared bacause ");
		for (auto i = insuffIngreds.begin(); i != insuffIngreds.end(); i++)
			buffer.append(*i + ", ");
		buffer.append("is/are not sufficient.");
		if (unavailable) {
			buffer.append(" Also, ");
			for (auto i = unavailIngreds.begin(); i != unavailIngreds.end(); i++) {
				buffer.append(*i + ", ");
			}
			buffer.append("is/are not available");
		}
		cout << buffer;
		return;
	}
	else if (unavailable) {
		buffer.append(beverageName + " cannot be prepared bacause ");
		for (auto i = unavailIngreds.begin(); i != unavailIngreds.end(); i++) {
			buffer.append(*i + ", ");
		}
		buffer.append("is/are not available");
		cout << buffer;
		return;
	}
	else {
		// Prepare the beverage, write is required in this case (keep lock with it)
		buffer.append(beverageName + " is prepared!");
		cout << buffer;
	}
	// Update container and refill if the level goes below 20%
	itr = ingreds.begin();
	while (itr != ingreds.end()) {
		ingred = itr->first;
		quantity = itr->second;
		int currentQuantity = ingred_container.getCurrentQuantity(ingred);
		int maxCapacity = ingred_container.getCapacity(ingred);
		int remaining = currentQuantity - quantity;
		int inventoryCurrentQuantity = inventory.getQuantity(ingred);
		ingred_container.setCurrentQuantity(ingred, remaining);
		if (inventoryCurrentQuantity > 0 && remaining < (0.2 * maxCapacity)) {
			refillContainer(ingred);
		}
		itr++;
	}
	// Write is done, leave the lock
	ingredientMutex.unlock();
	return;
}
