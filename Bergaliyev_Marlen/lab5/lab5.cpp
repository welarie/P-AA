#include <iostream>
#include <map>
#include <vector>

class trie{
	struct node{
		int n_pattern;
		int length;
		std::map<char, node*> direct;
		node* suff;
		node(int length) : suff(nullptr), length(length), n_pattern(0) {}
	};
public:	
	trie(const std::vector<std::string>& patterns){
		root = new node(0);
		node* cur;
		std::vector<std::map<std::string, node*>> nodes;
		int n;
		std::string cur_str;
		std::string s;
		for(int j=0; j<patterns.size(); ++j){
			s = patterns[j];
			cur = root;
			n = s.length();
			cur_str = "";
			for(int i=0; i<n; ++i){
				if(i >= nodes.size())
					nodes.push_back(std::map<std::string, node*>());
				cur_str.push_back(s[i]);
				if(nodes[i].find(cur_str) == nodes[i].end()){
					node* new_node = new node(i+1);
					cur->direct.emplace(s[i], new_node);
					cur = new_node;
					nodes[i].emplace(cur_str, new_node);
				}
				else{
					cur->direct.emplace(s[i], nodes[i][cur_str]);
					cur = nodes[i][cur_str];
				}
			}
			cur->n_pattern = j+1;
		}
		n = nodes.size();
		node* suff;
		for(auto k : nodes[0])
			k.second->suff = root;
		for(int i=0; i<n; ++i)
			for(auto k : nodes[i]){
				for(auto j : k.second->direct){
					cur = k.second->suff;
					j.second->suff = root;
					while(cur != nullptr){
						if(cur->direct.find(j.first) != cur->direct.end()){
							j.second->suff = cur->direct[j.first];
							break;
						}
						cur = cur->suff;
					}
				}
			}
	}
	std::vector<std::pair<int, int>> aho_corasick(std::string s){
		node* cur = root;
		node* cur_suff;
		std::vector<std::pair<int, int>> ans;
		for(int i=0; i<s.length(); ++i){
			if(cur->direct[s[i]] != nullptr){
				cur = cur->direct[s[i]];
				if(cur->n_pattern != 0)
					ans.push_back(std::make_pair(i-cur->length+2, cur->n_pattern));
				cur_suff = cur->suff;
				while(cur_suff != nullptr){
					if(cur_suff->n_pattern != 0)
						ans.push_back(std::make_pair(i-cur_suff->length+2, cur_suff->n_pattern));
					cur_suff = cur_suff->suff;
				}	
			}
			else if(cur != root){
				cur = cur->suff;
				--i;
			}
					
		}
		return ans;					
	}

private:
	node* root;
};

int main(){
	std::vector<std::string> v;
	std::string s;
	int n;
	std::cin >> n;
	for(int i=0; i<n; ++i){
		std::cin >> s;
		v.push_back(s);
	}
	trie t(v);
	std::string text;
	std::cin >> text;
	auto ans = t.aho_corasick(text);
	for(auto i : ans)
		std::cout << i.first << ' ' << i.second << std::endl;
	return 0;
}
