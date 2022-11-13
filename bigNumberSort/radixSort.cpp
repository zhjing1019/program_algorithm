/**
 * 基数排序
 * by zhangjing_ZF2221515
 * 平均时间复杂度为O(nlogn)，最坏的时间复杂度为O(n²)。
 * 运行命令行 g++ radixSort.cpp
 * ./a.out radixSort.cpp
 * */

#include <iostream>
#include <stdlib.h>

using namespace std;

int maxbit(unsigned long long data[], int n) //辅助函数，求数据的最大位数
{
//    int maxData = data[0];              ///< 最大数
//    /// 先求出最大数，再求其位数，这样有原先依次每个数判断其位数，稍微优化点。
//    for (int i = 1; i < n; ++i)
//    {
//        if (maxData < data[i])
//            maxData = data[i];
//    }
//    int d = 1;
//    int p = 10;
//    while (maxData >= p)
//    {
//        //p *= 10; // Maybe overflow
//        maxData /= 10;
//        ++d;
//    }
//    cout << "ddddddddddddd"<< d << endl;
    int d = 30;
    return d;

}

void radixsort(unsigned long long data[], int n) //基数排序
{
    int d = maxbit(data, n);
    int *tmp = new int[n];
    unsigned long long *count = new unsigned long long[10]; //计数器
    int i, j, k;
    int radix = 1;
    for(i = 1; i <= d; i++) //进行d次排序
    {
        for(j = 0; j < 10; j++)
            count[j] = 0; //每次分配前清空计数器
        for(j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10; //统计每个桶中的记录数
            count[k]++;
        }
        for(j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //这就相当于把链表连起来了
        for(j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for(j = 0; j < n; j++) //将临时数组的内容复制到data中
            data[j] = tmp[j];
        radix = radix * 10;
    }
    delete []tmp;
    delete []count;
}

void PrintArray(unsigned long long a[], int n) {
    for(int i = 0; i < n; i++)
        cout<<a[i]<<" ";
    cout<<endl;
}
const int maxSize = 1000000;
int main() {
    auto start_time = std::chrono::steady_clock::now();
    int i, n = maxSize;
    unsigned long long a[maxSize];
    for(i = 1;i < 10; i++) {
        // 用rand函数生成-10的100次方至10的100次方的随机数，并赋值给数组a[i]
        // arr[i] = ((rand () % (b - a + 1)) + a);
        // todo：此处大数随机数按照上面的方式取值会有问题，导致概率不均，所以按照拼接成大数的方式来获取大数随机数
        a[i] = (rand()<<30) + (rand()<<30) + (rand()<<30) + (rand()<<30) + (rand()<<30) + (rand()<<15) + rand();
    }

    cout<<"排序之前：";
    PrintArray(a, n);
    radixsort(a, n);
    cout<<"排序之后：";
    PrintArray(a, n);
    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed_seconds = end_time - start_time;
    // 算出程序总共花费的时间
    printf("基数排序\n");
    cout << "随即初始化数组的"<< maxSize <<"个数(范围是-10的100次方～10的100次方).\n" << endl;
    cout << "排序时间花费" << endl;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}

