#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
//funkcija izpise vsebino tabele tabel
void print_tab(vector<vector<int>>& t){
    cout << "[";
    for(int i = 0; i < t.size(); i++){
        cout << "[";
        if(!t[i].empty()){
            for(int j = 0; j < t[i].size() - 1; j++) cout << t[i][j] << ", ";
            cout << t[i].back();
        }
        if(i != t.size()-1) cout << "], ";
        else cout << "]";
    }
    cout << "]" << "\n";
}

vector<int> merge(vector<int> a, vector<int> b){
    vector<int> c;
    int i = 0, j = 0;
    while (i<a.size() || j<b.size()) {
        if (i<a.size() && j<b.size()) {
            if (a[i]<=b[j]) c.push_back(a[i++]);
            else c.push_back(b[j++]);
        } else if (i<a.size()) c.push_back(a[i++]);
        else c.push_back(b[j++]);
    }
    return c;

}

void add(vector<vector<int>>& t, int x, int c){
    //stevilo bitov v stevilu elementov = stevilo tabel v tabeli
    int n = floor((int)log2(c)) + 1;

    vector<int> buffer = {x};
     if ((int)t.size() < n) t.resize(n);

    for(int i = 0; i < n; i++){
        int bit = (c >> i) & 1;

        if(bit == 0){
            if(!t[i].empty()){
                buffer = merge(buffer, t[i]);
                t[i].clear();
            }
        } else {
            t[i] = buffer;
            break;
        }
    }
    
    return;
}


//vrne indeks elementa, ce se ta nahaja v tabeli
int bisection(vector<int>& t, int x) {
    int lo = -1;
    int hi = t.size();
    while (hi - lo > 1) {
        int i = (lo + hi) / 2;
        if(i == lo) return hi;
        if (t[i] < x) lo = i;
        else hi = i;
    }
    return hi;
}


//funkcija izpise i oz. -i-1, kjer je i indeks, na katerem se nahaja stevilo x
//oz. na katerem bi se stevilo x nahajalo, ce bi bilo v tabeli tabel
int index(vector<vector<int>>& t, int x){
    if(t.empty()) return -1;

    int ind = 0;
    bool is_element = false;
    for(int i = 0; i < t.size(); i++){
        if(t[i].empty()) continue;
        int ind_ti = bisection(t[i], x);
        ind += ind_ti;
        if(t[i][ind_ti] == x) is_element = true;
    }
    if(is_element) return ind;
    return (0 - ind - 1);
}


int main(){
    //stevilo ukazov
    int u;
    cin >> u;

    vector<vector<int>> tab;

    //steje stvilo elementov, ki jih vsebuje tabela tabel - je binarno stevilo elementov, zapisano v LSM
    int counter = 0;

    for(int i = 0; i < u; i++){
        //preberemo in preverimo ukaz
        char instruction;
        cin >> instruction;

        //pri ukazu za izpis ni se stevila, zato pri ukazu i samo izpisemo in nadaljujemo z zanko
        if(instruction == 'i'){
            print_tab(tab);
            continue;
        }

        int number;
        cin >> number;

        if(instruction == '+'){
            add(tab, number, ++counter);
        } else cout << index(tab, number) << "\n";
    }

    return 0;
}