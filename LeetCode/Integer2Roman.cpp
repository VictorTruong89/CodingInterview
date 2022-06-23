/**
 * @file Integer2Roman.cpp
 * @author VictorTruong
 * 
 * @brief Convert an integer to Roman number 
 * @date 2022-06-22
 * @link https://leetcode.com/problems/integer-to-roman/ @endlink
 * 
 * Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
 * Constraints:
 * 1 <= num <= 3999
 */

/**
 * @brief Example 1:
 * Input: num = 3
 * Output: "III"
 * Explanation: 3 is represented as 3 ones.
 * 
 * 
 * @brief Example 2:
 * Input: num = 58
 * Output: "LVIII"
 * Explanation: L = 50, V = 5, III = 3.
 * 
 * 
 * @brief Example 3:
 * Input: num = 1994
 * Output: "MCMXCIV"
 * Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
*/


class Solution {
public:
    string intToRoman(int num) {
        /**
         * @brief Algorithm
         * 1/ Decrease the number into ones/tens/hundreds/thousands
         * 2/ ones  : I V X
         * 3/ tens  : X L C
         * 4/ hundreds: C D M
         * 5/ thousand: M
        */
        std::stack<char> roman_char;
        
        int digit = num % 10;
        num = (num - digit) / 10;
        
        // Transform the 1st digit
        if(digit == 0) {
            // Intentionally empty
        } else if(1 <= digit && digit <= 3) {
            for(int i = 0; i < digit; i++) {
                roman_char.push('I');
            }
        } else if(digit == 4) {
            roman_char.push('V');
            roman_char.push('I');
        } else if(digit == 5) {
            roman_char.push('V');
        } else if(6 <= digit && digit <= 8) {
            for(int i = 0; i < (digit - 5); i++)
                roman_char.push('I');
            roman_char.push('V');
        } else if(digit == 9) {
            roman_char.push('X');
            roman_char.push('I');
        }
        
        digit = num % 10;
        num = (num - digit) / 10;
        // Transform the 2nd digit
        if(digit == 0) {
            // Intentionally empty
        } else if(1 <= digit && digit <= 3) {
            for(int i = 0; i < digit; i++) {
                roman_char.push('X');
            }
        } else if(digit == 4) {
            roman_char.push('L');
            roman_char.push('X');
        } else if(digit == 5) {
            roman_char.push('L');
        } else if(6 <= digit && digit <= 8) {
            for(int i = 0; i < (digit - 5); i++)
                roman_char.push('X');
            roman_char.push('L');
        } else if(digit == 9) {
            roman_char.push('C');
            roman_char.push('X');
        }
        
        digit = num % 10;
        num = (num - digit) / 10;
        // Transform the 3nd digit
        if(digit == 0) {
            // Intentionally empty
        } else if(1 <= digit && digit <= 3) {
            for(int i = 0; i < digit; i++) {
                roman_char.push('C');
            }
        } else if(digit == 4) {
            roman_char.push('D');
            roman_char.push('C');
        } else if(digit == 5) {
            roman_char.push('D');
        } else if(6 <= digit && digit <= 8) {
            for(int i = 0; i < (digit - 5); i++)
                roman_char.push('C');
            roman_char.push('D');
        } else if(digit == 9) {
            roman_char.push('M');
            roman_char.push('C');
        }
        
        digit = num % 10;
        if(digit != 0) {
            for(int i = 0; i < digit; i++) {
                roman_char.push('M');
            }
        }
        
        
        // Revert the stack<char> into string
        std::string roman;
        while(roman_char.size() > 0) {
            roman.push_back(roman_char.top());
            roman_char.pop();
        }
        
        return roman;
    }
};
