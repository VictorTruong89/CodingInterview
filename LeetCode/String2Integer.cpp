/**
 * @file String2Integer.cpp
 * @author VictorTruong
 * 
 * @brief Covert a string to a 32-bit integer
 * @date 2022-06-21
 * @link https://leetcode.com/problems/string-to-integer-atoi/ @endlink 
 * 
 * Implement the myAtoi(string s) function, which converts a string to a 32-bit signed integer (similar to C/C++'s atoi function).
 * The algorithm for myAtoi(string s) is as follows:
 * 1. Read in and ignore any leading whitespace.
 * 2. Check if the next character (if not already at the end of the string) is '-' or '+'. Read this character in if it is either. 
 *    This determines if the final result is negative or positive respectively. Assume the result is positive if neither is present.
 * 3. Read in next the characters until the next non-digit character or the end of the input is reached. The rest of the string is ignored.
 * 4. Convert these digits into an integer (i.e. "123" -> 123, "0032" -> 32). If no digits were read, then the integer is 0. Change the sign as necessary.
 * 5. If the integer is out of the 32-bit signed integer range [-231, 231 - 1], then clamp the integer so that it remains in the range. 
 *    Specifically, integers less than -231 should be clamped to -231, and integers greater than 231 - 1 should be clamped to 231 - 1.
 * 6. Return the integer as the final result.
 * 
 * Note:
 * Only the space character ' ' is considered a whitespace character.
 * Do not ignore any characters other than the leading whitespace or the rest of the string after the digits.
 */

/**
 * @brief Example 1:
 * Input: s = "42"
 * Output: 42
 * Explanation: The underlined characters are what is read in, the caret is the current reader position.
 * 
 * 
 * @brief Example 2:
 * Input: s = "   -42"
 * Output: -42
 * Explanation: "___-42" (leading whitespace is read and ignored)
 * 
 * 
 * @brief Example 3:
 * Input: s = "4193 with words"
 * Output: 4193
 * Explanation: "4193 with words" (no characters read because there is no leading whitespace)
 * 
 * 
 * @brief Example 4:
 * Input: s = "words and 987"
 * Output: 0
 * Explanation: The first non-whitespace character is 'w', which is not a numerical digit or a +/- sign. Therefore no valid conversion could be performed.
 * 
 * 
 * @brief Example 5:
 * Input: s = "-91283472332"
 * Output: -2147483648
 * Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer. Thefore INT_MIN (−2^31) is returned.
 */

#include <iostream>
#include <string.h>

class Solution {
public:
    int myAtoi(std::string s) {
        int sign = 1; // positive
        long result = 0;
        bool found = false;
        
        int posStart = 0;
        
        for(int i = 0; i < s.size(); i++){
            // Accept white-space in front
            if((s[i] == ' ') && (!found)) {
                posStart++;
            }
            
            // Find the starting position of the integer
            else if(s[i] == '-') {
                // Stop parsing if integer already encountered
                if(found) break;
                
                // Check next char, it should be a digit
                if((s[i+1] >= '0') && (s[i+1] <= '9'))
                    sign = -1;
                else return 0;
                
                posStart++;
                
            } else if(s[i] == '+') {
                // Stop parsing if integer already encountered
                if(found) break;
                
                // Check next char, it should be a digit
                if((s[i+1] >= '0') && (s[i+1] <= '9'))
                    sign = 1;
                else return 0;
                
                posStart++;

            } else if((s[i] >= '0') && (s[i] <= '9')) {
                found = true;
                // Start converting the integer
                int digit = static_cast<int>(s[i] - '0');
                result = result*10 + digit;
                
                // Check & Clamp if result exceeds int32_t limit
                if(sign*result < INT32_MIN)
                    return INT32_MIN;
                else if(sign*result > INT32_MAX)
                    return INT32_MAX;

            } else {
                if(found) 
                    // Stop parsing if integer already encountered
                    break;
                else    
                    // non-integer character should not come in front
                    return 0;
                
                posStart++;
            }
        }
        
        return result*sign;
    }
};