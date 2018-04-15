//
//  CStackWithMin.hpp
//  exam
//
//  Created by apple on 16/4/12.
//  Copyright © 2016年 wjc. All rights reserved.
//

#ifndef CStackWithMin_hpp
#define CStackWithMin_hpp

#include <stdio.h>

#endif /* CStackWithMin_hpp */

#include <deque>
#include <assert.h>

template <typename T> class CStackWithMin {
    
public:
    CStackWithMin(void){}
    virtual ~CStackWithMin(void){}
    
    T &top(void);
    const T& top(void) const;
    
    void push(const T& value);
    void pop(void);
    
    const T& min(void)const;
    
private:
    T m_data; // the elements of stack
    T m_minIndex;
};
