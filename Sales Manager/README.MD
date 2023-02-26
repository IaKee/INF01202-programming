# Program Description

This program is a sales manager that allows the user to input sales data for a set number of products and stores. The program then prompts the user to enter a product code and calculates the total number of sales for that product across all stores.

The program starts by prompting the user to enter the codes for each product. Then, for each store, the program prompts the user to enter the quantity of each product sold. The program uses a 2D array to store the sales data, with one dimension representing the stores and the other representing the products.

The user can then input a product code, and the program will calculate the total number of sales for that product across all stores by iterating through the 2D array and summing the quantities sold for that product. If the input product code is invalid or has no sales, the program prints an error message and prompts the user to enter a valid product code.

Once the user has queried all desired product codes, the program terminates with a message requesting the user to restart the program if they wish to make further queries.