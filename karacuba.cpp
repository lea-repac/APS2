#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//NA TAK NACIN SO ZAPISANA VSA STEVILA V TEM PROGRAMU
//prebere stevilo na vhodu in vsako stevko posebej zapise v vektor
//vrne "obrnjen" vektor, tako da je prvi element enica, desetica...
vector<int> number(){
    vector<int> n;

    char c;
    cin.get(c);
    while(c != '\n'){
        n.push_back(c - '0');
        cin.get(c);
    }
    
    reverse(n.begin(), n.end());
    return n;
}

//odstrani vodilne nicle
void pop_zeros(vector<int>& a){
    while (a.size() > 1 && a.back() == 0) a.pop_back();
}

//izpise faktorja v produktu v obliki: a * b 
void print_prod(vector<int>& a, vector<int>& b, int p){
    pop_zeros(a);
    pop_zeros(b);
    for(int i=0;i<4*p;i++) cout << " ";
    //izpise v obratnem vrstnem redu, ker ima vektor stevilo "od manjsih k vecjim mestom" zapisana stevila
    for(int i = a.size() - 1; i >= 0; i--) cout << a[i];
    cout << " * ";
    for(int i = b.size() - 1; i >= 0; i--) cout << b[i];;
    cout << "\n";
}

//izpise eno samo stevilo
void print_res(vector<int>& res, int p){
    pop_zeros(res);
    for(int i=0;i<4*p;i++) cout << " ";
    for(int i = res.size() - 1; i >= 0; i--) printf("%d", res[i]);
    cout << "\n";
}

//pisno zmnozi dve stevili in vrne produkt
vector<int> prod_normal(vector<int> a, vector<int> b){
    int na = (int)a.size();
    int nb = (int)b.size();

    //mnozenje stevil "dolzin" a in b nam da stevilo "dolzine" najvec a+b
    vector<int> prod(na+nb);
    for(int i = 0; i < na; i++){
        int over_prod = 0;
        for(int j = 0; j < nb; j++){
            int t = prod[i+j] + a[i]*b[j] + over_prod ;
            prod[i+j] = t % 10;
            over_prod = t / 10;
        }
        prod[i+nb] += over_prod;
    }
    
    return prod;
}

//pisno sesteje dve stevili in vrne vsoto
vector<int> sum(vector<int> a, vector<int> b){
    int na = (int)a.size();
    int nb = (int)b.size();
    int m = (int)max(na, nb);
    
    vector<int> sum;
    sum.reserve(m+1);
    //presezek cez 9
    int over_sum = 0;
    for(int i = 0; i < m; i++){
        //nastavimo sumande
        int sumand1 = (i < na) ? a[i] : 0; 
        int sumand2 = (i < nb) ? b[i] : 0;
        //sestejemo
        int t = sumand1 + sumand2 + over_sum;
        sum.push_back(t % 10);
        over_sum = t / 10;
    }
    
    if(over_sum) sum.push_back(over_sum);
    return sum;
}

//pisno odsteje dve stevili in vrne razliko
vector<int> sub(vector<int> a, vector<int> b){
    int na = (int)a.size();
    int nb = (int)b.size();

    //ce je a vektor, ki vsebuje (a1+a0)*(b1+b0) in b vsebuje (c0 + c2),
    //potem je stevilo v a praviloma vecje od stevila v b, zato odstevamo b od a
    vector<int> sub;
    sub.reserve(na);

    int over_sub = 0;
    for(int i = 0; i < na; i++){
        int subtracted = (i < nb) ? (b[i] + over_sub) : over_sub;
        int reduced = 0;
        if(a[i] < subtracted){
            reduced = a[i] + 10;
            over_sub = 1;
        } else {
            reduced = a[i];
            over_sub = 0;
        }
        sub.push_back(reduced - subtracted);
    }

    return sub;
}

vector<int> prod_karacuba(vector<int> a, vector<int> b, int r, int p){
    vector<int> n;
    print_prod(a, b, p);
    int na = (int)a.size();
    int nb = (int)b.size();

    if((na == 1 && a[0] == 0) || (nb == 1 && b[0] == 0)){
        n.push_back(0);
        print_res(n, p);
        return n;
    } else if(na <= r && nb <= r){
        n = prod_normal(a, b);
        print_res(n, p);
        return n;
    }

    //izracunamo max stevilo stevk in preverimo ali je sodo
    int m = max(na, nb);
    if(m % 2 == 1) m++;

    //napolnimo a in b z ustreznim stevilom nicel
    a.resize(m, 0);
    b.resize(m, 0);

    //konstruiramo dele stevil za racunanje s karacubo
    vector<int> a0 (a.begin(), a.begin() + m/2);
    vector<int> a1 (a.begin() + m/2, a.end());
    vector<int> b0 (b.begin(), b.begin() + m/2);
    vector<int> b1 (b.begin() + m/2, b.end());

    //c2 = a1*b1
    vector<int> c2 = prod_karacuba(a1, b1, r, p+1);
    //c0 = a0*b0
    vector<int> c0 = prod_karacuba(a0, b0, r, p+1);
    //c1 = (a0+a1)*(b0+b1) - c0 - c2
    vector<int> ab = prod_karacuba(sum(a0, a1), sum(b0, b1), r, p+1);
    vector<int> c1 = sub(ab, sum(c0, c2));

    c2.insert(c2.begin(), m, 0);
    c1.insert(c1.begin(), m/2, 0);

    n = sum(c2, sum(c1, c0));
    print_res(n, p);
    return n;
}

int main(){
    vector<int> a = number();
    vector<int> b = number();
    int r;
    cin >> r;

    //vector<int> res = prod_normal(a, b);
    //print_res(res);
    prod_karacuba(a, b, r, 0);
    return 0;
}