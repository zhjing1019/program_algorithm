#include<iostream>

#include<stdio.h>
#include<stdlib.h>
#define OK 1				//操作成功
#define ERRO 0				//操作失败
#define MAX_LENGTH 100		//初次创建栈的最长长度
#define ADD_LENGTH 40		//每次扩展栈的长度
typedef int State;			//利用BOOL表示操作是否成功
typedef int EmType;

typedef struct {
    EmType* s;			//数据
    int top;			//当前栈顶位置
    int maxSize;		//最大长度
}Stack, *linkStack;

//函数声明
State isFullStack(Stack s);						//判断栈满
State creatStack(linkStack s_link);				//创建空栈
State increaseStack(linkStack s_link);			//为栈重新分配空间
State pushStack(linkStack s_link, EmType ch);		//压栈
State isEmptyStack(linkStack s_link);			//判断栈空
EmType popStack(linkStack s_link);				//弹栈
void destroyStack(linkStack s);				//销毁栈

using namespace std;
linkStack getMulResult(Stack p1, Stack p2, linkStack lsq);
Stack getFinalResult(int number, Stack sq);
Stack getCoupledResult(int number, Stack sq, bool IsOne);

int main() {
    int number;
    cin >> number;
    double run_time;

    Stack sq;
    if (!creatStack(&sq)) {
        cout << "栈空间创建失败" << endl;
        exit(0);
    }

    int Num = number;
    //将数据压入栈
    while (number!=0) {
        int _number = number % 10;
        if (!pushStack(&sq, _number)) {
            cout << "压栈失败!" << endl;
            exit(0);
        }
        number = number / 10;
    }
    Stack ResultS = getFinalResult(Num, sq);
    for (int i = ResultS.top; i >= 0; i--) {
        //cout << result->s[i];
        printf("%d", ResultS.s[i]);
    }
    destroyStack(&ResultS);

    getchar();
    getchar();

}

Stack getFinalResult(int number, Stack sq) {
    if (number < 2) {
        return sq;
    }
    int ComNum = 2;
    while (ComNum <= number) {
        ComNum *= 2;
    }
    ComNum /= 2;
    Stack CouSq = getCoupledResult(ComNum, sq,true);
    int AloneNumber = number - ComNum;
    Stack AloneSq;
    if (AloneNumber > 0) {
        //处理剩余元素
        AloneSq = getFinalResult(AloneNumber, sq);
        //destroyStack(&sq);
        Stack s;
        linkStack result = &s;
        creatStack(result);
        getMulResult(CouSq, AloneSq, result);
        destroyStack(&CouSq);
        destroyStack(&AloneSq);
        return *result;
    }
    else{
        //内部无剩余
        //destroyStack(&sq);
        return CouSq;
    }
}

Stack getCoupledResult(int number, Stack sq,bool IsOne) {
    if (number <= 1) {
        return sq;
    }
    Stack s;
    linkStack result = &s;
    creatStack(result);
    Stack ResultSq = *getMulResult(sq, sq, result);
    if (!IsOne) {
        destroyStack(&sq);
    }
    return getCoupledResult(number / 2, ResultSq,false);
}


linkStack getMulResult(Stack p1, Stack p2, linkStack lsq) {
    if (p2.top > p1.top) {
        Stack t = p1;
        p1 = p2;
        p2 = t;

    }
    creatStack(lsq);
    int ComIndex = 0;
    if (p1.top <= -1 || p2.top <= -1) {
        cout << "两数相乘传入数据不正确,已返回空栈！" << endl;
        return lsq;
    }
    int MaxIndex = p1.top > p2.top? p1.top: p2.top;			//两数中最长位数
    int MinIndex = p2.top < p1.top?p2.top:p1.top;
    int SumIndex = p1.top + p2.top;							//结果位数总和
    int NextAdd = 0;
    for (int i = 0; i <= SumIndex; i++) {
        //t和z为移动标志，用于记录那位相乘
        int t = i;
        if (i > MaxIndex) {
            t = MaxIndex;
        }
        int z = 0;
        int AddResult = NextAdd;				//保留最后当前位的相加结果
        while(t>=0&&z<= MinIndex) {
            if (t + z == i) {
                int ProductResult = p1.s[t] * p2.s[z];
                AddResult += ProductResult;
                //cout << "计算：" << i << " " << t << "," << z << " " << ProductResult << endl;
                z++;
                t--;
            }
            else  {
                z++;
            }
        }
        NextAdd = AddResult / 10;
        if (!pushStack(lsq, AddResult % 10)) {
            cout << "两数计算过程入栈失败！" << endl;
            exit(0);
        }
    }
    if (NextAdd != 0) {
        if (!pushStack(lsq, NextAdd)) {
            cout << "两数计算过程入栈失败！" << endl;
            exit(0);
        }
    }

    return lsq;
}


//栈函数实现
/*************************************************
Function: popStack
Description: 弹栈
Input:s_link 栈指针
Return: 返回是否为空
*************************************************/
EmType popStack(linkStack s_link) {
    return s_link->s[s_link->top--];
}

/*************************************************
Function: isEmptyStack
Description: 判断栈空
Input:s_link 栈指针
Return: 返回是否为空
*************************************************/
State isEmptyStack(linkStack s_link) {
    if (s_link->top == -1)
        return OK;
    else
        return ERRO;
}

/*************************************************
Function: creatStack
Description: 为栈分配空间
Input:s_link 栈指针
Return: 返回是否执行成功
*************************************************/
State creatStack(linkStack s_link) {
    //为栈数据域分配连续空间
    s_link->s = (EmType*)malloc(MAX_LENGTH * sizeof(EmType));
    //判断是否分配成功
    if (s_link->s == NULL) return ERRO;
    //部分内容初始化
    s_link->maxSize = MAX_LENGTH;
    s_link->top = -1;
    return OK;
}

/*************************************************
Function: pushStack
Description: 压栈
Input:s_link 栈指针
Return: 返回是否执行成功
*************************************************/
State pushStack(linkStack s_link, EmType ch) {
    if (isFullStack(*s_link)) {			//判断是否栈满，栈满则重新分配空间，否则直接压栈
        //栈满
        if (!increaseStack(s_link))		//重新分配栈空间,并判断是否分配成功
            return ERRO;
    }
    s_link->s[++s_link->top] = ch;
    return OK;
}

/*************************************************
Function: increaseStack
Description: 为栈重新分配空间
Input:s_link 栈指针
Return: 返回是否执行成功
*************************************************/
State increaseStack(linkStack s_link) {
    //重新分配栈空间
    s_link->s = (EmType*)realloc(s_link->s, sizeof(EmType)*(s_link->maxSize + ADD_LENGTH));
    if (s_link->s == NULL)		//判断是否分配空间成功
        return ERRO;
    s_link->maxSize += ADD_LENGTH;
    return OK;
}

/*************************************************
Function: isFullStack
Description: 判断栈满
Input:s_link 栈指针
Return: 返回是否执行成功
*************************************************/
State isFullStack(Stack s) {
    //如果当前top+1与栈最大空间相等则判断为栈满
    if (s.maxSize == s.top + 1)
        return OK;
    else
        return ERRO;
}

/*************************************************
Function: destroyStack
Description: 销毁栈
Input:s_link 栈指针
Return: 返回是否执行成功
*************************************************/
void destroyStack(linkStack s) {
    free(s->s);
    s->top = -1;
}



