#include <iostream>
#include <vector>

/*
    Implementati un arbore binar de cautare reprezentat pe un array.

Folositi valori speciale (e.g -1) pentru a marca noduri non-prezente (NULL).

Folositi valori speciale (e.g -3 si -2) pentru a imbunatati performanta stergerii:

Stergerea se comporta la fel ca la arborele cu pointeri, mai putin cazul:

Cand un nod cu un singur fiu este sters, in loc sa caram toate nodurile din subarbore un nivel mai sus, nodul ia valoarea -3 sau -2 specificand ca arborele se continua pe acea directie, fara sa mai mutam nodurile.

Analizati ce cazuri speciale (arbori degenerati) pot sa apara din cauza introducerii valorilor speciale.
*/

class Node{
    public:
        Node(int info, Node* fiu_stang, Node* fiu_drept) :
        info(info), fiu_stang(fiu_stang), fiu_drept(fiu_drept){}

        int getInfo () const{
            return this -> info;
        }

        Node* getFiuStang() const {
            return this -> fiu_stang;
        }

        Node* getFiuDrept() const{
            return this -> fiu_drept;
        }

        void setInfo( int info ){
            this -> info = info;
        }

        void setFiuStang( Node* fiu_stang){
            this -> fiu_stang = fiu_stang;
        }

        void setFiuDrept( Node* fiu_drept){
            this -> fiu_drept = fiu_drept;
        }

    private:
        int info;
        Node* fiu_stang;
        Node* fiu_drept;

};

class BinaryTree{
    public:
        BinaryTree(std::vector<int>& nodes) : nodes(nodes){}

        void insertElement(int x){
            int i = 0;

            while(i < (int)nodes.size() && nodes[i] != -1){
                    if(nodes[i] == -2){
                        i = 2 * i + 1;
                    }
                    
                    else if(nodes[i] == -3){
                        i = 2 * i + 2;
                    }

                    else if(x < nodes[i]){
                        i = 2 * i + 1;
                    }
                    
                    else{
                        i = 2 * i + 2;
                    }
            }

            if( i >= (int)nodes.size()){
                nodes.resize(i + 1, -1);
            }

            nodes[i] = x;
        }

        bool search( int x ){
            int i = 0;

            while( i < (int)nodes.size() ){
                if(nodes[i] == -1){
                    return false;
                }

                else if(nodes[i] == x){
                    return true;
                }

                else if( nodes[i] == -2 ){
                    i = 2 * i + 1;
                }

                else if( nodes[i] == -3 ){
                    i = 2 * i + 2;
                }

                else if( x < nodes[i] ){
                    i = 2 * i + 1;
                }

                else{
                    i = 2 * i + 2;
                }
            }

            return false;
        }

        bool deleteElement( int x ){
            int i = 0;

            while( i < (int)nodes.size() && nodes[i] != -1 && nodes[i] != x ){
                if( nodes[i] == -2 ){
                    i = 2 * i + 1;
                }

                else if( nodes[i] == -3 ){
                    i = 2 * i + 2;
                }

                else if( x < nodes[i] ){
                    i = 2 * i + 1;
                }

                else{
                    i = 2 * i + 2;
                }
            }

            if( i >= (int)nodes.size() || nodes[i] != x ){
                return false;                       
            }

            bool areStang = exists(2 * i + 1);
            bool areDrept = exists(2 * i + 2);

            if( !areStang && !areDrept ){
                nodes[i] = -1;
                cleanup(i);
            }

            else if( areStang && !areDrept ){
                nodes[i] = -2;                     
            }

            else if( !areStang && areDrept ){
                nodes[i] = -3;                      
            }

            else{
                int j = 2 * i + 2;

                while( true ){
                    if( nodes[j] == -2 ){
                        j = 2 * j + 1;
                    }

                    else if( nodes[j] == -3 ){
                        j = 2 * j + 2;
                    }

                    else if( exists(2 * j + 1) ){
                        j = 2 * j + 1;
                    }

                    else{
                        break;                      
                    }
                }

                nodes[i] = nodes[j];

               
                if( exists(2 * j + 2) ){
                    nodes[j] = -3;
                }

                else{
                    nodes[j] = -1;
                    cleanup(j);
                }
            }

           
            while( !nodes.empty() && nodes.back() == -1 ){
                nodes.pop_back();
            }

            return true;
        }

        void print() const{
            int valori = 0, marcaje = 0;

            for( int i = 0; i < (int)nodes.size(); i++ ){
                if( nodes[i] == -1 ){
                    std::cout << ". ";
                }

                else{
                    std::cout << nodes[i] << " ";

                    if( nodes[i] == -2 || nodes[i] == -3 ){
                        marcaje++;
                    }

                    else{
                        valori++;
                    }
                }
            }

            std::cout << "\n  marime vector = " << nodes.size()
                      << ", valori reale = " << valori
                      << ", marcaje -2/-3 = " << marcaje
                      << ", pozitii goale = " << (int)nodes.size() - valori - marcaje << "\n";
        }

        
        int searchSteps( int x ) const{
            int i = 0, pasi = 0;

            while( i < (int)nodes.size() && nodes[i] != -1 ){
                pasi++;

                if( nodes[i] == x )       return pasi;
                else if( nodes[i] == -2 ) i = 2 * i + 1;
                else if( nodes[i] == -3 ) i = 2 * i + 2;
                else if( x < nodes[i] )   i = 2 * i + 1;
                else                      i = 2 * i + 2;
            }

            return pasi;
        }

    private:
        std::vector<int> nodes;

        bool exists( int i ) const{
            return i < (int)nodes.size() && nodes[i] != -1;
        }

        void cleanup( int i ){
            while( i > 0 ){
                int p = (i - 1) / 2;

                if( (nodes[p] == -2 || nodes[p] == -3) && !exists(2 * p + 1) && !exists(2 * p + 2) ){
                    nodes[p] = -1;
                    i = p;
                }

                else{
                    break;
                }
            }
        }
};


int main(){
    std::ios_base::sync_with_stdio(false);

    std::cout << "inserare sortata 10 20 30 40 50 \n";
    std::vector<int> v1;
    BinaryTree t1(v1);

    for( int x : {10, 20, 30, 40, 50} ){
        t1.insertElement(x);
    }

    t1.print();
    std::cout << "  5 valori, dar vectorul are 31 de pozitii.\n\n";

    std::cout << "lant de marcaje dupa stergeri\n";
    std::vector<int> v2;
    BinaryTree t2(v2);

    for( int x : {50, 40, 30, 20, 10} ){
        t2.insertElement(x);                
    }

    std::cout << "BEFORE:\n";
    t2.print();
    std::cout << "  search(10) face " << t2.searchSteps(10) << " pasi\n\n";

    for( int x : {40, 30, 20} ){
        t2.deleteElement(x);                 
    }

    std::cout << "AFTER stergere 40, 30, 20:\n";
    t2.print();
    std::cout << "  search(10) face tot " << t2.searchSteps(10) << "\n";
    std::cout << "  search(10) gaseste: " << (t2.search(10) ? "da" : "nu") << "\n\n";

    t2.deleteElement(10);
    std::cout << "AFTER stergere 10" << "\n";
    t2.print();

    return 0;
}