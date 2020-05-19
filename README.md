# integers-of-arbitrary-length-in-C
A C library for the integers of arbitrary length (intal).

C allows integer values between the range -2147483648 to +2147483647 for a regular int variable

C allows integer values between the range -9223372036854775808 to +9223372036854775807 for a long int variable

This C library, allows integer values of any arbitrary length by storing them in string format. The library provides the basic mathematical operations similar to the operations between two positive int values. An intal is represented as a string of decimal digits (0-9) that are stored in the big-endian style.

The functions include:

  - Addition of two intals
  - Subtraction of two intals
  - Multiplication of two intals
  - Mod of two intals
  - GCD of two intals
  - Factorial of an integer (result returned as an intal)
  - nth Fibonacci number (result returned as an intal)
  - Comparison of two intals
  - Power of one intal to the other
  - Binomial coefficient of two integers (result returned as an intal)
  - Finding index of max intal in an unsorted intal array
  - Finding index of min intal in an unsorted intal array
  - Finding index of the given intal in an unsorted intal array (linear search)
  - Sorting an array of intals in O(nlogn) time (merge sort)
  - Searching for the given intal in a sorted intal array (binary search)
