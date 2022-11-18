//归并排序
#include <stdio.h>
#include<stdlib.h>
#include <time.h>
//快速排序
void quick_sort(int num[], int low, int high )
{
    int i,j,temp;
    int tmp;

    i = low;
    j = high;
    tmp = num[low];   //任命为中间分界线，左边比他小，右边比他大,通常第一个元素是基准数

    if(i > j)  //如果下标i大于下标j，函数结束运行
    {
        return;
    }

    while(i != j)
    {
        while(num[j] >= tmp && j > i)
        {
            j--;
        }

        while(num[i] <= tmp && j > i)
        {
            i++;
        }

        if(j > i)
        {
            temp = num[j];
            num[j] = num[i];
            num[i] = temp;
        }
    }

    num[low] = num[i];
    num[i] = tmp;

    quick_sort(num,low,i-1);
    quick_sort(num,i+1,high);
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
    quick_sort(arr, 0, size);
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
