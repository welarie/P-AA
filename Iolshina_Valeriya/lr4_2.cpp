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

int shift(string &A, string &B, vector <int> &prefix)
{
  p_func(A, prefix);
  int k = 0, l = 0;
  int flag = 0; //совпадения
  for (int i = 0; i < A.size(); i++)
  {
    while (A[k] == B[l])
    {
      flag++;
      k = (k + 1) % A.size();
      l = (l + 1) % A.size();
      if (flag == A.size())
        return (l % A.size());
      i++;
    }
    flag = 0;
    if (A[k] != B[l])
      if (k != 0)
      {
        k =  prefix[k - 1];
        i--;
      }
      else l++;
  }
  return -1;
}

int main()
{
  string A, B;
  vector <int> prefix (B.size());
  getline(cin, A);
  getline(cin, B);
  if (A.size() - B.size())
  {
    cout << -1;
    return 0;
  }
  cout << shift(A, B, prefix) << endl;
  return 0;
}
