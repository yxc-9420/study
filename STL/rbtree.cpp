#include "rbtree.h"
#include<stack>
#include<iostream>

/**********************************************
****@projectName study
****@Author      yuwenchao
****@Describe
****@Time        2021-09-09 15:23:26
****            10
****           /  \
****          6    14
****         / \   / \
****        4   8 11 17
****        \
****         5
**********************************************/

RBTree::RBTree()
{

}

void RBTree::preOrder()
{
    preOrder(root);
}

void RBTree::inOrder()
{
    inOrder(root);
}

void RBTree::postOrder()
{
    postOrder(root);
}

RBNode *RBTree::search(int key)
{
    return search(root,key);
}

RBNode *RBTree::iterativeSearch(int key)
{
    return iterativeSearch(root,key);
}

int RBTree::mininum()
{
    RBNode *res = mininum(root);
    if(res !=nullptr)
        return res->key;
    return INT_MIN;
}

int RBTree::maxinum()
{
    RBNode *res = maxinum(root);
    if(res != nullptr)
        return res->key;
    return INT_MAX;
}

RBNode *RBTree::successor(RBNode *node)
{
    if(node->right !=nullptr)
        return mininum(node->right);
    // 如果x没有右孩子。则x有以下两种可能：
    // (01) x是"一个左孩子"，则"x的后继结点"为 "它的父结点"。
    // (02) x是"一个右孩子"，则查找"x的最低的父结点，并且该父结点要具有左孩子"，找到的这个"最低的父结点"就是"x的后继结点"。
    RBNode *res = node->parent;
    while (res !=nullptr && node == res->right) {
        node = res;
        res = res->parent;
    }
    return res;
}

RBNode *RBTree::predecessor(RBNode *node)
{
    if(node->left !=nullptr)
        return maxinum(node->left);
    // 如果x没有左孩子。则x有以下两种可能：
    // (01) x是"一个右孩子"，则"x的前驱结点"为 "它的父结点"。
    // (01) x是"一个左孩子"，则查找"x的最低的父结点，并且该父结点要具有右孩子"，找到的这个"最低的父结点"就是"x的前驱结点"。
    RBNode *res = node->parent;
    while (res!=nullptr && node == res->left) {
        node = res;
        res = res->parent;
    }
    return res;
}

void RBTree::insert(int key)
{
    RBNode *cur = nullptr;
    if((cur = new RBNode(key,black,nullptr,nullptr,nullptr)) == nullptr)
        return;
    insert(root,cur);
}

/**
 * @brief RBTree::preOrder 中左右 10 6 4 5 8 14 11 17
 * @param node
 */
void RBTree::preOrder(RBNode *node) const
{
    if(node == nullptr) return;
    std::stack<RBNode*> s;
    RBNode *cur = node;
    while(!s.empty()||cur){
        while(cur){
            std::cout<<cur->key<<" ";
            s.push(cur);
            cur = cur->left;
        }
        cur = s.top();
        s.pop();
        cur = cur->right;
    }
}

/**
 * @brief RBTree::inOrder 左中右 4 5 6 8 10 11 14 17
 * @param node
 */
void RBTree::inOrder(RBNode *node) const
{
    if(node == nullptr) return;
    std::stack<RBNode*> s;
    RBNode *cur = node;
    while(!s.empty()||cur){
        while(cur){
            s.push(cur);
            cur = cur->left;
        }
        cur = s.top();
        s.pop();
        std::cout<<cur->key<<" ";
        cur = cur->right;
    }
}

/**
 * @brief RBTree::postOrder 左右中 5 4 8 6 11 17 14 10
 * @param node
 */
void RBTree::postOrder(RBNode *node) const
{
    if(node == nullptr) return;
    RBNode *cur = node;
    std::stack<RBNode*> s;
    RBNode *pre = nullptr;
    while (cur) {
        s.push(cur);
        cur = cur->left;
    }
    while (!s.empty()) {
        cur = s.top();//最左节点
        s.pop();
        if(!cur->right||pre == cur->right){//如果右子树为空或者右子树已遍历
            std::cout<<cur->key<<" ";
            pre = cur;
        }
        else{
            s.push(cur);
            cur = cur->right;
            while (cur) {
                s.push(cur);
                cur = cur->left;
            }
        }
    }
}

RBNode *RBTree::search(RBNode *node, int key) const
{
    if(node == nullptr || node->key == key)
        return node;
    if(key>node->key)
        return search(node->right,key);
    else
        return search(node->left,key);
}

RBNode *RBTree::iterativeSearch(RBNode *node, int key) const
{
    while (node !=nullptr && key!=node->key) {
        if(key>node->key)
            node = node->right;
        else
            node = node->left;
    }
    return node;
}

RBNode *RBTree::mininum(RBNode *node)
{
    if(nullptr == node) return nullptr;
    while (node->left) {
        node = node->left;
    }
    return node;
}

RBNode *RBTree::maxinum(RBNode *node)
{
    if(nullptr == node) return nullptr;
    while (node->right) {
        node = node->right;
    }
    return node;
}

/**
 * @brief RBTree::leftRotate
 * @param root
 * @param node node父和右，r左和父，rl(如果存在)父，node父节点(如果存在) 子
 *        o              o(如果存在，左子或右子)
 *        |              |
 *        n              r(右不变，左 和 父)
 *       / \    ->      / \
 *      l   r          n   rr  n：(左不变，右 和 父)
 *         / \        / \
 *        rl rr      l  rl(如果存在，父)
 */
void RBTree::leftRotate(RBNode *&root, RBNode *node)
{
    RBNode *r = node->right;

    node->right = r->left;//node右节点

    if(nullptr !=r->left)
        r->left->parent = node;//rl(如果存在)父

    r->parent = node->parent;//r父节点
    if(nullptr == node->parent)
        root = r;
    else{//node父节点(如果存在) 子
        if(node == node->parent->right)
            node->parent->right = r;
        else
            node->parent->left = r;
    }
    r->left = node;//r左
    node->parent = r;//node父
}

/**
 * @brief RBTree::rightRatate
 * @param root
 * @param node
 *        o              o(如果存在，左子或右子)
 *        |              |
 *        n              l(左不变， 右 和 父
 *       / \    ->      / \
 *      l   r          ll  n(右不变， 左 和 父)
 *     / \                / \
 *    ll lr              lr  r   lr(如果存在,父)
 */
void RBTree::rightRatate(RBNode *&root, RBNode *node)
{
    RBNode *l = node->left;
    node->left = l->right;
    if(nullptr != l->right)
        l->right->parent = node;

    l->parent = node->parent;
    if(nullptr == node->parent)
        root = l;
    else{
        if(node->parent->left == node)
            node->parent->left = l;
        else
            node->parent->right = l;
    }
    l->right = node;
    node->parent = l;
}

void RBTree::insert(RBNode *&root, RBNode *node)
{
    RBNode *cur = root;
    RBNode *pre = nullptr;
    while (cur) {
        pre = cur;
        if(node->key > cur->key)
            cur = cur->right;
        else
            cur = cur->left;
    }
    if(nullptr != pre){
        if(node->key > pre->key)
            pre->right = node;
        else
            pre->left = node;
    }
    else
        root = node;
    node->color = red;
    insertFixUp(root,node);
}

void RBTree::insertFixUp(RBNode *&root, RBNode *node)
{

}
