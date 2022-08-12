#include "Numbers.h"

#include<stdexcept>
#include<iostream>
#include<string>
#include<cmath>
#include<sstream>
#include<algorithm>

/**
If you are reading this, you may be puzzled as to why subtrahend is not passed as reference to const.
This is one of those few exceptions: we will need to make a copy of subtrahend anyway in order to modify
it in this function. It would actually be less efficient to pass by reference to const and then make a copy
inside the function. We just make a copy straightaway. Unless you really understand this deeply, do not
pass an object by value.
*/

unsigned char charToDigit(char c)
{
	//reassign c to a variable of unsigned char and subtract char '0' from c to match
	//it with the ascii table, then return unsigned char variable
	unsigned char a = (c - '0');
	return a;
	
}

char digitToChar(unsigned char u)
{
	//reassign u to a variable of char and add char '0' to u to match
	//it with the ascii table, then return char variable
	char b = (u + '0');
	return b;
}

std::string twoPower(size_t ex) //this is the function that will make any number exponent
{
	//Initialize all variables that will be modified in the loop
	unsigned char ten = 10;
	std::string result = "1"; 
	//this is the for loop that will start at 0 and starts at pow. 
	for (size_t i = 0; i != ex; i++) 
	{
		//result adds to itself
		result = add(result, result, ten); 
	}
	// return the result string
	return result;
}

void reverseString(std::string &reverseMe)
{
	//Since all outputs will be of type string, we can use this function to reverse strings.
	//reverse function from c++ 11, start from beginning to string to end of string.
	reverse(reverseMe.begin(), reverseMe.end());
	return;
}


std::string add(const std::string& first, const std::string& second, unsigned char base)
{
	//initialize all necessry variable types before the loop
	char zero = '0';
	std::string zeros;
	//convert first and second to strings so they can be maniupulated by the function.
	std::string s1 = first;
	std::string s2 = second;
	//Pointers are used in the input types of function

	// If one string is shorter than the other, this if else statement will add 
	// zeros to the beginning of each number (to make the strings the same length)
	// to add the strings with the same length by using our previous charToDigit and digitToChar functions.

	if (s1.length() < s2.length())
	{
		size_t len1 = s2.length() - s1.length();
		zeros = std::string(len1, zero);
		s1 = zeros + s1;
	}
	else if (s1.length() > s2.length())
	{
		size_t len2 = s1.length() - s2.length();
		zeros = std::string(len2, zero);
		s2 = zeros + s2;
	}
	// initialize result to an empty string, and the carry to zero
	std::string result = "";
	unsigned char carry = 0;
	//for loop for each i starting at the begging of the string length all the way to the end
	for (int i = s1.length() - 1; i >= 0; --i)
	{
		//convert each i of each string to digits to be added to carry
		int total = carry + charToDigit(s2[i]) + charToDigit(s1[i]);
		//Find the remainder of the total/base for each i
		unsigned char append = total % base;
		//pushback function for result, this will append the append variable to result
		result.push_back(digitToChar(append));
		//find the carry value so it can be added to the beginning of the function
		carry = total / base;
		//if the carry does not equal zero and the ith char of the string is 0, append the carry
		// this will be for adding numbers of base 2 (binary)
		if (carry != 0 && (i == 0))
		{
			result.push_back(digitToChar(carry));
		}
		
	}
	// reverse string the result because in binary the first number is of highest nth exponent of base 2
	reverseString(result);

	return result; //return result of type string
}

std::string subtract(const std::string& minuend, std::string subtrahend, unsigned char base) 
{

	// ensure subtrahend has as many digits as minuend
	if (subtrahend.size() < minuend.size()) {
		subtrahend = std::string(minuend.size() - subtrahend.size(), '0') + subtrahend;
	}

	/* We first wish to modify each digit of subtrahend by turning it into its complement.
	The digit d should be converted into (base-1-d).
	*/
	for (auto& c : subtrahend) { // for each char in the subtrahend string
		// need to convert the char to digits, do the arithmetic, and go back to char!
		c = digitToChar((base - 1) - charToDigit(c));
	}

	//Subtraction can be done by addition, now. We first add 1 to the subtrahend.
	subtrahend = add(subtrahend, "1", base);

	// now, add the minuend and updated subtrahend
	std::string difference = add(minuend, subtrahend, base);

	/*
	The resulting number will always have a superfluous digit at index 0 that we do not want.
	In addition, we wish to move past all the zeros at the start.
	*/
	size_t zeroEnd = 1; // index to track where zeros end

	// size of the difference  
	const size_t diff_sz = difference.size();

	// while index still within bounds (checked first) and there are still zeros
	while ((zeroEnd < diff_sz) && (difference[zeroEnd] == '0')) {
		++zeroEnd; // increase the index
	}

	if (zeroEnd == diff_sz) { // if zeroEnd is out of range then it was all 0's
		return "0";
	}

	return difference.substr(zeroEnd); // return the truncated number going from first nonzero to end of string
}


bool lessThanOrEqual(const std::string& first, const std::string& second) 
{
	if (first == second) { // if the two strings are equal, then they are equal!
		return true;
	}

	/* We need to look at their lengths: a longer number in proper format (no 0's at beginning)
	will always be larger than a number that is shorter */

	if (first.size() < second.size()) { // second longer
		return true; // so first < second
	}
	else if (second.size() < first.size()) { // first longer
		return false; // so first > second
	}
	else { // If the numbers have the same length, we can compare digit by digit because the chars 0-9 are ordered
		return first < second;
	}
}

//this is the function that will be converting binary to decimal, start with input of string type binary
std::string binaryToDecimal(std::string binary) 
{
	//initialize all variables that will be manipulated in the loop
	int oneInt = 1;
	unsigned ten = 10;
	std::string bin; 
	std::string zero = "0";
	//the for loop from zero to binary.size
	for (int i = 0; i <= binary.size() - oneInt; ++i)
	{
		//use if else statement for whether or not a one or a zero is located at the specified location
		if (binary[i] == '1') 
		{
			//use add function to add the number in binary with specific location of chars, repeat with else condition
			bin = add(bin, twoPower(binary.size() - 1 - i), ten);
		}
		else
		{
			bin = add(bin, zero, 10);
		}
	}
	return bin; //return string type bin
}

//this function will convert decimal to binary with input decimal number
std::string decimalToBinary(std::string dec)
{
	//Initialize all variables that will be manipulated in the loop
	size_t maxx = 0;

	//Use a while loop to compare the two strings, if it's true it will count
	while (lessThanOrEqual(twoPower(maxx), dec) == true)
	{
		//counter for to continue adding chars
		maxx++; 
	}

	// another condition for when maxx is not equal to zero
	if (maxx != 0)
	{
		// the counter will be -1 because of the index adding one by itself
		maxx += -1; 
		//initialize all the variables that will be modified in the for loop 
		std::string decBin;
		char one = '1'; 
		char zero = '0'; 
		unsigned char ten = 10;
		//for loop from zero to the max power
		for (size_t i = 0; i <= maxx; i++) 
		{
			//decrement max power for each iteration and compare the strings with lessthanorequal function
			if (lessThanOrEqual(twoPower(maxx - i), dec) == true)															 
			{
				//use subtract function for each iteration and twoPower
				dec = subtract(dec, twoPower(maxx - i), ten); 
				//in binary that value will be stored as a one
				decBin.push_back(one); 
			}
			//else statement will push back a 0 and continue with the if statement
			else
			{
				decBin.push_back(zero); 
			}
		}
		//return the string we have created
		return decBin;
	}
}
