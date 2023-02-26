# Program Description

This program is a substitution cipher encryption tool, implemented in C language. It takes as input a set of characters to be substituted, a set of replacement characters, and a phrase to be encrypted. The program then substitutes each character of the input phrase with the corresponding character from the substitution set, producing the encrypted output.

The substitution cipher is implemented by using two character arrays: cripto_in and cripto_out. The cripto_in array stores the characters to be replaced, and the cripto_out array stores their corresponding replacements. The input phrase is stored in the frase array, and the encrypted output is stored in the holder array.

The program starts by prompting the user to input the substitution characters and the phrase to be encrypted. It then calculates the length of the phrase using the strlen function. The substitution cipher is then applied to each character of the input phrase using nested for loops. The outer loop iterates over the characters of the input phrase, while the inner loop iterates over the substitution character arrays. If the current character in the input phrase does not match any of the characters in cripto_in, it is simply copied to the corresponding position in the holder array. If the character in the input phrase matches a character in cripto_in, its corresponding character from cripto_out is copied to the corresponding position in the holder array.

Finally, the encrypted output is printed to the console using the puts function, and the length of the input phrase is printed using the printf function.

Note: The use of gets function to read user input is deprecated and unsafe. It is recommended to use fgets instead to avoid buffer overflow vulnerabilities.