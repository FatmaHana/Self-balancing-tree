#include <iostream>
#include "stablo.h"

using namespace std;

int main()
{


    /*Stablo<int> s;
    s.Insert(10);
    s.Insert(5);
    s.Insert(12);
    s.Insert(15);
    s.Insert(13);
    s.InOrderRek();*/


    /*Stablo<int> s;
    s.Insert(100);
    s.Insert(90);
    s.Insert(120);
    s.Insert(80);
    s.Insert(95);
    s.Insert(110);
    s.Insert(125);
    s.Insert(70);
    s.Insert(85);
    s.Insert(115);
    s.Insert(98);
    s.Erase(100);*/

    /*Stablo<int> s;
    s.Insert(50);
    s.Insert(30);
    s.Insert(70);
    s.Insert(25);
    s.Insert(40);
    s.Insert(65);
    s.Insert(75);
    s.Insert(20);
    s.Insert(37);
    s.Insert(80);
    s.Insert(45);
    s.Insert(68);
    s.Insert(90);
    s.Insert(15);
    s.Insert(32);
    s.Erase(25);*/


    Stablo<int> s;
    s.Insert(90);
    s.Insert(80);
    s.Insert(78);
    s.Insert(85);
    s.Insert(105);
    s.Insert(95);
    s.Insert(92);
    s.Insert(100);
    s.Insert(110);
    s.Insert(112);


    s.InOrderRek();

    Stablo<int> t(s);
    s.Erase(98);
    s.Erase(90);

    //t.InOrderRek();

    Stablo<int> k;
    k.Insert(2);
    k.Insert(5);
    k.Insert(3);

    k = s;

    k.Erase(115);

    //k.InOrderRek();

    Stablo<int> s1(move(s));

    //s1.InOrderRek();

    Stablo<int> s2;
    s2.Insert(95);
    s2.Insert(110);
    s2.Insert(125);
    s2.Insert(70);

    s2 = move(k);

    //s2.InOrderRek();



    return 0;
}
