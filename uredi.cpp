#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

vector<int> tabela(int u, int n){
    vector<int> t;

    switch(u){
        case 1:
            for(int i = 1; i <= n; i++) t.push_back(i);
            break;
        case 2: 
            for(int i = n; i >= 1; i--) t.push_back(i);
            break;
        case 3: 
            int second = n;
            for(int i = 1; i <= n/2; i++){
                t.push_back(i);
                t.push_back(second);
                second--;
            }
            if(n % 2 == 1) t.push_back(second);
            break;
    }

    return t;
}

vector<int> merge(vector<int> a, vector<int> b) {
    int i = 0, j = 0;
    vector<int> c;

    while (i < a.size() || j < b.size()) {
        if (i < a.size() && j < b.size()) {
            if (a[i] <= b[j]) c.push_back(a[i++]);
            else c.push_back(b[j++]);
        } else if (i < a.size()) c.push_back(a[i++]);
        else c.push_back(b[j++]);
    }

    return c;
}

void insertion_sort(vector<int>& t){
    int n = t.size();

    for(int i = 1; i < n; i++){
        int x = t[i];
        int j = i-1;
        while(j >= 0 && t[j] > x){
            t[j+1] = t[j];
            j--; 
        }
        t[j+1] = x;
    }
}


void bogosort(vector<int>& t){
    std::random_device rnd;       
    std::mt19937 rng(rnd());

    while (1) {
        // preverimo urejenost seznama
        bool sorted = true;
        for (int i = 0; i + 1 < t.size();i++) {
            if (t[i] > t[i+1]) sorted = false;
        }
        if (sorted) break;
        shuffle(t.begin(), t.end(), rng);
    }
}

vector<int> mergesort(vector<int>& t){
    int n = t.size();
    if(n <= 1) return t;

    vector<int> left(t.begin(), t.begin() + n/2);
    vector<int> right(t.begin() + n/2, t.end());

    left = mergesort(left);
    right = mergesort(right);
    return merge(left, right);
}




int main(int argc, char* argv[]){
    /*  a - tip algoritma (1 - insertion sort, 2 - mergesort, 3 - bogosort)
        n - dolžina tabele
        u - začetna urejenost:
            1 - urejeno zaporedje (>)
            2 - obratno urejeno zaporedje (<)
            3 - "izmenjujoče" zaporedje (1, n, 2, n-1,...)
        i - število izvedb postopka
    */
    int a, n, u, i;
    
    a = std::atoi(argv[1]);
    n = std::atoi(argv[2]);
    u = std::atoi(argv[3]);
    i = std::atoi(argv[4]);


    vector<int> t = tabela(u, n);
    //for(int j = 0; j < n; j++) cout << t[j] << " ";
    //cout << endl;

    long long duration = 0;
    vector<int> temp;

    switch(a){
            case 1:
                for(int c = 0; c < i; c++){
                    auto start = high_resolution_clock::now();
                    temp = t;
                    insertion_sort(temp);
                    auto stop = high_resolution_clock::now();
                    duration += duration_cast<microseconds>(stop - start).count();
                }
                
                break;
            case 2:
                for(int c = 0; c < i; c++){
                    auto start = high_resolution_clock::now();
                    temp = t;
                    temp = mergesort(temp);
                    auto stop = high_resolution_clock::now();
                    duration += duration_cast<microseconds>(stop - start).count();
                }
                break;
            case 3:
                for(int c = 0; c < i; c++){
                    auto start = high_resolution_clock::now();
                    temp = t;
                    bogosort(temp);
                    auto stop = high_resolution_clock::now();
                    duration += duration_cast<microseconds>(stop - start).count();
                }
                break;
        }

    long long duration_per_izvajanje = (long long) duration / i;

    cout << duration_per_izvajanje << endl;
    //cout << duration << endl;
    return 0;
}