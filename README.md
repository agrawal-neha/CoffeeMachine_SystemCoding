# CoffeeMachine
Implement a coffee machine that serves beverages. The machine has 'n' number of outlets (n>0) and can serve beverages in parallel. 
A beverage will be prepared based on some ingredients.
Assumption: Time taken to prepare any beverage is same

# Scenarios that are considered/handled
1. A beverage is requested and can be prepared as the container has enough ingredients present
2. A Beverage is requested and can be prepared. The container is having less ingredient, but we have enough present in our inventory.
   So, we'll first refill the coffee machine container and then prepare the beverage.
3. A beverage is requested, but cannot be prepared because some of the ingredients are not suffient
4. A beverage is requested, but cannot be prepared because some of the ingredients are not available
5. A beverage is requested, but cannot be prepared because some of the ingredients are not suffient and some of the ingredients are not available
6. A beverage is requested, but cannot be prepared because the quantity of ingredient required is more than size of the coffee machine ingredient container that it can hold.


# Future work
1. Can read beverage requests and serve beverages in parrallel. Currently, it starts serving after it's completed reading the input file.
2. Handling negative test cases e.g. input with negative quantity. Currently, we are assuming that input is sanitized
3. We can add unit to the quantity and manipulate them. 
   e.g. Inventory can keep sugar in kg, but user can provide in gms while requesting a coffee
4. We can keep some default options of beverages and have their classes implemented. If the user does not provide ingredient details, will get regular coffee, 
   also can customise his/her coffee by providing ingredients details.


# How to run the application

