
//希尔排序
#include <stdio.h>
#include<stdlib.h>
#include <time.h>
void ShellSort(int* arr, int sz)
{
    int count=0;//这是我为了看看希尔排序和直接插入排序的性能比较而设置的计数
    int gap = sz;//设置排序的间隔
    while ( gap > 1 )
    {
        //这里一定要保证gap最后进来循环后为1，所以对此加1
        gap = gap / 3 + 1;//gap>1为与排序，gap==1，为直接插入排序

        for (int i = 0; i < sz - gap; i++)//这里并不是一次性把一组排完，而是挨个往后，一组一个轮流排
        {
            int end = i;
            int tmp = arr[end + gap];
            while (end >= 0)
            {
                if (tmp < arr[end])
                {
                    arr[end + gap] = arr[end];
                    end -= gap;
                }
                else
                {
                    break;
                }
            }
            arr[end + gap] = tmp;
        }
    }
}
int main()
{
    clock_t start, finish;
    double Total_time;
    //定义随机生出的随机数组
    int size,i;
    int * arr;
    arr = (int *) malloc(30000 * sizeof(int ));//定义动态数组
    printf("请输入随机数组的长度:\n");
    scanf("%d",&size);
    printf("生成的随机数组:\n");
    for ( i = 0; i < size; i++) {
        arr[i]=rand()%30001 - 15000;//c语言生成的随机数为无符号数，即都是正的，要想生成正负随机的，可以通过模除限定返回，再减去对应范围的中间值即可。
        //要获取-15000~+15000范围的随机数，总的数量为30001个，这样就可以通过代码rand()%30001 使得到的结果限制在0-30000范围，再减去15000, 结果就是-15000~+15000之间了。
        printf("%d  ",arr[i]);
        if(i%20==19)
            printf("\n");
    }
    printf("\n");
    //对生成的数组进行排序
    start = clock();
    ShellSort(arr,  size);
    finish = clock();
    Total_time = (double)(finish - start) / CLOCKS_PER_SEC; //单位换算成秒

    int j = 0;
    printf("排序后的数组：\n");
    for (j = 0; j < size; j++)
    {
        printf("%d  ", arr[j]);
        if(j%20==19)
            printf("\n");
    }
    printf("程序的运行时间为：");
    printf("%f seconds\n", Total_time);
    return 0;
}
