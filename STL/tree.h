#ifndef TREE_H
#define TREE_H
#include<list>
using std::list;

struct Node{
    int val;
    Node *left;
    Node *right;
}; 

class Tree
{
public:
    int count;//节点个数
    Node* root;//根节点
    Tree();
    ~Tree();
    Tree& insert(int value);
    //前序遍历  中左右
    void preorderR(list<int>& l);//递归
    void preorderI(list<int>& l);
    void preorderI2(list<int>& l);
    //中序遍历  左中右
    void inorderR(list<int>& l);//递归
    void inorderI( list<int>& l);
    //后序遍历  左右中
    void postorderR(list<int>& l);//递归
    void postorderI(list<int>& l);
    //层次遍历
    void level(list<int>& l);
};

#endif // TREE_H
