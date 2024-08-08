
#include "ThreeAVL.hpp"

/*======================================*/
/*=========== Конструкторы =============*/
/*======================================*/

template<typename T>
Node<T>* ThreeAVL<T>::root = nullptr;

template<typename T>
Node<T>::Node(Node* parentSource, size_t heightSource, Node* leftSource, Node* rightSource) : 
                            parent(parentSource),
                            left(leftSource),
                            right(rightSource),
                            height(heightSource)
{} 

template<typename T>
ThreeAVL<T>::ThreeAVL()
{
    this->root = nullptr;
}

template<typename T>
ThreeAVL<T>::~ThreeAVL()
{
    this->reverseBypass([](Node<T>* node) {delete node;}, this->root);
}

/*======================================*/
/*============== Методы ================*/
/*======================================*/

template<typename T>
int64_t ThreeAVL<T>::height(Node<T>* node)
{
    return (node ? node->height : -1);
}

template<typename T>
void ThreeAVL<T>::fixHeight(Node<T>* node)
{
    node->height = ((height(node->left) > height(node->right)) ? height(node->left) : height(node->right)) + 1;
}

template<typename T>
int64_t ThreeAVL<T>::balanceFactor(Node<T>* node)
{
    return (height(node->left) - height(node->right));;
}

template<typename T>
Node<T>* ThreeAVL<T>::rotateToRight(Node<T>* oldTop)
{
    Node<T>* newTop = oldTop->left;
    oldTop->left = newTop->right;

    if(newTop->right != nullptr) {
        newTop->right->parent = oldTop;
    }

    newTop->parent = oldTop->parent;
    if(oldTop->parent == nullptr) {
        this->root = newTop;
    } else if(oldTop->parent->left == oldTop) {
        oldTop->parent->left = newTop;
    } else {
        oldTop->parent->right = newTop;
    }
    
    newTop->right = oldTop;
    oldTop->parent = newTop;


    
    fixHeight(newTop);
    fixHeight(oldTop);
    return newTop;
}

template<typename T>
Node<T>* ThreeAVL<T>::rotateToLeft(Node<T>* oldTop)
{
    Node<T>* newTop = oldTop->right;
    oldTop->right = newTop->left;   
    if(newTop->left != nullptr) {
        newTop->left->parent = oldTop;
    }

    newTop->parent = oldTop->parent;
    if(oldTop->parent == nullptr) {
        this->root = newTop;
    } else if(oldTop->parent->left == oldTop) {
        oldTop->parent->left = newTop;
    } else {
        oldTop->parent->right = newTop;
    }


    newTop->left = oldTop;
    oldTop->parent = newTop;
    fixHeight(newTop);
    fixHeight(oldTop);
    return newTop;
}

template<typename T>
Node<T>* ThreeAVL<T>::balanceNode(Node<T>* node)
{
    // fixHeight(node);
    // Если левое поддерево выше правого
    if(balanceFactor(node) > 1) {
        if (balanceFactor(node->left) >= 0) {
           return rotateToRight(node);
        } 
        else {
           node->left = rotateToLeft(node->left);
           return rotateToLeft(node); 
        }
        return node;
    }
    // Если правое поддерево больше левого
    if(balanceFactor(node) < -1) {
        if (balanceFactor(node->right) <= 0) { 
            return rotateToLeft(node);
        }
        else {
            node->right = rotateToRight(node->right);
            return rotateToLeft(node);
        }
        return node;
    }   

    return node;
}

// Поиск эллемента[внутреня функия]
template<typename T>
Node<T>* ThreeAVL<T>::find(T value, Node<T>* node)
{   
    if(node == nullptr || node->value == value) {
        return node;
    }

    if (node->value < value) {
        return find(node->right);
    }
    else {
        return find(node->left);
    }

    return node;
}

// Вставка
template<typename T>
Node<T>* ThreeAVL<T>::insert(T value, Node<T>* node, Node<T>* parentNode)
{
    if(root == nullptr) {
        root = new Node<T>;
        root->value = value;
        return root;
    }
 
    if (node == nullptr) {
        node = new Node<T>(parentNode);
        node->value = value;
        fixHeight(parentNode);
        return balanceNode(parentNode);
    }

    if(value < node->value) {
        node->left = insert(value, node->left, node);
    }
    else if(value > node->value) {
        node->right = insert(value, node->right, node);
    }
    else {
        return node;
    }

    fixHeight(node);
    return balanceNode(node);
}

// Удаление эллемента
template<typename T>
Node<T>* ThreeAVL<T>::deleteItem(T value, Node<T>* node)
{
    if(node == nullptr) {
        return nullptr;
    }

    if (node->value < value) {
        node->right = deleteItem(value, node->right);
    }
    else if (node->value > value){
        node->left = deleteItem(value, node->left);
    }
    else {
        if(node->left != nullptr && node->right != nullptr) {
            Node<T>* minNode = node->right;
            while (minNode->left != nullptr) {
                minNode = minNode->left;
            }
            minNode->left = node->left;
            minNode->right = node->right;
            minNode->parent->left = nullptr;
            delete node;
            fixHeight(minNode);
            return balanceNode(minNode);
        } else {
            Node<T>* temp = (node->left != nullptr) ? node->left : node->right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        }
    }
    
    if (node == nullptr) {
        return nullptr;
    }

    fixHeight(node);
    return balanceNode(node);
}

// Центральный обход
template<typename T>
void ThreeAVL<T>::centralBypass(void func(Node<T>*), Node<T>* node)
{
    if (node->right == nullptr && node->left == nullptr) {
        func(node);
        return;
    }

    if(node->left != nullptr) {
        centralBypass(func, node->left);
    }
    
    func(node);

    if(node->right != nullptr) {
        centralBypass(func, node->right);
    }
    return;
}

// Обратный обход
template<typename T>
 void ThreeAVL<T>::reverseBypass(void func(Node<T>*), Node<T>* node)
 {
    if (node->right == nullptr && node->left == nullptr) {
        func(node);
        return;
    }

    if (node->left != nullptr) {
        reverseBypass(func, node->left);
    }

    if (node->right != nullptr) {
        reverseBypass(func, node->right);
    }

    func(node);
    return;
}

// Прямой обход
template<typename T>
void ThreeAVL<T>::directBypass(std::ostream& out, Node<T>* node)
{
    out << node->value << " ";
    if (node->right == nullptr && node->left == nullptr) {
        return;
    }
    
    if (node->left != nullptr) {
        directBypass(out, node->left);
    }

    if (node->right != nullptr) {
        directBypass(out, node->right);
    }
    return;
}

// Вывод дерева
template<typename T>
void ThreeAVL<T>::print() {
    this->centralBypass([](Node<T>* node) {std::cout << node->value << " ";}, this->root);
}