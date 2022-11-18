
#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>
//基数排序
void RadixSort(int* arr, int n)
{
    //max为数组中最大最小值
    int max = arr[0];
    int min = arr[0];
    int base = 1;

    //找出数组中的最大值
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    //循环结束max就是数组最大最小值

    //循环将数组的元素全部变为正数
    //所有元素加上最小值的绝对值
    for (int i = 0; i < n; i++)
    {
        arr[i] += abs(min);
    }

    //临时存放数组元素的空间
    int* tmp = (int*)malloc(sizeof(int)*n);

    //循环次数为最大数的位数
    while (max / base > 0)
    {
        //定义十个桶，桶里面装的不是数据本身，而是每一轮排序对应（十、白、千...）位的个数
        //统计每个桶里面装几个数
        int bucket[10] = { 0 };
        for (int i = 0; i < n; i++)
        {
            //arr[i] / base % 10可以取到个位、十位、百位对应的数字
            bucket[arr[i] / base % 10]++;
        }
        //循环结束就已经统计好了本轮每个桶里面应该装几个数


        //将桶里面的元素依次累加起来，就可以知道元素存放在临时数组中的位置
        for (int i = 1; i < 10; i++)
        {
            bucket[i] += bucket[i - 1];
        }
        //循环结束现在桶中就存放的是每个元素应该存放到临时数组的位置


        //开始放数到临时数组tmp
        for (int i = n - 1; i >= 0; i--)
        {
            tmp[bucket[arr[i] / base % 10] - 1] = arr[i];
            bucket[arr[i] / base % 10]--;
        }
        //不能从前往后放，因为这样会导致十位排好了个位又乱了，百位排好了十位又乱了
        /*for (int i = 0; i < n; i++)
        {
            tmp[bucket[arr[i] / base % 10] - 1] = arr[i];
            bucket[arr[i] / base % 10]--;
        }*/

        //把临时数组里面的数拷贝回去
        for (int i = 0; i < n; i++)
        {
            arr[i] = tmp[i];
        }
        base *= 10;
    }
    free(tmp);

    //还原原数组
    for (int i = 0; i < n; i++)
    {
        arr[i] -= abs(min);
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
    RadixSort(arr,  size);
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

