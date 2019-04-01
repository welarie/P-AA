#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <queue>
#include <tuple>

struct point
{
    char name;
    double key;
    double way;
    double heuristic;
    std::vector<char> path;

    point(char name, double way, double heuristic, std::vector<char> path)
        : name(name), key(heuristic + way), way(way), heuristic(heuristic), path(path) {}

    friend bool operator<(const point& l, const point& r) {return l.key > r.key;}
};


class adjacency_list
{
    std::vector<std::tuple<char, char, double, double>> paths;

public:

    void add_path(char from, char to, double length, double heuristic)
    {
        paths.push_back(std::make_tuple(from, to, length, heuristic));
    }

    bool get_path(char start, char finish, std::vector<char> &answer)
    {
        std::priority_queue<point> queue;
        double way = 0;
        std::vector<char> cur_path;
        cur_path.push_back(start);
        do
        {
            for (auto el : paths)
            {
                if (std::get<0>(el) == start)
                {
                    cur_path.push_back(std::get<1>(el));
                    queue.push(point(std::get<1>(el), way + std::get<2>(el), heuristic_fun(el), cur_path));
                    cur_path.pop_back();
                }
            }
            if (!queue.empty())
            {
                start = queue.top().name;
                way = queue.top().way;
                cur_path = queue.top().path;
                queue.pop();
                continue;
            }
        }
        while(start != finish);

        answer = cur_path;
        return true;

    }

    double heuristic_fun(std::tuple<char, char, double, double> el)
    {
        return std::get<3>(el);
    }
};

#endif // GRAPH_H
