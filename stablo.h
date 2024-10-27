#ifndef STABLO_H
#define STABLO_H
#include <vector>

using namespace std;

template <typename T>
class Stablo {

    struct Cvor {
        T element;
        Cvor *rod, *ld, *dd;
        int broj_elemenata;
        int visina;
        Cvor(T element, Cvor *rod = nullptr, Cvor *ld = nullptr, Cvor *dd = nullptr, int br_el = 1, int visina = 0) :
                element(element), rod(rod), ld(ld), dd(dd), broj_elemenata(br_el), visina(visina) {}
    };

    Cvor* korijen;
    vector<T> SortiraniNiz(Cvor*);
    void InOrderRek(Cvor*, vector<T> &niz);
    Cvor* BalansiranoStabloRek(int indeks, int distanca, Cvor* rod, vector<T> &niz, T &flag);
    void InsertObicni(T element);
    void PodesiVisine(Cvor *pocetak, Cvor *kraj);
    void InOrderRekIspisi(Cvor* cvor);
    Cvor* InsertObicni(T element, Cvor* trenutni);
    Cvor* ObicniErase(Cvor *cvor);
    Cvor* sljedbenik(Cvor* cvor);
    Cvor* RekurzivnoStablo(Cvor *cvor, Cvor *roditelj);
    void RekurzivnoErase(Cvor *cvor);

    public:
    Stablo() : korijen(nullptr) {}
    Stablo(const Stablo<T>& kopija);
    Stablo(Stablo<T>&& rhs) : korijen(rhs.korijen) { rhs.korijen = nullptr; }
    Stablo<T>& operator=(const Stablo<T> &rhs);
    Stablo<T>& operator=(Stablo<T> &&rhs);
    void Insert(T element);
    void Erase(T element);
    Cvor* Find(T element);
    void InOrderRek() { InOrderRekIspisi(korijen); }
    ~Stablo();

};

#include "stablo.cpp"

#endif //STABLO_H
