#pragma once

enum Color
{
    RED,
    BLACK,
};

template<class K, class V>
struct RBTreeNode {
    RBTreeNode<K, V>* _left = nullptr;
    RBTreeNode<K, V>* _right = nullptr;
    RBTreeNode<K, V>* _parent = nullptr;

    pair<K, V> _kv;
    Color _color = RED;

    //用于生成一个默认的构造函数
    RBTreeNode() = default;
};

class RBTree {
    typedef RBTreeNode<K, V> Node;
public:
    RBTree()
    {
        _header = new Node;
        _header->_parent = nullptr;
        _header->_left = _header;
        _header->_right = _header;
    }

    bool Insert(const pair<K, V>& kv)
    {
        if (_header->_parent == nullptr)
        {
            Node* root = new Node;
            root->_kv = kv;
            root->_color = BLACK;
            root->_parent = _header;
            _header->_parent = root;
            _header->_left = root;
            _header->_right = root;

            return true;
        }
        Node* root = _header->_parent;
        Node* parent = nullptr;
        Node* cur = root;
        while (cur)
        {
            if (cur->_kv.first < kv.first)
            {
                parent = cur;
                cur = cur->_right;
            } else if (cur->_kv.first > kv.first)
            {
                parent = cur;
                cur = cur->_left;
            } else {
                return false;
            }
        }
        
        cur = new Node;
        cur->_kv = kv;
        if (parent->_kv.first < kv.first)
        {
            parent->_right = cur;
            cur->_parent = parent;
        } else {
            parent->_left = cur;
            cur->_parent = parent;
        }
    
        //保持红黑树的规则
        while (cur != root &&
               cur->_parent->_color == RED)
        {
            Node* parent = cur->_parent;
            Node* grandfather = cur->_parent->_parent;
            if (grandfather->_left == parent)
            {
                Node* uncle = grandfather->_right;
                
                //uncle存在且红，变色
                if (uncle && uncle->_color == RED)
                {
                    //1.变色处理
                    parent->_color = uncle->_color = BLACK;
                    grandfather->_color = RED;
                    cur = 
                } else {
                    //1.uncle存在且为黑，或者不存在
                    //旋转+变色
                    //双旋
                    if (cur == parent->_right)
                    {
                        Rotatel(parent);//左单旋
                        swap(parent, cur);
                    }
                    RotateR(grandfather);//右单旋
                    parent->_color = BLACK;
                    grandfather->_color = RED;
                    break;
                }
                

            } else {
                //parent 是祖父的左边
                Node* uncle = grandfather->_left;
                if (uncle && uncle->_color == RED)
                {
                    parent->_color = uncle->_color = BLACK;
                    grandfather->_color = RED;
                    cur = grandfather;
                } else {
                    if (cur == parent->_left)
                    {
                        RotateR(parent);
                        swap(parent, cur);
                    }

                    RotateL(grandfather);
                    parent->_color = BLACK;
                    grandfather->_color = RED;
                }
            }
        }

        _header->_parent->_color = BLACK;
        _header->_left = LeftMost();
        _header->_right = RightMost();
        return true;
    }
    
    //找最小结点数
    Node* LeftMost()
    {
        Node* cur = _header->_parent;
        while (cur && cur->_left != nullptr)
        {
            cur = cur->_left;
        }
    }

    //找最大结点数
    Node* RightMost()
    {
        Node* cur = _header->_parent;
        while (cur && cur->_right != nullptr)
        {
            cur = cur->_right;
        }
    }

    bool Empty()
    {
        return _header->_parent == nullptr;
    }


private:
    Node* _header;//头结点因为迭代器的需要实现的
};


