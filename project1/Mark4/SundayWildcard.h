#ifndef SUNDAY_WILDCARD_H
#define SUNDAY_WILDCARD_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> preprocess(string &pat) {
    int p_len = pat.length();
    // Initialize shift table with default shift value
    vector<int> shift(256, p_len + 1);
    // Update shift values for each character in the pattern
    for (int i = 0; i < p_len; i++) {
        shift[pat[i]] = p_len - i;
    }

    return shift;
}

bool sunday(string pat, string txt) {
    int p_len = pat.length(), t_len = txt.length();
    // Generate shift table using the function
    vector<int> shift = preprocess(pat);

    int i = 0;
    while (i <= t_len - p_len) {
        int j, k = 0;

        for (j = 0; j < p_len; j++){
            // Check for escape character '\'
            if(pat[j] == '\\'){
                j++;
                k++;
                if (txt[i + j - k] != pat[j]) break;
                continue;
            }
            if (pat[j] == '?') {
                continue;
            } 
            else if (pat[j] == '*') {
                 // Skip consecutive '*' and '?' characters
                while (pat[j+1] == '*' || pat[j+1] == '?') {
                    j++;
                }
                // Recursive call for remaining pattern and text
                for (int y = 0; i + j + y < t_len; y++) {
                    if (sunday((pat.substr(j+1)), (txt.substr(i + j + y - k)))) {
                        return true;
                    }
                }
                return false;
            } 

            if (txt[i + j - k] != pat[j]) break;
        }

        if (j == p_len){
            return true;
        }
        if (i + p_len >= t_len) {
            break;
        }

        i += shift[txt[i + p_len]];
    }

    return false;
}

#endif  // SUNDAY_WILDCARD_H