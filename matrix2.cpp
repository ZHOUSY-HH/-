//以假设为2的幂的阶数。
#include <iostream>
#include <vector>

#define il first
#define jl second

using namespace std;

const int N = 8;

void erase2(int **&temp)
{
    for (int i = 0; i < N; i++)
        delete[] temp[i];
    delete[] temp;
    temp = nullptr;
}

void erase3(pair<int, int> **&temp)
{
    for (int i = 0; i < 2; i++)
        delete[] temp[i];
    delete[] temp;
    temp = nullptr;
}

void show(int **temp)
{
    if (temp)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                cout << temp[i][j] << " ";
            cout << endl;
        }
    }
    else
    {
        cout << "nullptr" << endl;
    }
    cout << endl;
}

void div(int count, int ai, int aj, int bi, int bj, int ci, int cj, int **a, int **b, int **c)
{
    if (count == 2)
    {
        for (int i = 0; i < count; i++)
            for (int j = 0; j < count; j++)
                for (int k = 0; k < count; k++)
                {
                    c[i + ci][j + cj] += a[i + ai][k + aj] * b[k + bi][j + bj];
                }
    }
    else
    {
        /*
        //结果矩阵:
        int ci2 = ci; //右上矩阵；
        int cj2 = (cj + count) / 2;
        int ci3 = (ci + count) / 2; //左下矩阵;
        int cj3 = cj;
        int ci4 = ci3; //右下矩阵
        int cj4 = cj2;
        //a矩阵:
        int ai2 = ai; //右上矩阵；
        int aj2 = (aj + count) / 2;
        int ai3 = (ai + count) / 2; //左下矩阵;
        int aj3 = aj;
        int ai4 = ai3; //右下矩阵
        int aj4 = aj2;
        //b矩阵:
        int bi2 = bi; //右上矩阵；
        int bj2 = (bj + count) / 2;
        int bi3 = (bi + count) / 2; //左下矩阵;
        int bj3 = bj;
        int bi4 = bi3; //右下矩阵
        int bj4 = bj2;
        count /=2;
        div(count, ai, aj, bi, bj, ci, cj, a, b, c);
        div(count, )
        */
        pair<int, int> **a_temp = new pair<int, int> *[2];
        for (int i = 0; i < 2; i++)
            a_temp[i] = new pair<int, int>[2];
        pair<int, int> **b_temp = new pair<int, int> *[2];
        for (int i = 0; i < 2; i++)
            b_temp[i] = new pair<int, int>[2];
        pair<int, int> **c_temp = new pair<int, int> *[2];
        for (int i = 0; i < 2; i++)
            c_temp[i] = new pair<int, int>[2];

        a_temp[0][0].il = ai;
        a_temp[0][0].jl = aj;
        a_temp[0][1].il = ai;
        a_temp[0][1].jl = aj + count/ 2;
        a_temp[1][0].il = ai + count/ 2;
        a_temp[1][0].jl = aj;
        a_temp[1][1].il = a_temp[1][0].il;
        a_temp[1][1].jl = a_temp[0][1].jl;

        b_temp[0][0].il = bi;
        b_temp[0][0].jl = bj;
        b_temp[0][1].il = bi;
        b_temp[0][1].jl = bj + count / 2;
        b_temp[1][0].il = bi + count / 2;
        b_temp[1][0].jl = bj;
        b_temp[1][1].il = b_temp[1][0].il;
        b_temp[1][1].jl = b_temp[0][1].jl;

        c_temp[0][0].il = ci;
        c_temp[0][0].jl = cj;
        c_temp[0][1].il = ci;
        c_temp[0][1].jl = cj + count / 2;
        c_temp[1][0].il = ci + count / 2;
        c_temp[1][0].jl = cj;
        c_temp[1][1].il = c_temp[1][0].il;
        c_temp[1][1].jl = c_temp[0][1].jl;

        count /= 2;

        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++)
                    div(count, a_temp[i][k].il, a_temp[i][k].jl, b_temp[k][j].il, b_temp[k][j].jl, c_temp[i][j].il, c_temp[i][j].jl, a, b, c);
        erase3(a_temp);
        erase3(b_temp);
        erase3(c_temp);
    }
}

int main()
{
    int **a = new int *[N];
    int **b = new int *[N];
    int **c = new int *[N];
    for (int i = 0; i < N; i++)
    {
        a[i] = new int[N]();
        b[i] = new int[N]();
        c[i] = new int[N]();
    }
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
        {
            a[i][j] = i+j;
            b[i][j] = i+j+1;
        }
    div(N, 0,0,0,0,0,0,a,b,c);
    show(a);
    show(b);
    show(c);
    erase2(a);
    erase2(b);
    erase2(c);
}