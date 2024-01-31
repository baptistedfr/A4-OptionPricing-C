#pragma once

#include <stdio.h>
#include <vector>
#include <iostream>
#include "BinaryTree.cpp"
using namespace std;

template <class T>
class BinaryTree
{
private:
  
    std::vector< std::vector<T> > _tree;
public:
    int _depth;
    void setNode(int, int, T); //configure the value of a node in our tree
    T getNode(int, int); //return the value of a node in our tree
    void display(); //display the tree
    void setDepth(int); //configure the initial depth of the tree
   
};
template<class T>
T BinaryTree<T>::getNode(int a, int b) {
    return _tree[a][b]; //return this value
}


template<class T>
void BinaryTree<T>::setDepth(int N) {
    if (_depth == 0) { //if I have never initialized my tree
        _tree.resize(N + 1);
        for (int i = 0; i <= N; i++) { //create an empty vector for each depth of my tree
            std::vector<T> vector;
            for (int j = 0; j <= i; j++) {
                T object = T(); //create T objects for each line of my tree (on line 2 I have 2 elements)
                vector.push_back(object); //add to line vector
            }
            _tree[i] = vector; //my tree is a vector of vectors so here I attribute each vector to my large vector which is the tree
        }
        _depth = N;
    }
    else {
        if (N < _depth) { //if already defined and larger than the one I want, I just have to shorten my tree
            _tree.resize(N + 1);
        }
        else if (N > _depth) { //if I want a bigger tree
            for (int i = _depth + 1; i <= N; i++) { //create for missing rows of vectors
                std::vector<T> vector;
                for (int j = 0; j <= i; j++) {//add in each vector a number of elements T equal to their depth
                    T object = T();
                    vector.push_back(object);
                }
                _tree.push_back(vector);//my tree is a vector of vectors so here I add to my large vector which represents the tree the vector lines
            }
        }
        _depth = N;
    }
}

template<class T>
void BinaryTree<T>::setNode(int a, int b, T value) {
    _tree[a][b] = value; //assign a value to a certain depth a and a certain number b
}


template<class T>
void BinaryTree<T>::display() {
    // first display my tree in digital form (without branch representations /)
    for (int i = 0; i <= _depth; i++) {
        for (int j = 0; j <= i; j++) {
            std::cout << _tree[i][j] << " ";
        }
        std::cout << std::endl;
    }


    // representation of my tree with branches
    int count = (_depth + 1) * 2; // half of my tree for the first value
    //configuration of own display
    for (int i = 0; i <= _depth; i++) {
        for (int j = 0; j < count - 2 * i - 1; j++) {
            cout << " ";
        }

        for (int j = 0; j <= i; j++) {
            cout << _tree[i][j] << "   ";
        }
        cout << endl;

        if (i < _depth) {
            for (int k = 0; k < count - 2 * i - 2; k++) {
                cout << " ";
            }

            for (int j = 0; j <= i; j++) {
                cout << "/ \\ ";
            }
            cout << endl;
        }
    }
    cout << endl;
}
