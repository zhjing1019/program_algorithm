///**
// * 选择排序
// * by zhangjing_ZF2221515
// * */
#include<iostream>
#include<algorithm>
#include <random>
#include <vector>
#include <time.h>
#include <chrono>

using namespace std;

const int maxSize = 10000;

template<class T>
void SelectSort(T arr[], int n); // 选择排序

int main(int argc, const char * argv[]) {
    auto start_time = std::chrono::steady_clock::now();
    int i, n, arr[maxSize];
    n = maxSize;
    //用当前系统时间设置种子
    srand((unsigned)time(NULL));
    printf("随即初始化数组的100个数(范围是0~10000).\n");
    for(int i = 0;i < maxSize; i++) {
        arr[i] = rand() % 100;    //用rand函数生成0-10000的随机数，并赋值给数组a[i]
    }

    cout << "排序前：" << endl;
    for(i = 1; i <= n; i++)
        cout << arr[i] << " ";
    cout << endl;
    SelectSort(arr, n);
    cout << "排序后：" << endl;
    for(i = 1; i <= n; i++)
        cout << arr[i] << " ";
    cout << endl;
    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed_seconds = end_time - start_time;
    cout << "排序时间花费" << endl;
    std::cout << elapsed_seconds.count() << std::endl;
    return 0;
}

// 选择排序
template <class T>
void SelectSort(T arr[], int n) {
    int i, j, pos;

    for(i = 1; i < n; i++) { // 共作n-1趟选择排序
        pos = i; // 保存最小数的位置
        for(j = i; j <= n; j++) { // 找比arr[i]更小的值
            if(arr[j] < arr[pos]) {
                pos = j; // 指向更小的数的位置
            }
        }
        if(pos != i) { // 找到了更小的值，就交换位置
            arr[0] = arr[i]; // arr[0]作为暂存单元
            arr[i] = arr[pos];
            arr[pos] = arr[0];
        }
    } // for
} // SelectSort