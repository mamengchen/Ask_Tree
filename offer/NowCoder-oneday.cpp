//第一题：组队竞赛
//一个队伍三个队员的水平值是3, 3, 3.那么队伍的水平值是3
//一个队伍三个队员的水平值是3, 2, 3.那么队伍的水平值是3
//一个队伍三个队员的水平值是1, 5, 2.那么队伍的水平值是2
//
//输出一个整数表示所有队伍的水平值总和最大值．
//实例１
//输入：
//2
//5 2 8 5 1 5
//输出：
//10

//本题思路：最大的不可能是中位数，所以我们要去取第二大的数，第三大的数字我们
//也不能取，所以我们对已开始输入的数据排序，取第二大的数和第四大的数

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    int n;
    while (std::cin >> n) {
        long long sum = 0;
        vector<int> a(3 * n);
        for (int i = 0; i < (3 * n); i++)
        {
            std::cin >> a[i];
        }
        sort(a.begin(), a.end());
        for (int i = n; i <= (3 * n - 2); i += 2)
        {
            sum += a[i];
        }
        std::cout << sum << std::endl;
    }
    return 0;
}


//题目2:删除公共字符
//实例：
//输入：They are students , aeiou
//输出：Thy r stdnts.

#include <iostream>
#include <string>
using namespace std;

int main()
{
    //oj中输入字符使用getline.
    std::string str1,str2;
    getline(cin, str1);
    getline(cin, str2);

    //使用哈希映射思想先str2统计字符出现的次数
    int hashtable[256] = {0};
    for (size_t i = 0; i < str2.size(); ++i)
    {
        hashtable[str2[i]]++;
    }

    //在用一个新的数组接受删除的字符
    std::string ret;
    for (size_t i = 0; i < str1.size(); ++i)
    {
        if (hashtable[str1[i]] == 0)
        {
            ret += str1[i];
        }
    }
    std::cout << ret << std::endl;
    return 0;
}



