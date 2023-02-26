# Brute Force Password Cracker in C

This repository contains a C program that can perform a brute force attack to guess a password of up to 8 characters long. The program prompts the user to input the desired password and then tries to guess it by checking every possible combination of characters using a sequential brute force algorithm.

The program uses an alphabet string containing lowercase and uppercase letters, numbers, and special characters to generate all possible combinations of characters for the password. It then tests each combination until it matches the password entered by the user.

The bruteImpl function is responsible for generating all possible combinations of characters for the password, and the bruteSequential function iterates through all possible password lengths and calls the bruteImpl function for each length.

Once the program successfully guesses the password, it prints the password and the number of iterations it took to find the password.

This program is intended to showcase basic programming concepts such as loops, conditional statements, functions, and string manipulation. The program should not be used for malicious purposes. The code may not be optimized for performance, and there may be more efficient algorithms for password cracking.

This repository is also intended to store the author's works related to the Introduction to Programming in C course.