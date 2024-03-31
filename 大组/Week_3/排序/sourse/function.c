//function.c
#include "head.h"

// 一般的冒泡排序实现
void bubbleSort(int arr[], int length) {
    int i, j, temp;
    for (i = 0; i < length - 1; ++i) {
        for (j = 0; j < length - 1 - i; ++j) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// 冒泡排序优化1：设置一个标志位，如果一轮比较没有数据交换，则排序完成
void bubbleSortOptimized1(int arr[], int length) {
    int i, j, temp;
    int swapped;
    for (i = 0; i < length - 1; ++i) {
        swapped = 0;
        for (j = 0; j < length - 1 - i; ++j) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

// 冒泡排序优化2：记录最后一次交换的位置，减少排序的范围
void bubbleSortOptimized2(int arr[], int length) {
    int i, j, temp;
    int newLength;
    int lastSwapIndex = length - 1;
    while (lastSwapIndex > 0) {
        newLength = 0;
        for (j = 0; j < lastSwapIndex; ++j) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                newLength = j;
            }
        }
        lastSwapIndex = newLength;
    }
}

// 冒泡排序优化3：双向冒泡排序，同时从两边开始
void bubbleSortOptimized3(int arr[], int length) {
    int start = 0, end = length - 1;
    int temp, swapped;
    while (start < end) {
        swapped = 0;
        for (int i = start; i < end; ++i) { // 正向冒泡找到最大值
            if (arr[i] > arr[i + 1]) {
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
            }
        }
        --end; // 减少排序范围
        for (int i = end; i > start; --i) { // 反向冒泡找到最小值
            if (arr[i] < arr[i - 1]) {
                temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
                swapped = 1;
            }
        }
        ++start; // 减少排序范围
        if (!swapped) break;
    }
}

void insertSort(int arr[], int length) {
    int i, j, key;
    for (i = 1; i < length; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// 归并操作，合并两个有序数组
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // 创建临时数组
    int L[n1], R[n2];

    // 复制数据到临时数组
    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    // 合并临时数组回原数组
    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // 将剩余的元素复制回原数组
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// 递归部分的归并排序
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        // 找到中间索引
        int m = l + (r - l) / 2;

        // 分别递归排序两个子数组
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // 合并两个有序数组
        merge(arr, l, m, r);
    }
}

// 选择一个基准，并根据其划分数组
int partition(int arr[], int l, int r) {
    int pivot = arr[r];
    int i = (l - 1);

    for (int j = l; j <= r - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[r];
    arr[r] = temp;
    return (i + 1);
}

// 快速排序递归部分实现
void quickSort(int arr[], int l, int r) {
    if (l < r) {
        // 对数组进行划分
        int pi = partition(arr, l, r);

        // 递归排序划分后的两部分
        quickSort(arr, l, pi - 1);
        quickSort(arr, pi + 1, r);
    }
}

// 归并排序的适配器
void mergeSortAdapter(int arr[], int length) {
    mergeSort(arr, 0, length - 1);
}

// 快速排序的适配器
void quickSortAdapter(int arr[], int length) {
    quickSort(arr, 0, length - 1);
}

void countSort(int arr[], int length) {
    int output[length];
    int maxVal = arr[0];
    int minVal = arr[0];

    // 找到数组中的最大值和最小值
    for (int i = 1; i < length; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        } else if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }

    int k = maxVal - minVal + 1;

    // 初始化计数数组
    int countArray[k];
    memset(countArray, 0, sizeof(countArray));

    // 计数数组中每个元素的个数
    for (int i = 0; i < length; i++) {
        countArray[arr[i] - minVal]++;
    }

    // 更改countArray，现在它包含实际位置信息
    for (int i = 1; i < k; i++) {
        countArray[i] += countArray[i - 1];
    }

    // 构建输出数组
    for (int i = length - 1; i >= 0; i--) {
        output[countArray[arr[i] - minVal] - 1] = arr[i];
        countArray[arr[i] - minVal]--;
    }

    // 将排序好的数组复制回原数组
    for (int i = 0; i < length; i++) {
        arr[i] = output[i];
    }
}

void countingSortForRadix(int arr[], int length, int exp) {
    int output[length]; // 输出数组
    int i, count[10] = {0};

    // 存储计数
    for (i = 0; i < length; i++)
        count[(arr[i] / exp) % 10]++;

    // 更改 count，现在包含实际位置信息
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // 构建输出数组
    for (i = length - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // 将 sorted 数组复制回 arr[]
    for (i = 0; i < length; i++)
        arr[i] = output[i];
}

// 获取最大元素值的函数
int getMax(int arr[], int length) {
    int mx = arr[0];
    for (int i = 1; i < length; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void radixCountSort(int arr[], int length) {
    int m = getMax(arr, length);

    // 从最低位开始，对每一位进行计数排序
    for (int exp = 1; m / exp > 0; exp *= 10)
        countingSortForRadix(arr, length, exp);
}


int isSorted(int arr[], int length) {
    for (int i = 0; i < length - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0; // 如果当前元素比下一个大，返回未排序
        }
    }
    return 1; // 所有元素都按升序排列
}


// function.c 或者 head.h 中相应的函数声明部分
// 测试排序函数并返回持续时间
double testSort(void (*sortFunc)(int*, int), int data[], int length, const char* sortName) {
    clock_t start, end;
    double duration;

    // 创建一个副本，因为排序会改变数组
    int *arrCopy = (int*)malloc(sizeof(int) * length);
    if (arrCopy == NULL) {
        fprintf(stderr, "内存分配失败。\n");
        return -1;  // 返回错误代码
    }
    memcpy(arrCopy, data, sizeof(int) * length);

    start = clock();
    sortFunc(arrCopy, length); // 执行排序函数
    end = clock();

    if (isSorted(arrCopy, length)) {
        printf("数组已成功排序。\n");
    } else {
        printf("错误：数组未排序。\n");
    }

    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("排序算法: %s, 数据量: %d, 用时: %.6f 秒\n", sortName, length, duration);

    free(arrCopy); // 释放排序数组副本的内存

    return duration;  // 返回排序操作的持续时间
}

void writeArrayToFile(const char* filename, int arr[], int length) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < length; i++) {
        fprintf(file, "%d\n", arr[i]);
    }
    fclose(file);
}

void readArrayFromFile(const char* filename, int arr[], int length) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("打开文件失败");
        return;
    }

    for (int i = 0; i < length; i++) {
        if (fscanf(file, "%d", &arr[i]) != 1) {
            break; // 如果读取出错或者文件结束，停止读取
        }
    }
    fclose(file);
}

