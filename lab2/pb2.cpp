#include <iostream>
#include <vector>
#include <utility>


/*
    Implementati polinoame rare (reprezentate prin perechea coeficient, exponent) folosind o lista.
    Este o lista rara ordonata dupa exponent (presupunem ca se citesc in ordine exponentii, nu sortam).
    Exemplu: 7x^123 + 8x^22 + 15 ar putea fi (0,15)->(22,8)->(123,7)
    Calculati suma a doua polinoame prin interclasarea listelor ce retin termenii.
*/

//cu <vector>

void citirePolinomVector(std::vector<std::pair<int, int>>& v){
    int n, coeficient = 0;
    std::cin >> n;

    for( int i = 0; i < n; i++ ){
        int coef, exponent;
        std::cin >> coef >> exponent;

        v.push_back({exponent, coef});
    }
}

void afisarePolinomVector(const std::vector<std::pair<int, int>>& v){
    for( auto it : v ){
        std::cout << it.second <<"X^" << it.first << " + ";
    }

    std::cout << "\n";
}

std::vector<std::pair<int,int>> suma(const std::vector<std::pair<int, int>>& P, const std::vector<std::pair<int, int>>& Q){
    std::vector<std::pair<int, int>> suma;

    size_t i = 0, j = 0;

    while( (!P.empty()) && (!Q.empty()) ){
        if( P[i].first < Q[j].first ){
            suma.push_back(P[i++]);
        }
        else if( P[i].first > Q[j].first){
            suma.push_back(Q[j++]);
        }
        else{
            int c = P[i].second + Q[j].second;
            
            if(c != 0){
                suma.push_back({P[i].first, c});
            }

            i++, j++;
        }
    }

    while (i < P.size()){
        suma.push_back(P[i++]);
    }

    while (j < Q.size()){
        suma.push_back(Q[j++]);
    }   
}

int main(){
    std::ios_base::sync_with_stdio(false);

    std::vector<std::pair<int, int>> v, w, sum;

    citirePolinomVector(v);
    citirePolinomVector(w);

    sum = suma(v, w);

    afisarePolinomVector(sum);
    return 0;
}