//
// Created by oyiou on 2023/10/30.
//
#include <cmath>
#include <vector>

using namespace std;

#define ROW 10
#define COL 10

//点类型
struct Mypoint
{
    int row;
    int col;
    int f, g, h;
    bool operator==(const Mypoint& pos) const
    {
        return (pos.row == row && pos.col == col);
    }
    void GetH(const Mypoint& Begpos, const Mypoint& Endpos)
    {
        int x = abs(Begpos.col - Endpos.col);//计算水平差距
        int y = abs(Begpos.row - Endpos.row);//计算垂直差距
        h = x + y;//计算总的差距
    }
    inline void GetF()
    {
        f = g + h;//计算f
    }
};
//树结构存储节点
struct TreeNode
{
    Mypoint pos{};//当前点坐标
    TreeNode* pParent;//当前点的父节点
    vector<TreeNode*> pChild;	//存储当前点的所有孩子节点
    //构造函数
    explicit TreeNode(const Mypoint& pos)
    {
        this->pos = pos;
        pParent = nullptr;
    }
};
//判断某个点能否走
bool CanWalk(int map[ROW][COL], bool vis[ROW][COL], const Mypoint& pos)
{
    //如果越界，不能走
    if (pos.row < 0 || pos.col < 0 || pos.row >= ROW || pos.col >= COL)
    {
        return false;
    }
    //如果是墙，不能走
    if (map[pos.row][pos.col])
    {
        return false;
    }
    //如果已经走过，不能走
    if (vis[pos.row][pos.col])
    {
        return false;
    }
    return true;//否则能走
}
void init()
{
    //地图，1表示墙，0表示路径
    int map[ROW][COL] =
            {
                    {0,0,0,0,1,0,0,0,0,0},
                    {0,0,0,0,1,0,0,0,0,0},
                    {0,0,0,1,1,0,1,0,0,0},
                    {0,0,0,0,1,0,1,0,0,0},
                    {0,0,0,0,1,0,1,0,0,0},
                    {0,0,1,0,1,0,0,0,0,0},
                    {0,0,0,0,1,0,0,0,0,0},
                    {0,0,0,0,0,0,1,0,0,0},
                    {0,0,0,0,1,1,0,0,0,0},
                    {0,0,0,0,1,0,0,0,0,0},
            };

    //起始点和终点
    Mypoint Begpos = { 1,1 };
    Mypoint Endpos = { 6,5 };

    //标记有没有走过
    bool vis[ROW][COL] = { false };

    //创建树根，即根节点
    auto* pRoot = new TreeNode(Begpos);

    vector<TreeNode*> buff;	//存储孩子节点的数组

    TreeNode* pCurrent = pRoot;	//记录当前点
    TreeNode* pTemp = nullptr;	//试探节点,用于试探下一个位置的点

    bool isFindEnd = false;//终点标记
}

