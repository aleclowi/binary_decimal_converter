#ifndef _NUMBERS_
#define _NUMBERS_

#include<string>
#include<cstddef>

/**provide a declarationand definition for decimalToBinary that accepts a string
representation of a nonnegative integer in decimaland outputs its binary representation as a std::string;
 provide a declarationand definition for binaryToDecimal that accepts a string
representation of a nonnegative integer in binaryand outputs its decimal representation as a std::string;
 provide a declarationand definition for reverseString that can be passed an
std::string, reverses the characters of the input, and returns nothing;
/



/**
This function takes a single character and returns an unsigned char for its value from 0-9

@param c the character to convert
@return its value from 0-9
*/

unsigned char charToDigit(char c);

/**
This function converts an unsigned char from 0-9 and returns a char '0' to '9'

@param u the unsigned char to convert
@return its digit representation as a char
*/
char digitToChar(unsigned char u);

/**
This function takes an input of string and reverses the characters of the input

@param reverseMe, the string to reverse
@return nothing
*/
void reverseString(std::string &reverseMe);



/**
This function adds two unsigned integer types, represented as strings, given a base to work in.
The return format will be a sum, computed in whatever base is specified, where 2 <= base <= 10.

For example,
std::string sum1 = add("116", "14", 10); // sum1 == "130"
std::string sum2 = add("11", "10", 2); // sum == "101"

@param first the first addend
@param second the second addend
@param base the base being used: from 2-10

@return the sum, num1+num2 in the base
*/
std::string add(const std::string& first, const std::string& second, unsigned char base);


/**
This function subtracts two unsigned integer types, represented as strings, given a base to work in.
The return format will be a difference, computed in whatever base is specified, with as few digits as possible,
i.e., "0010" would be returned as "10", etc. We require 2 <= base <= 10.

The result is not defined if the minuend is less than the subtrahend!

For example,
std::string diff1 = subtract("130", "14", 10); // diff1 == "116"
std::string diff2 = subtract("101", "10", 2); // diff == "11"
subtract("30", "108", 10); // Do not do this!

@param minuend the term being subtracted from
@param subtrahend the value being subtracted
@param base the base being used

@return the difference, minuend-subtrahend in the base given
*/
std::string subtract(const std::string& minuend, std::string subtrahend, unsigned char base);


/**
This function determines whether two string representations of unsigned integers satisfy <= numerically

For example,
lessThanOrEqual("12", "108"); // true
lessThanOrEqual("100", "100"); // true
lessThanOrEqual("19", "6"); // false

@param first the first number
@param second the second number

@return whether first <= second as unsigned integer types
*/
bool lessThanOrEqual(const std::string& first, const std::string& second);


/**
This function computes 2 to a given nonnegative integer power with the output as an std::string, in base 10

@param pow the power
@return 2 to that power
*/
std::string twoPower(size_t ex);

/**
This function accepts a non negative number in binary represented as a string, then returns the number in 
decimal represented as a string.

@param non-negative number in binary
@return number in decimal
*/
std::string binaryToDecimal(std::string binary);

/**
This function accepts a non negative number in decimal represented as a string, then returns the number in
binary represented as a string.

@param non-negative number in decimal
@return number in binary
*/

std::string decimalToBinary(std::string dec);




#endif
