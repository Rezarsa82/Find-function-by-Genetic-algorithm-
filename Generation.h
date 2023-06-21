#ifndef GENERATION_H_INCLUDED
#define GENERATION_H_INCLUDED

#include "BST.h"
#include <vector>

class Generation{
public:
    Generation(BST*, double, size_t, double[5], double[5], size_t);

    void target_setter(double x){ target = x; }
    double target_getter(){ return target; }
    int generate_random_int();
    void display_generation();
    void best_person();
    BST functionn();
    void set_possibilities();
    bool check_target();
    void main_setter();
    BST *random_father();
    BST *random_mother();
    void create_child();
    void set_children();
    void change_generation();

    ~Generation();
private:
    BST *children = new BST[10];
    BST *people = new BST[10];
    int index_best_person;
    double best_MSE = 0;
    double target;
    size_t generate_size;
    double ele[5];
    double var[5];
    vector<double> prob;
    size_t child_size = 0;
};







#endif // GENERATION_H_INCLUDED