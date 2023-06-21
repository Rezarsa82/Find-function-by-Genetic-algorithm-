#include "Generation.h"

Generation::Generation(BST *b, double t, size_t n, double e[5], double v[5], size_t x){
    generate_size = x;
    people= b;
    target_setter(t);
    generate_size = n;
    for (int i = 0; i < 5; i++){
        ele[i] = e[i];
        var[i] = v[i];
    }
}

int Generation::generate_random_int(){
    uniform_int_distribution<> dis(0, 100);
    int rndnum = dis(gen);
    rndnum %= MAX_HEIGHT;
    return rndnum;
}

void Generation::display_generation(){
    for (int i = 0; i < generate_size; i++){
        cout << "Person[" << i << "] is: ";
        people[i].display_inorder(); 
        cout << " and the MSE is: " << people[i].MSE_getter() 
            << " and the possibility to choose is: " << people[i].possibility_getter() << endl;
    }
    best_person();
    cout << "The best MSE in this generation is for person " << index_best_person 
        << " with " << best_MSE << " MSE rate" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
}

void Generation::best_person(){
    best_MSE = people[0].MSE_getter();
    index_best_person = 0;
    for (int i = 0; i < generate_size; i++){
        if(people[i].MSE_getter() < best_MSE){
            best_MSE = people[i].MSE_getter();
            index_best_person = i;
        }
    }  
}

BST Generation::functionn(){
   best_person();
   return people[index_best_person]; 
}

void Generation::set_possibilities(){
    double total_MSE = 0;
    double this_MSE = 0;
    for (int i = 0; i < generate_size; i++)
        if(people[i].MSE_getter() < 10000)
            total_MSE += people[i].MSE_getter();
    for (int i = 0; i < generate_size; i++){
        if(people[i].MSE_getter() < 10000){
            this_MSE = 0;
            this_MSE = ((total_MSE - people[i].MSE_getter()) / total_MSE);
            people[i].possibility_setter(this_MSE);
        }
    }
}

bool Generation::check_target(){
    if(best_MSE <= target_getter())
            return true;
    return false;
}

void Generation::main_setter(){
    for (int i = 0; i < generate_size; i++)
        people[i].calculate_MSE(ele, var);
    set_possibilities();
    for (int i = 0; i < generate_size; i++)
        prob.insert(prob.end(), people[i].possibility_getter());
    display_generation();
} 

BST *Generation::random_father(){
    discrete_distribution<> dis(prob.begin(), prob.end());
    double p = dis(gen);
    return &people[int(p)];
}

BST *Generation::random_mother(){
    discrete_distribution<> dis(prob.begin(), prob.end());
    double p = dis(gen);
    return &people[int(p)];
}

void Generation::create_child(){
    BST *f = random_father();
    BST *m = random_mother();
    BST *temp = new BST;
    int parent_rand;
    for (int i = 0; i <= MAX_HEIGHT; i++){
        parent_rand = generate_random_int();
        if(parent_rand %2 == 0)
            temp->operand(f);
        else
            temp->operand(m);
    }
    temp->call_convertor(temp->root_getter());
    //cout << "father: ";
    //f->display_inorder();
    //cout << "mother: ";
    //m->display_inorder();
    children[child_size] = *temp;
    child_size++;    
}

void Generation::set_children(){
    for (int i = 0; i < generate_size; i++)
        create_child();
}

void Generation::change_generation(){
    for (int i = 0; i < generate_size; i++)
        people[i] = children[i];
    main_setter();
    child_size = 0;
}

Generation::~Generation(){
    delete[] people;
    delete[] children;
}