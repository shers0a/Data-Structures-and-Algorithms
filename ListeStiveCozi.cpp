#include <iostream>
#include <stdexcept>

/*
    lista alocata secvential - cu array 
*/

class arrayStruct{
    public:
        arrayStruct(int siz, int arr[]){
            n = siz;
            a = new int[maxsize];
            
            for(int i = 0; i < siz; i++)
                a[i] = arr[i];
        }

        void afis(){
            for( int i = 0; i < n; i++ )
                std::cout << a[i] << " ";
            
            std::cout << "\n";
        }

        int search(int x){
            for( int i = 0; i < n; i++ ){
                if ( a[i] == x )
                    return i; 
            }

            throw std::invalid_argument("Value not found inside the List.");

        }

        void insert( int x, int poz ){
            for( int i = n - 1; i >= poz; i-- ){
                a[i + 1] = a[i];
            }

            a[poz] = x;
            n++;

            if( n == maxsize ){
                maxsize *= 2;
                int *aaa = new int [maxsize];
                
                for ( int i = 0; i < n; i++ ){
                    aaa[i] = a[i];
                }

                delete[] a;
                a = aaa;
            }
        }    
        
        void remove( int poz ){
            for( int i = poz; i < n - 1; i++ ) {
                a[i] = a[i + 1];
            }

            n--;
        }
        
    private:
        int *a;
        int n;
        int maxsize = 128;
};

class stivaCuVector{
    public:
        void push(int x){
            if( varf == 200 ){
                throw std::invalid_argument("OVERFLOW");
            }

            elemente[varf] = x;
            varf++;
        }

        int pop(){
            if(varf == 0){
                throw std::invalid_argument("UNDERFLOW");
            }

            varf--;
            return elemente[varf];
        }

        void afisare(){
            int i;
            std::cout << "[BAZA >";

            for( int i = 0; i < varf; i++)
                std::cout << elemente[i];
        
            std::cout << "[VARF >" << "\n";
        }
    private:
        int *elemente = new int [200];
        int varf = 0;
};

class nod{
    public:
        nod(int info = 0, nod* next = nullptr) : info(info), next(next){}

        int getInfo(){
            return info;
        }

        nod* getNext(){
            return next;
        }

        void setInfo(int info){
            this -> info = info;
        }
        
        void setNext(nod *next){
            this -> next = next;
        }

    private:
        int info;
        nod* next;
};

class lista {
public:
    lista() : primul_element(nullptr), ultimul_element(nullptr) {}

    ~lista() {
        while (primul_element != nullptr) {
            nod* aux = primul_element;
            primul_element = primul_element->getNext();
            delete aux;
        }
    }

    void insert_la_inceput(int x) {
        nod* nou = new nod(x, primul_element);
        primul_element = nou;

        if (ultimul_element == nullptr)   
            ultimul_element = nou;
    }

    void insert_la_final(int x) {
        nod* nou = new nod(x);

        if (ultimul_element == nullptr) {     
            primul_element = ultimul_element = nou;
        } else {
            ultimul_element->setNext(nou);
            ultimul_element = nou;
        }
    }

    void afisare() const {
        for (nod* p = primul_element; p != nullptr; p = p->getNext())
            std::cout << p->getInfo() << ' ';
        std::cout << '\n';
    }
    //de facut si stergerea
    void stergere(nod *de_sters){
        if (de_sters == nullptr || primul_element == nullptr){
            return;
        }
            
        if (primul_element == nullptr){
            ultimul_element = nullptr;
        }

        if( de_sters == primul_element ){
            nod *aux = primul_element;
            primul_element = primul_element -> getNext();

            delete aux;
            return;
        }

        if( de_sters == ultimul_element){
            nod *aux = ultimul_element;
            nod *p;
            for(p = primul_element; p -> getNext() != ultimul_element; p = p -> getNext());

            p -> setNext(nullptr); //se taie legatura cu nodul sters

            ultimul_element = p;
            delete aux;

            return;
        }
        for( nod *p = primul_element; p != nullptr; p = p -> getNext()){
            if( p -> getNext() == de_sters ){
                nod *aux = p -> getNext();
                p -> setNext( p -> getNext() -> getNext());

                delete aux;
                return;
            }
        }
    }

    private:
        nod* primul_element;
        nod* ultimul_element;
};

int main(int argc, char* argv[]){

    return 0;
}