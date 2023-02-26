# Program Description

This program calculates the distance between a user-defined point of interest and three other points, and outputs the smallest distance found. It prompts the user to enter the x and y coordinates of the point of interest and of the three other points.

The program uses a 2D array to store the coordinates of the points, and a loop to iterate over the three points. For each point, it calculates the distance between that point and the point of interest using the Pythagorean theorem, and updates the smallest distance found so far if the distance just calculated is smaller than the current smallest distance.

The output is the smallest distance between the point of interest and the three other points, displayed with two decimal places.

Note that this program uses a #define statement to define the number of points to be processed (#define N 3), and that the author of the program and their university ID are included in the code as comments.