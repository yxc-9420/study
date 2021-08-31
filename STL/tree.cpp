#include "tree.h"
#include<queue>
#include<malloc.h>
#include<stdio.h>
#include<stack>
using namespace std;
Tree::Tree()
{
    this->count = 0;
    root = nullptr;
}

void freeTree(Node* root){
    if(root == nullptr) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

Tree::~Tree()
{
    freeTree(root);
}


Tree& Tree::insert(int value)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = value;
    node->left=nullptr;
    node->right=nullptr;
    if(root==nullptr){
        root=node;
    }
    else
    {
        Node* curr = root;
        Node* parent = nullptr;//父节点
        while (curr!=nullptr) {
            parent = curr;
            if(value<curr->val){
                curr = curr->left;
            }
            else if(value>curr->val){
                curr = curr->right;
            }
        }
        if(value>parent->val){
            parent->right = node;
        }
        else if(value < parent->val){
            parent->left = node;
        }
    }
    return *this;
}

void preorder(Node* node,list<int> &l){
    if(node!=nullptr){
        l.push_back(node->val);
        preorder(node->left,l);
        preorder(node->right,l);
    }
}
void Tree::preorderR(list<int> &l)
{
    preorder(root,l);
}

void Tree::preorderI(list<int> &l){

    std::stack<Node*> nodeStack;
    nodeStack.push(root);
    while (!nodeStack.empty()) {
        Node* cur = nodeStack.top();
        l.push_back(cur->val);
        nodeStack.pop();
        //左子树全部出栈之前，不会遍历右子树
        if(cur->right)nodeStack.push(cur->right);//右子树进栈
        if(cur->left) nodeStack.push(cur->left);//左子树进栈
    }
}
void Tree::preorderI2(list<int> &l)//非递归
{
    Node* cur = root;
    std::stack<Node*> nodeStack;
    while (cur||!nodeStack.empty()) {
        while (cur) {//一直处理左节点
            l.push_back(cur->val);
            nodeStack.push(cur);
            cur = cur->left;
        }
        cur = nodeStack.top();
        nodeStack.pop();
        cur = cur->right;
    }
}

void inorder(Node* node,list<int> &l){
    if(node!=nullptr){

        preorder(node->left,l);
        l.push_back(node->val);
        preorder(node->right,l);
    }
}
void Tree::inorderR(list<int> &l)
{
    inorder(root,l);
}

void Tree::inorderI(list<int> &l)
{
    Node* cur = root;
    std::stack<Node*> nodeStack;
    while (cur||!nodeStack.empty()) {
        while (cur) {
            nodeStack.push(cur);
            cur = cur->left;
        }
        cur = nodeStack.top();
        nodeStack.pop();
        l.push_back(cur->val);
        cur = cur->right;
    }
}

void postorder(Node* node,list<int> &l){
    if(node!=nullptr){

        preorder(node->left,l);
        preorder(node->right,l);
        l.push_back(node->val);
    }
}
void Tree::postorderR(list<int> &l)
{
    postorder(root,l);
}

void Tree::postorderI(list<int> &l)
{
    Node* cur = root;
    Node* preNode = nullptr;//标记
    std::stack<Node*> nodeStack;

    while(cur){//cur移动到左子树最左边
        nodeStack.push(cur);
        cur = cur->left;
    }
    while (!nodeStack.empty()) {
        //此时cur为空
        cur = nodeStack.top();
        nodeStack.pop();
        //如果右节点为空或者已访问
        if(!cur->right||preNode == cur->right){
            l.push_back(cur->val);
            preNode = cur;
        }
        //右子树未访问
        else{
            nodeStack.push(cur);
            cur = cur->right;
            while (cur) {
                nodeStack.push(cur);
                cur = cur->left;
            }
        }
    }
}
/**********************************************
****@projectName study
****@Author      yuwenchao
****@Describe    层次遍历
****@Time        2021-02-04 13:52:59
****@param       l:按序存储节点内容列表
**********************************************/
void Tree::level(list<int>& l)
{//层次遍历
    if(root == NULL) return;

    queue<Node*> q;
    q.push(root);//根节点入队
    Node* tmpNode;//临时节点
    while(!q.empty())
    {
        tmpNode = q.front();//返回队列顶部节点
        l.push_back(tmpNode->val);//列表中加入
        q.pop();//弹出节点
        //加入左右子树
        if(tmpNode->left) q.push(tmpNode->left);
        if(tmpNode->right) q.push(tmpNode->right);
    }
}
