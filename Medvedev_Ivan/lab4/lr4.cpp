#include <string>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class kmp {
    friend int shift(string A, string B);
    string pattern;
    vector<size_t> prefix;
    size_t last_prefix;

public:
    kmp(string tmp) :pattern(tmp), prefix(pattern.length()) {
        last_prefix = prefix[0] = 0;
        for (size_t i=1; i<pattern.length(); i++) {
            set_prefix(pattern[i]);
            prefix[i] = last_prefix;

        }
        last_prefix = 0;
    }

    bool set_prefix(char temp) {
        while (last_prefix && pattern[last_prefix] != temp)
            last_prefix = prefix[last_prefix-1];

        if (pattern[last_prefix] == temp)
            last_prefix++;

        return last_prefix == pattern.length();
    }


};

int shift(string A, string B) {
    if (A == B)
        return 0;
    kmp e(A + "$" + B);
    size_t index = e.prefix[e.prefix.size() - 1];
    for(size_t i = index; i < A.size(); i++){
        if(A[i] != B[i - index])
            return -1;
    }
    return index;
}

int main() {

    string pattern = "";
    string text = "";
    string ans = "";
    cin >> pattern >> text;
    kmp tmp(pattern);
    for (size_t i = 0; i<text.length(); i++) {
        if (tmp.set_prefix(text[i])) {
            if(!ans.empty())
                ans += ',';

            ans += to_string(i + 1 - pattern.length());
        }

    }
    if (ans == ""){
        cout << "-1" <<endl;
        return 0;
        }

     cout << ans << endl;
     return 0;
}
