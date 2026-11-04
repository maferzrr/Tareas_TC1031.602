/*
 * bst.h
 *
 *  Created on: 12/10/2026
 *      Autor: María Fernanda Zetina Reyes
 *      Matrícula: A01709799
 */

#ifndef BST_H_
#define BST_H_

#include <string>
#include <sstream>
#include <iostream>
#include <queue>

template <class T> class BST;

template <class T>
class Node {
private:
    T value;
    Node *left, *right;

public:
    Node(T);
    Node(T, Node<T>*, Node<T>*);
    void add(T);
    bool find(T);
    void removeChilds();
    
    void inorder(std::stringstream&) const;
    void preorder(std::stringstream&) const;
    void postorder(std::stringstream&) const;
    void ancestors(T val, std::stringstream &aux) const;
    int height() const;
    int whatlevelamI(T val) const;

    friend class BST<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri) : value(val), left(le), right(ri) {}

template <class T>
void Node<T>::add(T val) {
    if (val < value) {
        if (left != 0) {
            left->add(val);
        } else {
            left = new Node<T>(val);
        }
    } else {
        if (right != 0) {
            right->add(val);
        } else {
            right = new Node<T>(val);
        }
    }
}

template <class T>
bool Node<T>::find(T val) {
    if (val == value) {
        return true;
    } else if (val < value) {
        return (left != 0 && left->find(val));
    } else {
        return (right != 0 && right->find(val));
    }
}

template <class T>
void Node<T>::removeChilds() {
    if (left != 0) {
        left->removeChilds();
        delete left;
        left = 0;
    }
    if (right != 0) {
        right->removeChilds();
        delete right;
        right = 0;
    }
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
    if (left != 0) {
        left->inorder(aux);
    }
    if (aux.tellp() != 1) {
        aux << " ";
    }
    aux << value;
    if (right != 0) {
        right->inorder(aux);
    }
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
    aux << value;
    if (left != 0) {
        aux << " ";
        left->preorder(aux);
    }
    if (right != 0) {
        aux << " ";
        right->preorder(aux);
    }
}

template <class T>
void Node<T>::postorder(std::stringstream &aux) const {
    if (left != 0) {
        left->postorder(aux);
    }
    if (right != 0) {
        right->postorder(aux);
    }
    if (aux.tellp() != 1) {
        aux << " ";
    }
    aux << value;
}

template <class T>
void Node<T>::ancestors(T val, std::stringstream &aux) const {
    if (val == value) {
        return;
    }
    if (aux.tellp() != 1) {
        aux << " ";
    }
    aux << value;

    if (val < value && left != 0) {
        left->ancestors(val, aux);
    } else if (val > value && right != 0) {
        right->ancestors(val, aux);
    }
}

template <class T>
int Node<T>::height() const {
    int leftHeight = 0;
    int rightHeight = 0;

    if (left != 0) {
        leftHeight = left->height();
    }
    if (right != 0) {
        rightHeight = right->height();
    }

    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}

template <class T>
int Node<T>::whatlevelamI(T val) const {
    if (val == value) {
        return 1;
    } else if (val < value) {
        if (left != 0) {
            return left->whatlevelamI(val) + 1;
        }
    } else if (val > value) {
        if (right != 0) {
            return right->whatlevelamI(val) + 1;
        }
    }
    return 0;
}


template <class T>
class BST {
private:
    Node<T> *root;

public:
    BST();
    ~BST();
    bool empty() const;
    void add(T);
    bool find(T) const;
    void removeAll();

    std::string inorder() const;
    std::string preorder() const;
    std::string postorder() const;
    std::string levelbyLevel() const;
    std::string visit() const;
    int height() const;
    std::string ancestors(T val) const;
    int whatlevelamI(T val) const;
};

template <class T>
BST<T>::BST() : root(0) {}

template <class T>
BST<T>::~BST() {
    removeAll();
}

template <class T>
bool BST<T>::empty() const {
    return (root == 0);
}

template <class T>
void BST<T>::add(T val) {
    if (root != 0) {
        if (!root->find(val)) {
            root->add(val);
        }
    } else {
        root = new Node<T>(val);
    }
}

template <class T>
bool BST<T>::find(T val) const {
    if (root != 0) {
        return root->find(val);
    }
    return false;
}

template <class T>
void BST<T>::removeAll() {
    if (root != 0) {
        root->removeChilds();
    }
    delete root;
    root = 0;
}

template <class T>
std::string BST<T>::preorder() const {
    std::stringstream aux;
    aux << "[";
    if (!empty()) {
        root->preorder(aux);
    }
    aux << "]";
    return aux.str();
}

template <class T>
std::string BST<T>::inorder() const {
    std::stringstream aux;
    aux << "[";
    if (!empty()) {
        root->inorder(aux);
    }
    aux << "]";
    return aux.str();
}

template <class T>
std::string BST<T>::postorder() const {
    std::stringstream aux;
    aux << "[";
    if (!empty()) {
        root->postorder(aux);
    }
    aux << "]";
    return aux.str();
}

template <class T>
std::string BST<T>::levelbyLevel() const {
    std::stringstream aux;
    aux << "[";
    if (!empty()) {
        std::queue<Node<T>*> q;
        q.push(root);
        bool first = true;
        while (!q.empty()) {
            Node<T>* current = q.front();
            q.pop();

            if (!first) {
                aux << " ";
            }
            aux << current->value;
            first = false;

            if (current->left != 0) {
                q.push(current->left);
            }
            if (current->right != 0) {
                q.push(current->right);
            }
        }
    }
    aux << "]";
    return aux.str();
}

template <class T>
std::string BST<T>::visit() const {
    std::stringstream aux;
    aux << preorder() << "\n";
    aux << inorder() << "\n";
    aux << postorder() << "\n";
    aux << levelbyLevel();
    return aux.str();
}

template <class T>
int BST<T>::height() const {
    if (!empty()) {
        return root->height();
    }
    return 0;
}

template <class T>
std::string BST<T>::ancestors(T val) const {
    std::stringstream aux;
    aux << "[";
    if (!empty() && find(val)) {
        root->ancestors(val, aux);
    }
    aux << "]";
    return aux.str();
}

template <class T>
int BST<T>::whatlevelamI(T val) const {
    if (!empty() && find(val)) {
        return root->whatlevelamI(val);
    }
    return 0;
}

#endif /* BST_H_ */