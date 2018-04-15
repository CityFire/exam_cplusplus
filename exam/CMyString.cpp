//
//  CMyString.cpp
//  exam
//
//  Created by apple on 16/4/6.
//  Copyright © 2016年 wjc. All rights reserved.
//

#include "CMyString.hpp"
#include <string.h>

CMyString& CMyString::operator=(const CMyString &str) // 考虑异常安全性
{
    /*
    if (this == &str) {
        return *this;
    }
    delete []m_pData;
    m_pData = NULL;
    m_pData = new char[strlen(str.m_pData)+1]; // 此时如果内存不足导致new char抛出异常，m_pData将是一个空指针，这样容易导致程序崩溃。
    strcpy(m_pData, str.m_pData);
    return *this;
     */
    
    if (this != &str) {
        CMyString strTemp(str);
        char *pTemp = strTemp.m_pData;
        strTemp.m_pData = m_pData;
        m_pData = pTemp;
    }
    return *this;
}

CMyString::CMyString(const CMyString& str)
{
    if (this != &str) {
        m_pData = new char[strlen(m_pData)+1];
        strcpy(m_pData, str.m_pData);
    }
}

CMyString::~CMyString(void)
{
    delete []m_pData;
    m_pData = NULL;
}
