/**
 * 归并排序
 * by zhangjing_ZF2221515
 * 运行命令行 g++ mergeSort.cpp
 * ./a.out mergeSort.cpp
 * */

#include<iostream>
#include<algorithm>
#include <time.h>
#include <chrono>
#include <stdlib.h>
using namespace std;
/* 初始版本，升序排序 */
/* 时间复杂度：O(nlbn) 将n个待排序记录归并次数为lbn，一趟归并O(n)
   空间复杂度：O(n) 递归栈最大深度为[lbn] + 1 ，而辅助数组大小为n
   稳定：无论最好还是最坏情况时间复杂度都是O(nlbn)
*/
const int maxSize = 1000000;

void Merge(unsigned long long *arr, int n)
{
    int temp[n];    // 辅助数组
    int b = 0;  // 辅助数组的起始位置
    int mid = n / 2;    // mid将数组从中间划分，前一半有序，后一半有序
    int first = 0, second = mid;    // 两个有序序列的起始位置

    while (first < mid && second < n)
    {
        if (arr[first] <= arr[second])   // 比较两个序列
            temp[b++] = arr[first++];
        else
            temp[b++] = arr[second++];
    }

    while(first < mid)              // 将剩余子序列复制到辅助序列中
        temp[b++] = arr[first++];
    while(second < n)
        temp[b++] = arr[second++];
    for (int i = 0; i < n; ++i)    // 辅助序列复制到原序列
        arr[i] = temp[i];
}

void MergeSort(unsigned long long *arr, int n)
{
    if (n <= 1)    // 递归出口
        return;
    if (n > 1)
    {
        MergeSort(arr, n / 2);    // 对前半部分进行归并排序
        MergeSort(arr + n / 2, n - n / 2);    // 对后半部分进行归并排序
        Merge(arr, n);    // 归并两部分
    }
}

int main(int argc, char *argv[])
{
    // 计算程序开始时间
    auto start_time = std::chrono::steady_clock::now();
    int i, n;
    // a为-10的100次方  b为10的100次方
    // int a = -pow(10, 100);
    // int b = pow(10, 100);
    unsigned long long arr[maxSize];

    n = maxSize;
    //用当前系统时间设置种子
    srand((unsigned)time(NULL));
    for(i = 0; i < n; i++) {
        //用rand函数生成-10的100次方至10的100次方的随机数，并赋值给数组a[i]
        // arr[i] = ((rand () % (b - a + 1)) + a);
        // todo：此处大数随机数按照上面的方式取值会有问题，导致概率不均，所以按照拼接成大数的方式来获取大数随机数
        arr[i] = (rand()<<30) + (rand()<<30) + (rand()<<15) + rand();
    }

    cout << "排序前：" << endl;
    for(i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    MergeSort(arr, n);
    cout << "排序后：" << endl;
    for(i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed_seconds = end_time - start_time;
    // 算出程序总共花费的时间
    printf("归并排序\n");
    cout << "随即初始化数组的"<< maxSize <<"个数(范围是-10的100次方～10的100次方).\n" << endl;

    cout << "排序时间花费" << endl;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    return 0;
}

