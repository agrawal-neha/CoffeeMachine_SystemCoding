# CoffeeMachine
Implement a coffee machine that serves beverages. The machine has 'n' number of outlets (n>0) and can serve beverages in parallel. 
A beverage will be prepared based on some ingredients.
Assumption: Time taken to prepare any beverage is same

# Implementation:
using C++

# Approach
First of all inventory is updated with all the ingredients and their quantity.
Then coffee machine is configured with the given input i.e number of outlets and its ingredient container. 
All the containers are filled to make it ready to use by taking out ingredients from inventory. 
At this point of time, we are ready to serve beverages. For any request, we perform following steps:
1. We check the ingredient requirements in terms of what is needed and how much is needed to prepare a beverage.
2. If we don't have any container in our coffee machine for any of the ingredients for beverage , we mark those ingredients as unavailable.
3. If required quantity of any of the ingredients is more than what we have in total (i.e. in our inventory and in the coffee container), we mark those ingredients as
   insufficient.
4. There can be a case that we have in total equals or more than required ingredient, but our ingredient container's size is smaller than required, we mark this as container
   is too small to hold the required quantity
6. If container can hold the required quantity, but it does not have enough quantity, but we can take out from inventory. In this case, we refill the container first.
7. If all the ingredients are sufficient, we prepare the coffee. Once the coffee is under preparation, we update the container quantity. Also, if the container quantity goes
   below 20%, we refill the container so that next beverage request is served in a better way. The indicators keeps on updating whenver there is a change in quantity of
   containers.

## Performance:
To serve the beverages in parallel, we are adding all the beverages in a common queue and creating as number of threads as outlets. 
Each thread will be taking the first request present in the queue and serve that request until the queue is empty. 
Mutex is used to ensure that no two threads take same request. Also, while preparing beverages, mutex is used to ensure that the common resources are always consistent. 
Only one thread will have access to inventory and container resources at a time to avoid the race condition.

Below are the classes and their APIs:
1. CoffeeMachine: 
   - number of outlets
   - inventory details
   - container in coffee machine for each ingredient that coffee machine supports
   APIs:
        - to fill all the ingredient container
        - to refill any given ingredient container
        - prepareBeverage
2. Inventory: 
   -ingredients and their quantity available in inventory
   APIs:
        - to get the quantity of any ingredient present in inventory
        - to update quantity of any ingredient in the inventory
3. IngredientContainer (a part of coffee machine)
   - max capacity of the ingredient containers
   - current quantity present in ingredient containers
   - indicators for each container which is ON when it is running low (Currently, set to 0, can be set to say <=10%)
   APIs:
        - to get capacity of the container for any ingredient
        - to get current quantity of the container for any ingredient
        - to update the current quantity of the container for any ingredient
        - to check if the indicator of an ingredient is low
        - to check if we have a container for a particular ingredient available or not
4. Beverage: 
   - name of the beverage
   - ingredients (name and quantity )
   APIs:
        - to get beverage name
        - to get beverage details
   

# Scenarios that are considered/handled
1. A beverage is requested and can be prepared as the container has enough ingredients present
2. A Beverage is requested and can be prepared. The container is having less ingredient, but we have enough present in our inventory.
   So, we'll first refill the coffee machine container and then prepare the beverage.
3. A beverage is requested, but cannot be prepared because some of the ingredients are not suffient
4. A beverage is requested, but cannot be prepared because some of the ingredients are not available
5. A beverage is requested, but cannot be prepared because some of the ingredients are not suffient and some of the ingredients are not available
6. A beverage is requested, but cannot be prepared because the quantity of ingredient required is more than 
   size of the coffee machine ingredient container that it can hold.

# Future work
1. Can read beverage requests and serve beverages in parrallel. Currently, it starts serving after it's completed reading the input file.
2. Handling negative test cases e.g. input with negative quantity. Currently, we are assuming that input is sanitized
3. We can add unit to the quantity and manipulate them. 
   e.g. Inventory can keep sugar in kg, but user can provide in gms while requesting a coffee
4. We can keep some default options of beverages and have their classes implemented. If the user does not provide ingredient details, will get regular coffee, 
   also can customise his/her coffee by providing ingredients details.
5. We can show outlet number with the beverages that are being served. 
   e.g.  ***Outlet 1**: Tea is prepared!
        **Outlet 2**: Coffee is prepared!


# How to run the application

