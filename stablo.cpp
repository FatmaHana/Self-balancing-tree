#ifndef STABLO_CPP
#define STABLO_CPP
#include "stablo.h"
#include <vector>

#include <iostream>
using namespace std;

template <typename T>
typename Stablo<T>::Cvor* Stablo<T>::InsertObicni(T element, Cvor* trenutni) {
    Cvor *prethodni = trenutni->rod;
    while(trenutni != nullptr) {
        prethodni = trenutni;
        trenutni->broj_elemenata++;
        if(element < trenutni->element)
            trenutni = trenutni->ld;
        else trenutni = trenutni->dd;
    }

    Cvor *novi = new Cvor(element, prethodni);
    if(element < prethodni->element)
        prethodni->ld = novi;
    else prethodni->dd = novi;
    return novi;
}

template <typename T>
void Stablo<T>::Insert(T element) {

    if(korijen == nullptr) {
        korijen = new Cvor(element);
        return;
    }

    if(Find(element) != nullptr) return;

    Cvor *trenutni = korijen;
    while(trenutni != nullptr) {
        if(element > trenutni->element) {
            if(trenutni->visina > 2) {
                if(trenutni->dd->broj_elemenata + 1 >= 2*trenutni->ld->broj_elemenata) {
                    InsertObicni(element, trenutni);
                    vector<T> niz = SortiraniNiz(trenutni);
                    T flag = niz[niz.size()/2];
                    Cvor *balansirano = BalansiranoStabloRek(niz.size()/2, niz.size()/2, trenutni->rod, niz, flag);
                    if(trenutni == korijen)
                        korijen = balansirano;
                    else if(trenutni == trenutni->rod->ld)
                        trenutni->rod->ld = balansirano;
                    else
                        trenutni->rod->dd = balansirano;
                    RekurzivnoErase(trenutni);
                    trenutni = balansirano;
                    break;
                }
                else {
                    trenutni->broj_elemenata++;
                    trenutni = trenutni->dd;
                }
            }
            else if(trenutni->visina < 2) {
                trenutni = InsertObicni(element, trenutni);
                break;
            }

            else {
                Cvor *novi = InsertObicni(element, trenutni);
                PodesiVisine(novi, trenutni);
                if(trenutni->visina == 3) {
                    if(trenutni->ld == nullptr || trenutni->dd->broj_elemenata >= 2*trenutni->ld->broj_elemenata) {
                        vector<T> niz = SortiraniNiz(trenutni);
                        T flag = niz[niz.size()/2];
                        Cvor *balansirano = BalansiranoStabloRek(niz.size()/2, niz.size()/2, trenutni->rod, niz, flag);
                        if(trenutni == korijen)
                            korijen = balansirano;
                        else if(trenutni == trenutni->rod->ld)
                            trenutni->rod->ld = balansirano;
                        else
                            trenutni->rod->dd = balansirano;
                        RekurzivnoErase(trenutni);
                        trenutni = balansirano;
                        break;
                    }
                }
                break;
            }

        }
        else {
            if(trenutni->visina > 2) {
                if(trenutni->ld->broj_elemenata + 1 >= 2*trenutni->dd->broj_elemenata) {
                    InsertObicni(element, trenutni);
                    vector<T> niz = SortiraniNiz(trenutni);
                    T flag = niz[niz.size()/2];
                    Cvor *balansirano = BalansiranoStabloRek(niz.size()/2, niz.size()/2, trenutni->rod, niz, flag);
                    if(trenutni == korijen)
                        korijen = balansirano;
                    else if(trenutni == trenutni->rod->ld)
                        trenutni->rod->ld = balansirano;
                    else
                        trenutni->rod->dd = balansirano;
                    RekurzivnoErase(trenutni);
                    trenutni = balansirano;
                    break;
                }
                else {
                    trenutni->broj_elemenata++;
                    trenutni = trenutni->ld;
                }
            }
            else if(trenutni->visina < 2) {
                trenutni = InsertObicni(element, trenutni);
                break;
            }

            else {
                Cvor *novi = InsertObicni(element, trenutni);
                PodesiVisine(novi, trenutni);
                if(trenutni->visina == 3) {
                    if(trenutni->dd == nullptr || trenutni->ld->broj_elemenata >= 2*trenutni->dd->broj_elemenata) { // broj_elemenata smo vec podesili
                        vector<T> niz = SortiraniNiz(trenutni);
                        T flag = niz[niz.size()/2];
                        Cvor *balansirano = BalansiranoStabloRek(niz.size()/2, niz.size()/2, trenutni->rod, niz, flag);
                        if(trenutni == korijen)
                            korijen = balansirano;
                        else if(trenutni == trenutni->rod->ld)
                            trenutni->rod->ld = balansirano;
                        else
                            trenutni->rod->dd = balansirano;
                        RekurzivnoErase(trenutni);
                        trenutni = balansirano;
                        break;
                    }
                }
                break;
            }
        }
    }

    PodesiVisine(trenutni, korijen);
}

template <typename T>
typename Stablo<T>::Cvor* Stablo<T>::ObicniErase(Cvor* trenutni) {

    Cvor *cvor = korijen;
    while(cvor != trenutni) {
        cvor->broj_elemenata--;
        if(trenutni->element > cvor->element) cvor = cvor->dd;
        else cvor = cvor->ld;
    }

    Cvor *za_vracati = nullptr;
    //ako je list
    if(trenutni->ld == nullptr && trenutni->dd == nullptr) {
        if(trenutni == korijen) {
            korijen = nullptr;
        }
        else {
            if(trenutni == trenutni->rod->ld)
                trenutni->rod->ld = nullptr;
            else trenutni->rod->dd = nullptr;
            if(trenutni->rod->ld == nullptr && trenutni->rod->dd == nullptr)
                trenutni->rod->visina = 0;
            else if(trenutni->rod->ld != nullptr)
                trenutni->rod->visina = trenutni->rod->ld->visina;
            else trenutni->rod->visina = trenutni->rod->dd->visina;

            za_vracati = trenutni->rod;
        }
    }
    //ako nema desnog djeteta
    else if(trenutni->dd == nullptr) {
        Cvor* dijete = trenutni->ld;
        dijete->rod = trenutni->rod;
        if(trenutni == korijen) {
            korijen = dijete;
        }
        else {
            if(trenutni->rod->ld == trenutni)
                trenutni->rod->ld = dijete;
            else trenutni->rod->dd = dijete;
            za_vracati = dijete;
        }
    }
    //ako nema lijevog djeteta
    else if(trenutni->ld == nullptr) {
        Cvor* dijete = trenutni->dd;
        dijete->rod = trenutni->rod;
        if(trenutni == korijen) {
            korijen = dijete;
        }
        else {
            if(trenutni->rod->ld == trenutni)
                trenutni->rod->ld = dijete;
            else trenutni->rod->dd = dijete;
            za_vracati = dijete;
        }
    }
    //ako ima oba djeteta
    else {
        Cvor* target = sljedbenik(trenutni);
        if(target == target->rod->ld) {
            if(target->rod->dd != nullptr)
                target->rod->visina = max(target->visina, target->rod->dd->visina) + 1;
            else target->rod->visina = target->visina;
            target->rod->ld = target->dd;

            Cvor *za_mijenjati = target->rod;
            while(za_mijenjati != trenutni) {
                za_mijenjati->broj_elemenata--;
                za_mijenjati = za_mijenjati->rod;
            }
        }
        else
            target->rod->dd = target->dd;

        if(target->dd != nullptr)
        target->dd->rod = target->rod;

        target->ld = trenutni->ld;
        target->dd = trenutni->dd;
        target->rod = trenutni->rod;
        trenutni->ld->rod = target;
        trenutni->dd->rod = target;
        if(korijen == trenutni) {
            korijen = target;
        }
        else {
            if(trenutni == trenutni->rod->ld)
                trenutni->rod->ld = target;
            else trenutni->rod->dd = target;
        }

        if(target->dd != nullptr) {
            target->visina = max(target->ld->visina, target->dd->visina) + 1;
            target->broj_elemenata = target->ld->broj_elemenata + target->dd->broj_elemenata + 1;
        }
        else {
            target->visina = target->ld->visina + 1;
            target->broj_elemenata = target->ld->broj_elemenata + 1;
        }
        za_vracati = target;
    }

    delete trenutni;
    return za_vracati;
}

template <typename T>
void Stablo<T>::Erase(T element) {

    Cvor* target = Find(element);
    if(target == nullptr) return;

    Cvor *zamjena = ObicniErase(target);
    PodesiVisine(zamjena, korijen);
    Cvor *trenutni = korijen;
    while(trenutni != nullptr) {
        if(trenutni->visina < 3)
            break;
        if(zamjena->element < trenutni->element) {
            if(2*trenutni->ld->broj_elemenata <= trenutni->dd->broj_elemenata) {
                vector<T> niz = SortiraniNiz(trenutni);
                T flag = niz[niz.size()/2];
                Cvor *balansirano = BalansiranoStabloRek(niz.size()/2, niz.size()/2, trenutni->rod, niz, flag);
                if(trenutni == korijen)
                    korijen = balansirano;
                else if(trenutni == trenutni->rod->ld)
                    trenutni->rod->ld = balansirano;
                else
                    trenutni->rod->dd = balansirano;
                RekurzivnoErase(trenutni);
                trenutni = balansirano;
                break;
            }
            trenutni = trenutni->ld;
        }
        else if(zamjena->element > trenutni->element) {
            if(trenutni->ld->broj_elemenata >= 2*trenutni->dd->broj_elemenata) {
                vector<T> niz = SortiraniNiz(trenutni);
                T flag = niz[niz.size()/2];
                Cvor *balansirano = BalansiranoStabloRek(niz.size()/2, niz.size()/2, trenutni->rod, niz, flag);
                if(trenutni == korijen)
                    korijen = balansirano;
                else if(trenutni == trenutni->rod->ld)
                    trenutni->rod->ld = balansirano;
                else
                    trenutni->rod->dd = balansirano;
                RekurzivnoErase(trenutni);
                trenutni = balansirano;
                break;
            }
            trenutni = trenutni->dd;
        }
        else {
            if(trenutni->ld->broj_elemenata >= 2*trenutni->dd->broj_elemenata) {
                vector<T> niz = SortiraniNiz(trenutni);
                T flag = niz[niz.size()/2];
                Cvor *balansirano = BalansiranoStabloRek(niz.size()/2, niz.size()/2, trenutni->rod, niz, flag);
                if(trenutni == korijen)
                    korijen = balansirano;
                else if(trenutni == trenutni->rod->ld)
                    trenutni->rod->ld = balansirano;
                else
                    trenutni->rod->dd = balansirano;
                RekurzivnoErase(trenutni);
                trenutni = balansirano;
                break;
            }
            trenutni = trenutni->dd;
            while(trenutni != nullptr && trenutni->visina > 2) {
                if(trenutni->dd != nullptr && trenutni->ld == nullptr || 2*trenutni->ld->broj_elemenata <= trenutni->dd->broj_elemenata) {
                    vector<T> niz = SortiraniNiz(trenutni);
                    T flag = niz[niz.size()/2];
                    Cvor *balansirano = BalansiranoStabloRek(niz.size()/2, niz.size()/2, trenutni->rod, niz, flag);
                    if(trenutni == korijen)
                        korijen = balansirano;
                    else if(trenutni == trenutni->rod->ld)
                        trenutni->rod->ld = balansirano;
                    else
                        trenutni->rod->dd = balansirano;
                    RekurzivnoErase(trenutni);
                    trenutni = balansirano;
                    break;
                }
                trenutni = trenutni->ld;
            }
        }
    }

    PodesiVisine(trenutni, korijen);
}

template <typename T>
typename Stablo<T>::Cvor* Stablo<T>::Find(T element) {
    Cvor *trenutni = korijen;
    while(trenutni != nullptr) {
        if(element > trenutni->element) trenutni = trenutni->dd;
        else if(element < trenutni->element) trenutni = trenutni->ld;
        else return trenutni;
    }
    return nullptr;
}

template <typename T>
typename Stablo<T>::Cvor* Stablo<T>::BalansiranoStabloRek(int indeks, int distanca, Cvor* rod, vector<T> &niz, T &flag) {
    Cvor* novi = new Cvor(niz[indeks], rod);
    niz[indeks] = flag;
    if(indeks-(distanca+1)/2 > -1 && niz[indeks-(distanca+1)/2] != flag){
        novi->ld = BalansiranoStabloRek(indeks-(distanca+1)/2, (distanca+1)/2, novi, niz, flag);
        niz[indeks-(distanca+1)/2] = flag;
        novi->visina = novi->ld->visina + 1;
        novi->broj_elemenata += novi->ld->broj_elemenata;

    }
    if(indeks+(distanca+1)/2 < niz.size() && niz[indeks+(distanca+1)/2] != flag){
        novi->dd = BalansiranoStabloRek(indeks+(distanca+1)/2, (distanca+1)/2, novi, niz, flag);
        niz[indeks+(distanca+1)/2] = flag;
        novi->visina = max(novi->visina, novi->dd->visina + 1);
        novi->broj_elemenata += novi->dd->broj_elemenata;
    }
    if(indeks+(distanca+1)/2 >= niz.size() && niz[niz.size()-1] != flag) {
        novi->dd = BalansiranoStabloRek(niz.size()-1, (distanca+1)/2, novi, niz, flag);
        niz[niz.size()-1] = flag;
        novi->visina = max(novi->visina, novi->dd->visina + 1);
        novi->broj_elemenata += novi->dd->broj_elemenata;
    }

    return novi;
}

template <typename T>
vector<T> Stablo<T>::SortiraniNiz(Cvor* cvor) {
    vector<T> niz;
    InOrderRek(cvor, niz);
    return niz;
}

template <typename T>
void Stablo<T>::InOrderRek(Cvor* cvor, vector<T> &niz){
    if(cvor == nullptr) return;
    InOrderRek(cvor->ld, niz);
    niz.push_back(cvor->element);
    InOrderRek(cvor->dd, niz);
}

template <typename T>
void Stablo<T>::InOrderRekIspisi(Cvor* cvor){
    if(cvor == nullptr) return;
    InOrderRekIspisi(cvor->ld);
    cout << "ELEMENT: " << cvor->element << endl;
    cout << "VISINA: " <<cvor->visina << endl;
    cout << "BROJ ELEMENATA: " <<cvor->broj_elemenata << endl;
    if(cvor->ld != nullptr) cout << "LD: " << cvor->ld->element;
    if(cvor->dd != nullptr) cout << " DD: " <<cvor->dd->element;
    if(cvor->rod != nullptr) cout << " ROD: " << cvor->rod->element;
    cout << endl << endl;
    InOrderRekIspisi(cvor->dd);
}

template <typename T>
void Stablo<T>::PodesiVisine(Cvor *pocetak, Cvor *kraj) {
    Cvor *trenutni = pocetak;
    while(trenutni != kraj) {
        int stara_visina = trenutni->rod->visina;
        if(trenutni->rod->ld != nullptr && trenutni->rod->dd != nullptr){
            trenutni->rod->visina = max(trenutni->rod->ld->visina, trenutni->rod->dd->visina) + 1;
        }
        //nema desnog djeteta
        else if(trenutni->rod->ld != nullptr)
            trenutni->rod->visina = trenutni->rod->ld->visina + 1;
        //nema lijevog djeteta
        else if(trenutni->rod->dd != nullptr)
            trenutni->rod->visina = trenutni->rod->dd->visina + 1;
        trenutni = trenutni->rod;
        if(trenutni->visina == stara_visina) return;
    }
    return;
}

template <typename T>
typename Stablo<T>::Cvor* Stablo<T>::sljedbenik(Cvor* cvor) {
  if(cvor->dd != nullptr) {
    Cvor* target = cvor->dd;
    while(target->ld != nullptr)
        target = target->ld;
    return target;
  }
  else {
    Cvor *target = cvor;
    while(target->rod != nullptr && target->rod->dd == target)
        target = target->rod;
    return target->rod;
  }
}

template <typename T>
typename Stablo<T>::Cvor* Stablo<T>::RekurzivnoStablo(Cvor *cvor, Cvor *roditelj) {
    if(cvor == nullptr) return nullptr;
    Cvor *novi = new Cvor(cvor->element, roditelj, nullptr, nullptr, cvor->broj_elemenata, cvor->visina);
    novi->ld = RekurzivnoStablo(cvor->ld, novi);
    novi->dd = RekurzivnoStablo(cvor->dd, novi);
    return novi;
}

template <typename T>
void Stablo<T>::RekurzivnoErase(Cvor *cvor) {
    if(cvor == nullptr) return;
    RekurzivnoErase(cvor->ld);
    RekurzivnoErase(cvor->dd);
    delete cvor;
}

template <typename T>
Stablo<T>::Stablo(const Stablo<T> &kopija) {
    this->korijen = RekurzivnoStablo(kopija.korijen, nullptr);
}

template <typename T>
Stablo<T>& Stablo<T>::operator=(const Stablo<T> &rhs) {

    if(this->korijen == rhs.korijen)
        return *this;

    RekurzivnoErase(this->korijen);
    this->korijen = RekurzivnoStablo(rhs.korijen, nullptr);

    return *this;
}

template <typename T>
Stablo<T>& Stablo<T>::operator=(Stablo<T>&& rhs) {

    if(this->korijen == rhs.korijen)
        return *this;

    RekurzivnoErase(this->korijen);
    korijen = rhs.korijen;
    rhs.korijen = nullptr;

    return *this;
}

template <typename T>
Stablo<T>::~Stablo() {
    RekurzivnoErase(korijen);
}


#endif //STABLO_CPP
