#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

using namespace std;

bool is_equal(double x, double y) {
    return fabs(x - y) < numeric_limits<double>::epsilon();
}

class Matrix{
private:
    unsigned size;
    char begin;
    char end;
    char end2;

    vector<vector<double> > matrix;
    vector<unsigned> camefrom;
    vector<double> costsofar;
    vector<double> queue;
    vector<double> queue2;
    vector<char> finalway;


public:
    Matrix() : size(26){
        for(unsigned int i = 0; i < 26; i++){
            vector<double> temp;
            for(unsigned int j = 0; j < 26; j++)
                temp.push_back(0);
            matrix.push_back(temp);

            camefrom.push_back(0);
            costsofar.push_back(0);
            queue.push_back(numeric_limits<double>::max());
            queue2.push_back(numeric_limits<double>::max());
        }
    }

    void setLeng(unsigned i, unsigned j, double leng){
        matrix[i][j] = leng;
    }

    ~Matrix(){
        for(unsigned int i = 0; i < size; i++){
            matrix[i].clear();
        }
        matrix.clear();
        camefrom.clear();
        costsofar.clear();
        queue.clear();
        queue2.clear();
        finalway.clear();
    }

    void read();
    bool findtheway(unsigned start);
    double h(unsigned current);
    double h2(unsigned current);
};

void Matrix :: read(){
    double leng;
    char i, j;
    int N;
    cin >> N;
    cin >> begin;
    cin >> end;
    cin >> end2;

    for (int k = 0; k < N; k++) {
        cin >> i;
        cin >> j;
        cin >> leng;
        setLeng(static_cast<unsigned>(i) - 97, static_cast<unsigned>(j) - 97, leng);
    }

    if(findtheway(static_cast<unsigned>(begin) - 97)){
        for (vector<char> :: iterator it = finalway.begin(); it != finalway.end(); ++it)
               cout << *it;
    }
    else cout << "no way";
}

double Matrix :: h(unsigned current){
    return abs(static_cast<double>(end) - 97 - current);
}

double Matrix :: h2(unsigned current){
    return abs(static_cast<double>(end2) - 97 - current);
}

bool Matrix :: findtheway(unsigned start){
    queue[start] = 0;
    costsofar[start] = 0;
    double min = numeric_limits<double>::max(), tmpF;
    unsigned k, current = start;
    while(queue.size() != 0){
        min = numeric_limits<double>::max();
        for (k = 0; k < queue.size(); k++) {
            if(queue[k] < min && queue[k] > 0){
                min = queue[k];
                current = k;
            }
        }
        for (k = 0; k < queue2.size(); k++) {
            if(queue2[k] < min && queue2[k] > 0){
                min = queue2[k];
                current = k;
            }
        }

        if(current == static_cast<unsigned>(end) - 97 || current == static_cast<unsigned>(end2) - 97){
            finalway.insert(finalway.begin(), static_cast<char>(current + 97));
            unsigned d = current;
            while(camefrom[d] != start){
                finalway.insert(finalway.begin(), static_cast<char>(camefrom[d] + 97));
                d = camefrom[d];
            }
            finalway.insert(finalway.begin(), static_cast<char>(start + 97));
            return true;
        }

        if(current != start && is_equal(min, numeric_limits<double>::max())){
            return false;
        }

        for (unsigned j = 0; j < matrix[current].size(); j++) {
            if(matrix[current][j] > 0){
                tmpF = costsofar[current] + matrix[current][j];

                if((is_equal(costsofar[j], 0) || tmpF < costsofar[j])){
                    costsofar[j] = tmpF;
                    queue[j] = tmpF + h(j);
                    queue2[j] = tmpF + h2(j);
                    camefrom[j] = current;
                }
            }
        }
        queue[current] = numeric_limits<double>::max();
        queue2[current] = numeric_limits<double>::max();
    }
    return false;
}

int main()
{
    Matrix mt;
    mt.read();
    return 0;
}
