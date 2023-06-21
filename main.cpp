#include <iostream>
#include "BST.h"
#include "Generation.h"
#include <exception>

using namespace std;

int main(){
    /*
    BST b;                            // A test case for Tree and function
    b.make_BST();
    b.display_inorder();
    cout << b.root_getter()->element << endl;
    cout << b.value(1);
    */

    /*
    double elements[5] = {1, 2, 3, 4, 5};           // f(x) = x
    double variables[5] = {1, 4, 9, 16, 25};
    */

    /*
    double elements[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};         // f(x) =  x * x
    double variables[10] = {1, 4, 9, 16, 25, 36, 49, 64, 81, 100};
    */

    
    double elements[5] = {0, 1, 2, 3, 4};            // f(x) = x * x + sin(x)cos(x)
    double variables[5] = {0, 2.38, 1.49, 0.15, -0.41};
    

    try{
    BST *bst = new BST[11];
    Generation gen(bst, 10, 10, elements, variables, 10);
    for (int i = 0; i < 10; i++)
        bst[i].make_BST();
    gen.main_setter();
    do{
        gen.set_children();
        gen.change_generation();
    }while (!gen.check_target());
    BST best = gen.functionn();
    best.display_inorder();
    cout << "f(0)= " << best.value(0) << endl;
    cout << "f(1)= " << best.value(1) << endl;
    cout << "f(2)= " << best.value(2) << endl;
    cout << "f(3)= " << best.value(3) << endl;
    cout << "f(4)= " << best.value(4) << endl;
    }
    catch(exception *err){
        cout << err->what();
    }

    return 0;
}