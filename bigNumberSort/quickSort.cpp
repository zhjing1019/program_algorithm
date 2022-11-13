/**
 * 快速排序
 * by zhangjing_ZF2221515
 * 平均时间复杂度为O(nlogn)，最坏的时间复杂度为O(n²)。
 * 运行命令行 g++ quickSort.cpp
 * ./a.out quickSort.cpp
 * */

#include<iostream>

using namespace std;
const int maxSize = 1000000;
// 快速排序算法(从小到大)
// arr:需要排序的数组，begin:需要排序的区间左边界，end:需要排序的区间的右边界
void quickSort(unsigned long long *arr,int begin,int end)
{
    //如果区间不只一个数
    if(begin < end)
    {
        int temp = arr[begin]; //将区间的第一个数作为基准数
        int i = begin; //从左到右进行查找时的“指针”，指示当前左位置
        int j = end; //从右到左进行查找时的“指针”，指示当前右位置
        //不重复遍历
        while(i < j)
        {
            //当右边的数大于基准数时，略过，继续向左查找
            //不满足条件时跳出循环，此时的j对应的元素是小于基准元素的
            while(i<j && arr[j] > temp)
                j--;
            //将右边小于等于基准元素的数填入右边相应位置
            arr[i] = arr[j];
            //当左边的数小于等于基准数时，略过，继续向右查找
            //(重复的基准元素集合到左区间)
            //不满足条件时跳出循环，此时的i对应的元素是大于等于基准元素的
            while(i<j && arr[i] <= temp)
                i++;
            //将左边大于基准元素的数填入左边相应位置
            arr[j] = arr[i];
        }
        //将基准元素填入相应位置
        arr[i] = temp;
        //此时的i即为基准元素的位置
        //对基准元素的左边子区间进行相似的快速排序
        quickSort(arr,begin,i-1);
        //对基准元素的右边子区间进行相似的快速排序
        quickSort(arr,i+1,end);
    }
        //如果区间只有一个数，则返回
    else
        return;
}
int main(int argc, char *argv[])
{
    // 计算程序开始时间
    auto start_time = std::chrono::steady_clock::now();
    int i, n;
    unsigned long long arr[maxSize];
    // a为-10的100次方  b为10的100次方
    // int a = -pow(10, 100);
    // int b = pow(10, 100);
    n = maxSize;
    //用当前系统时间设置种子
    srand((unsigned)time(NULL));

    for(i = 0; i < n; i++) {
        //用rand函数生成-10的100次方至10的100次方的随机数，并赋值给数组a[i]
        // arr[i] = ((rand () % (b - a + 1)) + a);
        // todo：此处大数随机数按照上面的方式取值会有问题，导致概率不均，所以按照拼接成大数的方式来获取大数随机数
        arr[i] = (rand()<<30) + (rand()<<30) + (rand()<<30) + (rand()<<30) + (rand()<<30) + (rand()<<30) + (rand()<<30) + (rand()<<15) + rand();
    }

    cout << "排序前：" << endl;
    for(i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    quickSort(arr,0,n-1);
    cout << "排序后：" << endl;
    for(i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed_seconds = end_time - start_time;
    // 算出程序总共花费的时间
    printf("快速排序\n");
    cout << "随即初始化数组的"<< maxSize <<"个数(范围是-10的100次方～10的100次方).\n" << endl;
    cout << "排序时间花费" << endl;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    return 0;
}
