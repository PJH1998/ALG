#include <iostream>
#include "BinarySearchTree.h"
using namespace std;
#include <thread>

int main()
{
    BinarySearchTree bst;

    bst.Insert(10);
    bst.Print();
    this_thread::sleep_for(1s);

    bst.Insert(30);
    bst.Print();
    this_thread::sleep_for(1s);

    bst.Delete(10);
    bst.Print();
    this_thread::sleep_for(1s);

    bst.Insert(20);
    bst.Print();
    this_thread::sleep_for(1s);

    bst.Insert(25);
    bst.Print();
    this_thread::sleep_for(1s);

    bst.Delete(20);
    bst.Print();
    this_thread::sleep_for(1s);

    bst.Insert(40);
    bst.Print();
    this_thread::sleep_for(1s);

    bst.Insert(50);
    bst.Print();
    this_thread::sleep_for(1s);


    //bst.Delete(10);

    

    return 0;
}