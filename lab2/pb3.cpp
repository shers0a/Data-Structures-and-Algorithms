#include <iostream>
#include <vector>
/*
Creati o lista dublu inlantuita (cu pointeri prev, next) cu doua operatii insert si extract care 
insereaza sau sterg aceeasi cheie (cu semn schimbat) la ambele 
capete de fiecare data: insert 1,2,3: ... -3 -2 -1 1 2 3 ...
*/

class Nod{
    public:
        Nod(int val = 0, Nod* next = nullptr, Nod* prev = nullptr) 
            : val(val), next(next), prev(prev){}

        void setVal(int val){
            this -> val = val;
        }

        void setNext(Nod* next){
            this -> next = next;
        }

        void setPrev(Nod* prev){
            this -> prev = prev;
        }

        int getVal() const {
            return val;
        }

        Nod* getNext() const{
            return next;
        }

        Nod* getPrev() const{
            return prev;
        }

    private:
        int val;
        Nod* next;
        Nod* prev;
};

class Lista{
    public:
        Lista(Nod* top = nullptr, Nod* bott = nullptr) : top(top), bott(bott) {}

        void insert(int x){
            Nod* st = new Nod();
            Nod* dr = new Nod();

            st -> setVal(-x);
            dr -> setVal(x);

            st -> setNext(top);
            st -> setPrev(nullptr);
            
            dr -> setNext(nullptr);
            dr -> setPrev(bott);

            if(!top){
                st -> setNext(dr);
                dr -> setNext(st);
            }
            else{
                top -> setPrev(st);
                bott -> setNext(dr);
            }

            top = st;
            bott = dr;
        }

        int extract(){
            int key = bott -> getVal();
            Nod* st = top;
            Nod* dr = bott;

            if(top -> getNext() == bott){
                top = bott = nullptr;
            }
            else{
                top = top -> getNext();
                bott = bott -> getPrev();
                top -> setPrev(nullptr);
                bott -> setNext(nullptr);
            }

            delete st;
            delete dr;
            return key;
        }

        bool empty() const { 
            return top == nullptr;
        }

        void afisare() const {
            for(Nod* p = top; p; p = p -> getNext())
                std::cout << p -> getVal() << " ";
            std::cout << "\n";
        }

        ~Lista(){
            while(!empty()) extract();
        }

    private:
        Nod* top;
        Nod* bott;
};

int main(){
    std::ios_base::sync_with_stdio(false);

    return 0;
}