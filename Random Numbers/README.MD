# Program Description

This program generates an array of random numbers and asks the user to input a test value. It then finds the value in the array that is the farthest away from the test value and prints it out.

The program starts by including the necessary header files and defining a constant NUM_VALORES as the length of the array of random numbers. It also declares several variables, including the array of random numbers, a test value, a value that is farthest away from the test value, and a difference between two values.

In the main function, the program first sets the seed for the random number generator using the current time. It then prints out a message to indicate the start of the program and generates an array of random numbers using a for loop that runs NUM_VALORES times. Each element of the array is set to a random float value between 0 and 99 using the rand function.

The program then asks the user to input a test value and reads it in using the scanf function. It initializes the value that is farthest away from the test value to the first element of the array and then uses a for loop to compare the difference between each element of the array and the test value with the difference between the current farthest value and the test value. If the difference is greater, the program updates the farthest value to the current element.

Finally, the program prints out the value that is farthest away from the test value.