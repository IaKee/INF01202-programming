# Rainfall Precipitation Calculator

This program calculates the average precipitation of three cities and compares it to an expected value. It receives the precipitation values (in mm) and the city codes as input from the user, and outputs the average precipitation of the cities and a message indicating whether each city had above, below, or equal to the expected precipitation value.

## Input

- Identifiers of precipitation of rains (in mm)
- City codes in the following format: xxx yyy zzz

## Output

- Average precipitation of the cities
- Comparison of the entered value to the expected value (105mm)

## Variables

- precip1, precip2, precip3, precipmedia: Holds the respective precipitation values and the average precipitation.
- city1, city2, city3: Holds the city codes.
- valoresperado: Holds the expected precipitation value.

## Program Logic

- Prompt the user to enter the city codes and precipitation values of the three cities.
- Calculate the average precipitation of the three cities.
- Compare the precipitation values of each city to the expected value and output a message indicating whether it is above, below, or equal to the expected value.