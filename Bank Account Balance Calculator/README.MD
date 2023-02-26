# Bank Account Balance Calculator

This program is designed to calculate the balance of a bank account after a deposit or withdrawal operation.

## Program Overview

- The program starts by prompting the user to input the initial balance of the account. If the balance is negative or zero, the program will display a warning message.
- The user will then be prompted to choose between a deposit or withdrawal operation. If the user selects a withdrawal operation, the program will prompt for the amount to be withdrawn, and will automatically convert the value to a negative number. If the user selects a deposit operation, the program will prompt for the amount to be deposited.
- The program will then calculate the final balance by adding the inputted value to the initial balance. If the final balance is negative or zero, the program will display a warning message.

## Code Overview
- The program is written in C, and begins by including the standard input/output library stdio.h.
- The program uses four variables: saldoinicial for the initial balance, valoropera for the deposit/withdrawal amount, saldofinal for the final balance, and operacao to determine whether the user wants to make a deposit or withdrawal.
- The program then prompts the user for the initial balance, and checks whether the balance is negative or zero.
- The user is then prompted to select an operation, and depending on their choice, the program prompts for the deposit/withdrawal amount and converts the value to negative if it is a withdrawal.
- The program then calculates the final balance by adding the deposit/withdrawal value to the initial balance, and checks whether the final balance is negative or zero.

# Conclusion

The Bank Account Balance Calculator program is a useful tool for individuals who want to keep track of their finances and monitor their bank account balance. It is a simple and efficient program that can be used by anyone with basic computer skills.