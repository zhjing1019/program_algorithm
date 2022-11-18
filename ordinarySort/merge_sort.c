//归并排序
#include <stdio.h>
#include<stdlib.h>
#include <time.h>
void merge(int a[],int left,int right,int mid) {
    int s[30000];//数组的最大个数为30000
    int i = left, j = mid + 1;
    int sor = left;
    while (i <= mid && j <= right) {
        if (a[i] < a[j]) {
            s[sor++] = a[i++];
        }
        else {
            s[sor++] = a[j++];
        }
    }
    while (i <= mid) s[sor++] = a[i++];
    while (j <= right)  s[sor++] = a[j++];
    sor = left;
    while (sor <= right) {
        a[sor] = s[sor];
        sor++;
    }
}
void merge_sort(int a[],int left,int right){
    if(left<right){
        int mid = (left + right) / 2;
        merge_sort(a,left, mid);
        merge_sort(a, mid + 1, right);
        merge(a, left, right, mid);
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
    merge_sort(arr, 0, size);
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
