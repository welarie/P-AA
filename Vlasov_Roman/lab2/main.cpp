#include <iostream>
#include <vector>
#include "adjacency_list.h"

int main()
{
    char from, to;
    double length, heuristic;
    char start, finish;
    std::cin >> start >> finish;
    adjacency_list *head = new adjacency_list();
    while(std::cin >> from >> to >> length >> heuristic)
    {
        head->add_path(from, to, length, heuristic);
    }
    std::vector<char> ans;
    head->get_path(start, finish, ans);
    for (auto c : ans)
        std::cout << c;
    delete head;
    return 0;
}
