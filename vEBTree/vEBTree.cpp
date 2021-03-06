#include "stdafx.h"
#include "vEBTree.h"
#include <math.h>
#include <vector>



 int lowerSquare(int i) {
    return (int)pow(2.0, floor((log(i) / log(2.0)) / 2.0));
}

 int upperSquare(int i) {
    return (int)pow(2.0, ceil((log(i) / log(2.0)) / 2.0));
}

 vEBTree::vEBTree(int iU)
 {
     m_iU = iU;
     m_iMax = -1;
     m_iMin = -1;
     m_iMaxValue = -1;
     m_iMinValue = -1;

     if (m_iU > 2) {
         int universeSizeLowerSquare = lowerSquare(iU);
         int mask = universeSizeLowerSquare - 1;

         int universeSizeUpperSquare = upperSquare(m_iU);
         m_Summary = new vEBTree(universeSizeUpperSquare);
         m_Cluster = std::vector<vEBTree*>(universeSizeLowerSquare);
         for (int i = 0; i < universeSizeUpperSquare; i++) {
             m_Cluster[i] = new vEBTree(universeSizeLowerSquare);
         }
     }
 }


vEBTree::~vEBTree()
{

}

int vEBTree::high(int y)
{
    return y / (int) sqrt(m_iU);
}

int vEBTree::low(int x)
{
    return x % (int) sqrt(m_iU);
}

int vEBTree::index(int x, int y)
{
    return x * (int) sqrt(m_iU) + y;
}

bool vEBTree::contains(int key) {
    if (key == m_iMin || key == m_iMax) return true;
    if (m_iU == 2) return false;
    return m_Cluster[high(key)]->contains(low(key));
}

int vEBTree::successor(int key) {
    if (m_iU == 2) {
        if (key == 0 && m_iMax == 1) return 1;
        else return -1;
    }
    if (m_iMin != -1 && key < m_iMin) return m_iMin;
    int maxLow = m_Cluster[high(key)]->m_iMax;
    if (maxLow != -1 && low(key) < maxLow) return index(high(key), m_Cluster[high(key)]->successor(low(key)));
    int successorCluster = m_Summary->successor(high(key));
    if (successorCluster == -1) return -1;
    return index(successorCluster, m_Cluster[successorCluster]->m_iMin);
}

void vEBTree::insert(int key, int value) {
    if (m_iMin == -1)
        emptyInsert(key, value);
    else {
        if (key < m_iMin) {
            int tmpK = key;
            int tmpV = value;
            key = m_iMin;
            m_iMin = tmpK;
            value = m_iMinValue;
            m_iMinValue = tmpV;
        }
        if (m_iU > 2)
            if (m_Cluster[high(key)]->m_iMin == -1) {
                m_Summary->insert(high(key), value);
                m_Cluster[high(key)]->emptyInsert(low(key), value);
            }
            else
                m_Cluster[high(key)]->insert(low(key), value);
        if (key > m_iMax) {
            m_iMax = key;
            m_iMaxValue = value;
        }
    }
}

void vEBTree::remove(int key) {
    if (m_iMin == m_iMax) {
        m_iMin = -1;
        m_iMax = -1;
        m_iMinValue = -1;
        m_iMaxValue = -1;
    }
    else if (m_iU == 2) {
        if (key == 0) {
            m_iMinValue = m_iMaxValue;
            m_iMin = 1;
        }
        else
            m_iMin = 0;
        m_iMaxValue = m_iMinValue;
        m_iMax = m_iMin;
    }
    else {
        if (key == m_iMin) {
            int firstCluster = m_Summary->m_iMin;
            key = index(firstCluster, m_Cluster[firstCluster]->m_iMin);
            m_iMinValue = getValue(key);
            m_iMin = key;
        }
        m_Cluster[high(key)]->remove(low(key));
        if (m_Cluster[high(key)]->m_iMin == -1) {
            m_Summary->remove(high(key));
            if (key == m_iMax) {
                int summaryMax = m_Summary->m_iMax;
                if (summaryMax == -1) {
                    m_iMaxValue = m_iMinValue;
                    m_iMax = m_iMin;
                }
                else {
                    int m = index(summaryMax, m_Cluster[summaryMax]->m_iMax);
                    m_iMaxValue = getValue(m);
                    m_iMax = m;
                }
            }
        }
        else if (key == m_iMax) {
            int m = index(high(key), m_Cluster[high(key)]->m_iMax);
            m_iMaxValue = getValue(m);
            m_iMax = m;
        }
    }
}

int vEBTree::getValue(int key) {
    if (key == m_iMin) return m_iMinValue;           
    if (key == m_iMax) return m_iMaxValue;
    if (m_iU == 2) return -1;
    return m_Cluster[high(key)]->getValue(low(key));
}

void vEBTree::emptyInsert(int key, int value) {
    m_iMin = key;
    m_iMax = key;
    m_iMinValue = value;
    m_iMaxValue = value;
}
