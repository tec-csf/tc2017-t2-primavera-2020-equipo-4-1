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

// An AVL tree node
template <typename T>
class Node{
    public:
    T key;
    Node *left;
    Node *right;
    T height;
};//Close Node

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
    void preOrder(Node<T> *N);
    void search(Node<T> *root, T x);
};//Close AVLtree

// A utility function to get height of the tree
template <typename T>
int AVLtree<T>::height(Node<T> *N){
    if (N == NULL){
        return 0;
    }//Close if

    return N->height;
}//Close height

// A utility function to get maximum of two integers
template <typename T>
T AVLtree<T>::max(T a, T b){
    return (a > b)? a : b;
}//Close max

/* Helper function that allocates a new node with the
given key and NULL left and right pointers. */
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

// A utility function to right rotate subtree rooted
// with y. See the diagram given above.
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

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
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

// Get Balance factor of node N
template <typename T>
int AVLtree<T>::getBalance(Node<T> *N){
    if (N == NULL){
        return 0;
    }//Close if

    return height(N->left) - height(N->right);
}//Close getBalance

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

/* Given a non-empty binary search tree,
return the node with minimum key value
found in that tree. Note that the entire
tree does not need to be searched. */
template <typename T>
Node<T>* AVLtree<T>::minValueNode(Node<T>* node){
    Node<T>* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL){
        current = current->left;
    }//Close while

    return current;
}//Close minValueNode

// Recursive function to delete a node
// with given key from subtree with
// given root. It returns root of the
// modified subtree.
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

template <typename T>
void AVLtree<T>::search(Node<T> *root, T x)
{
  if (root==NULL){
      cout<<"No se encontro el elemento\n"<<endl;
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
              cout << "Se ha encontrado el elemento.\n" << endl;
          }//Close else
      }//Close else
  }//Close else 
}//Close search

template <typename T>
void AVLtree<T>::preOrder(Node<T> *N)
{
    if(N != NULL)
    {
        cout << N->key << " ";
        preOrder(N->left);
        preOrder(N->right);
    }
}

void scramble_array(int arr[],int size)
{
    srand(time(NULL));

    for(int i = 0; i < size; i++)
    {
        arr[i] = rand()%(size*10);
    }//Close for
}//Close scramble_array

int main()
{
    AVLtree<int> t;
    Node<int> *root = NULL;
    int size = 100000, arr_size, menu_option = 0, nodeValue;
    bool menu = true;

    int* arr = new int[size];
    arr_size = size;

    scramble_array(arr, arr_size);

    for (size_t i = 0; i < size; i++)
    {
     root = t.insert(root, arr[i++]);
   }//Close for

    cout << "\n 1. Insertar \n 2. Borrar \n 3. Buscar \n 4. Imprimir ordenado ascendentemente \n 5. Imprimir ordenado descendientemente \n 6. Obtener altura de un nodo \n 7. Obtener profundidad de un nodo \n 8. Obtener nivel de un nodo \n 9. Salir" << endl;

    while (menu)
    {
        cout << "\n-----------------------------------------------";
        cout << "\nSeleccione una operacion: " << endl;
        cin >> menu_option;

        if (menu_option == 1)
        {
          cout << "\nOperacion seleccionada: Insertar" << endl;
          auto start = high_resolution_clock::now();

          cout << "Inserta un valor: " << endl;
          cin >> nodeValue;

          root = t.insert(root, nodeValue);

          auto stop = high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(stop - start);
          cout << "\nTiempo de ejecucion: " << duration.count() << " microsegundos." << endl;
        }//Close if

        else if (menu_option == 2)
        {
          cout << "\nOperacion seleccionada: Borrar" << endl;
          auto start = high_resolution_clock::now();

          cout << "Inserta un valor para borrar: " << endl;
          cin >> nodeValue;

          root = t.deleteNode(root, nodeValue);

          auto stop = high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(stop - start);
          cout << "\nTiempo de ejecucion: " << duration.count() << " microsegundos." << endl;
        }//Close if

        else if (menu_option == 3)
        {
          cout << "\nOperacion seleccionada: Buscar" << endl;
          auto start = high_resolution_clock::now();

          cout << "Inserta un valor para buscar: " << endl;
          cin >> nodeValue;

          t.search(root, nodeValue);

          auto stop = high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(stop - start);
          cout << "\nTiempo de ejecucion: " << duration.count() << " microsegundos." << endl;
        }//Close if

        else if (menu_option == 4)
        {
          cout << "\nOperacion seleccionada: Imprimir ordenado ascendentemente" << endl;
          auto start = high_resolution_clock::now();

          t.preOrder(root);

          auto stop = high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(stop - start);
          cout << "\nTiempo de ejecucion: " << duration.count() << " microsegundos." << endl;
        }//Close if

        else if (menu_option == 5)
        {
          cout << "\nOperacion seleccionada: Imprimir ordenado descendientemente" << endl;
          auto start = high_resolution_clock::now();
          //Imprimir
          auto stop = high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(stop - start);
          cout << "\nTiempo de ejecucion: " << duration.count() << " microsegundos." << endl;
        }//Close if

        else if (menu_option == 6)
        {
          cout << "\nOperacion seleccionada: Obtener altura de un nodo" << endl;
          auto start = high_resolution_clock::now();

          auto stop = high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(stop - start);
          cout << "\nTiempo de ejecucion: " << duration.count() << " microsegundos." << endl;
        }//Close if

        else if (menu_option == 7)
        {
          cout << "\nOperacion seleccionada: Obtener profundidad de un nodo" << endl;
          auto start = high_resolution_clock::now();
          //Profundidad
          auto stop = high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(stop - start);
          cout << "\nTiempo de ejecucion: " << duration.count() << " microsegundos." << endl;
        }//Close if

        else if (menu_option == 8)
        {
          cout << "\nOperacion seleccionada: Obtener nivel de un nodo" << endl;
          auto start = high_resolution_clock::now();
          //Nivel
          auto stop = high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(stop - start);
          cout << "\nTiempo de ejecucion: " << duration.count() << " microsegundos." << endl;
        }//Close if

        else if (menu_option == 9)
        {
          cout << "\nSaliendo." << endl;
          menu = false;
        }//Close if

        else
        {
          cout << "\nInput no es valido, seleccione una opcion valida." << endl;
        }//Close else
    }//Close while

    cout << "\n";

    delete [] arr;

    return 0;
}//Close main
