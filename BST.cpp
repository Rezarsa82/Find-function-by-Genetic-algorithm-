#include "BST.h"

string BST::two_operand[5] = {"-", "+", "+", "/", "."};
string BST::single_operand[2] = {"sin", "cos"};
string BST::numbers[10] = {"5", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

BST::BST(){
    root = nullptr;
}

Node* BST::insert(const string e, Node *temp){
    int i = generate_random();
    if(temp == nullptr){
        temp = new Node;
        temp->left = nullptr;
        temp->right = nullptr;
        temp->element = e;
    }
    else if(i % 2 == 0)
        temp->right = insert(e, temp->right);
    else if(i % 2 == 1)
        temp->left = insert(e, temp->left);
    return temp;
}

void BST::insert(const string e){
    root = insert(e, root);
}

int BST::generate_random(){
    uniform_int_distribution<> dis(0,100);
    int rndnum = dis(gen);
    return rndnum;
}

void BST::make_BST(){
    int k = generate_random();
    insert(two_operand[k % 5]);
    while (height <= MAX_HEIGHT){
        int i = generate_random();
        int j = generate_random();
        if(j % 6 != 0)
            insert(two_operand[i % 5]);
        else
            insert(single_operand[i % 2]);
        height++;
    }
    call_convertor(root);
}

void BST::convert_BST_to_function(Node *temp){
    int i = generate_random();
    int j = generate_random();
    if ((temp->element == "-") || (temp->element == "+") || (temp->element == "/") || (temp->element == ".")){
        if((temp->left != nullptr) && (temp->right != nullptr))
            return;
        if(temp->right == nullptr){
            Node *right = new Node;
            right->left = nullptr;
            right->right = nullptr;
            if(i % 4 == 0)
                right->element = "x";
            else
                right->element = numbers[7 * j % 10];
            temp->right = right;
        }
        if(temp->left == nullptr){
            Node *left = new Node;
            left->left = nullptr;
            left->right = nullptr;
            if(i % 4 == 0)
                left->element = "x";
            else
                left->element = numbers[j / 3 % 10];
            temp->left = left;
        }
    }
    if ((temp->element == "sin") || (temp->element == "cos")){
        if((temp->left == nullptr) && (temp->right == nullptr))
            if(i % 2 == 0){
                Node *right = new Node;
                right->left = nullptr;
                right->right = nullptr;
                if(i % 4 == 0)
                    right->element = numbers[j * 9 % 10];
                else
                    right->element = "x";
                temp->right = right;
            }
            else{
                Node *left = new Node;
                left->left = nullptr;
                left->right = nullptr;
                if(i % 4 == 0)
                    left->element = numbers[2 * j % 10];
                else
                    left->element = "x";
                temp->left = left;
            }
        if((temp->left != nullptr) && (temp->right != nullptr)){
            Node *node = new Node;
            node->left = nullptr;
            node->right = nullptr;
            if(i % 5 != 0){
                node->element = numbers[3 * j % 10];
                temp->left = node;
                temp->right = nullptr;
            }
            else{
                node->element = "x";
                temp->left = node;
                temp->right = nullptr;
            }
        }   
    }
}

void BST::call_convertor(Node *temp){
    convert_BST_to_function(temp);
    if(temp->left != nullptr)
        call_convertor(temp->left);
    if(temp->right != nullptr)
        call_convertor(temp->right);
}

double BST::value(double x){
    this->function = 0;
    return calculate_function(root, x);
}

double BST::calculate_function(Node *temp, double x){
    if(temp->element == "+")
        function = (calculate_function(temp->left, x) + calculate_function(temp->right, x));
    
    else if(temp->element == "-")
        function = (calculate_function(temp->left, x) - calculate_function(temp->right, x));
    
    else if(temp->element == ".")
        function = (calculate_function(temp->left, x) * calculate_function(temp->right, x));
    
    else if(temp->element == "/")
        function = (calculate_function(temp->left, x) / calculate_function(temp->right, x));

    else if( temp->element == "0" || temp->element == "1" || temp->element == "2" || temp->element == "3" || temp->element == "4" ||
        temp->element == "5" || temp->element == "6" || temp->element == "7" || temp->element == "8" || temp->element == "9" )
        return (stod(temp->element));
    
    else if(temp->element == "sin")
        return sin(x);

    else if(temp->element == "cos")
        return cos(x);
    
    else if(temp->element == "x")
        return x; 
    return function;
}

void BST::display_inorder(){
    print_elements(root);
    cout << endl;
    //cout << "root: " << root->element << endl;
} 

void BST::print_elements(Node *temp){
    if(temp == nullptr)
            return;
    print_elements(temp->left);
    cout << temp->element << " ";
    print_elements(temp->right);
}

void BST::operand(BST *t){
    int j = t->generate_random();
    int i = t->generate_random();
    int k = t->generate_random();
    if(i % 2 == 0)
        insert(two_operand[k % 5]);
    else
        insert(single_operand[k % 2]);
    if(j % 6 == 0)
        if(k % 4 == 0)
            insert(single_operand[k % 2]);
        else
            insert(two_operand[k % 5]);
}

void BST::calculate_MSE(double ele[5], double var[5]){
    double bst_varibale[5];
    double subt[5];
    for (int i = 0; i < 5; i++)
        bst_varibale[i] = this->value(ele[i]);
    //for (int i = 0; i < 5; i++)
        //cout << bst_varibale[i] << ", ";
    //cout << endl;
    for (int i = 0; i < 5; i++)
        subt[i] = abs(bst_varibale[i] - var[i]); 
    for (int i = 0; i < 5; i++)
        subt[i] *= subt[i];
    for (int i = 0; i < 5; i++)
        this->MSE_setter(subt[i]);
} 