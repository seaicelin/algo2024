#算法学习2024

## 基础算法

### 二叉树
### 堆
### 并查集
### 二分法

### 遇到的问题
#### 读取空格 换行
```
/*
1、getline(cin,str)读取换行符 并且将换行符替换成'\0'，并将换行符从输入队列中抹去。
2、cin不会读入换行符；//这个总所周知，但是可以利用这个特点来连续读入任意个字符串。
3、cin.getline(char*,len)读取换行符并替换成'\0'，并将换行符从输入队列中抹去
*/
```

#### 排序比较
https://blog.csdn.net/qq_39521554/article/details/79364718
https://cloud.tencent.com/developer/article/2381985

#### 日志用这个来打印啊
```
FILE* fp;
fp = fopen("log.txt", "w");
fprintf(fp, "hello world\n");
```

#### 二分三分 r-l 临界值问题处理 
求三分或者二分的时候，如果 r-l < 5 ,避免临界值问题，这个时候可以跳出来穷举