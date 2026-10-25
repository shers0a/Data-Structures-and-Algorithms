#include <iostream>
#include <vector>

//cu <vector>

/*
    Sortati o lista folosind selectia minimului.
    Se poate implementa in mai multe feluri, de exemplu:
    La fiecare pas caut minimul, il extrag din lista si il inserez in alta lista.
*/

void citireVector(std::vector<int>& vector){
    int n, x;

    std::cin >> n;
    for( int i = 0; i < n; i++ ){
        std::cin >> x;

        vector.push_back(x);
    }
}   

void afisareVector(const std::vector<int>& vector){
    for( int v : vector ){
        std::cout << v << " ";
    }

    std::cout << "\n";
}

struct elemMIN{
    int val, pos;
};

elemMIN min_element(const std::vector<int>& v){
    elemMIN min = {v[0], 0};

    for( int i = 1; i < v.size(); i++ ){
        if( v[i] < min.val ){
            min.val = v[i];
            min.pos = i;
        }
    }

    return min;
}

std::vector<int> sortareVector(std::vector<int>& de_sortat){
    std::vector<int> result;
    
    while(!de_sortat.empty()){
        auto minim = min_element(de_sortat);
        result.push_back(minim.val);

        de_sortat.erase(de_sortat.begin() + minim.pos);
    }

    return result;
}
int main(){
    std::ios_base::sync_with_stdio(false);
    std::vector<int> v, aux;

    citireVector(v);
    aux = sortareVector(v);

    afisareVector(aux);
    return 0;
}