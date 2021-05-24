// Main.cpp: This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <json/json.h>
#include <fstream>
#include<map>
#include<unordered_map>
#include<string>
#include<queue>
#include<thread>
#include<mutex>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/FileReadStream.h"
#include "json/json.h"
using namespace rapidjson;

#include"CoffeeMachine.h"
#include"Inventory.h"
//#include"Beverage.h"
using namespace std;

std::mutex beverageQueue;

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
    //assuming that user will enter quantity >=0, negative testing can be done as future scope
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
   // Inventory invent(inventory);

    
    ///Coffee Machine

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
    cout << n;
    while (n <= 0) {
        cout << "\nInvalid input!";
        cout << "\nEnter again: ";
        cin >> n;
    }
    //CoffeeMachine coffeeMachine(n);

    //Assuming that container total quantity inputted by user 
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
    //string ingredient;
    //int quantity;
    //int choice;
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


//void run_in_built_test_cases() {
//    Json::Reader reader;
//    Json::Value root;
//    Json::StyledStreamWriter writer;
//    std::string text = "{ \"first\": \"James\", \"last\": \"Bond\", \"nums\": [0, 0, 7] }";
//    std::ofstream outFile;
//
//    // Parse JSON and print errors if needed
//    if (!reader.parse(text, root)) {
//        std::cout << reader.getFormattedErrorMessages();
//        exit(1);
//    }
//    else {
//
//        // Read and modify the json data
//        std::cout << "Size: " << root.size() << std::endl;
//        std::cout << "Contains nums? " << root.isMember("nums") << std::endl;
//        root["first"] = "Jimmy";
//        root["middle"] = "Danger";
//
//        // Write the output to a file
//        outFile.open("output.json");
//        writer.write(outFile, root);
//        outFile.close();
//    }
//}

struct ThreadArgument {
    CoffeeMachine* coffeeMachine;
    queue<Beverage>* beverageRequests;

};

void prepareBeverage( struct ThreadArgument thArgs)
//void prepareBeverage(CoffeeMachine* cm, queue<Beverage>& requests)
{   
   // cout << "\nHello ";
   
    CoffeeMachine *cm = thArgs.coffeeMachine;
    queue<Beverage>* requests = thArgs.beverageRequests;
    //cout << "\nnewHello ";
   // coffeeMachine.prepareBeverage(bev);
    
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
void run_in_built_test_cases() {
    //Read JSON file
    Json::Value json;
    Document d;
    
    std::map<std::string, int> test_input;
   //std::ifstream json1("Input.json");
    //test_input_file>> root;
    //const char* json1 = "{\"project\":\"rapidjson\",\"stars\":10}";
    //std::cout << json1;
    //d.Parse(json1);
   // Value& s = d["stars"];
   // s.SetInt(s.GetInt() + 1);
   // std::cout<< s.GetInt();

    FILE* fp;
    fopen_s(&fp, "InputData/output2.json", "r"); // stupid windows need rb
    char buf[0XFFFF];

    //FileReadStream(FILE *fp, char *buffer, std::size_t bufferSize)
    rapidjson::FileReadStream input(fp, buf, sizeof(buf));
    rapidjson::Document document;
    document.ParseStream(input);
    //fclose(fp);

    //////////////////////here//////////////////////////

    int outlets, quantity;
    string ingredient, beverage;
    unordered_map<string, int> inventory;
    unordered_map<string, int> containerCapacity;
    unordered_map<string, int> beverageIngredients;
    queue<Beverage> beverageRequests;
    
    
    // = document["machine"]["outlets"].GetInt();
    //std::cout<< document.GetObject();
   

    //Fetch machine details
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
                cout << endl << ingredient<< quantity;
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
            cout <<ingredient<< quantity;
        }
    }

    CoffeeMachine coffeeMachine(outlets, containerCapacity, inventory);

    //Fetch beverages
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
                cout << endl << ingredient << quantity;
            }
            Beverage b(beverage, beverageIngredients);
            beverageRequests.push(b);
            //coffeeMachine.prepareBeverage(b);
        }
    }
    ThreadArgument thArgs;
    thArgs.coffeeMachine = &coffeeMachine;
    thArgs.beverageRequests = &(beverageRequests);
    CoffeeMachine* cm = &(coffeeMachine);
    cout << "\n \n ";
    std::vector<std::thread> t(outlets);
    for (int i = 0; i < outlets; i++) {
           //Beverage bev = beverageRequests.front();
           //beverageRequests.pop();
           //cout << "Here";
           t[i] = std::thread{prepareBeverage, thArgs};
           //t[i] = std::thread{prepareBeverage, cm, beverageRequests};

          
       }
    for (int i = 0; i < outlets; i++) {
        t[i].join();
    }


    /*for (std::vector<thread>::iterator it = t.begin(); it != t.end(); ++it)
    {
        cout << "\nHere";
        t.push_back( helloWorld, bev);
    }*/
   // while (!beverageRequests.empty()) {
   //    
   //     Beverage bev = beverageRequests.front();
   //     beverageRequests.pop();
   //     thread ttt1(helloWorld, coffeeMachine, bev);
   //     ttt1.join();
   //     /*if ((!beverageRequests.empty())) {
   //         Beverage bev = beverageRequests.front();
   //         beverageRequests.pop();
   //         thread ttt2(helloWorld, coffeeMachine, bev);
   //         ttt2.join();
   //     }*/
   //}
    //coffeeMachine.prepareBeverage(b);




    //////////////////////here//////////////////////////
   // std::cout << document["machine"]["outlets"]["count_n"].GetInt();
   // /*
   // std::stringstream ss;
   // std::ifstream file("output1.json");
   // if (file) {
   //     ss << file.rdbuf();
   //     file.close();
   // }
   // else {
   //     throw std::runtime_error("!! Unable to open json file");
   // }
   // Document doc;
   // if (doc.Parse<0>(ss.str().c_str()).HasParseError())
   //     throw std::invalid_argument("json parse error");
   // // Start parsing json string
   // //std::string jsonvals001 = doc["jSONOBJECT"].GetString();
   // //std::cout << jsonvals001;
   // //std::string date = doc["data"].GetString();
   //// const Value& array = doc["file"];
   // for (rapidjson::SizeType i = 0; i < array.Size(); i++) {
   //     m_vReadFilePath.push_back(array[i].GetString());
   // }


   // //std::cout<<d["project"];
   // //Json::CharReader::parse(test_input_file, test_input, root, root);

   // //std::cout<< test_input;
   // */
}

int main()
{   
    std::cout << "\nWelcome to coffee machine :)";
    int user_choice;
    while (1) {
        std::cout << "\n################################################################################";
        std::cout << "\n\nDo you want to proceed with your custom test cases or inbuilt one";
        std::cout << "\n Press 1 for interactive one";
        std::cout << "\n Press 2 for inbuilt test cases as a JSON file input at this location";
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

    //run_in_built_test_cases();
    std::cout << "\nThank you. Have a nice day!";

}
