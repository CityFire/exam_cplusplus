//
//  CMyString.hpp
//  exam
//
//  Created by apple on 16/4/6.
//  Copyright © 2016年 wjc. All rights reserved.
//

#ifndef CMyString_hpp
#define CMyString_hpp

#include <stdio.h>

#endif /* CMyString_hpp */

class CMyString
{
public:
    CMyString& operator=(const CMyString &str);
    CMyString(char *pData = NULL);
    CMyString(const CMyString& str);
    ~CMyString(void);
private:
    char *m_pData;
};
