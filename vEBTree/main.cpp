// vEBTree.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "vEBTree.h"
#include <iostream>
using namespace std;

int main()
{
    int iInput;
    vEBTree tree(16);
    tree.insert(1,1);
    tree.insert(3, 3);
    tree.insert(5, 5);
    tree.insert(9, 9);
    tree.insert(7, 7);
    tree.insert(11, 11);
    tree.insert(15, 15);
    tree.insert(12, 12);

    if (tree.contains(15)) {
        cout << "The tree contains 15" << endl;
    }
    if (tree.contains(9)) {
        cout << "The tree contains 9" << endl;
    }
    if (tree.contains(1)) {
        cout << "The tree contains 1" << endl;
    }
    if (tree.contains(7)) {
        cout << "The tree contains 7" << endl;
    }
    if (!tree.contains(2)) {
        cout << "The tree not contains 2" << endl;
    }
    cout << "the succesor of 3 is: " << tree.successor(3) << " which has value: " << tree.getValue(tree.successor(3)) << endl;

    tree.remove(7);
    if (!tree.contains(7)) {
        cout << "The tree no contains 7" << endl;
    }
    return 0;
}
