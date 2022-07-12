/**
 * @file 44WildCardMatching.cpp
 * @author VictorTruong
 * 
 * @brief Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*'
 * @date 2022-07-12
 * @link https://leetcode.com/problems/wildcard-matching/ @endlink
 * 
 * 
 * Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:
 *      '?' Matches any single character.
 *      '*' Matches any sequence of characters (including the empty sequence).
 * The matching should cover the entire input string (not partial).
 * 
 * Constraints:
 *      0 <= s.length, p.length <= 2000
 *      s contains only lowercase English letters.
 *      p contains only lowercase English letters, '?' or '*'.
 */

/**
 * @brief Example 1:
 * Input: s = "aa", p = "a"
 * Output: false
 * Explanation: "a" does not match the entire string "aa".
 * 
 * 
 * @brief Example 2
 * Input: s = "aa", p = "*"
 * Output: true
 * Explanation: '*' matches any sequence.
 * 
 * 
 * @brief Example 3
 * Input: s = "cb", p = "?a"
 * Output: false
 * Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
 */

class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.length();
        int m = p.length();
        
        // Check if empty pattern >> Match only empty string
        if(p.length() == 0)
            return (s.length() == 0);
        
        // Lookup table for storing the results of subproblems
        bool lookup[n + 1][m + 1];
        memset(lookup, false, sizeof(lookup));
        // Empty pattern can match with empty string
        lookup[0][0] = true;
        
        // Check for scenario '*' match with empty string
        for(int j = 1; j <= p.length(); j++) {
            if(p[j - 1] == '*')
                lookup[0][j] = lookup[0][j - 1];
        }
        
        // Fill the lookup table in bottom-up order
        for(int i = 1; i <= s.length(); i++) {
            for(int j = 1; j <= p.length(); j++) {
                // When encounter '*'
                if(p[j - 1] == '*')
                    lookup[i][j] = lookup[i][j - 1] ||
                                    lookup[i - 1][j];
                
                // Match current character with '?' and actual matching
                else if(p[j - 1] == '?' || s[i - 1] == p[j - 1])
                    lookup[i][j] = lookup[i - 1][j - 1];
                
                else    // If character not match
                    lookup[i][j] = false;
            }
        }
        
        return lookup[n][m];
    }
};