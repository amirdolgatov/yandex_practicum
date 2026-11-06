// https://contest.yandex.ru/contest/24810/run-report/170751817/

#ifndef REMOTE_JUDGE
struct Node
{
    int value;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(Node* left, Node* right, int value) : value(value), left(left), right(right) {}
};
#endif
#ifdef REMOTE_JUDGE
#include "solution.h"
#endif
#include <cassert>
#include <iostream>

/*
 * ИДЕЯ РЕШЕНИЯ
 *
 * Очевидно, все удаления сводятся к трем случаям
 * - удаление листа, простейший случай
 * - удаление корня дерева, если имелись потомки, то потребуется соединить 2 поддерева
 * - удаление не листа и не корня, возможно потребуется соединить до 3-х деревьев
 *
 * Удаление листа реализуется просто, необходимо "обнулить" соответствующий указатель родителя листа.
 * Удаление корня непустого дерева потребует соединить два поддерева, в качестве нового корня выбирается
 * крайний правый узел левого поддерева. Если одного из сыновей нет, операция сильно упрощается.
 * Удаление третьего типа потребует объединить два поддерева, что реализуется как удаление корня
 * (это локальный корень), затем когда новый корень выбран, надо присоединить его к родителю удаляемого
 * узла.
 *
 * СЛОЖНОСТЬ
 * Удаление складывается из нескольких действий
 * Рассмотрим удаление не листа и не корня, а промежуточного узла
 * 1. Поиск удалеямого узла, сложность O(H/2), H - глубина дерева.
 * 2. Объединение поддеревьев, которых в общем случае 3 штуки.
 *      2.1 Поиск крайнего правого элемента O(H/2)
 *      2.2 Соединение деревьев O(1)
 *
 *  Итого имеем сложность O(H).
 *
 *  Если рассмотреть удаление листа, то для удаления его достаточно только найти, сложность O(H)
 *  Если рассмотреть удаление корня, то сложность также O(H)
 *
 * ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ
 * Дополнительная память не требуется.
*/

/*
 * Найти узел по ключу
 * @root корень дерева
 * @key ключ
 * @parent указатель на адрес родителя найденного узла
*/
Node* find(Node* root, int key, Node** parent)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (key == root->value)
    {
        return root;
    }
    else if (key > root->value)
    {
        *parent = root;
        return find(root->right, key, parent);
    }
    else
    {
        *parent = root;
        return find(root->left, key, parent);
    }
}

/*
 * Найти узел по ключу
 * @root - корень дерева (поддерева)
 * @parent - указатель на адрес родителя найденного узла
*/
Node* findRightNode(Node* root, Node** parent)
{
    while (root)
    {
        Node* right = root->right;
        if (right)
        {
            *parent = root;
            root = right;
        }
        else
        {
            return root;
        }
    }
    return nullptr;
}

/*
 * Назначить нового родителя ребенку
 * @deleted удаляемый узел
 * @parent родитель
 * @newChild новый ребенок
*/
Node* adoptNewChild(Node* deleted, Node* parent, Node* newChild)
{
    if (parent)
    {
        if (deleted == parent->left)
        {
            parent->left = newChild;
        }
        else
        {
            parent->right = newChild;
        }
        return parent;
    }
    return newChild;
}

/*
 * Объеденить поддеревья удаляемого узла
 * @root корень дерева (поддерева)
*/
Node* joinChildrenSubtrees(Node* root)
{
    if (root->left == nullptr)
    {
        return root->right;
    }
    if (root->right == nullptr)
    {
        return root->left;
    }

    Node* parent = root;
    Node* max_element = findRightNode(root->left, &parent);

    if (parent != root)
    {
        parent->right = max_element->left;
        max_element->left = root->left;
    }
    max_element->right = root->right;
    return max_element;
}

/*
 * Удалить корень дерева
 * @root корень дерева
*/
Node* deleteRoot(Node* root)
{
    return joinChildrenSubtrees(root);
}

/*
 * Удалить лист
 * @deleted лист
 * @parent родитель листа
*/
Node* deleteLeaf(Node* deleted, Node* parent)
{
    return adoptNewChild(deleted, parent, nullptr);
}

/*
 * Объединить поддеревья удаляемого узла с его родителем
 * @deleted удаляемый узел
 * @parent родитель удаляемого узла
*/
Node* joinChildrenSubtreesAndParent(Node* deleted, Node* parent)
{
    Node* newRoot = joinChildrenSubtrees(deleted);
    return adoptNewChild(deleted, parent, newRoot);
}

/*
 * Удалить элемент из дерева по ключу
 * @root корень дерева
 * @key ключ
*/
Node* remove(Node* root, int key)
{
    Node* parent = nullptr;
    Node* deleted = find(root, key, &parent);
    if (deleted == nullptr)
    {
        return root;
    }

    bool isRoot = (deleted == root);
    bool isLeaf = (deleted->left == nullptr) && (deleted->right == nullptr);
    if (isRoot)
    {
        return deleteRoot(root);
    }
    else if (isLeaf)   // this is leaf
    {
        deleteLeaf(deleted, parent);
        return root;
    }
    else
    {
        joinChildrenSubtreesAndParent(deleted, parent);
        return root;
    }
}

#ifndef REMOTE_JUDGE
void test()
{
    Node node1({nullptr, nullptr, 2});
    Node node2({&node1, nullptr, 3});
    Node node3({nullptr, &node2, 1});
    Node node4({nullptr, nullptr, 6});
    Node node5({&node4, nullptr, 8});
    Node node6({&node5, nullptr, 10});
    Node node7({&node3, &node6, 5});
    Node* newHead = remove(&node7, 10);
    assert(newHead->value == 5);
    assert(newHead->right == &node5);
    assert(newHead->right->value == 8);
}

int main()
{
    test();
}
#endif
