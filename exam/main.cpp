//
//  main.cpp
//  exam
//
//  Created by apple on 16/2/24.
//  Copyright © 2016年 wjc. All rights reserved.
//  红黑树 Tire树 B树 B+树 搜索二叉树 最大堆 最小堆 归并 二分查找 快排 hash表 哈夫曼 LWZ算法 动态规划 贪心 回溯法

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cassert>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include "TemplateDemo.hpp"
#include <exception>
#include <pthread.h>

typedef struct {
    pthread_mutex_t mutex; // Mutex to protect access to the structure
    char *name;
    void **ptr;
    size_t bufsize;
    int freetotal;
    int freecurr;
    
}cache_t;

using namespace std;

#ifndef NDEBUG
const uint64_t redzone_pattern = 0xdeadbeefcafebabe;
int cache_error = 0;
#endif

const int initial_pool_size = 64;

cache_t* cache_create(const char *name, size_t bufsize, size_t align) {
    cache_t *ret = (cache_t *)calloc(1, sizeof(cache_t));
    char* nm = strdup(name);
    void **ptr = (void **)calloc(initial_pool_size, sizeof(void *));
    if (ret == NULL || nm == NULL || ptr == NULL || pthread_mutex_init(&ret->mutex, NULL) == -1) {
        free(ret);
        free(nm);
        free(ptr);
        return NULL;
    }
    
    ret->name = nm;
    ret->ptr = ptr;
    ret->freetotal = initial_pool_size;
#ifndef NDEBUG
    ret->bufsize = bufsize + 2 * sizeof(redzone_pattern);
#else
    ret->bufsize = bufsize;
#endif
    
    return ret;
}

class Solution
{
public:
    // ip字符串输入默认采用IPV4的点分十进制法，合法地址为0.0.0.0-255.255.255.255
    bool isLegalIP(const string& ip)
    {
        int validSegSize = 0; // 记录一共有多少个分段
        
        int oneSeg = 0; // 记录每个分段的数值
        int segLen = 0; // 记录是否分段有数值
        for (int i = 0; i < ip.length(); ++i)
        {
            // 计算每个分段的数值
            if (ip[i] >= '0' && ip[i] <= '9')
            {
                oneSeg = oneSeg * 10 + (ip[i] - '0');
                // 如果分段有数值，就置segLen为1
                ++segLen;
            }
            else if (ip[i] == '.') // 如果此字符为'.'，那么就判断之前的那个分段的值是否合法且是否存在值
            {
                if (oneSeg <= 255 && segLen > 0)
                    validSegSize++;
                else
                    return false;
                
                oneSeg = 0; // 重置分段值
                segLen = 0; // 重置分段是否存在值
            }
            else // 如果出现0-9或'.'以外的字符都判断为非法
                return false;
        }
        
        // 判断最后一个分段的合法性
        if (oneSeg <= 255 && segLen > 0)
            validSegSize++;
        
        // 判断是否一共有四个分段
        if (validSegSize == 4)
            return true;
        else
            return false;
    }
};

bool findMatrix(int *martix, int rows, int columns, int number);
// 二维数组中的查找
bool findMatrix(int *martix, int rows, int columns, int number)
{
    bool found = false;
    if (martix != NULL && rows > 0 && columns > 0) {
        int row = 0;
        int column = columns - 1;
        while (row < rows && column >= 0) {
            if (martix[row * columns + column] == number) {
                found = true;
                break;
            }
            else if (martix[row * columns + column] > number)
                --column;
            else
                ++row;
        }
    }
    return found;
}

// 空格的替换
/*length为字符数组string替换后的总容量*/
void ReplaceBlank(char string[], int length)
{
    if (string == NULL && length <= 0) {
        return;
    }
    /*originalLength为字符串string的实际长度*/
    int originalLength = 0;
    int numberOfBlank = 0;
    int i = 0;
    while (string[i] != '\0') {
        ++originalLength;
        if (string[i] == ' ') {
            ++numberOfBlank;
        }
        ++i;
    }
    /*newLength为把空格替换成'%20'之后的长度*/
    int newLength = originalLength + numberOfBlank * 2;
    if (newLength > length) {
        return;
    }
    int indexOfOriginal = originalLength;
    int indexOfNew = newLength;
    while (indexOfOriginal >= 0 && indexOfNew > indexOfOriginal) {
        if (string[indexOfOriginal] == ' ') {
            string[indexOfNew--] = '0';
            string[indexOfNew--] = '2';
            string[indexOfNew--] = '%';
        }
        else {
            string[indexOfNew--] = string[indexOfOriginal];
        }
        --indexOfOriginal;
    }
}

struct BinaryTreeNode {
    int m_nValue;
    BinaryTreeNode *m_pLeft;
    BinaryTreeNode *m_pRight;
};

/*重建二叉树*/
BinaryTreeNode *ConstructCore(int *startPreorder, int *endPreorder, int *startInorder, int *endInorder)
{
    // 前序遍历序列的第一个数字是根结点的值
    int rootValue = startPreorder[0];
    BinaryTreeNode *root = new BinaryTreeNode();
    root->m_nValue = rootValue;
    root->m_pLeft = root->m_pRight = NULL;
    
    if (startPreorder == endPreorder) {
        if (startInorder == endInorder && *startPreorder == *startInorder) { // 只有一个结点的情况并判断两种遍历序列是否匹配
            return root;
        }
        else {
//            throw std::exception("Invalid input");
        }
    }
    // 在中序遍历中找到根结点的值
    int *rootInorder = startInorder;
    while (rootInorder <= endInorder && *rootInorder != rootValue) {
        ++rootInorder;
    }
    if (rootInorder == endInorder && *rootInorder != rootValue) { //
//        throw std::exception("Invalid input.");
    }
    long leftLength = rootInorder - startInorder;
    int *leftPreorderEnd = startPreorder + leftLength;
    if (leftLength > 0) {
        // 构建左子树
        root->m_pLeft = ConstructCore(startPreorder+1, leftPreorderEnd, startInorder, rootInorder-1);
    }
    if (leftLength < endPreorder - startPreorder) {
        // 构建右子树
        root->m_pRight = ConstructCore(leftPreorderEnd+1, endPreorder, rootInorder+1, endInorder);
    }
    return root;
}

BinaryTreeNode *Construct(int *preoder, int *inorder, int length)
{
    if (preoder == NULL || inorder == NULL || length <= 0) { // 判断二叉树的根结点指针为NULL情况
        return NULL;
    }
    return ConstructCore(preoder, preoder + length - 1, inorder, inorder + length - 1);
}



typedef struct LNode{
    int data;
    struct LNode *prior;
    struct LNode *next;
}LNode, *DLinkList;

int StrToInt(char *string)
{
    int number = 0;
    while (*string != 0) {
        number = number * 10 + *string - '0';
        ++string;
    }
    return number;
}

#define is_digit(a) ((a) >= '0' && (a) <= '9')
#define is_space(a) ((a) == ' ' || (a) == '\t')

int atoi(char* s) {
    if(!s || !*s) return 0;
    while(is_space(*s)) ++s;
    
    int sign = *s != '-';
    if(*s == '+' || *s == '-') ++s;
    if(!is_digit(*s)) return 0;
    
    unsigned v = *s - '0', upper = sign > 0 ? INT_MAX : INT_MIN;;
    while(*++s && is_digit(*s)){
        if(v > upper/10 || (v = v * 10  + (*s-'0')) > upper){
            return sign ? INT_MAX : INT_MIN;
        }
    }
    return sign ? v : -v;
}

// atoi字符串转整型函数 考虑到各种特殊的输入 譬如：输入的字符串中有非数字字符和正负号，要考虑到最大的正整数和最小的负整数以及溢出。当输入的字符串不能转换成整数时，如何做错误处理。对空指针判断并加以特殊处理
/*
int atoi(const char *str)
{
    if(str == NULL)
        return 0;
    const char *p = str;
    char c;
    int i = 0;
    
    if (*str == '-' || *str == '+') { // 如果第一个字符是正负号
        // 则移到下一个字符
        str++;
    }
    
    while ((c = *str++)) {
        if(c >= '0' && c <= '9') {
            i = i * 10 + (c - '0');
        }
        else
            break;
    }
    if (*p == '-') {
        i = -i;
    }
    
    return i;
}
 */

// 用两个栈实现一个队列。 题目：用两个栈实现一个队列。队列的生命如下，请实现它的两个函数appendTail和deleteHead，分别完成在队列尾部插入结点和在队列头部删除结点的功能。

template <typename T> class CQueue
{
public:
    CQueue(void);
    ~CQueue(void);
    void appendtail(const T& node);
    T deleteHead();
private:
    stack<T> stack1;
    stack<T> stack2;
};

// 构造函数
template <typename T> CQueue<T>::CQueue(void)
{
}

// 析构函数
template <typename T> CQueue<T>::~CQueue(void)
{
}

// 插入元素
template <typename T> void CQueue<T>::appendtail(const T& node)
{
    stack1.push(node);
}

// 删除元素并返回
template <typename T> T CQueue<T>::deleteHead()
{
    if(stack2.size()<=0)
    {
        while(stack1.size()>0)
        {
            stack2.push(stack1.top());
            stack1.pop();
        }
    }
    if(stack2.size()==0)
        cout<<"队列为空"<<endl;
//        throw new exception("队列为空");
    T head=stack2.top();
    stack2.pop();
    return head;
}

// 使用两个队列实现一个栈
//解法：

//有两个队列q1和q2，先往q1内插入a，b，c，这做的都是栈的push操作。
//现在要做pop操作，即要得到c，这时可以将q1中的a,b两个元素全部dequeue并存入q2中，这时q2中元素为a，b，对q1再做一次dequeue操作即可得到c。
//如果继续做push操作，比如插入d，f，则把d，f插入到q2中，
//此时若要做pop操作，则做步骤2
//以此类推，就实现了用两个队列来实现一个栈的目的。
//注意在此过程中，新push进来的元素总是插入到非空队列中，空队列则用来保存pop操作之后的那些元素，那么此时空队列不为空了，原来的非空队列变为空了，总是这样循环。

//对于push和pop操作，其时间为O(n).

template <typename T>class CStack
{
public:
    CStack(void){};
    ~CStack(void){};
    void push(const T& node);
    T pop();
private:
    queue<T> queue1;
    queue<T> queue2;
    
};

//插入元素
template <typename T> void CStack<T>::push(const T& element)
{
    if(queue1.size()>0)     // 如果queue1不为空则往queue1中插入元素
        queue1.push(element);
    else if(queue2.size()>0)// 如果queue2不为空则往queue2中插入元素
        queue2.push(element);
    else                    // 如果两个队列都为空，则往queue1中插入元素
        queue1.push(element);
    
}

// 删除元素
template <typename T> T CStack<T>::pop()
{
    if(queue1.size()==0)// 如果queue1为空
    {
        while(queue2.size()>1)// 保证queue2中有一个元素，将其余元素保存到queue1中
        {
            queue1.push(queue2.front());
            queue2.pop();
        }
        T& data=queue2.front();
        queue2.pop();
        return data;
    }
    else// 如果queue2为空
    {
        while(queue1.size()>1)// 保证queue2中有一个元素，将其余元素保存到queue1中
        {
            queue2.push(queue1.front());
            queue1.pop();
        }
        T& data=queue1.front();
        queue1.pop();
        return data;
    }
    
}

//// memcpy内存拷贝函数实现
//void *memcpy(void *dest, const void *src, size_t count)
//{
//    assert(dest != NULL && src != NULL);
//    char *tmp = (char *)dest;
//    const char *s = (const char *)src;
//    while (count--) {
//        *tmp++ = *s++;
//    }
////    while ((*tmp++ = *s++) != '\0');
//    return dest;
//}

char *strcpy(char *strDest, const char *strSrc) // 实现strSrc到strDest的复制
{
    if ((strDest == NULL) || (strSrc == NULL)) //判断参数strDest和strSrc的有效性
    {
        return NULL;
    }
    char *strDestCopy = strDest;        //保存目标字符串的首地址
    while ((*strDest++ = *strSrc++)!='\0'); //把strSrc字符串的内容复制到strDest下
    
    return strDestCopy;
}

// 请写出双向链表的删除目标值nVal的方法，并输出删除数量
DLinkList DLinkListDelete(DLinkList L,int i)
{
    int tempi = 1;
    DLinkList p; //p为查找结点。
    p = L->next;
    while((tempi++) != i && p != NULL)
    {
        p = p->next;
    }
    //检查是不是在双链表中的位置
    if(p == NULL)  printf("位置不合法。\n");
    else if(p->next == NULL) //最后一个结点特殊处理，原因最后一个结点p->next没有prior
    {
        p->prior->next = NULL;
        free(p);
    }
    else //进行删除操作
    {
        p->prior->next = p->next;
        p->next->prior = p->prior;
        free(p);
    }
    return L;
}

//链表结构
struct ListNode
{
    int m_nValue;
    ListNode* m_pNext;
};

//创建一个链表结点
ListNode* CreateListNode(int value)
{
    ListNode *pNode=new ListNode();
    pNode->m_nValue=value;
    pNode->m_pNext=NULL;
    return pNode;
    
}

//遍历链表中的所有结点
void PrintList(ListNode* pHead)
{
    ListNode *pNode=pHead;
    while(pNode!=NULL)
    {
        cout<<pNode->m_nValue<<" ";
        pNode=pNode->m_pNext;
    }
    cout<<endl;
}

//往链表末尾添加结点
/*
 注意这里pHead是一个指向指针的指针，在主函数中一般传递的是引用。
 因为如果要为链表添加结点，那么就会修改链表结构，所以必须传递引用才能够保存修改后的结构。
 */
void AddToTail(ListNode** pHead,int value)
{
    ListNode* pNew=new ListNode();//新插入的结点
    pNew->m_nValue=value;
    pNew->m_pNext=NULL;
    
    if(*pHead==NULL)//空链表
    {
        *pHead=pNew;
    }
    else
    {
        ListNode* pNode=*pHead;
        while(pNode->m_pNext!=NULL)
            pNode=pNode->m_pNext;
        pNode->m_pNext=pNew;
    }
    
}

ListNode* ReverseList(ListNode* pHead)
{
    ListNode* pNode=pHead;//当前结点
    ListNode* pPrev=NULL;//当前结点的前一个结点
    ListNode* pReversedHead=NULL;//反转链表头结点
    while(pNode!=NULL)
    {
        ListNode* pNext=pNode->m_pNext;
        if(pNext==NULL)//如果当前结点的下一个结点为空，那么反转链表的头结点就是当前结点。
            pReversedHead=pNode;
        
        pNode->m_pNext=pPrev;//当前结点指向前一个结点
        
        pPrev=pNode;//pPrev和pNode往前移动。
        pNode=pNext;//这里要使用前面保存下来的pNext，不能使用pNode->m_pNext
    }
    return pReversedHead;//返回反转链表头指针。
}

ListNode* ReverseList2(ListNode* pHead)
{
    ListNode* pNode=pHead;//当前结点
    ListNode* pPrev=NULL;//当前结点的前一个结点
    while(pNode!=NULL)
    {
        ListNode* pNext=pNode->m_pNext;
        pNode->m_pNext=pPrev;//当前结点指向前一个结点
        
        pPrev=pNode;//pPrev和pNode往前移动。
        pNode=pNext;//这里要使用前面保存下来的pNext，不能使用pNode->m_pNext
    }
    return pPrev;//返回反转链表头指针。
}

ListNode * ReverseList_Digui(ListNode* pHead,ListNode* pHead2 = NULL)
{
    if(pHead == NULL)
        return pHead2;
    ListNode * pTemp = pHead->m_pNext;
    pHead->m_pNext = pHead2;
    return ReverseList_Digui(pTemp,pHead);
}

// 创建二叉树结点
BinaryTreeNode *CreateBinaryTreeNode(int value)
{
    BinaryTreeNode *pNode = new BinaryTreeNode;
    pNode->m_pLeft = NULL;
    pNode->m_pRight = NULL;
    pNode->m_nValue = value;
    return pNode;
}

void ConnectTreeNodes(BinaryTreeNode *pParent, BinaryTreeNode *pLeft, BinaryTreeNode *pRight)
{
    if (pParent != NULL) {
        pParent->m_pLeft = pLeft;
        pParent->m_pRight = pRight;
    }
}

void InOrderPrintTree(BinaryTreeNode *pRoot)
{
    cout<<"调用"<<pRoot<<endl;
    // 中序遍历
    if (pRoot != NULL) {
        if (pRoot->m_pLeft != NULL) {
            InOrderPrintTree(pRoot->m_pLeft);
        }
        cout<<"value of this node is "<<pRoot->m_nValue<<endl;
        if (pRoot->m_pRight != NULL) {
            InOrderPrintTree(pRoot->m_pRight);
        }
    }
    else {
        cout<<"this node is null."<<endl;
    }
}

// 在转换成排序双向链表时，原先指向左子结点的指针调整为链表中指向前一个结点的指针，原先指向右子树结点的指针调整为链表中指向后一个结点指针。

void ConvertNode(BinaryTreeNode *pNode,BinaryTreeNode **pLastNodeInList)
{
    if (pNode == NULL) {
        return;
    }
    
    BinaryTreeNode *pCurrent = pNode;
    // 左子树转换，遍历到左子树的叶子结点
    if (pCurrent->m_pLeft != NULL) {
        // 遍历左子树
        ConvertNode(pCurrent->m_pLeft, pLastNodeInList);
    }
    
    pCurrent->m_pLeft = *pLastNodeInList;
    if ((*pLastNodeInList) != NULL) {
        (*pLastNodeInList)->m_pRight = pCurrent;
    }
    
    *pLastNodeInList = pCurrent;
    // 右子树转换
    if (pCurrent->m_pRight != NULL) {
        // 遍历右子树
        ConvertNode(pCurrent->m_pRight, pLastNodeInList);
    }
}

// 转换左子树和右子树
BinaryTreeNode *Convert(BinaryTreeNode *pRootOfTree)
{
    BinaryTreeNode *pLastNodeInList = NULL;     // 指向双向链表的尾接点
    ConvertNode(pRootOfTree, &pLastNodeInList); // 转换排序二叉树为双向链表
    
    // 求双向链表的头结点,我们需要返回头结点
    BinaryTreeNode *pHeadOfList = pLastNodeInList;
    while (pHeadOfList != NULL && pHeadOfList->m_pLeft != NULL) {
        pHeadOfList = pHeadOfList->m_pLeft;
    }
    return pHeadOfList;
}

// 输出双向链表
void PrintList(BinaryTreeNode *pRoot)
{
    BinaryTreeNode *pNode = pRoot;
    while (pNode != NULL) {
        printf("%d\t", pNode->m_nValue);
        pNode = pNode->m_pRight;
    }
    printf("\nPrintList ends.\n");
}

// 二叉搜索树的后序遍历序列 Binary Search Tree
bool VerifySequenceOfBST(int sequence[], int length)
{
    if (sequence == NULL || length <= 0) {
        return false;
    }
    
    int root = sequence[length - 1];
    
    // 在二叉搜索树中左子树的结点小于根节点
    int i = 0;
    for (; i < length - 1; ++i) {
        if (sequence[i] > root) {
            break;
        }
    }
    // 在二叉搜索树中右子树的结点大于根结点
    int j = i;
    for (; j < length - 1; ++j) {
        if (sequence[j] < root) {
            return false;
        }
    }
    // 判断左子树是不是二叉搜索树
    bool left = true;
    if (i > 0) {
        left = VerifySequenceOfBST(sequence, i);
    }
    // 判断右子树是不是二叉搜索树
    bool right = true;
    if (i < length - 1) {
        right = VerifySequenceOfBST(sequence + i, length - i - 1);
    }
    
    return (left && right);
}

template <typename AnyType>

void Swap(AnyType &a, AnyType &b)
{
    AnyType temp;
    temp = a;
    a = b;
    b = temp;
}

// 全排列
void Permutation(char string[], int start, size_t end)
{
    if (string == NULL) {
        return;
    }
    if(start == end) {
        cout<<string<<endl;
    }
    else {
        for (int i = start; i <= end; i++) {
            Swap(string[i], string[start]);
            Permutation(string, start+1, end);
            Swap(string[i], string[start]);
        }
    }
}

void Permutation(char *pStr, char *pBegin)
{
    if (*pBegin == '\0') {
        printf("%s\n", pStr);
    }
    else {
        for (char *pCh = pBegin; *pCh != '\0'; ++pCh) {
            char temp = *pCh;
            *pCh = *pBegin;
            *pBegin = temp;
            
            Permutation(pStr, pBegin + 1);
            
            temp = *pCh;
            *pCh = *pBegin;
            *pBegin = temp;
        }
    }
}

void Permutation(char *pStr)
{
    if (pStr == NULL) {
        return;
    }
    Permutation(pStr, pStr);
}

bool fun2(int b, int c, int *a)
{
    return true;
}

const int *fun(int x, int y)
{
    int b = x+y;
    int *c = &b;
    
    return c;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/*生成一个在start和end之间的随机数*/
int RandomInRange(int start, int end)
{
    int rand = static_cast<int>(random());
    do {
        rand = static_cast<int>(random());
    } while (rand > start && rand < end);
    return rand;
}

// 快速排序算法的关键在于先在数组中选择一个数字，接下来把数组中的数字分为两部分，比选择的数字小的数字移到数组的左边，比选择的数字大的数字移到数组的右边
int Partition(int data[], int length, int start, int end)
{
    if (data == NULL || length <= 0 || start < 0 || end >= length) {
        //        throw new std::exception("Invalid Parameters");
        return -1;
    }
    int index = RandomInRange(start, end);
    swap(&data[index], &data[end]);
    
    int small = start - 1;
    for (index = start; index < end; ++index) {
        if (data[index] < data[end]) {
            ++small;
            if (small != index) {
                swap(&data[index], &data[small]);
            }
        }
    }
    ++small;
    swap(&data[small], &data[end]);
    
    return small;
}

void QuickSort(int data[], int length, int start, int end)
{
    if (start == end) {
        return;
    }
    int index = Partition(data, length, start, end);
    if (index > start) {
        QuickSort(data, length, start, index - 1);
    }
    if (index < end) {
        QuickSort(data, length, index + 1, end);
    }
}

void Qsort(int a[], int low, int high)
{
    cout<<"循环一次"<<endl;
    if(low >= high)
    {
        return;
    }
    int first = low;
    int last = high;
    int key = a[first];/*用字表的第一个记录作为枢轴*/
    
    while(first < last)
    {
        while(first < last && a[last] >= key)
        {
            --last;
        }
        
        a[first] = a[last];/*将比第一个小的移到低端*/
        
        while(first < last && a[first] <= key)
        {
            ++first;
        }
        
        a[last] = a[first];
        /*将比第一个大的移到高端*/
    }
    a[first] = key;/*枢轴记录到位*/
    Qsort(a, low, first-1);
    Qsort(a, first+1, high);
}

void SortAges(int ages[], int length)
{
    if (ages == NULL || length <= 0) {
        return;
    }
    const int oldestAge = 99;
    int timesOfAge[oldestAge+1];
    for (int i = 0; i <= oldestAge; i++) {
        timesOfAge[i] = 0;
    }
    for (int i = 0; i < length; i++) {
        int age = ages[i];
        if (age > oldestAge || age < 0) {
//            throw new std::exception("age out of range.");
        }
        ++timesOfAge[age];
        cout<<"age为"<<age<<"的次数为:"<<timesOfAge[age]<<endl;
    }
    
    int index = 0;
    for (int i = 0; i <= oldestAge; i++) {
        for (int j = 0; j < timesOfAge[i]; j++) {
            ages[index] = i;
            index++;
        }
    }
}

// 旋转数组的最小数字 二分查找
int MinInOrder(int *numbers, int index1, int index2)
{
    int result = numbers[index1];
    for (int i = index1 + 1; i <= index2; i++) {
        if (result > numbers[i]) {
            result = numbers[i];
        }
    }
    return result;
}

int MinNumber(int *numbers, int length) // 考查思维的全面性。排序数组本身是数组旋转的一个特例。另外考虑数组中有相同数字的特例
{
    if (numbers == NULL || length <= 0) {
//        throw new std::exception("Invalid parameters");
    }
    int index1 = 0;
    int index2 = length - 1;
    int indexMid = index1; // 之所以把indexMid初始化为index1，是因为有特例，如果把排序数组的前面0个元素搬到最后面，即排序数组本身，这仍然是数组的一个旋转，
    while (numbers[index1] >= numbers[index2]) {
        if (index2 - index1 == 1) {
            indexMid = index2;
            break;
        }
        indexMid = (index1 + index2) / 2;
        // 如果下标为index1、index2和indexMid指向的三个数字相等，则只能顺序查找
        if (numbers[index1] == numbers[index2] && numbers[indexMid] == numbers[index1]) {
            return MinInOrder(numbers, index1, index2);
        }
        
        if (numbers[indexMid] >= numbers[index1]) {
            index1 = indexMid;
        }
        else if (numbers[indexMid] <= numbers[index2]) {
            index2 = indexMid;
        }
    }
    return numbers[indexMid];
}

// 递归
int AddFrom1ToN_Recursive(int n)
{
    return n <= 0 ? 0 : n + AddFrom1ToN_Recursive(n - 1);
}

int AddFrom1ToN_Iterative(int n)
{
    int result = 0;
    for (int i = 1; i <= n; i++) {
        result += i;
    }
    return result;
}

long long Fibonacci(unsigned n) // 第三种方法 转换成求矩阵的乘方
{
    int result[2] = {0, 1};
    if (n < 2) {
        return result[n];
    }
    long long fibNMinusOne = 1;
    long long fibNMinusTwo = 0;
    long long fibN = 0;
    for (unsigned int i = 2; i <= n; ++i) {
        fibN = fibNMinusOne + fibNMinusTwo;
        fibNMinusTwo = fibNMinusOne;
        fibNMinusOne = fibN;
    }
    return fibN;
}

// 二进制中1的个数
int NumberOf1(int n) // 右移考虑负数，当为负数，最高位为1，导致出现0xFFFFFFFF进入死循环
{
    int count = 0;
    unsigned int flag = 1; // 复杂度为o(n),有多少个位数就得循环多少次
    while (flag) {
        if (n & flag) {
            count++;
        }
        flag = flag << 1;
    }
    return count;
}

// 把一个整数1100减去1得到1011，再和原整数做与运算得到1000，会把该整数最右边一个1变成0.那么一个整数的二进制表示中有多少个1，就可以进行多少次这样的操作。
int NumberOf1InBinary(int n) // 1.一个整数如果是2的整数次方，那么它的二进制表示中有且只有一位是1，其他位都是0.把整数减去1之后再和它自己做与运算 ，这个整数中唯一的1就会变成0.      2.输入两个整数m和n,计算需要改变m的二进制表示中的多少位才能得到0.第一步求这两个数的异或，第二步统计异或结果中1的位数。 举一反三：把一个整数减去1之后再和原整数做位与运算，得到的结果相当于是把整数的二进制表示中的最右边一个1变成0.
{
    int count = 0;
    while (n) {
        ++count;
        n = (n - 1) & n;
    }
    return count;
}

// 基数的几次方
bool equal(double num1, double num2)
{
    if ((num1 - num2 > -0.0000001) && (num1 - num2 < 0.0000001)) {
        return true;
    }
    else {
        return false;
    }
}

double PowerWithUnsignedExponent(double base, unsigned int exponent) // 左移
{
    /*
    double result = 1.0;
    for (int i = 1; i <= exponent; ++i) {
        result *= base;
    }
    return result;
     */
    if (exponent == 0) {
        return 1;
    }
    if (exponent == 1) {
        return base;
    }
    
    double result = PowerWithUnsignedExponent(base, exponent >> 1);
    result *= result;
    if ((exponent & 0x1) == 1) { // 判断是否是奇数，如果是奇数，则需要再一次乘以基数base。位与运算代替了求余运算符%来判断一个数是奇数还是偶数。
        result *= base;
    }
    return result;
}

bool g_InvalidInput = false;

double Power(double base, int exponent)
{
    g_InvalidInput = false;
    if (equal(base, 0.0) && exponent < 0) {
        g_InvalidInput = true;
        return 0.0;
    }
    
    unsigned int absExponent = (unsigned int)(exponent);
    if (exponent < 0) {
        absExponent = (unsigned int)(-exponent);
    }
    double result = PowerWithUnsignedExponent(base, absExponent);
    if (exponent < 0) {
        result = 1.0 / result;
    }
    return result;
}

bool Increment(char *number)
{
    bool isOverflow = false;
    int nTakeOver = 0;
    int nLength = static_cast<int>(strlen(number));
    for (int i = nLength - 1; i >= 0; i--) {
        int nSum = number[i] - '0' + nTakeOver;
        if (i == nLength - 1) {
            nSum++;
        }
        if (nSum >= 10) {
            if (i == 0) {
                isOverflow = true;
            }
            else {
                nSum -= 10;
                nTakeOver = 1;
                number[i] = '0' + nSum;
            }
        }
        else {
            number[i] = '0' + nSum;
            break;
        }
    }
    return isOverflow;
}

void PrintNumber(char *number)
{
    bool isBeginning0 = true;
    int nLength = static_cast<int>(strlen(number));
    for (int i = 0; i < nLength; i++) {
        if (isBeginning0 && number[i] != '0') {
            isBeginning0 = false;
        }
        if (!isBeginning0) {
            printf("%c", number[i]);
        }
    }
    printf("\t");
}

void Printf1ToMaxOfDigitsRecursively(char *number, int length, int index)
{
    if (index == length - 1) {
        PrintNumber(number);
        return;
    }
    
    for (int i = 0; i < 10; ++i) {
        number[index + 1] = i + '0';
        Printf1ToMaxOfDigitsRecursively(number, length, index + 1);
    }
}

void Print1ToMaxOfNDigits(int n)
{
    if (n < 0) {
        return;
    }
    char *number = new char[n+1];
    memset(number, '0', n);
    number[n] = '\0';
    /* 第一种做法
    while (!Increment(number)) {
        PrintNumber(number);
    }
     */
    
    /* 第二种做法 */
    for (int i = 0; i < 10; ++i) {
        number[0] = i + '0';
        Printf1ToMaxOfDigitsRecursively(number, n, 0);
    }
    delete []number;
}

void RecorderOddEven(int *pData, unsigned int length)
{
    if (pData == NULL || length == 0) {
        return;
    }
    int *pBegin = pData;
    int *pEnd = pData + length - 1;
    while (pBegin < pEnd) {
        // 向后移动pBegin,直到它指向偶数
        while (pBegin < pEnd && (*pBegin & 0x1) != 0) {
            pBegin++;
        }
        // 向前移动pEnd,直到它指向奇数
        while (pBegin < pEnd && (*pEnd & 0x1) == 0) {
            pEnd--;
        }
        if (pBegin < pEnd) {
            int temp = *pBegin;
            *pEnd = temp;
            *pBegin = *pEnd;
        }
    }
    
//    Recorder(pData, length, isEven);
}

void Recorder(int *pData, unsigned int length, bool (*func)(int))
{
    if (pData == NULL || length == 0) {
        return;
    }
    int *pBegin = pData;
    int *pEnd = pData + length - 1;
    while (pBegin < pEnd) {
        // 向后移动pBegin,直到它指向偶数
        while (pBegin < pEnd && !func(*pBegin)) {
            pBegin++;
        }
        // 向前移动pEnd,直到它指向奇数
        while (pBegin < pEnd && func(*pEnd)) {
            pEnd--;
        }
        if (pBegin < pEnd) {
            int temp = *pBegin;
            *pEnd = temp;
            *pBegin = *pEnd;
        }
    }
}

bool isEven(int n)
{
    return (n & 0x1) == 0;
}

// 栈的压人、弹出序列
bool IsPopOrder(const int *pPush, const int *pPop, int nLength)
{
    bool bPossible = false;
    
    if (pPush != NULL && pPop != NULL && nLength > 0) {
        const int *pNextPush = pPush;
        const int *pNextPop = pPop;
        
        std::stack<int>stackData;
        while (pNextPop - pPop < nLength) {
            while (stackData.empty() || stackData.top() != *pNextPop) {
                if (pNextPush - pPush == nLength) {
                    break;
                }
                stackData.push(*pNextPush);
                pNextPush++;
            }
            
            if (stackData.top() != *pNextPop) {
                break;
            }
            
            stackData.pop();
            pNextPop++;
        }
        if (stackData.empty() && pNextPop - pPop == nLength) {
            bPossible = true;
        }
    }
    
    return bPossible;
}

// 从上往下打印二叉树

void PrintFromTopToBottom(BinaryTreeNode *pTreeRoot) // 不管是广度优先遍历一个有向图还是一棵树，都要用到队列。
{
    if (!pTreeRoot) {
        return;
    }
    std::deque<BinaryTreeNode *>dequeTreeNode;
    dequeTreeNode.push_back(pTreeRoot);
    while (dequeTreeNode.size()) {
        BinaryTreeNode *pNode = dequeTreeNode.front();
        dequeTreeNode.pop_front();
        printf("%d", pNode->m_nValue);
        
        if (pNode->m_pLeft) {
            dequeTreeNode.push_back(pNode->m_pLeft);
        }
        if (pNode->m_pRight) {
            dequeTreeNode.push_back(pNode->m_pRight);
        }
    }
    
}

// 二叉搜索树的后序遍历序列
bool VerifySquenceOfBST(int sequence[], int length)
{
    if (sequence == NULL || length <= 0) {
        return false;
    }
    
    int root = sequence[length - 1];
    // 在二叉搜索树中左子树的结点小于根结点
    int i = 0;
    for (; i < length; ++i) {
        if (sequence[i] > root) {
            break;
        }
    }
    
    // 在二叉搜索树种右子树的结点大于根结点
    int j = i;
    for (; j < length - 1; ++j) {
        if (sequence[j] < root) {
            return false;
        }
    }
    // 判断左子树是不是二叉搜索树
    bool left = true;
    if (i > 0) {
        left = VerifySquenceOfBST(sequence, i);
    }
    // 判断右子树是不是二叉搜索树
    bool right = true;
    if (i < length - 1) {
        right = VerifySquenceOfBST(sequence + i, length - i - 1);
    }
    return (left && right);
}

// 二叉树中和为某一值的路径
void FindPath(BinaryTreeNode *pRoot, int expectedSum, std::vector<int>& path, int& currentSum)
{
    currentSum += pRoot->m_nValue;
    path.push_back(pRoot->m_nValue);
    
    // 如果是叶结点，并且路径上结点的和等于输入的值
    // 打印出这条路径
    bool isLeaf = pRoot->m_pLeft == NULL && pRoot->m_pRight == NULL;
    if (currentSum == expectedSum && isLeaf) {
        printf("A path is found: ");
//        std::vector<int>::iterator iter = path.begin();
        auto iter = path.begin(); // 等同于上面
        for (; iter != path.end(); ++iter) {
            printf("%d\t", *iter);
        }
        printf("\n");
    }
    
    // 如果不是叶结点，则遍历它的结点
    if (pRoot->m_pLeft != NULL) {
        FindPath(pRoot->m_pLeft, expectedSum, path, currentSum);
    }
    if (pRoot->m_pRight != NULL) {
        FindPath(pRoot->m_pRight, expectedSum, path, currentSum);
    }
    
    // 在返回到父结点之前，在路径上删除呢当前结点，并在currentSum中减去当前结点的值
    currentSum -= pRoot->m_nValue;
    path.pop_back();
}

void FindPath(BinaryTreeNode *pRoot, int expectedSum)
{
    if (pRoot == NULL || expectedSum <= 0) {
        return;
    }
    std::vector<int>path;
    int currentSum = 0;
    FindPath(pRoot, expectedSum, path, currentSum);
}

// 复杂链表的复制
struct ComplexListNode
{
    int             m_nValue;
    ComplexListNode *m_pNext;
    ComplexListNode *m_pSibling;
};

void CloneNodes(ComplexListNode *pHead) // 复制原始链表的任意结点N并创建新结点N‘，再把N’链接到N的后面。
{
    ComplexListNode *pNode = pHead;
    while (pNode != NULL) {
        ComplexListNode *pCloned = new ComplexListNode();
        pCloned->m_nValue = pNode->m_nValue;
        pCloned->m_pNext = pNode->m_pNext;
        pCloned->m_pSibling = NULL;
        
        pNode->m_pNext = pCloned;
        pNode = pCloned->m_pNext;
    }
}

void ConnectSiblingNodes(ComplexListNode *pHead) // 如果原始链表上的结点N的m_pSibling指向S，则它对应的复制结点N‘的m_pSibling指向S的下一结点S’。
{
    ComplexListNode *pNode = pHead;
    while (pNode != NULL) {
        ComplexListNode *pCloned = pNode->m_pNext;
        if (pNode->m_pSibling != NULL) {
            pCloned->m_pSibling = pNode->m_pSibling->m_pNext;
        }
        pNode = pCloned->m_pNext;
    }
}

ComplexListNode *ReconnectNodes(ComplexListNode *pHead) // 把第二步得到的链表拆分成两个链表，奇数位置上的结点组成原始链表，偶数位置上的结点组成复制出来的链表。
{
    ComplexListNode *pNode = pHead;
    ComplexListNode *pClonedHead = NULL;
    ComplexListNode *pClonedNode = NULL;
    if (pNode != NULL) {
        pClonedHead = pClonedNode = pNode->m_pNext;
        pNode->m_pNext = pClonedNode->m_pNext;
        pNode = pNode->m_pNext;
    }
    
    while (pNode != NULL) {
        pClonedNode->m_pNext = pNode->m_pNext;
        pClonedNode = pClonedNode->m_pNext;
        pNode->m_pNext = pClonedNode->m_pNext;
        pNode = pNode->m_pNext;
    }
    return pClonedNode;
}

ComplexListNode *Clone(ComplexListNode *pHead)
{
    CloneNodes(pHead);
    ConnectSiblingNodes(pHead);
    return ReconnectNodes(pHead);
}

bool g_bInputInvalid = false;
bool CheckInvalidArray(int *numbers, int length)
{
    g_InvalidInput = false;
    if (numbers == NULL && length <= 0) {
        g_InvalidInput = true;
    }
    return g_InvalidInput;
}

bool CheckMoreThanHalf(int *numbers, int length, int number)
{
    int times = 0;
    for (int i = 0; i < length; i++) {
        if (numbers[i] == number) {
            times++;
        }
    }
    
    bool isMoreThanHalf = true;
    if (times * 2 <= length) {
        g_InvalidInput = true;
        isMoreThanHalf = false;
    }
    
    return isMoreThanHalf;
}

int MoreThanHalfNum(int *numbers, int length)
{
    if (CheckInvalidArray(numbers, length)) {
        return 0;
    }
    
    int middle = length >> 1;
    int start = 0;
    int end = length - 1;
    int index = Partition(numbers, length, start, end);
    while (index != middle) {
        if (index > middle) {
            end = index - 1;
            index = Partition(numbers, length, start, end);
        }
        else {
            start = index + 1;
            index = Partition(numbers, length, start, end);
        }
    }
    
    int result = numbers[middle];
    if (!CheckMoreThanHalf(numbers, length, result)) {
        result = 0;
    }
    return result;
}

typedef multiset<int, greater<int> > intSet;
typedef multiset<int, greater<int> >::iterator setIterator;
void GetLeastNumbers(const vector<int>& data, intSet& leastNumbers, int k)
{
    leastNumbers.clear();
    if (k < 1 || data.size() < k) {
        return;
    }
    
    vector<int>::const_iterator iter = data.begin();
    for (; iter != data.end(); ++iter) {
        if ((leastNumbers.size()) < k) {
            leastNumbers.insert(*iter);
        }
        else {
            setIterator iterGreatest = leastNumbers.begin();
            if (*iter < *(leastNumbers.begin())) {
                leastNumbers.erase(iterGreatest);
                leastNumbers.insert(*iter);
            }
        }
    }
}

int FindGreatestSumOfSubArray(int *pData, int nLength)
{
    if (pData == NULL || (nLength <= 0)) {
        g_InvalidInput = true;
        return 0;
    }
    g_InvalidInput = false;
    
    int nCurSum = 0;
    int nGreatestSum = 0x80000000;
    for (int i = 0; i < nLength; ++i) {
        if (nCurSum <= 0) {
            nCurSum = pData[i];
        }
        else {
            nCurSum += pData[i];
        }
        if (nCurSum > nGreatestSum) {
            nGreatestSum = nCurSum;
        }
    }
    return nGreatestSum;
}

// 动态规划


void reverse_c(char arr[], int start, int end)
{
    int mid = (start + end) / 2;
    for (int s = start, i = 1; i < mid; s++, i++) {
        char temp = arr[s];
        arr[s] = arr[end - i];
        arr[end - 1] = temp;
    }
}

void useReverse_c(char arr[], int len, int m)
{
    reverse_c(arr, 0, m);
    reverse_c(arr, m, len);
    reverse_c(arr, 0, len);
}

class AA
{
private:
    int n1;
    int n2;
public:
    AA():n2(0), n1(n2 + 2)
    {
        
    }
    
    void Print()
    {
        std::cout << "n1: " << n1 << ", n2: " << n2 << std::endl;
    }
};

int main(int argc, const char * argv[]) {
    
    AA a22;
    a22.Print();
    
    Solution solution;
    cout<<solution.isLegalIP("129.45.354.34")<<endl;
    cout<<solution.isLegalIP("129.45.54.34")<<endl;
    cout<<solution.isLegalIP("329.45.54.34")<<endl;
    
//    int *ptr = const_cast<int *>(fun(2,3));
    
    string str88 = "012345678";
    
    //求出字符串的长度
    int len8 = str88.length();
    
    for (int i = 0; i<len8/2; i++)
    {
        //前后交换
        char temp = str88[i];
        str88[i] = str88[len8-i-1];
        str88[len8-i-1] = temp;
    }
    
    //输出交换后的字符串
    cout<<str88<<endl;
    
    
    double d1, d2;
    d1 = 1.001;
    d2 = 1.0001;
    cout << equal(d1, d2) << endl;    // 由于精度原因不能用等号判断两个小数是否相等。
    // 判断两个小数是否相等，只能判断他们之差的绝对值是不是在一个很小的范围内。比如小于0.0000001
    
    cout<<Power(2, 8)<<endl;
    cout<<Power(2, 0)<<endl;
    cout<<Power(0, 2)<<endl;
    cout<<Power(0, -2)<<endl;
    cout<<Power(2, -3)<<endl;
    // 判断g_InvalidInput
    
    cout<<NumberOf1(11)<<endl;
    cout<<NumberOf1(-11)<<endl;
    cout<<NumberOf1InBinary(12)<<endl;
    cout<<NumberOf1InBinary(-12)<<endl;
    
    cout<<AddFrom1ToN_Recursive(101819)<<endl; // 当数据够大时，会调用栈会溢出。 递归时，内存栈中分配空间以保存参数，返回地址，临时变量等，而且往栈中压人数据和弹出数据都需要时间，每个进程栈容量有限 空间和时间消耗
    cout<<AddFrom1ToN_Iterative(101819)<<endl;
    
    // 快速排序
    int arr[] = {1, 57, 68, 59, 52, 72, 28, 96, 33, 24};
    Qsort(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1);/*这里原文第三个参数要减1否则内存越界*/
    
    for(int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        cout << arr[i] << " ";
    }
    
//    QuickSort(arr, 9, 0, 8);
//    for (int i = 0; i < 9; i++) {
//        cout<<" "<<arr[i]<<",";
//    }
    cout<<endl;
    int ages[] = {1, 57, 68, 59, 52, 52, 57, 25, 34, 25, 24, 23, 24, 72, 28, 96, 33, 24, 25, 25};
    SortAges(ages, sizeof(ages) / sizeof(ages[0]));
    
    for(int i = 0; i < sizeof(ages) / sizeof(ages[0]); i++)
    {
        cout << ages[i] << " ";
    }
    
    cout<<endl;
    
//    int arr2[] = {6, 8, 9, 11, 1, 1, 2, 5};
//    int arr3[] = {1, 0, 1, 1, 1}; // {1, 1, 1, 0, 1}
    int arr3[] = {1, 1, 1, 0, 1};
    int minNm = MinNumber(arr3, sizeof(arr3)/sizeof(arr3[0]));
    cout<<"最小数字为:"<<minNm;
    
    cout<<endl;
    
    CStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    
    int len=4;
    while(len>0)
    {
        cout<<stack.pop()<<" ";
        --len;
    }
    
    cout<<endl;
    
    CQueue<int> queue;
    queue.appendtail(1);
    queue.appendtail(2);
    queue.appendtail(3);
    queue.appendtail(4);
    len=4;
    while(len>0)
    {
        cout<<queue.deleteHead()<<endl;
        --len;
    }
    system("pause");
    
    int a[][4] = {{1,2,8,9},{2,4,9,5},{4,7,10,13},{6,8,11,15}};
    cout << findMatrix((int *)a, 4, 4, 11) <<endl;
    
    char str[16] = "we are  happy! ";
    ReplaceBlank(str, 24);
    cout<<"str="<<str<<endl;
    
    std::cout << "Hello, World!\n";
    cout << "最大值：" << (numeric_limits<int>::max)();
    cout << "\t最小值：" << (numeric_limits<int>::min)() << endl;
    printf("%d\n", atoi("2147483648"));
    printf("%d\n", atoi("2147483647"));
    printf("%d\n", atoi("-2147483648"));
    printf("%d\n", atoi("-2147483649"));
    
    char strSrc[] = "Hello, World!\nyyyy";   //要被复制的源字符串
    char strDest[20];                  //要复制到的目的字符数组

    strcpy(strDest, strSrc);
    printf("strDest: %s\n", strDest);
    /*
    memcpy(strDest, strSrc, 4);    //复制strSrc的前4个字符到strDest中
    strDest[4] = '\0';             //把strDest的第5个元素赋为结束符'\0'
    printf("strDest: %s\n", strDest);
     */
    
//    Hello, World!
//    12345
//strDest: Hello, World!
//    yyyy
//strDest: Hell
    
    /*
    int i;
    for(i=0; i<2; i++){
        fork();
        printf("g");
    }
    
    wait(NULL);
    wait(NULL);
// gggggggg
    
    for(i=0; i<2; i++){
        fork();
        printf("\ng  ppid=%d, pid=%d, i=%d \n", getppid(), getpid(), i);
    }
    
    wait(NULL);
    wait(NULL);
    
    printf("\nstart the dead loop\n");
//    while(1)
//    {
//        printf("/b->");
//        fflush(stdout);//刷新输出缓冲区
//        usleep(100000);
//    }
     */
    
    
    //创建结点
    ListNode* pNode1=CreateListNode(1);//创建一个结点
    PrintList(pNode1);//打印
    //往链表中添加新结点
    AddToTail(&pNode1,2);//为链表添加一个结点
    AddToTail(&pNode1,3);//为链表添加一个结点
    AddToTail(&pNode1,4);//为链表添加一个结点
    AddToTail(&pNode1,5);//为链表添加一个结点
    AddToTail(&pNode1,6);//为链表添加一个结点
    AddToTail(&pNode1,7);//为链表添加一个结点
    //打印链表
    PrintList(pNode1);//打印
    //反转链表
    ListNode* pReversedHead=ReverseList(pNode1);
    PrintList(pReversedHead);//打印
    
    system("pause");
    
    
    //            10
    //         /      \
    //        6        14
    //       /\        /\
    //      4  8     12  16
    //创建树结点
    BinaryTreeNode *pNode10 = CreateBinaryTreeNode(10);
    BinaryTreeNode *pNode6 = CreateBinaryTreeNode(6);
    BinaryTreeNode *pNode14 = CreateBinaryTreeNode(14);
    BinaryTreeNode *pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode *pNode8 = CreateBinaryTreeNode(8);
    BinaryTreeNode *pNode12 = CreateBinaryTreeNode(12);
    BinaryTreeNode *pNode16 = CreateBinaryTreeNode(16);
    //连接树结点
    ConnectTreeNodes(pNode10, pNode6, pNode14);
    ConnectTreeNodes(pNode6, pNode4, pNode8);
    ConnectTreeNodes(pNode14, pNode12, pNode16);
    
    InOrderPrintTree(pNode10);//中序遍历
    BinaryTreeNode *pHeadOfList=Convert(pNode10);//获取双向链表头结点
    PrintList(pHeadOfList);//输出链表
    
    system("pause");
    
    char string[] = "abcde";
    size_t length = strlen(string);
    Permutation(string, 0, length-1);
    
    vector<int> v1;
    
    vector<int>::iterator Iter;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);
    v1.push_back(10);
//    v1.push_back(50);
    cout<<"v1=" ;
    for (Iter = v1.begin(); Iter != v1.end(); Iter++) {
        cout<<" "<<*Iter;
    }
    cout<<endl;
    v1.erase(v1.begin());
    cout<<"v1=";
    for (Iter = v1.begin(); Iter != v1.end(); Iter++) {
        cout<<" "<<*Iter;
    }
    
    // 1.第一种方案
    /*
    for(Iter = v1.begin(); Iter != v1.end(); Iter++)
    {
        if(*Iter == 10)
        {
            v1.erase(Iter);  // 如果最后一个元素为10，删除最后一个10时，返回值为下一个元素，而下一个元素没有了，导致迭代器失效变为野指针，需要把旧容器整成新的容器
//            Iter = v1.begin(); // 当erase后，旧的容器会被重新整理成一个新的容器
        }
    }
     */
    
    for(Iter = v1.begin(); Iter != v1.end(); Iter++)
    {
        if(*Iter == 10)
        {
            Iter = v1.erase(Iter);//Iter为删除元素的下一个元素的迭代器
            //即第一次这段语句后Iter 会是20，大家可以通过debug调试出来查看下数值
        }
        
        if(Iter == v1.end()) //要控制迭代器不能超过整个容器
        { 
            break;
        } 
    }
    
    cout<<endl;
    cout<<"v1=";
    for (Iter = v1.begin(); Iter != v1.end(); Iter++) {
        cout<<" "<<*Iter;
    }
    
    cout<<endl;
    vector<int>::iterator itera = v1.erase(v1.begin()+1, v1.begin()+3);
    cout<<" "<<*itera<<endl; // 返回值是一个迭代器，指向删除元素下一个元素
    cout<<"v1=";
    for (Iter = v1.begin(); Iter != v1.end(); Iter++) {
        cout<<" "<<*Iter;
    }
    cout<<endl;
    
    int k;
    float f;
    f = (float)k;
    f = static_cast<float>(k);
    
    // 2.const_case
    
    
//    A<int> a;
//    cout<<a.g(2, 5)<<endl;
    
//    double *a;
//    double *b;
//    double a1 = 4.74;
//    double b1 = 5.43;
//    a = &a1;
//    b = &b1;
//    Swap(a, b);
//    
//    cout<<"a="<<*a<<" "<<"b="<<*b<<endl;
//    
//    int i = 10;
//    int j = 30;
//    cout<< "i, j= "<<i<<", "<<j<<".\n";
//    Swap(i,j);
//    cout<<"now i, j = "<<i<<","<<j<<".\n";
    
    
    
    
    
    return 0;
}
