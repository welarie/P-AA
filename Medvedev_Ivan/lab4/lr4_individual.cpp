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
        set_prefix(pattern, 0, true);
        last_prefix = 0;
    }

    void set_prefix(string str, int start, bool flag) {
		
		size_t i;
		flag ? i = 1 : i = 0;
		for (; i < str.length(); i++) {
        	while (last_prefix && pattern[last_prefix] != str[i])
            		last_prefix = prefix[last_prefix-1];

        	if (pattern[last_prefix] == str[i])
            		last_prefix++;
		if (flag)
			prefix[i] = last_prefix;
		
        	if (last_prefix == pattern.length() && !flag)
			cout << i + start + 1 - pattern.length() << ' ';
	}
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
    int k, start = 0, len;
	cout<< "Enter number of substrs"<<endl;
    cin >> k;
	while (k > text.length()){
		cout<< "Wrong number of substrs"<<endl;
		cin >> k;
	}
    if(text.length() % k)
		len = (text.length() / k) + 1;
	else
		len = (text.length() / k);
	while (k){
		string str = text.substr(start, len);
		tmp.set_prefix(str, start, false);
		start += len;
		k--;
	}
     cout << ans << endl;
     return 0;
}
