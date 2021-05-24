//// Main.cpp: This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<map>
#include<unordered_map>
#include<string>
#include<queue>
#include<thread>
#include<mutex>

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/FileReadStream.h"
using namespace rapidjson;

#include"CoffeeMachine.h"
#include"Inventory.h"
using namespace std;

std::mutex beverageQueue;

struct ThreadArgument {
    CoffeeMachine* coffeeMachine;
    queue<Beverage>* beverageRequests;

};

void prepareBeverage(struct ThreadArgument thArgs)
{
    CoffeeMachine* cm = thArgs.coffeeMachine;
    queue<Beverage>* requests = thArgs.beverageRequests;
    while (1) {
        beverageQueue.lock();
        if (requests->empty()) {
            beverageQueue.unlock();
            return;
        }
        Beverage b = requests->front();
        requests->pop();
        beverageQueue.unlock();
        cm->prepareBeverage(b);
    }
}

void run_custom_test_cases() {
    ///Inventory
     /*
    "inventory": {
      "hot_water": 500,
      "hot_milk": 500,
      "ginger_syrup": 100,
      "sugar_syrup": 100,
      "tea_leaves_syrup": 100
    }
    */
    unordered_map<string, int> inventory;
    string ingredient;
    int quantity;
    int choice;
    // Assuming that user will enter quantity >=0, negative testing can be done as future scope
    // Unit can be added in future
    cout << "\n##############################################################################";
    cout << "\nInventory details: ";
    cout << "\n-------------------------------";

    while (1) {
        cout << "\n Enter ingredient and its quantity: ";
        cin >> ingredient >> quantity;
        inventory[ingredient] = quantity;
        cout << "\nMore ingredients? (0/1): ";
        cin >> choice;
        if (!choice)
            break;
    }
    // Coffee Machine
   /* "machine": {
        "outlets": {
            "count_n": 3
        }*/
    int n;
    cout << "\n##############################################################################";
    cout << "\nMachine details";
    cout << "\n-------------------------------";
    cout << "\nEnter number of outlets in the machine: ";
    cin >> n;
    while (n <= 0) {
        cout << "\nInvalid input!";
        cout << "\nEnter again: ";
        cin >> n;
    }
    // Assuming that container total quantity inputted by user is not a negative number
    // Unit can be added in future
    /*
    "container_max_capacity": {
      "hot_water": 500,
      "hot_milk": 500,
      "ginger_syrup": 100,
      "sugar_syrup": 100,
      "tea_leaves_syrup": 100
    }
    */
    unordered_map<string, int> containerCapacity;
    //assuming that user will enter quantity >=0, negative testing can be done as future scope
    cout << "\n##############################################################################";
    cout << "\nCoffee Machine container details: ";
    cout << "\n-------------------------------";

    while (1) {
        cout << "\n Enter ingredient and its capacity: ";
        cin >> ingredient >> quantity;
        containerCapacity[ingredient] = quantity;
        cout << "\nMore ingredients? (0/1): ";
        cin >> choice;
        if (!choice)
            break;
    }

    CoffeeMachine coffeeMachine(n, containerCapacity, inventory);

    //Beverages
    std::string beverage;
    cout << "\n##############################################################################";
    cout << "\nProvide the beverage details: ";
    cout << "\n-------------------------------";

    while (1) {

        cout << "\n================================";
        cout << "\n Enter name of beverage: ";


        cin >> beverage;
        unordered_map<string, int> beverageIngredients;
        while (1) {
            cout << "\n Enter ingredient and its capacity: ";
            cin >> ingredient >> quantity;
            beverageIngredients[ingredient] = quantity;
            cout << "\nMore ingredients? (0/1): ";
            cin >> choice;
            if (!choice)
                break;
        }
        Beverage b(beverage, beverageIngredients);
        coffeeMachine.prepareBeverage(b);
        cout << "\nMore beverages? (0/1): ";
        cin >> choice;
        if (!choice)
            break;

    }
}


void run_in_built_test_cases() {
    // Read input from JSON file
    Document d;
    FILE* fp;
    fopen_s(&fp, "output2.json", "r");
    char buf[0XFFFF];

    rapidjson::FileReadStream input(fp, buf, sizeof(buf));
    rapidjson::Document document;
    document.ParseStream(input);
    fclose(fp);

    int outlets, quantity;
    string ingredient, beverage;
    unordered_map<string, int> inventory;
    unordered_map<string, int> containerCapacity;
    unordered_map<string, int> beverageIngredients;
    queue<Beverage> beverageRequests;

    if (document.HasMember("machine")) {
        const Value& coffeeMachine = document["machine"];

        //fetch outlets
        if (coffeeMachine.HasMember("outlets")) {
            outlets = coffeeMachine["outlets"].GetInt();
            cout << "\nOutlets: " << outlets;
        }

        //fetch containerCapacity
        if (coffeeMachine.HasMember("container_capacity")) {
            const Value& containerMaxCapacity = coffeeMachine["container_capacity"];
            for (Value::ConstMemberIterator iter = containerMaxCapacity.MemberBegin();
                iter != containerMaxCapacity.MemberEnd(); ++iter)
            {
                ingredient = iter->name.GetString();
                quantity = iter->value.GetInt();
                containerCapacity[ingredient] = quantity;
                cout << endl << ingredient << "\t" << quantity;
            }
        }
    }

    // Fetch inventory details
    if (document.HasMember("inventory")) {
        const Value& inventoryDetails = document["inventory"];
        for (Value::ConstMemberIterator iter = inventoryDetails.MemberBegin();
            iter != inventoryDetails.MemberEnd(); ++iter)
        {
            ingredient = iter->name.GetString();
            quantity = iter->value.GetInt();
            inventory[ingredient] = quantity;
            cout << ingredient << "\t" << quantity;
        }
    }

    // Instantiate coffee machine with the details provided by user
    CoffeeMachine coffeeMachine(outlets, containerCapacity, inventory);

    // Fetch beverages
    if (document.HasMember("beverages")) {
        const Value& beverageDetails = document["beverages"];
        for (Value::ConstMemberIterator iter = beverageDetails.MemberBegin();
            iter != beverageDetails.MemberEnd(); ++iter)
        {
            beverage = iter->name.GetString();
            cout << "\n" << beverage;
            const Value& beverageIngredientDetails = beverageDetails[iter->name];
            // Fetch ingredient details for this beverage
            for (Value::ConstMemberIterator ingredIter = beverageIngredientDetails.MemberBegin();
                ingredIter != beverageIngredientDetails.MemberEnd(); ++ingredIter)
            {
                ingredient = ingredIter->name.GetString();
                quantity = ingredIter->value.GetInt();
                beverageIngredients[ingredient] = quantity;
                cout << endl << ingredient << "\n" << quantity;
            }

            Beverage b(beverage, beverageIngredients);

            // Add beverage to the beverage requests queue 
            beverageRequests.push(b);
        }
    }
    cout << "\n##############################################################################";
    ThreadArgument thArgs;
    thArgs.coffeeMachine = &coffeeMachine;
    thArgs.beverageRequests = &(beverageRequests);
    cout << "\n \n";
    std::vector<std::thread> t(outlets);

    // Beverages can be served in parallel using different outlets
    // creating same number of threads as outlets
    for (int i = 0; i < outlets; i++) {
        t[i] = std::thread{ prepareBeverage, thArgs };
    }
    for (int i = 0; i < outlets; i++) {
        t[i].join();
    }
}

int main()
{
    std::cout << "\nWelcome to coffee machine :)";
    int user_choice;
    while (1) {
        std::cout << "\n################################################################################";
        std::cout << "\n\nDo you want to proceed with your custom test cases or inbuilt one";
        std::cout << "\n Press 1 for interactive one";
        std::cout << "\n Press 2 for inbuilt test cases as a JSON file input";
        std::cout << "\n Press 3 to exit\nInput: ";
        std::cin >> user_choice;
        if (user_choice == 3)
            break;
        switch (user_choice) {
        case 1:
            run_custom_test_cases();
            break;
        case 2:
            run_in_built_test_cases();
            break;
        default:
            std::cout << "Unexpected input, please try again";
        }
    }
    std::cout << "\nThank you. Have a nice day!";
}
