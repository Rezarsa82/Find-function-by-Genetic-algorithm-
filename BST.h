#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include <iostream>
#include <random>
#include <exception>
#include <math.h>
#include <cmath>
#define MAX_HEIGHT 10
#define MAX_NUMBER_OF_TREES 10

using namespace std;

static random_device rd;
static mt19937 gen(rd());

class Node{
private:
    Node *right;
    Node *left;
    string element;
    friend class BST;
};

class BST{
public:
    BST();

    void MSE_setter(double x){ MSE += x; }
    double MSE_getter() { return MSE; }
    void possibility_setter(double x){ possibility = x; }
    double possibility_getter(){return possibility; }
    Node* insert(const string, Node*);
    void insert(const string);
    int generate_random();
    void make_BST();
    void convert_BST_to_function(Node*);
    void call_convertor(Node*);
    double value(double);
    double calculate_function(Node*, double);
    void find_func(Node*);
    void display_inorder();
    void print_elements(Node *);
    Node *root_getter(){ return root; }
    void operand(BST*);
    void calculate_MSE(double[5], double[5]);

private:
    Node *root;
    static string two_operand[5];  
    static string single_operand[2];
    static string numbers[10];
    size_t height = 0;
    double function = 0;                                     
    double MSE = 0;
    double possibility = 0;
    
};
#endif // BST_H_INCLUDED