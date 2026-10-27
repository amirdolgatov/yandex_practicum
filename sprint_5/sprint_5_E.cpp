#ifndef REMOTE_JUDGE
struct Node 
{  
  int value;  
  const Node* left = nullptr;  
  const Node* right = nullptr;
  Node(int value, Node* left, Node* right) : value(value), left(left), right(right) {}
};  
#endif

#ifdef REMOTE_JUDGE
#include "solution_tree.h"
#endif
#include <cmath>
#include <iostream>
#include <cassert>

using namespace std;

bool process(const Node* node)
{
  bool left_correct = (node->left == nullptr) || (node->left != nullptr && node->value > node->left->value);
  bool right_correct = (node->right == nullptr) || (node->right != nullptr && node->value < node->right->value);
  return (left_correct && right_correct);
}

void traverse(const Node* node, bool& is_bst)
{
  if (node == nullptr)
  {
    return;
  }

  if (process(node))
  {
    std::cout << " | node is ok " << node->value; 
    traverse(node->left, is_bst);
    traverse(node->right, is_bst);
  }
  else
  {
    std::cout << " | node is bad " << node->value; 
    is_bst = false;
    return;
  }
}


bool Solution(const Node* root) 
{
  bool is_bst = true;
  traverse(root, is_bst);
  std::cout << std::endl;
  return is_bst;
} 


#ifndef REMOTE_JUDGE
void test() 
{
    {
      Node node1({1, nullptr, nullptr});
      Node node2({4, nullptr, nullptr});
      Node node3({3, &node1, &node2});
      Node node4({8, nullptr, nullptr});
      Node node5({5, &node3, &node4});
      assert(Solution(&node5));
    }
    {
      Node node1({1, nullptr, nullptr});
      Node node2({5, nullptr, nullptr});
      Node node3({3, &node1, &node2});
      Node node4({8, nullptr, nullptr});
      Node node5({5, &node3, &node4});
      assert(!Solution(&node5));
    }
}


int main() 
{
  test();
}
#endif