#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

struct MatriceRara {
    int n, m;                                     
    std::vector<std::tuple<int, int, int>> elem; 
};

MatriceRara citMatRara(){
    MatriceRara A;
    std::cin >> A.n >> A.m;

    for( int i = 0; i < A.n * A.m; i++ ){
        int x;
        std::cin >> x;
        if( x ){
            A.elem.push_back({i / A.m, i % A.m, x});
        }
    }

    return A;
}

MatriceRara produs(const MatriceRara& A, const MatriceRara& B){
    MatriceRara C;
    C.n = A.n;
    C.m = B.m;

    std::vector<std::tuple<int, int, int>> temp;
    for( auto [la, ca, va] : A.elem )
        for( auto [lb, cb, vb] : B.elem )
            if( ca == lb )
                temp.push_back({la, cb, va * vb});

    std::sort(temp.begin(), temp.end());

    size_t i = 0;
    while( i < temp.size() ){
        int lin = std::get<0>(temp[i]);
        int col = std::get<1>(temp[i]);
        int suma = 0;

        size_t j = i;
        while( j < temp.size() &&
               std::get<0>(temp[j]) == lin &&
               std::get<1>(temp[j]) == col ){
            suma += std::get<2>(temp[j]);
            j++;
        }

        if( suma != 0 )
            C.elem.push_back({lin, col, suma});

        i = j;
    }

    return C;
}

void afisare(const MatriceRara& A){
    for( auto [lin, col, val] : A.elem )
        std::cout << "(" << lin << ", " << col << ", " << val << ")\n";
}

int main(){
    std::ios_base::sync_with_stdio(false);

    MatriceRara A = citMatRara();
    MatriceRara B = citMatRara();

    if( A.m != B.n ){
        std::cout << "Dimensiuni incompatibile\n";
        return 0;
    }

    afisare(produs(A, B));
    return 0;
}