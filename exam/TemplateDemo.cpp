//
//  TemplateDemo.cpp
//  exam
//
//  Created by apple on 16/3/24.
//  Copyright © 2016年 wjc. All rights reserved.
//

#include "TemplateDemo.hpp"

template <class T> A<T>::A() {}

template <class T> T A<T>::g(T a, T b) {
    return a + b;
}


