#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <limits>
using namespace std;

template <typename type, typename T>
class Flow{
private:
    map<type, map<type, T>> graph;
    type u;
    type v;
public:

    Flow(){
        u = 0;
        v = 0;
    }

    void Init(){
        type a, b;
        size_t N;
        T w;
        cin>>N>>u>>v;
        for(size_t i = 0;i<N;i++){
            cin>>a>>b>>w;
            graph[a][b] = w;
        }
        maxFlow(u, v);
    }

    map<type, pair<type, T>> find_way(map<type, map<type, T>> m, type start, type finish){
        map<type, pair<type, T>> way;
        map<type, bool> visited;
        vector<type> stack;
        typename map<type, map<type, T>>::iterator it;
        typename map<type, map<type, T>>::iterator t;
        for (it = m.begin(); it != m.end(); it++)
            visited[it->first] = false;
        stack.push_back(start);
        it = graph.begin();
        for (   ; it != m.end(); it++) {
            if(stack[stack.size()-1] == finish)
                break;
            visited[stack[stack.size()-1]] = true;
            vector<pair<type, T>> neighbors;
            for(pair<type, T> neighbor:m.find(stack[stack.size()-1])->second)
                if(!visited[neighbor.first])
                    neighbors.push_back(neighbor);
            if(neighbors.empty()){
                if(way.size()==1 || way.empty()){
                    way.clear();
                    return way;
                }
                way.erase(stack[stack.size()-1]);
                stack.pop_back();
                continue;
            }
            pair<type, T> max = *max_element(neighbors.begin(),neighbors.end(),[](pair<type, T>& n1,pair<type, T>& n2){
                    return  n1.second < n2.second;
            });
                way[stack[stack.size()-1]] = pair<type, T>(max.first, max.second);
                stack.push_back(max.first);
        }
        return way;
    }

    int get_min_flow(map<type,pair<type,T>> way){
        auto t = way.begin();
        T min_flow = t->second.second;
        for(    ;t!=way.end();t++) {
            if(min_flow > t->second.second)
                min_flow = t->second.second;
        }
        return min_flow;
    }

    void reconstructionNetwork(map<type,map<type,T>> & network,map<type,pair<type,T>> way){
        int min_flow=get_min_flow(way);
        for (auto t = way.begin();t!=way.end();t++) {
            if(t->second.second - min_flow == 0)
                network[t->first].erase(t->second.first);
            else
                network[t->first][t->second.first] -= min_flow;
            network[t->second.first][t->first] += min_flow;
        }
    }

    void maxFlow(type source,type stock){
        map<type,map<type,T>> network=graph;
        map<type,pair<type,T>> way=find_way(network,source,stock);
        while(!way.empty()){
            reconstructionNetwork(network,way);
            way = find_way(network,source,stock);
        }
        T max_flow = 0;
        for_each(graph[source].begin(),graph[source].end(),[&max_flow,&network,source](pair<type,T> neighbor){
            max_flow+=neighbor.second-network[source][neighbor.first];
        });
        cout<<max_flow<<endl;
        for_each(graph.begin(),graph.end(),[&network](pair<type,map<type,T>> neighbors){
            for_each(neighbors.second.begin(),neighbors.second.end(),[&network,neighbors](pair<type,T> ver){
                cout<<neighbors.first<<" "<<ver.first<<" ";
                if(ver.second-network[neighbors.first][ver.first]>=0)
                   cout<<ver.second-network[neighbors.first][ver.first]<<endl;
                else
                   cout<<0<<endl;
            });
        });
    }
};

int main()
{
    Flow<char, int> a;
    a.Init();
    return 0;
}


