/**
 * 希尔排序
 * by zhangjing_ZF2221515
 * 运行命令行 g++ shellSort.cpp
 * ./a.out shellSort.cpp
 * */

//希尔排序
#include <iostream>
#include <chrono>
const int maxSize = 1000000;
using namespace std;

void ShellSort(unsigned long long array[],int length){
    for(int step=length/2;step>0;step=step/2){//初始步长step为length/2
        for(int i=0;i<step;i++){	//遍历每一次分组后的第一个元素
            for(int j=i+step;j<length;j+=step){	//遍历步长为step的所有元素 ，进行直接插入排序
                int temp=array[j];
                int m=j-step;
                for(m=j-step;m>=0&&array[m]>temp;m-=step){//array[m]小于 temp 时循环结束，结束后应将 temp 赋值给a[m+step]
                    array[m+step]=array[m];
                }
                array[m+step]=temp;		//将 temp 赋值给a[m+step]
            }
        }
//        Print(array,length);	//每排序一趟就打印一次序列
    }
}
int main(int argc, char *argv[]){
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
    int length= sizeof(arr) / sizeof(*arr);
    ShellSort(arr, length);
    cout << "排序后：" << endl;
    for(i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed_seconds = end_time - start_time;
    // 算出程序总共花费的时间
    printf("希尔排序\n");
    cout << "随即初始化数组的"<< maxSize <<"个数(范围是-10的100次方～10的100次方).\n" << endl;
    cout << "排序时间花费" << endl;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    return 0;
}