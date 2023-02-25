# 实验报告

陆子睦

PB20051150



### 实验内容

编写两个动态规划程序：矩阵链乘最优方，最长公共子序列。

并分析运行结果和时间复杂度。



### 实验设备和环境

处理器	12th Gen Intel(R) Core(TM) i5-12500H   2.50 GHz

机带 RAM	16.0 GB

系统类型	64 位操作系统, 基于 x64 的处理器

版本	Windows 11 家庭中文版

软件 	VSCode，g++



### 实验方法和步骤

先编写matrix_chain_order.cpp 和 lcs.cpp 两个程序，从input中读出输入数据，并进行计算。

其中测试时间的方法是通过测试100000次运行时间取平均。

然后得出输出数据。

本次输出数据是直接打印到终端上，然后复制粘贴到相应的文件中。

然后用 matplotlib 绘制折线图并进行分析。

### 截图

2.1 n=5 截图如下：

![image-20221117162805973](C:/Users/luzim/AppData/Roaming/Typora/typora-user-images/image-20221117162805973.png)

2.1整体运行截图如下：

![image-20221117165202997](C:/Users/luzim/AppData/Roaming/Typora/typora-user-images/image-20221117165202997.png)

2.2 整体运行截图如下：

![image-20221117165359502](C:/Users/luzim/AppData/Roaming/Typora/typora-user-images/image-20221117165359502.png)



### 运行时间分析

matrix_chain_order 的运行时间折线图：

![image-20221117163643198](C:/Users/luzim/AppData/Roaming/Typora/typora-user-images/image-20221117163643198.png)

这个算法的时间复杂度是$\Theta(n^3)$ 的，从上图可以看出与我的程序的运行时间与这个复杂度大致相符



LCS 的运行时间折线图：

![image-20221117164429429](C:/Users/luzim/AppData/Roaming/Typora/typora-user-images/image-20221117164429429.png)

这个算法的时间复杂度是$\Theta(mn)$ (m，n为两个序列的长度)。在这里就是 $\Theta(n^2)$ , 可以看出我的程序运行时间趋势与此基本符合。