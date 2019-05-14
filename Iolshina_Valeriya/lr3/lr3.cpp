#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>
#include<climits>
#define N 20

using namespace std;

struct way
{
  int max_b = 0;
  int result_b = 0;
  bool flag = false;
};

class Graph
{
  char start;
  char finish;
  int max_flow;

  vector<char> find_path()
  {
    vector<char> tmp_path;
    vector<char> vis = vertex;
    stack<int> stack;
    stack.push(0);

    do
    {
      vector<char> arr;  //массив вершин, в которые можно пойти из данной
      int size = arr.size();
      int cur = stack.top();
      tmp_path.push_back(vertex[cur]);
      if(cur == 1) return tmp_path;
      for(int i = 1; i < vertex.size(); i++)
      {
        if(vis[i]!=0 && (edges[cur][i].max_b))
        {
            arr.push_back(vertex[i]);
        }
      }
        if(arr.size() == size)
        {
          int i = stack.top();
          stack.pop();
          tmp_path.pop_back();
          while(!stack.empty() && !tmp_path.empty() && (edges[stack.top()][i].max_b))
          {
            if(stack.top() == 1)
            {
              if(tmp_path.back() != vertex[1])
                tmp_path.push_back(vertex[1]);
              return tmp_path;
            }
            tmp_path.pop_back();
            i = stack.top();
            stack.pop();
          }
        }
        else
        {
          sort(arr.begin(), arr.end());
          for(int i = arr.size() - 1; i >= 0; i--)
            stack.push(find(vertex.begin(), vertex.end(), arr[i]) - vertex.begin());
        }
    }  while (!stack.empty());
        return vector<char>();
  }


public:
  vector<char> vertex;
  way** edges;

  Graph(char start, char finish)
  {
    max_flow = 0;
    edges = new way*[N];
    for (int i = 0; i < N; i++)
      edges[i] = new way[N];
  }

  ~Graph()
  {
  for (int i = 0; i < N; i++)
    delete[] edges[i];
  delete[] edges;
  }

  int get_index(char name)
  {
    for (int i = 0; i<vertex.size(); i++)
    {
      if (vertex[i] == name)
        return i;
    }
    vertex.push_back(name);
  return vertex.size()-1;
    }

  int find_flow()
  {
    vector<char> path = find_path();
    int cur_b = 0;
    while(path.size())
    {
      int i = get_index(path[0]);
      int j = get_index(path[1]);
      int tmp = edges[i][j].max_b;
      for (int k = 2; k < path.size(); k++)
      {
        i=j;
        j = get_index(path[k]);
        if (edges[i][j].max_b < tmp)
        tmp = edges[i][j].max_b;
      }

      max_flow += tmp;

      i = get_index(path[0]);
      j = get_index(path[1]);
      edges[i][j].max_b -= tmp;
      edges[i][j].result_b += tmp;
      for (int k = 2; k < path.size(); k++)
      {
        i = j;
        j = get_index(path[k]);
        edges[i][j].max_b -= tmp;
        edges[i][j].result_b += tmp;
      }

      path = find_path();
    }
    return  max_flow;
  }

  void print_answer()
  {
    int i, j;
    vector<char> order = vertex;
    sort(order.begin(), order.end());
    cout << max_flow << endl;
    for (int k = 0; k < vertex.size(); k++)
    {
      i = get_index(order[k]);
      for (int l = 0; l < vertex.size(); l++)
      {
        j = get_index(order[l]);
        if (edges[i][j].flag)
          cout << vertex[i] << ' ' << vertex[j] << ' ' << edges[i][j].result_b << endl;
      }
    }
  }
};


int main()
{
    int n;
    cin >> n;
    char start, finish;
    cin >> start >> finish;
    Graph graph(start, finish);
    graph.vertex.push_back(start);
    graph.vertex.push_back(finish);
    for (int i = 0; i < n; i++)
    {
      int l;
      cin >> start >> finish >> l;
      int index_f = graph.get_index(start);
      int index_d = graph.get_index(finish);
      graph.edges[index_f][index_d].max_b = l;
      graph.edges[index_f][index_d].flag = true;
    }
    graph.find_flow();
    graph.print_answer();

    return 0;
}
