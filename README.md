# C program for polynomial interpolation
File "input.txt" contains the number of known data points, x and y coordinates of these points
## Algorithm
1. Read data from the input.txt
2. Read x* from user
3. Calculate the divided differences
4. Calculate the polynomial at w:

   If x* is closer to the beginning of the interval then use Newton forward divided difference formula

   Else use Newton backward divided difference formula
6. Print results
