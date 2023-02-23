#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * 【折半查找原理解析】
 *   折半查找又称二分查找，它仅适用于有序的顺序表。
 *   1、折半查找的基本思想：首先将给定值key与表中间位置的元素比较，若相等，则查找成功，返回该元素的存储位置；
 *   若不等，则所需查找的元素只能在中间元素以外的前半部分或后半部分(例如，在查找表升序排序时，
 *   若给定值key大于中间元素，则所查找的元素只可能在后半部分)。然后在缩小的范围内继续进行同样的查找。
 *   如此重复，直到找到为止，或确定表中没有所需要查找的元素，则查找不成功，返回查找失败的信息。
 *   2、针对顺序表有序，使用qsort来排序。
 *   qsort的使用方法如下：
 *      #include<stdio.h>
 *      void qsort(void *buf,size_t num,size_t size,int (*compare)(const void*,const void*));
 *      buf:要排序数组的起始地址，也可以是指针，申请了一块连续的堆空间
 *      num:数组中元素的个数
 *      size:数组中每个元素所占用的空间大小
 *      compare:比较规则，需要传递一个函数名，这个函数由自己编写，返回值必须是int类型，形参是两个void
 *      类型指针，这个函数自己编写，由qsort内部调用，相当于传递一种行为给qsort
 * */
typedef int ElemType;
typedef struct {
    ElemType* elem;//整型指针
    int TableLen;//存储动态数组中的元素个数
}SSTable;
//初始化
void ST_Init(SSTable &ST,int len){//init进行了随机数生成
    ST.TableLen=len;
    ST.elem=(ElemType*) malloc(sizeof(ElemType)*ST.TableLen);
    srand(time(NULL));//随机数生成
    int i;
    for(i=0;i<ST.TableLen;i++){//因为第0个是哨兵，所以从1开始随机存入数据
        ST.elem[i]=rand()%100;//为了生成0-99的数字
    }
}
//打印
void ST_print(SSTable ST){
    int i;
    for(i=0;i<ST.TableLen;i++){
        printf("%3d",ST.elem[i]);
    }
    printf("\n");
}

int BinarySearch(SSTable ST,ElemType key){
    int low=0;
    int high=ST.TableLen-1;
    int mid;
    while(low<=high){//low<=high,可以让mid即能取到low，也能取到high
        mid=(low+high)/2;
        if(key>ST.elem[mid]){//如果目标值大于中间位置的值
            low=mid+1;
        }else if(key<ST.elem[mid]){
            high=mid-1;
        }else{
            return mid;//如果相等，则说明已经找到
        }
    }
    return -1;
}
//left指针和right指针是指向数组中的任意两个元素
//qsort规定如果left指针指向的值大于right指针指向的值，返回正值，小于，返回负值，相等，返回0
int compare(const void *left,const void *right){//函数名中存储的是函数的入口地址，也是一个指针，是函数指针类型
    return *(int*)left-*(int*)right;//从小到大排序
    //return *(ElemType*)right-*(ElemType*)left;//从大到小排序
}

//折半查找
int main() {
    SSTable ST;
    ST_Init(ST,10);//初始化
    ST_print(ST);//打印
    qsort(ST.elem,ST.TableLen,sizeof(ElemType),compare);//qsort实现的是快排
    ST_print(ST);
    ElemType key;
    printf("please input search key:\n");
    scanf("%d",&key);
    int pos;//存储查询元素的位置
    //有序数组
    pos= BinarySearch(ST,key);//二分查找，也叫折半查找
    if(pos!=-1){
        printf("find key %d\n",pos);
    }else{
        printf("not find\n");
    }
    return 0;
}
