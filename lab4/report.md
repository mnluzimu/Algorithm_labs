# 实验报告

陆子睦

PB20051150



### 实验内容

实现求所有点对最短路径的Johnson算法。

1. 有向图的顶点数 N 的取值分 别为: 27、81、243、729 ，每个顶点作为起点引出的边的条数取值分别 为：log_5⁡N、 log_7⁡N （取下整）。图的输入规模总共有4*2=8个，若同一个N，边的两种规模取值相等，则按后面输出要求输出两次，并在报告里说明。(不允许多重边，可以有环。)

2. 每种输入规模分别建立txt文件，文件名称为input11.txt, input12.txt,……,input42.txt （第一个数字为顶点数序号（27、81、243、729），第二个数字为弧数目序号（ log5N、log7N ））；生成的有向图信息分别存放在对应数据规模的txt文件中；每行存放一对结点i,j序号（数字表示）和wij，表示存在一条结点i指向结点j的边，边的权值为wij ，权 值范围为[-10,50],取整数。Input文件中为随机生成边以及权值，实验首先应判断输入图是否包含一个权重为负值的环路，如果存在，删除负环的一条边，消除负环，实验输出为处理后数据的实验结果，并在实验报告中说明。

3. lresult.txt:输出对应规模图中所有点对之间的最短路径包含结点序列及路径长，不同规模写到不同的 txt文件中，因此共有8个txt文件，文件名称为result11.txt,result12.txt,……,result42.txt;每行 存一结点的对的最短路径，同一最短路径的结点序列用一对括号括起来输出到对应的txt文件中，并输 出路径长度。若图非连通导致节点对不存在最短路径，该节点对也要单独占一行说明。

   ltime.txt:运行时间效率的数据，不同规模的时间都写到同个文件。

   lexample:对顶点为27，边为54的所有点对最短路径实验输出应为：(1,5,2 20)(1,5,9,3 50)……，执行

   结果与运行时间的输出路径分别为：

   output/result11.txt 

   output/time.txt 

   

### 实验设备和环境

处理器	12th Gen Intel(R) Core(TM) i5-12500H   2.50 GHz

机带 RAM	16.0 GB

系统类型	64 位操作系统, 基于 x64 的处理器

版本	Windows 11 家庭中文版

软件 	VSCode，g++



### 实验方法和步骤

认真阅读理解Johnson算法，通过依次实现输入数据生成、bellman ford算法、Dijkstra算法，得到johnson算法的结果

1. 编写 input_gen.cpp ，通过对每一个顶点用随机数生成该顶点出边的另一个节点，并控制出边数为$\log_5N$ 和 $log_7N$

   ```c++
   const int N[4] = {27, 81, 243, 729};
   const int l[2] = {5, 7};
   string infileName[4][2] = {{"input11.txt", "input12.txt"}, {"input21.txt", "input22.txt"}, {"input31.txt", "input32.txt"}, {"input41.txt", "input42.txt"}};
   const int MAX_SIZE = 1000;
   bool edges[MAX_SIZE][MAX_SIZE];
   
   int main() {
       for (int m = 0; m < 4; m++) {
           for (int n = 0; n < 2; n++) {
               int k = (int)(log(N[m])/log(l[n]));
               ofstream ofs;
               string infile = infileName[m][n];
               ofs.open(infile.c_str(), ios::out);
               for (int i = 0; i < N[m]; i++) {
                   for (int j = 0; j < k; j++) {
                       int v = (int) rand() * N[m] / RAND_MAX;
                       while (edges[i][v] == true) {
                           v = (int) rand() * N[m] / RAND_MAX;
                       }
                       int w = - 10 + (int) rand() * 60 / RAND_MAX;
                       ofs << i << " " << v << " " << w << endl;
                       edges[i][v] = true;
                   }
               }
               ofs.close();
           }
       }
       return 0;
   }
   ```

   通过两层循环生成4种节点数，每个节点数两种出边规模的输入图。

2. 读入图并建立邻接表

其中顶点的数据结构如下：

```c++
typedef struct Vnode {
    int d;
    int pi;
    Enode * next;
} Vnode;
```

边节点的数据结构如下：

```c++
typedef struct Enode {
    struct Enode * next;
    int w;
    int v;
} Enode;
```

建立邻接表的过程如下：

```c++
int u, v, w;
while (fscanf(fp, "%d %d %d", &u, &v, &w) == 3) {
Enode * p = new Enode;
p->v = v;
p->w = w;
p->next = vxs[u].next;
vxs[u].next = p;
}
for (int k = 0; k < n; k++) {
Enode * p = new Enode;
p->v = k;
p->w = 0;
p->next = vxs[n].next;
vxs[n].next = p;
}
```

先读入原图，再加入一个节点，到原图节点的边权都为0.

3. 编写 bellman ford 算法，确定h值以及是否有负权值的环路

```c++
void bellman_ford (int s, int n) {
    for (int i = 1; i < n; i++) {
        for (int u = 0; u < n; u++) {
            Enode * p = vxs[u].next;
            while (p != NULL) {
                relax(u, p->v, p->w);
                p = p->next;
            } 
        }
    }
    bool flag = false;
    for (int u = 0; u < n; u++) {
        Enode * p = vxs[u].next;
        Enode * q = NULL;
        while (p != NULL) {
            if (vxs[p->v].d > vxs[u].d + p->w) {
                if (q == NULL) {
                    vxs[u].next = p->next;
                    delete p;
                }
                else {
                    q->next = p->next;
                    delete p;
                }
                flag = true;
                break;
            }
            q = p;
            p = p->next;
        } 
        if (flag == true) {
            break;
        }
    }
    if (flag == true) {
        bellman_ford(s, n);
    }
    for (int i = 0; i < n; i++) {
        h[i] = vxs[i].d;
        cout << h[i] << endl;
    }
}
```

如果找到环路，就把环路上的一条边删除

4. 编写Dijkstra算法

```c++
struct vex {
    int v;
    Vnode * p;
};

void Dijkstra(int s, int n) {
    cout << "the source is " << s << endl;
    initialize_single_source(s, n);
    vector<vex> pq;
    for (int i = 0; i < n; i++) {
        vex a;
        a.v = i;
        a.p = &vxs[i];
        pq.push_back(a);
    }
    auto cmp = [](const vex x, const vex y) { return x.p->d > y.p->d;};
    make_heap(pq.begin(), pq.end(), cmp);
    while(pq.size() > 0) {
        pop_heap(pq.begin(), pq.end(), cmp);
        vex u = pq.back();
        pq.pop_back();
        if (u.p->d >= INFI) break;
        cout << u.v << endl;
        Enode * p = u.p->next;
        while (p != NULL) {
            relax(u.v, p->v, p->w);
            cout << p->v << " " << vxs[p->v].d << " " << vxs[p->v].pi << endl;
            p = p->next;
        }
        make_heap(pq.begin(), pq.end(), cmp);
    }
}
```

通过c++中heap操作来完成，底层容器为vector

5. 把结果打印到文件中

```c++
void printPaths (int s, int n) {
    cout << "enter print path" << endl;
    cout << "current source " << s << endl;
    vector<int> path;
    for (int i = 0; i < n; i++) {
        if (i == s) continue;
        path.clear();
        path.push_back(i);
        int u = i;
        while(vxs[u].pi != -1) {
            path.push_back(vxs[u].pi);
            u = vxs[u].pi;
        }
        if (path.size() == 1) {
            ofs << s << " to " << i << " path not found" << endl;
            continue;
        }
        ofs << "(";
        for (int j = path.size() - 1; j >= 0; j--) {
            ofs << path[j];
            if (j == 0) {
                ofs << ")";
            }
            else {
                ofs << " ";
            }
        }
        ofs << " " << vxs[i].d - h[s] + h[i] << endl;
    }
}
```

打印格式为括号中打印路径，后面跟着长度

6. 测时间的代码：

```c++
 LARGE_INTEGER nFreq;
 LARGE_INTEGER nBeginTime;
 LARGE_INTEGER nEndTime;
 QueryPerformanceFrequency(&nFreq);
 QueryPerformanceCounter(&nBeginTime);//开始计时 

bellman_ford(n, n + 1);
for (int k = 0; k < n; k++) {
Enode * p = vxs[k].next;
while (p != NULL) {
p->w = p->w + h[k] - h[p->v];
printf("%d %d %d\n", k, p->v, p->w);
p = p->next;
}
}
for (int k = 0; k < n; k++) {
Dijkstra(k, n);
printPaths(k, n);
}

QueryPerformanceCounter(&nEndTime);//停止计时  
time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
ofs_time << i + 1 << j + 1 << " 程序执行时间：" << time * 1000 << "ms" << endl;

```





### 实验结果

实验的输入和输出文件如要求组织，比较长这里就不附上了

时间：

```
11 程序执行时间：667.894ms
12 程序执行时间：149.635ms
21 程序执行时间：3953.59ms
22 程序执行时间：5631.76ms
31 程序执行时间：36801.1ms
32 程序执行时间：11527.1ms
41 程序执行时间：637771ms
42 程序执行时间：249333ms
```

![image-20221215123243536](C:/Users/luzim/AppData/Roaming/Typora/typora-user-images/image-20221215123243536.png)

从图中可以看出，时间复杂度与理论基本符合。
