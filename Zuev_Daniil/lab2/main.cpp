#include <iostream>
#include <cstdio>
#include <cmath>

#define SIZE 26

using namespace std;

class graph
{
private:
    double edges[SIZE][SIZE];
    char prev[SIZE];
    bool open_ver[SIZE];
    bool closed_ver[SIZE];
    double d[SIZE];
    char begin;
    char end;
public:
    graph()
    {
        for(int i = 0; i<SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
                edges[i][j] = 0;
            prev[i] = '\0';
            open_ver[i] = 0;
            closed_ver[i] = 0;
            d[i] = 0;
        }
    }
    void readCons()
    {
        int n;
        cin >> n;
        char f, s;
        cin >> begin;
        cin >> end;
        open_ver[static_cast<int>(begin) - 97] = 1;
        for(int i = 0; i<n; i++)
        {
            cin >> f;
            cin >> s;
            cin >> edges[static_cast<int>(f) - 97][static_cast<int>(s) - 97];
        }
    }
    double heuristic(int cur)
    {
        return abs(static_cast<int>(end) - 97 - cur);
    }
    int search_min_f()
    {
        double min = 1000;
        int min_i = 0;
        for(int i = 0; i< SIZE; i++)
        {
            if(d[i] + heuristic(i) <= min && open_ver[i])
            {

                min_i = i;
                min = d[i] + heuristic(i);
            }
        }
        open_ver[min_i] = 0;
        closed_ver[min_i] = 1;
        return min_i;
    }
    bool is_empty_open()
    {
        for(int i = 0; i<SIZE; i++)
        {
            if(open_ver[i] == 1)
            {
                return false;
            }
        }
        return true;
    }
    void a_star()
    {
        while(!is_empty_open())
        {
            int closing = search_min_f();
            if(closing == static_cast<int>(end)-97)
            {
                print_path();
                return;
            }
            for(int i = 0; i<SIZE; i++)
            {
                if(edges[closing][i] != 0)
                {
                    if(closed_ver[i])
                        continue;
                    if(open_ver[i])
                    {
                        if(d[i] > d[closing] + edges[closing][i])
                        {
                            d[i] = d[closing] + edges[closing][i];
                            prev[i] = static_cast<char>(closing + 97);
                        }
                    }
                    else
                    {
                        open_ver[i] = true;
                        d[i] = d[closing] + edges[closing][i];
                        prev[i] = static_cast<char>(closing + 97);
                    }

                }
            }
        }
        cout<<"Path is not found."<<endl;
    }
    bool is_admissible(int ver)
    {
        return d[static_cast<int>(end) - 97] - d[ver] >= heuristic(ver);
    }
    bool is_monotonic(int ver1, int ver2)
    {
        return d[ver1] + heuristic(ver1) <= d[ver2] + heuristic(ver2);
    }
    void print_path()
    {
        string out;
        bool admissible = 1;
        bool monotonic = 1;
        int i = 0;
        out[i] = end;
        while(out[i] != begin)
        {
            admissible = is_admissible(static_cast<int>(out[i]) - 97) && admissible ? 1 : 0;
            out[i+1] = prev[static_cast<int>(out[i]) - 97];
            i++;
            monotonic = is_monotonic(static_cast<int>(out[i])-97,static_cast<int>(out[i-1])-97) && monotonic ? 1 : 0;
        }
        admissible = is_admissible(static_cast<int>(out[i]) - 97) && admissible ? 1 : 0;
        for(i; i>=0 ; i--)
            cout << out[i];
        if(admissible)
            cout<<endl<<"Heuristic is admissible"<<endl;
        else
            cout<<endl<<"Heuristic is not admissible"<<endl;
        if(monotonic)
            cout<<"Heuristic is monotonic"<<endl;
        else
            cout<<"Heuristic is not monotonic"<<endl;
    }
};

int main()
{
    graph k;
    k.readCons();
    k.a_star();
}
