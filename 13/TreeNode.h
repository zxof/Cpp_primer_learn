/*
@time 2022-5-14
@description 一个简单的二叉树节点类
@author hjx
*/

#include<string>
class TreeNode{
private:
    std::string value;
    int         count;
    TreeNode*   left;
    TreeNode*   right;

public:
    TreeNode():value(""),count(1),left(nullptr),right(nullptr){}
    // 非常量引用的初始值必须为左值
    TreeNode(const std::string& s = std::string(),TreeNode* lhs = nullptr,TreeNode *rhs = nullptr):
        value(s),count(1),left(lhs),right(rhs){}
    // 拷贝构造函数
    TreeNode(const TreeNode&);
    TreeNode& operator=(const TreeNode&);
    void copyTree();
    int deleteTree();
    ~TreeNode();
};

class BinTree{
private:
    TreeNode *root;
public:
    BinTree():root(nullptr){}
    BinTree(TreeNode *t = nullptr):root(t) {}
    ~BinTree();
};

void TreeNode::copyTree(){
    if(left){
        left->copyTree();
    }
    if(right){
        right->copyTree();
    }
    count++;
}
TreeNode::TreeNode(const TreeNode& t):count(1),value(t.value),left(t.left),right(t.right){
    if(left){
        left->copyTree();
    }
    if(right){
        right->copyTree();
    }
}
int TreeNode::deleteTree(){
    return count;
}
TreeNode::~TreeNode(){
    if(count)  deleteTree();
}


BinTree::~BinTree(){
    if(!root->deleteTree()){
        delete root;
    }
}