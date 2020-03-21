/*
Autor: Sergio Hernandez Castillo
Fecha: 18/09/2019
Descripcion: Programa que implementa el arbol AVL
*/

#include <iostream>
#include <cctype>
#include <chrono>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

/**
 * An AVL tree node
 *     
*/
template <typename T>
class Node{
    public:
    T key;
    Node *left;
    Node *right;
    T height;
};//Close Node
/**
 * The class for the AVL Tree
 *     
*/
template <typename T>
class AVLtree{
    public:
    Node<T>* newNode(T key);
    Node<T>* rightRotate(Node<T> *y);
    Node<T>* leftRotate(Node<T> *x);
    Node<T>* insert(Node<T>* node, T key);
    Node<T>* minValueNode(Node<T>* node);
    Node<T>* deleteNode(Node<T>* root, T key);
    int height(Node<T> *N);
    T max(T a, T b);
    int getBalance(Node<T> *N);
    void search(Node<T> *root, T x);
};//Close AVLtree
    /**
     * A utility function to get height of the tree.
     * 
     * @param[in] Node with the height.
     * 
     * @returns The height of the node.
    */ 
template <typename T>
int AVLtree<T>::height(Node<T> *N){
    if (N == NULL){
        return 0;
    }//Close if

    return N->height;
}//Close height
    /**
     *  A utility function to get maximum of two integers.
     * 
     * @param[in] two values.
     * 
     * @returns Returns the maximum integer.
    */ 
template <typename T>
T AVLtree<T>::max(T a, T b){
    return (a > b)? a : b;
}//Close max
    /**
     * Helper function that allocates a new node with the 
     * given key and NULL left and right pointers..
     * @param[in] Key.
     * 
     * @returns Returns new node.
    */ 
template <typename T>
Node<T>* AVLtree<T>::newNode(T key){
    Node<T>* node = new Node<T>();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially
                      // added at leaf
    return(node);
}//Close newNode
    /**
     *  A utility function to right rotate subtree rooted
     *  with y. See the diagram given above.
     * @param[in] Node that points on y.
     * 
     * @returns Returns new root.
    */ 
template <typename T>
Node<T>* AVLtree<T>::rightRotate(Node<T> *y){
    Node<T> *x = y->left;
    Node<T> *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}//Close rightRotate
    /**
     * A utility function to left rotate subtree rooted with x.
     * See the diagram given above.
     * @param[in] Node that points on x.
     * 
     * @returns Returns new root.
    */ 
template <typename T>
Node<T>* AVLtree<T>::leftRotate(Node<T> *x){
    Node<T> *y = x->right;
    Node<T> *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}//Close leftRotate
    /**
     * Get Balance factor of node N
     * @param[in] Node N.
     * 
     * @returns Returns balance.
    */ 
template <typename T>
int AVLtree<T>::getBalance(Node<T> *N){
    if (N == NULL){
        return 0;
    }//Close if

    return height(N->left) - height(N->right);
}//Close getBalance
    /**
     * Insert and balance
     * @param[in] Node and key.
     * 
     * @returns Returns node or rotation or new node.
    */ 
template <typename T>
Node<T>* AVLtree<T>::insert(Node<T>* node, T key){
    /* 1. Perform the normal BST rotation */
    if (node == NULL){       
        return(newNode(key));
    }//Close if

    if (key < node->key){
        node->left = insert(node->left, key);
    }//Close if

    else if (key > node->key){
        node->right = insert(node->right, key);
    }//Close else if

    else { // Equal keys not allowed
        return node;
    }//Close else

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), height(node->right));

    /* 3. Get the balance factor of this
        ancestor node to check whether
        this node became unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced,
    // then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key){
        return rightRotate(node);
    }//Close if

    // Right Right Case
    if (balance < -1 && key > node->right->key){
        return leftRotate(node);
    }//Close if

    // Left Right Case
    if (balance > 1 && key > node->left->key){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }//Close if

    // Right Left Case
    if (balance < -1 && key < node->right->key){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }//Close if

    /* return the (unchanged) node pointer */
    return node;
}//Close insert
    /**
     * Given a non-empty binary search tree,
     * return the node with minimum key value
     * found in that tree.
     * @param[in] Node.
     * 
     * @returns Returns current.
    */ 
template <typename T>
Node<T>* AVLtree<T>::minValueNode(Node<T>* node){
    Node<T>* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL){
        current = current->left;
    }//Close while

    return current;
}//Close minValueNode
    /**
     * Recursive function to delete a node
     * with given key from subtree with
     * given root.
     * @param[in] root and key.
     * 
     * @returns It returns root of the modified subtree.
    */ 
template <typename T>
Node<T>* AVLtree<T>::deleteNode(Node<T>* root, T key){
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL){
        return root;
    }//Close if

    // If the key to be deleted is smaller
    // than the root's key, then it lies
    // in left subtree
    if (key < root->key){
        root->left = deleteNode(root->left, key);
    }//Close if

    // If the key to be deleted is greater
    // than the root's key, then it lies
    // in right subtree
    else if( key > root->key ){
        root->right = deleteNode(root->right, key);
    }//Close else if

    // if key is same as root's key, then
    // This is the node to be deleted
    else {
        // node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)){
            Node<T> *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL){
                temp = root;
                root = NULL;
            }//Close if

            else { // One child case
                *root = *temp; // Copy the contents of
                            // the non-empty child
                free(temp);
            }//Close else 
        }//Close if

        else {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            Node<T>* temp = minValueNode(root->right);

            // Copy the inorder successor's
            // data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }//Close else
    }//Close else

    // If the tree had only one node
    // then return
    if (root == NULL){
        return root;
    }//Close if 

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left), height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF
    // THIS NODE (to check whether this
    // node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced,
    // then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0){
        return rightRotate(root);
    }//Close if

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }//Close if

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0){
        return leftRotate(root);
    }//Close if

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }//Close if

    return root;
}//Close deleteNode
    /**
     * Search a certain node.
     * @param[in] root and element.
     * 
    */ 
template <typename T>
void AVLtree<T>::search(Node<T> *root, T x){
    if (root==NULL){
        cout << "\nNo se encontró el elemento" << endl;
    }//Close if 
    
    else {
        if (x < root->key){
            search(root->left, x);
        }//Close if 
        
        else {
            if (x>root->key){
                search(root->right, x);
            }//Close if
            
            else {
                cout << "\nSe ha encontrado el elemento." << endl;
            }//Close else
        }//Close else
    }//Close else 
}//Close search
    /**
     * Fills array with random numbers.
     * 
     * @param[in] array and size.
     * 
     * @returns array filled with random numbers.
    */ 
void scramble_array(int arr[],int size){
    for(int i = 0; i < size; i++){
        arr[i] = rand()%(size*10);
    }//Close for
}//Close scramble_array

//Does testing for insert, erase and search with a range of numbers
int main(){
    srand(time(NULL));
    AVLtree<int> t;
    Node<int> *root = NULL;
    int size1;
    int arr_size1;
    int arr_size2;
    int selection1;
    bool menu1 = true;

    cout << "Elige una cantidad de enteros: " << endl;
    cout << "\n1. 10 \n2. 100 \n3. 1,000 \n4. 10,000 \n5. 100,000 \n6. 1,000,000" << endl;

    while (menu1 == true){
        cin >> selection1;

        switch(selection1){
            case 1: size1 = 10;
                    menu1 = false;
                    break;
            case 2: size1 = 100;
                    menu1 = false;
                    break;
            case 3: size1 = 1000;
                    menu1 = false;
                    break;
            case 4: size1 = 10000;
                    menu1 = false;
                    break;
            case 5: size1 = 100000;
                    menu1 = false;
                    break;
            case 6: size1 = 1000000;
                    menu1 = false;
                    break;
            default: cout << "\nTienes que elegir una cantidad válida." << endl;
                    break;
        }//Close switch 
    }//Close while 

    int* arr1 = new int[size1];
    arr_size1 = size1;

    scramble_array(arr1, arr_size1);

    /*for (size_t i = 0; i < size1; i++){
        cout << "Arreglo 1: " << arr1[i] << endl;
    }//Close for*/

    auto start = high_resolution_clock::now();
    for (size_t i = 0; i < size1; i++){
        root = t.insert(root, arr1[i]);
    }//Close for
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nTiempo de ejecución de creación de árbol: " << duration.count() << " microsegundos." << endl;

    int* arr2 = new int[10];
    arr_size2 = 10;

    scramble_array(arr2, arr_size2);

    /*for (size_t i = 0; i < arr_size2; i++){
        cout << "Arreglo 2: " << arr2[i] << endl;
    }//Close for*/

    for (size_t i = 0; i < arr_size2; i++){
        auto start = high_resolution_clock::now();
        t.search(root, arr2[i]);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Tiempo de ejecución de busqueda " << i + 1 << ": " << duration.count() << " microsegundos." << endl;
    }//Close for

    for (size_t i = 0; i < arr_size2; i++){
        auto start = high_resolution_clock::now();
        root = t.deleteNode(root, arr2[i]);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);
        cout << "\nTiempo de ejecución de borrado " << i + 1 << ": " << duration.count() << " microsegundos." << endl;
    }//Close for

    delete [] arr1;
    delete [] arr2;

    return 0;
}//Close main
