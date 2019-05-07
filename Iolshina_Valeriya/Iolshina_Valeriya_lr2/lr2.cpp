#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <cmath>
#define N 26


using namespace std;

typedef struct Elem
{
    double key;   //приоритет
    vector <char> path;  //путь по вершинам графа до текущей
    double heur;
    friend bool operator < (const Elem& v1, const Elem& v2)
    {
        return v1.key > v2.key;
    }
}Elem;

class Adj_list
{
private:
    vector <tuple <char, char, double> > edge;
    int count;
    double way_to_finish; //длина пути до конечной вершины
    double way_to_ver[N];  //длина пути до вершины
public:
    void add_edge(char v1, char v2, double length)
    {
        edge.push_back(make_tuple(v1, v2, length));
    }

    double heuristic(char ver1, char ver2)
    {
        return abs(ver1 - ver2);
    }

    bool is_admissible(double way_to, char ver, char finish)
    {
        return  way_to_finish - way_to >= heuristic(finish, ver);
    }

    bool is_monotonic(int i, char finish)
    {
        return  get<2>(edge[i]) >= heuristic(get<0>(edge[i]), finish) - heuristic(get<1>(edge[i]), finish);
    }

    void make_path(char start, char finish, vector <char>& ans_path)   //алгоритм
    {
      vector<char> tmp_path;
      priority_queue <Elem> queue1;
      double way_len = 0;   //длина пути
      count = 0;  //количество вершин
      way_to_ver[count] = 0;  //путь до вершины
      while(true)
      {
            for(int i = 0; i < edge.size(); i++)
                if(get<0>(edge[i]) == start)
                {
                    Elem elem1;
                    elem1.heur = heuristic(finish, get<1>(edge[i]));
                    elem1.key = get<2>(edge[i]) + way_len + elem1.heur;  //эвристика
                    for(auto j : tmp_path)
                        elem1.path.push_back(j);
                    elem1.path.push_back(get<1>(edge[i]));
                    queue1.push(elem1);
                }
            if(!queue1.empty())
            {
                Elem popped = queue1.top();
                queue1.pop();
                start = popped.path[popped.path.size() - 1];
                tmp_path = popped.path;
                way_len = popped.key - popped.heur;
                count++;
                way_to_ver[count] = way_len;
            }
            else
              break;

              if(tmp_path[tmp_path.size() - 1] == finish)
              {
                for (auto j : tmp_path)
                  ans_path.push_back(j);
                way_to_finish = way_to_ver[count];
                break;
              }
      }

    }
    void print_result(vector <char>& ans_path, char finish)
    {
      bool admissible = 1;
      bool monotonic = 1;
      int i=0;
      for(auto j : ans_path)
      {
        admissible = is_admissible(way_to_ver[i], j, finish)  && admissible ? 1 : 0;
        monotonic = is_monotonic(i, finish) && monotonic ? 1 : 0;
        i++;
        if(i>=count) break;
      }
      for(auto j : ans_path)
        cout<<j;
      if(admissible)
        cout << endl << "Эвристика допустима" << endl;
      else
        cout << endl << "Эвристика не допустима" << endl;
      if(monotonic)
        cout << "Эвристика монотонна" << endl;
      else
        cout << "Эвристика не монотонна" << endl;
  }
};


int main()
{
    char start, finish;
    char first, second;
    double length;
    cin >> start >> finish;
    Adj_list head;
    bool f=1;
    while(cin >> first && isalpha(first))
    {
        cin >> second;
        cin >> length;
        head.add_edge(first, second, length);
    }
    vector <char> ans_path;
    ans_path.push_back(start);
    head.make_path(start, finish, ans_path);
    cout << endl;
    head.print_result(ans_path, finish);
    return 0;
}
