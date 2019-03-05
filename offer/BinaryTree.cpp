//26.寻找树的子结构
//解题思路：先遍历ａ树找到ａ树上一个节点和ｂ树根节点数值相等的
//  在遍历ａ树上那个节点与ｂ树对比是否相同
#include <iostream>

struct BinaryTreeNode {
    double m_dbValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
};

bool HasSubtree(BinartyTreeNode* pRoot1, BinartyTreeNode* pRoot2)
{
    bool result = false;
    if (pRoot1 != nullptr && pRoot2 != nullptr)
    {
        if(Equal(pRoot1->m_dbValue, pRoot2->m_dbValue))
            result = DoesTree1HaveTree2(pRoot1, pRoot2);
        if(!result)
            result = HasSubtree(pRoot1->m_pLeft, pRoot2);
        if(!result)
            result = HasSubtree(pRoot1->m_pRight, pRoot2);
    }
    return result;
}

bool DoesTree1HaveTree2(pRoot1, pRoot2)
{
    if (pRoot2 == nullptr)
        return true;
    if (pRoot1 == nullptr)
        return false;
    if (!Equal(pRoot1->m_dbValue, pRoot2->m_dbValue))
}

