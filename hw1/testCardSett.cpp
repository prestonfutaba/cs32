#include "CardSet.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    CardSet s;
    assert(s.size() == 0);
    s.add(50);
    s.add(1);
    s.add(1);

    s.print();

    cout << endl << s.size();

}