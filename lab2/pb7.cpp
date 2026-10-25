#include <iostream>
#include <stack>
#include <vector>
#include <utility>

int di[] = {-1, 0, 1, 0};
int dj[] = {0, 1, 0, -1};

void citire_matrice(std::vector<std::vector<int>>& m){
    int n;
    std::cin >> n;

    m.resize(n);                          

    for( int i = 0; i < n; i++ ){
        for( int j = 0; j < n; j++ ){
            int x;
            std::cin >> x;
            m[i].push_back(x);
        }
    }
}

void afisare_matrice(const std::vector<std::vector<int>>& m){
    for( const auto& linie : m ){
        for( int x : linie )
            std::cout << x << " ";
        std::cout << "\n";
    }
}

void etichetare(std::vector<std::vector<int>>& m){
    std::stack<std::pair<int, int>> st;
    int n = m.size();
    int eticheta = 2;

    for( int i = 0; i < n; i++ ){
        for( int j = 0; j < n; j++ ){
            if( m[i][j] == 1 ){          
                st.push({i, j});
                m[i][j] = eticheta;       

                while( !st.empty() ){
                    int ci = st.top().first;
                    int cj = st.top().second;
                    st.pop();

                    for( int k = 0; k < 4; k++ ){
                        int ni = ci + di[k];
                        int nj = cj + dj[k];

                        
                        if( ni < 0 || ni >= n || nj < 0 || nj >= n )
                            continue;

                        if( m[ni][nj] == 1 ){
                            m[ni][nj] = eticheta; 
                            st.push({ni, nj});
                        }
                    }
                }

                eticheta++;              
            }
        }
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);

    std::vector<std::vector<int>> mat;

    citire_matrice(mat);             
    etichetare(mat);
    afisare_matrice(mat);
    
    return 0;
}