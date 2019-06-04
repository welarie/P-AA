#include <iostream>
#include <string>
#include <vector>
using namespace std;

void p_func(string &pattern, vector <int> &prefix)
{
  prefix.assign(pattern.size(), 0);
  prefix[0] = 0;
  int i = 1, j = 0;
  while (i < pattern.size())
  {
    if(pattern[i] == pattern[j])
    {
      prefix[i] = j + 1;
      i++;
      j++;
    }
    if(pattern[i] != pattern[j])
      if(j == 0)
      {
        prefix[i] = 0;
        i++;
      }
      else j = prefix[j - 1];
  }
}

void KMP(string &pattern, vector <int> &prefix)
{
  char c;
  cin >> c;
  int i = 0;  //переход по тексту
  int j = 0; //переход по шаблону
  bool flag = false;
  p_func(pattern, prefix);
  while(true)
  {
    if(c == pattern[j])
    {
      i++; j++;
      if(j == pattern.size())
      {
        if(flag) cout << "," << i - pattern.size();
        else
        {
          flag = true;
          cout << i - pattern.size();
        }
        j = prefix[j - 1];
      }
      if(!(cin >> c)) break;
    }
    else if(j == 0)
    {
      i++;
      if(!(cin >> c)) break;
    }
    else j = prefix[j - 1];
  }
  if(!flag) cout << -1;
  return;
}

int main()
{
  string pattern;
  cin >> pattern;
  vector <int> prefix (pattern.size());
  KMP(pattern, prefix);
  cout << endl;
  return 0;
}
