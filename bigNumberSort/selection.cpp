/**
 * 选择排序
 * by zhangjing_ZF2221515
 * 运行命令行 g++ selection.cpp
 * ./a.out selection.cpp
 * */
#include<iostream>
#include<algorithm>
#include <time.h>
#include <chrono>
#include <math.h>

using namespace std;

const int maxSize = 1000000;

template<class T>
void SelectSort(T arr[], int n); // 选择排序

int main(int argc, const char * argv[]) {
    // 计算程序开始时间
    auto start_time = std::chrono::steady_clock::now();
    int i, n;
    unsigned long long arr[maxSize];
    //   a为-10的100次方  b为10的100次方
    // int a = -pow(10, 100);
    // int b = pow(10, 100);
    n = maxSize;
    //用当前系统时间设置种子
    srand((unsigned)time(NULL));
    for(i = 1;i < maxSize; i++) {
        // 用rand函数生成-10的100次方至10的100次方的随机数，并赋值给数组a[i]
        // arr[i] = ((rand () % (b - a + 1)) + a);
        // todo：此处大数随机数按照上面的方式取值会有问题，导致概率不均，所以按照拼接成大数的方式来获取大数随机数
        arr[i] = (rand()<<30) + (rand()<<30) + (rand()<<30) + (rand()<<30) + (rand()<<30) + (rand()<<30) + (rand()<<30) + (rand()<<15) + rand();
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
    // 算出程序总共花费的时间
    printf("选择排序\n");
    cout << "随即初始化数组的"<< maxSize <<"个数(范围是-10的100次方～10的100次方).\n" << endl;
    cout << "排序时间花费" << endl;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
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
    }
} // SelectSort