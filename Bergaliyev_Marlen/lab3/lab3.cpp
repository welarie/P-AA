#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#include <algorithm>

class Adj_Matrix{
private:
	struct Edge{
		int bandwidth;
		int flow;
		Edge(int band, int flow) : bandwidth(band) , flow(flow) {}
	};
public:
	Adj_Matrix(std::vector<std::tuple<char, char, int>> & v){
		for(auto i : v){
			if(find(indexes.begin(), indexes.end(), std::get<0>(i)) == indexes.end())
				indexes.push_back(std::get<0>(i));
			if(find(indexes.begin(), indexes.end(), std::get<1>(i)) == indexes.end())
				indexes.push_back(std::get<1>(i));
		}
		int n = indexes.size();
		matrix = new Edge**[n];
		for(int i=0; i<n; ++i){
			matrix[i] = new Edge*[n];
		}
		rest_net = new Edge**[n];
		for(int i=0; i<n; ++i){
			rest_net[i] = new Edge*[n];
		}
		char from, to;
		int bandwidth;
		int index_from, index_to;
		std::vector<char>::iterator it;
		for(auto i : v){
			std::tie(from, to, bandwidth) = i;
			it = find(indexes.begin(), indexes.end(), from);
			index_from = it - indexes.begin();
			it = find(indexes.begin(), indexes.end(), to);
			index_to = it - indexes.begin();
			matrix[index_from][index_to] = new Edge(bandwidth, 0);
			rest_net[index_to][index_from] = new Edge(0, 0);
		}
	}

	std::string bfs(char from, char to){
		std::queue<std::string> queue;
		std::vector<int> checked;
		std::string cur(1, from);
		int n = indexes.size();
		int i;
		while(true){
			i = find(indexes.begin(), indexes.end(), cur.back()) - indexes.begin();
			checked.push_back(i);
			for(int j=0; j<n; ++j){
				if(find(checked.begin(), checked.end(), j) != checked.end())
					continue;
				if((matrix[i][j] != nullptr) && (matrix[i][j]->flow != matrix[i][j]->bandwidth)){
					if(indexes[j] == to)
						return cur + '+' + to;
					queue.push(cur + '+' + indexes[j]);
					checked.push_back(j);
				}
				if((rest_net[i][j] != nullptr) && (rest_net[i][j]->flow != rest_net[i][j]->bandwidth)){
					queue.push(cur + '-' + indexes[j]);
					checked.push_back(j);
				}
			}
			if(queue.empty())
				return "";
			cur = queue.front();
			queue.pop();
		}
	}
	
	std::vector<std::tuple<char, char, int>> ford_fulkerson(char sourse, char stock){
		std::string path;
		int min;
		int i, j;
		while(true){
			path = bfs(sourse, stock);
			if(path == "")
				break;;
			min = 0;
			i = find(indexes.begin(), indexes.end(), path.front()) - indexes.begin();
			for(int k=1; k<path.length(); k += 2){
				j = find(indexes.begin(), indexes.end(), path[k+1]) - indexes.begin();
				if(path[k] == '+'){
					if((matrix[i][j]->bandwidth - matrix[i][j]->flow < min) && (matrix[i][j]->bandwidth - matrix[i][j]->flow != 0) || (min == 0))
						min = matrix[i][j]->bandwidth - matrix[i][j]->flow;
				}
				else if((rest_net[i][j]->bandwidth - rest_net[i][j]->flow < min) && (rest_net[i][j]->bandwidth - rest_net[i][j]->flow != 0) || (min == 0))
						min = rest_net[i][j]->bandwidth - rest_net[i][j]->flow;
				i = j;
			}
			i = find(indexes.begin(), indexes.end(), path.front()) - indexes.begin();
			for(int k=1; k<path.length(); k+=2){
				j = find(indexes.begin(), indexes.end(), path[k+1]) - indexes.begin();
				if(path[k] == '+'){
					matrix[i][j]->flow += min;
					rest_net[j][i]->flow -= min;
				}
				else{
					rest_net[i][j]->flow += min;
					matrix[j][i]->flow -= min;
				}
				i = j;
			}
		}
		int n=indexes.size();
		std::vector<std::tuple<char, char, int>> ans;
		for(i=0; i<n; ++i)
			for(j=0; j<n; ++j)
				if(matrix[i][j] != nullptr)
					ans.push_back(std::make_tuple(indexes[i], indexes[j], matrix[i][j]->flow));
		return ans;
	}

private:
	std::vector<char> indexes;
	Edge* **matrix;
	Edge* **rest_net;
};
	
int main(){
	std::vector<std::tuple<char, char, int>> net;
	int n;
	std::cin >> n;
	char sourse, stock;
	std::cin >> sourse;
	std::cin >> stock;
	char from, to;
	int w;
	for(int i=0; i<n; ++i){
		std::cin >> from;
		std::cin >> to;
		std::cin >> w;
		net.push_back(std::make_tuple(from, to, w));
	}
	Adj_Matrix matr(net);
	auto res = matr.ford_fulkerson(sourse, stock);
	std::sort(res.begin(), res.end());
	int sum = 0;
	for(auto i : res)
		if(std::get<0>(i) == sourse)
			sum += std::get<2>(i);
	std::cout << sum << std::endl;
	for(auto i : res)
		std::cout << std::get<0>(i) << " " << std::get<1>(i) << " " << std::get<2>(i) << std::endl;
	return 0;
}
