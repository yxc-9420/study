#ifndef RBTREE_H
#define RBTREE_H

typedef enum {black,red} colorType;

struct RBNode{
    int key;//关键字
    colorType color;//颜色
    RBNode *left;//左孩子
    RBNode *right;//右孩子
    RBNode *parent;//父节点

    RBNode(int k,colorType c,RBNode *l,RBNode *r,RBNode *p):
        key(k),color(c),left(l),right(r),parent(p){}
};

class RBTree{
private:
    RBNode *root;//根节点
public:
    RBTree();
    ~RBTree();
    void preOrder();//前序遍历
    void inOrder();//中序遍历
    void postOrder();//后序遍历

    RBNode *search(int key);//递归查找
    RBNode *iterativeSearch(int key);//非递归查找
    int mininum();//最小节点值
    int maxinum();//最大节点值
    /**
     * @brief successor 找节点x的后继节点，即查找值大于该节点的最小节点
     * @param x
     * @return
     */
    RBNode *successor(RBNode *node);
    /**
     * @brief predecessor 找节点x的前驱节点，即查找值小于该节点的最大节点
     * @param x
     * @return
     */
    RBNode *predecessor(RBNode *node);
    void insert(int key);
    void remove(int key);
    void destroy();
    void print();
private:
    void preOrder(RBNode *node) const;
    void inOrder(RBNode *node) const;
    void postOrder(RBNode *node) const;

    RBNode *search(RBNode *node,int key) const;//递归
    RBNode *iterativeSearch(RBNode *node, int key) const;//非递归
    RBNode *mininum(RBNode *node);
    RBNode *maxinum(RBNode *node);
    void leftRotate(RBNode *&root,RBNode *node);//左旋
    void rightRatate(RBNode *&root,RBNode *node);//右旋
    void insert(RBNode *&root,RBNode *node);//插入
    void insertFixUp(RBNode *&root,RBNode *node);//插入修正
    void remove(RBNode *&root,RBNode *node);//删除
    // 删除修正函数
    void removeFixUp(RBNode *&root, RBNode *node, RBNode *parent);

    void destroy(RBNode *&root);
    /**
     * @brief print
     * @param root
     * @param key       节点键值
     * @param direction 0，表示该节点是根节点;
                        -1，表示该节点是它的父结点的左孩子;
                        1，表示该节点是它的父结点的右孩子。
     *
     *
     */
    void print(RBNode *root,int key,int direction);
};
#endif // RBTREE_H
