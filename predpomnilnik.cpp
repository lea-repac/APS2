#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>


using namespace std;

int main(){
    //p - max stevilo blokov, ki jih lahko predpomnilnik vsebuje
    //g - max stevilo blokov, ki jih lahko vsebuje glavni pomnilnik - aka koliko blokov sploh imamo
    //n - stevilo naslavljanj
    int p, g, n;

    cin >> p >> g >> n;

    //"dvodimenzionalna tabela", ki za vsak blok hrani stevila korakov, v katerem jih naslavljamo
    vector<priority_queue<int, vector<int>, greater<int>>> mem(g);
    vector<int> blocks(n); 
    for(int i = 0; i < n; i++){
        int block;
        cin >> block;
        blocks[i] = block;
        mem[block].push(i);
    }

    //vektor, ki predstavlja predpomnilnik
    unordered_set<int> cache;
    cache.reserve(p);

    //stevilo odstranjevanj
    int rem = 0;

    for(int i = 0; i < n; i++){
    
        int block = blocks[i];

        //ce je blok ze v pomnilniku, ga ta samo vrne
        if(cache.count(block)){
            mem[block].pop();
            continue;
        }

        //ce pomnilnik se ni zapolnjen, blok enostavno dodamo vanj
        if(cache.size() < p){
            cache.insert(block);
            mem[block].pop();
            continue;
        }

        //preverimo, kateri od blokov v predpomnilniku bo naslovljen cez najvec casa
        int latest = 0;
        int latest_time = 0;
        for(int x : cache){
            if(mem[x].empty()){
                latest = x;
                break;
            }
            int tren = mem[x].top();
            if(latest_time < tren){
                latest = x;
                latest_time = tren;
            }
        } 

        //odstranimo ta blok in dodamo novega, stevilo odstranjevanj pa povečamo za ena
        cache.erase(latest);
        cache.insert(block);
        rem++;
    
        //posodobimo naslednje naslavljanje trenutnega bloka
        mem[block].pop();
    }

    cout << rem << "\n";
    return 0;
}