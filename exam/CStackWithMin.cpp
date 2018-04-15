//
//  CStackWithMin.cpp
//  exam
//
//  Created by apple on 16/4/12.
//  Copyright © 2016年 wjc. All rights reserved.
//

#include "CStackWithMin.hpp"

// get the last element of mutable stack
template <typename T> T& CStackWithMin<T>::top()
{
    return m_data.back();
//    return m_data.top();
}

// get the last element of non-mutable stack
template <typename T> const T& CStackWithMin<T>::top() const
{
    return m_data.back();
//    return m_data.top();
}

// insert an elment at the end of stack
template <typename T> void CStackWithMin<T>::push(const T& value)
{
    // append the data into the end of m_data
    m_data.push_back(value);
    
    // set the index of minimum elment in m_data at the end of m_minIndex
    if(m_minIndex.size() == 0)
        m_minIndex.push_back(0);
    else
    {
        if(value < m_data[m_minIndex.back()])
            m_minIndex.push_back(m_data.size() - 1);
        else
            m_minIndex.push_back(m_minIndex.back());
    }
    
    /*
    m_data.push(value);
    
    if (m_minIndex.size() == 0 || value < m_minIndex.top()) {
        m_minIndex.push(value);
    } else {
        m_minIndex.push(m_minIndex.top());
    }
     */
}

// erease the element at the end of stack
template <typename T> void CStackWithMin<T>::pop()
{
    // pop m_data
    m_data.pop_back();
    
    // pop m_minIndex
    m_minIndex.pop_back();
    
    /*
    assert(m_data.size() > 0 && m_minIndex.size() > 0);
    m_data.pop();
    m_minIndex.pop();
     */
}

// get the minimum element of stack
template <typename T> const T& CStackWithMin<T>::min() const
{
    assert(m_data.size() > 0 && m_minIndex.size() > 0);
    
    return m_data[m_minIndex.back()];
//    return m_minIndex.top();
}
