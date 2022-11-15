#### 学号：ZF2221515
#### 姓名：张静     
#### 《程序设计与算法》大作业队伍：静姐的背包

* 本次代码主要是排序算法：
选择排序，归并排序，快速排序，希尔排序，基数排序，
对所有算法进行分析并实现，分析其在不同规模的输入下单机性能变化情况；
* 利用多线程实现大规模数据的分布式排序，输入超过100万为最低大规模要求。
* 关于下面所有排序取大值随机数，都会使用以下方式

  用rand函数生成-10的100次方至10的100次方的随机数，并赋值给数组a[i],
  使用arr[i] = ((rand () % (b - a + 1)) + a)
  这种方式方式取值会有问题，导致概率不均，所以按照拼接成大数的方式来获取大数随机数
```C++
    int i, n;
    unsigned long long arr[maxSize];
    //   a为-10的100次方  b为10的100次方
    // int a = -pow(10, 100);
    // int b = pow(10, 100);
    n = maxSize;
    //用当前系统时间设置种子
    srand((unsigned)time(NULL));
    printf("选择排序\n");
    cout << "随即初始化数组的"<< maxSize <<"个数(范围是-10的100次方～10的100次方).\n" << endl;
    for(i = 1;i < maxSize; i++) {
        // 用rand函数生成-10的100次方至10的100次方的随机数，并赋值给数组a[i]
        // arr[i] = ((rand () % (b - a + 1)) + a);
        // todo：此处大数随机数按照上面的方式取值会有问题，导致概率不均，所以按照拼接成大数的方式来获取大数随机数
        arr[i] = (rand()<<30) + (rand()<<30) + (rand()<<30) + (rand()<<30) + (rand()<<30) + (rand()<<30) + (rand()<<30) + (rand()<<15) + rand();
    }
```

### 一、选择排序
##### 选择排序的代码思想 
每次都从未排序的序列中选择一个最小的数放在已排序列的最左边，直至排序完成。

```c++
// 算法核心代码
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
```

##### 选择排序算法执行结果
1、选择排序10个数(范围是-10的100次方～10的100次方)所花费的时间0.00011675s

![排序10个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/selectSort10.png)

2、选择排序100个数(范围是-10的100次方～10的100次方)所花费的时间0.0019795s

![排序100个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/selectSort100.png)

3、选择排序1000个数(范围是-10的100次方～10的100次方)所花费的时间0.0305028s
(由于排序数目过多就不截图排序后的及结果)

![排序1000个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/selectSort1000.png)

4、选择排序1w个数(范围是-10的100次方～10的100次方)所花费的时间0.226022s
(由于排序数目过多就不截图排序后的及结果)

![排序1w个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/selectSort1w.png)

5、选择排序10w个数(范围是-10的100次方～10的100次方)所花费的时间7.4667s
(由于排序数目过多就不截图排序后的及结果)

![排序10w个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/selectSort10w.png)

6、选择排序10w个数(范围是-10的100次方～10的100次方)所花费的时间644.349s
(由于排序数目过多就不截图排序后的及结果)

![排序100w个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/selectSort100w.png)

##### 选择排序的算法分析
选择排序的复杂度分析。第一次内循环比较N - 1次，然后是N-2次，N-3次，……，最后一次内循环比较1次。
共比较的次数是 (N - 1) + (N - 2) + ... + 1，求等差数列和，得 (N - 1 + 1)* N / 2 = N^2 / 2。
舍去最高项系数，其时间复杂度为 O(N^2)。

### 二、归并排序
##### 归并排序的代码思想 
归并排序是建立在归并操作上的一种有效，稳定的排序算法，该算法是采用分治法（Divide and Conquer）

分治模式在每一层递归上有三个步骤：

分解（Divide）：将n个元素分成个含n/2个元素的子序列。

解决（Conquer）：用合并排序法对两个子序列递归的排序。

合并（Combine）：合并两个已排序的子序列已得到排序结果。

![mergeSort](/image/mergeSort.png)

```c++
// 归并算法核心代码
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

```

##### 归并排序算法执行结果
1、归并排序10个数(范围是-10的100次方～10的100次方)所花费的时间8.3875e-05s

![排序10个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/mergeSort10.png)

2、归并排序100个数(范围是-10的100次方～10的100次方)所花费的时间0.001103s

![排序100个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/mergeSort100.png)

3、归并排序1000个数(范围是-10的100次方～10的100次方)所花费的时间0.029731s
(由于排序数目过多就不截图排序后的及结果)

![排序1000个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/mergeSort1000.png)

4、归并排序1w个数(范围是-10的100次方～10的100次方)所花费的时间0.153404s
(由于排序数目过多就不截图排序后的及结果)

![排序1w个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/mergeSort1w.png)

5、归并排序10w个数(范围是-10的100次方～10的100次方)所花费的时间1.25694s
(由于排序数目过多就不截图排序后的及结果)

![排序10w个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/mergeSort10w.png)

6、归并排序100w个数(范围是-10的100次方～10的100次方),排序没跑出来
(由于排序数目过多就不截图排序后的及结果)

![排序100w个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/mergeSort100w.png)

##### 归并排序的算法分析

空间复杂度分析：需要O(n),因为需要一个额外的，大小为n数组来存放临时数据。

时间复杂度分析：归并排序的时间复杂度均为O(nlog2n)


### 三、快速排序
##### 快速排序的代码思想 

1、快速排序使用分治的思想，通过一趟排序将待排序列分割成两部分，其中一部分记录的关键字均比另一部分记录的关键字小。之后分别对这两部分记录继续进行排序，以达到整个序列有序的目的。

2、快速排序的三个步骤：

(1)选择基准：在待排序列中，按照某种方式挑出一个元素，作为 “基准”（pivot）

(2)分割操作：以该基准在序列中的实际位置，把序列分成两个子序列。此时，在基准左边的元素都比该基准小，在基准右边的元素都比基准大

(3)递归地对两个序列进行快速排序，直到序列为空或者只有一个元素。


```c++
// 快速算法核心代码
// 快速排序算法(从小到大)
// arr:需要排序的数组，begin:需要排序的区间左边界，end:需要排序的区间的右边界
void quickSort(int *arr,int begin,int end)
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

```
##### 快速排序算法执行结果 
1、快速排序10个数(范围是-10的100次方～10的100次方)所花费的时间5.9792e-05s

![排序10个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/quickSort10.png)

2、快速排序100个数(范围是-10的100次方～10的100次方)所花费的时间0.00128517s

![排序100个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/quickSort100.png)

3、快速排序1000个数(范围是-10的100次方～10的100次方)所花费的时间0.0281961s
(由于排序数目过多就不截图排序后的及结果)

![排序1000个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/quickSort1000.png)

4、快速排序1w个数(范围是-10的100次方～10的100次方)所花费的时间0.181035s
(由于排序数目过多就不截图排序后的及结果)

![排序1w个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/quickSort1w.png)

5、快速排序10w个数(范围是-10的100次方～10的100次方)所花费的时间1.22785s
(由于排序数目过多就不截图排序后的及结果)

![排序10w个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/quickSort10w.png)

6、快速排序10w个数(范围是-10的100次方～10的100次方)所花费的时间11.9567s
(由于排序数目过多就不截图排序后的及结果)

![排序100w个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/quickSort100w.png)

##### 快速排序的算法分析
平均时间复杂度为O(nlogn)，最坏的时间复杂度为O(n²)。

### 四、希尔排序
##### 希尔排序的代码思想 

##### 希尔排序算法执行结果
1、希尔排序10个数(范围是-10的100次方～10的100次方)所花费的时间0.000108125s

![排序10个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/shellSort10.png)

2、希尔排序100个数(范围是-10的100次方～10的100次方)所花费的时间0.0012755s

![排序100个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/shellSort100.png)

3、希尔排序1000个数(范围是-10的100次方～10的100次方)所花费的时间0.0282804s
(由于排序数目过多就不截图排序后的及结果)

![排序1000个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/shellSort1000.png)

4、希尔排序1w个数(范围是-10的100次方～10的100次方)所花费的时间0.174639s
(由于排序数目过多就不截图排序后的及结果)

![排序1w个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/shellSort1w.png)

5、希尔排序10w个数(范围是-10的100次方～10的100次方)所花费的时间1.22705s
(由于排序数目过多就不截图排序后的及结果)

![排序10w个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/shellSort10w.png)

6、希尔排序100w个数(范围是-10的100次方～10的100次方)所花费的时间12.0249s
(由于排序数目过多就不截图排序后的及结果)

![排序100w个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/shellSort100w.png)

##### 希尔排序的算法分析
① 时间复杂度：

希尔排序的时间复杂度依赖增量序列的函数(和增量序列有关)这个涉及数学上尚未解决的问题，时间复杂度分析比较困难；

当n在某个特定范围时，希尔排序的时间复杂度约为O(n^1.3）;

最坏 的情况下，时间复杂度为O(n^2);

但是优于直接插入排序！！！

② 空间复杂度：

仅仅使用了常数个辅助单元，空间复杂度是O(1);

③ 算法稳定性：

由于多次插入排序，我们知道一次插入排序是稳定的，不会改变相同元素的相对顺序，

但在不同的插入排序过程中，相同的元素可能在各自的插入排序中移动，最后其稳定性就会被打乱

所以 希尔shell排序是不稳定的。


### 五、基数排序
##### 基数排序的代码思想
基数排序是按照低位先排序，然后收集；再按照高位排序，然后再收集；依次类推，直到最高位。有时候有些属性是有优先级顺序的，先按低优先级排序，再按高优先级排序。最后的次序就是高优先级高的在前，高优先级相同的低优先级高的在前。

算法描述

取得数组中的最大数，并取得位数；
arr为原始数组，从最低位开始取每个位组成radix数组；
对radix进行计数排序（利用计数排序适用于小范围数的特点）；

##### 基数排序算法执行结果
1、基数排序10个数(范围是-10的100次方～10的100次方)所花费的时间0.000135375s

![排序100w个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/radixSort10.png)

2、基数排序100个数(范围是-10的100次方～10的100次方)所花费的时间0.000467334s

![排序100w个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/radixSort100.png)

3、基数排序1000个数(范围是-10的100次方～10的100次方)所花费的时间1.5515ss
(由于排序数目过多就不截图排序后的及结果)

![排序100w个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/radixSort1000.png)

4、基数排序1w个数(范围是-10的100次方～10的100次方)所花费的时间0.174639s
(由于排序数目过多就不截图排序后的及结果)

![排序100w个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/radixSort1w.png)

5、基数排序10w个数(范围是-10的100次方～10的100次方)所花费的时间1.22705s
(由于排序数目过多就不截图排序后的及结果)

![排序100w个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/radixSort10w.png)

6、基数排序100w个数(范围是-10的100次方～10的100次方)所花费的时间12.0249s
(由于排序数目过多就不截图排序后的及结果)

![排序100w个数](https://github.com/zhjing1019/program_algorithm/blob/main/bigNumberSort/image/radixSort100w.png)

##### 基数排序的算法分析
假设在基数排序中，r为基数，d为位数。则基数排序的时间复杂度为O(d(n+r))。



