# Program Description

This program calculates the natural logarithm of (x+1) for values of x between -1 and 1. It uses a series approximation to compute the value of the logarithm.

The program starts by prompting the user to enter a value for x within the specified range. If the user enters an invalid value outside the range, the program requests a new input until a valid value is entered.

The logarithm calculation uses a do-while loop to iterate through the series approximation. The loop uses two variables, termo_ant and termo_prox, to store the current and next term in the series. The loop continues until the difference between termo_ant and termo_prox is sufficiently small.

Within the loop, the program uses the pow() function from the math.h library to calculate the power of valor_x raised to the termo_atual. It then divides this result by termo_atual to obtain the value of the current term. The program alternates the sign of the term based on whether termo_atual is odd or even.

After the loop completes, the program outputs the approximate value of the logarithm and the number of terms used in the approximation.

Overall, this program provides a simple way to calculate the natural logarithm of (x+1) for values of x between -1 and 1.