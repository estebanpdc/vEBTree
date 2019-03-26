#pragma once
#include <vector>
class vEBTree
{
public:
    vEBTree(int iU);
    ~vEBTree();

    int m_iMin;
    int m_iMax;
    int m_iMaxValue;
    int m_iMinValue;
    vEBTree* m_Summary;
    std::vector<vEBTree*> m_Cluster;

    bool contains(int key);
    int successor(int key);
    void insert(int key, int value);
    void emptyInsert(int key, int value);
    int getValue(int key);
    void remove(int key);

private:
    //Atributes
    int m_iU;

    //Utils
    int high(int y);
    int low(int x);
    int index(int x, int y);

  
};

