#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct element
{
    bool check;
    int sample;
    int suffix_link;
    int previous_vertex;
    char curr_vertex;
    map <char, int> edge;
    map <char, int> auto_move;

    element(int previous, char vertex)
    {
        check = false;
        sample = 0;
        suffix_link = -1;
        previous_vertex = previous;
        curr_vertex = vertex;
    }
};

class Aho_Korasik
{
    vector <element> tree;
    vector <string> result;
    int number_of_tree_nodes;
    char joker;
public:
    Aho_Korasik(char joker): joker(joker)
    {
        tree.push_back(element(0, 0));
        number_of_tree_nodes = 1;
    }

    void add_pattern(string &P)
    {
        int temp = 0;
        result.push_back(P);
        for(int num = 0; num < P.length(); num++)
         {
            if(tree[temp].edge.find(P[num]) == tree[temp].edge.end())
            {
                tree.push_back(element(temp, P[num]));
                tree[temp].edge[P[num]] = number_of_tree_nodes++;
            }
            temp = tree[temp].edge[P[num]];
        }
        tree[temp].check = true;
        tree[temp].sample = 1;
    }

    int get_suffix_link(int index_vertex)
    {
        if(tree[index_vertex].suffix_link == -1)
        {
            if(index_vertex == 0 || tree[index_vertex].previous_vertex == 0)
                tree[index_vertex].suffix_link = 0;
            else
                tree[index_vertex].suffix_link = get_auto_move(get_suffix_link(tree[index_vertex].previous_vertex), tree[index_vertex].curr_vertex);
        }
        return tree[index_vertex].suffix_link;
    }

    int get_auto_move(int index_vertex, char c)
    {
        if(tree[index_vertex].auto_move.find(c) == tree[index_vertex].auto_move.end())
            if(tree[index_vertex].edge.find(c) != tree[index_vertex].edge.end())
                tree[index_vertex].auto_move[c] = tree[index_vertex].edge[c];
            else if(tree[index_vertex].edge.find(joker) != tree[index_vertex].edge.end())
                tree[index_vertex].auto_move[c] = tree[index_vertex].edge[joker];
            else if(index_vertex == 0)
                tree[index_vertex].auto_move[c] = 0;
            else
                tree[index_vertex].auto_move[c] = get_auto_move(get_suffix_link(index_vertex), c);
        return tree[index_vertex].auto_move[c];
    }

    void algorithm(string T)
    {
        int ver = 0;
        for(int i = 0; i < T.length(); i++)
        {
            ver = get_auto_move(ver, T[i]);
            for(int j = ver; j != 0; j = get_suffix_link(j))
            {
                if(tree[j].check)
                    cout << i - result[tree[j].sample - 1].size() + 2 << endl;
            }
        }
    }
};

int main()
{
    string text, pattern;
    char joker;
    cin >> text >> pattern >> joker;
    Aho_Korasik object(joker);
    object.add_pattern(pattern);
    object.algorithm(text);
    return 0;
}
