#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include<windows.h>  

using namespace std;

#define INFI 999999999

typedef struct Enode {
    struct Enode * next;
    int w;
    int v;
} Enode;

typedef struct Vnode {
    int d;
    int pi;
    Enode * next;
} Vnode;

ofstream ofs;
int N[4] = {27, 81, 243, 729};
Vnode vxs[800];
int h[800];
string infileName[4][2] = {{"input11.txt", "input12.txt"}, {"input21.txt", "input22.txt"}, {"input31.txt", "input32.txt"}, {"input41.txt", "input42.txt"}};
string outfileName[4][2] = {{"output11.txt", "output12.txt"}, {"output21.txt", "output22.txt"}, {"output31.txt", "output32.txt"}, {"output41.txt", "output42.txt"}};

void initialize_single_source (int s, int n) {
    for (int i = 0; i < n; i++) {
        vxs[i].d = INFI;
        vxs[i].pi = -1;
    }
    vxs[s].d = 0;
}

void relax (int u, int v, int w) {
    if (vxs[v].d > vxs[u].d + w) {
        vxs[v].d = vxs[u].d + w;
        vxs[v].pi = u;
    }
}

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

struct vex {
    int v;
    Vnode * p;
};

// struct tmp {
//     bool operator () (const vex & a, const vex & b) {
//         return a.p->d > b.p->d;
//     }
// };



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

int main () {
    double time = 0;
    ofstream ofs_time;
    ofs_time.open("../output/time.txt", ios::out);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            int n = N[i];
            // int n = 5;
            string infile = "../input/" + infileName[i][j];
            string outfile = "../output/" + outfileName[i][j];
            
            ofs.open(outfile, ios::out);
            // string infile = "../input/input.txt";
            FILE * fp;
            for (int k = 0; k < n; k++) {
                vxs[k].next = NULL;
            }
            if ((fp = fopen(infile.c_str(), "r")) == NULL) {
                printf("cannot open file!\n");
            }
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

            printf("\n");
            ofs.close();
        }
    }
    return 0;
}