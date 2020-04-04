#include <iostream>
#include <chrono>

#define il first
#define jl second

using namespace std;

const int NUM = 512;

void add_matrix(const int &count, int **a, int **b, const pair<int, int> &begin1, const pair<int, int> &begin2)
{
    for (int i = 0; i < count; i++)
        for (int j = 0; j < count; j++)
            a[i + begin1.il][j + begin1.jl] += b[i + begin2.il][j + begin2.jl];
}

void sub_matrix(const int &count, int **a, int **b, const pair<int, int> &begin1, const pair<int, int> &begin2)
{
    for (int i = 0; i < count; i++)
        for (int j = 0; j < count; j++)
            a[i + begin1.il][j + begin1.jl] -= b[i + begin2.il][j + begin2.jl];
}

void inline erase2(int **&temp, const int &N)
{
    for (int i = 0; i < N; i++)
        delete[] temp[i];
    delete[] temp;
    temp = nullptr;
}

int **newone(const int &count)
{
    int **temp = new int *[count];
    for (int i = 0; i < count; i++)
        temp[i] = new int[count]();
    return temp;
}

pair<int, int> **new_temp()
{
    pair<int, int> **a_temp = new pair<int, int> *[2];
    for (int i = 0; i < 2; i++)
        a_temp[i] = new pair<int, int>[2];
    return a_temp;
}

void show(int **temp)
{
    if (temp)
    {
        for (int i = 0; i < NUM; i++)
        {
            for (int j = 0; j < NUM; j++)
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

int **div(int count, int **a, int **b, pair<int, int> ap, pair<int, int> bp)
{
    int **c = newone(count);
    if (count <= 64)
    {
        for (int i = 0; i < count; i++)
            for (int j = 0; j < count; j++)
                for (int k = 0; k < count; k++)
                    c[i][j] += a[i + ap.il][k + ap.jl] * b[k + bp.il][j + bp.jl];
    }
    else
    {
        pair<int, int> **a_temp = new_temp();
        pair<int, int> **b_temp = new_temp();

        //计算每个分块的顶点。
        a_temp[0][0].il = ap.il;
        a_temp[0][0].jl = ap.jl;
        a_temp[0][1].il = ap.il;
        a_temp[0][1].jl = ap.jl + count / 2;
        a_temp[1][0].il = ap.il + count / 2;
        a_temp[1][0].jl = ap.jl;
        a_temp[1][1].il = a_temp[1][0].il;
        a_temp[1][1].jl = a_temp[0][1].jl;

        b_temp[0][0].il = bp.il;
        b_temp[0][0].jl = bp.jl;
        b_temp[0][1].il = bp.il;
        b_temp[0][1].jl = bp.jl + count / 2;
        b_temp[1][0].il = bp.il + count / 2;
        b_temp[1][0].jl = bp.jl;
        b_temp[1][1].il = b_temp[1][0].il;
        b_temp[1][1].jl = b_temp[0][1].jl;

        count /= 2;

        //p1;
        sub_matrix(count, b, b, b_temp[0][1], b_temp[1][1]);
        int **p1 = div(count, a, b, a_temp[0][0], b_temp[0][1]);
        add_matrix(count, b, b, b_temp[0][1], b_temp[1][1]);

        //p2:
        add_matrix(count, a, a, a_temp[0][0], a_temp[0][1]);
        int **p2 = div(count, a, b, a_temp[0][0], b_temp[1][1]);
        sub_matrix(count, a, a, a_temp[0][0], a_temp[0][1]);

        //p3:
        add_matrix(count, a, a, a_temp[1][0], a_temp[1][1]);
        int **p3 = div(count, a, b, a_temp[1][0], b_temp[0][0]);
        sub_matrix(count, a, a, a_temp[1][0], a_temp[1][1]);

        //p4:
        sub_matrix(count, b, b, b_temp[1][0], b_temp[0][0]);
        int **p4 = div(count, a, b, a_temp[1][1], b_temp[1][0]);
        add_matrix(count, b, b, b_temp[1][0], b_temp[0][0]);

        //p5:
        add_matrix(count, a, a, a_temp[0][0], a_temp[1][1]);
        add_matrix(count, b, b, b_temp[0][0], b_temp[1][1]);
        int **p5 = div(count, a, b, a_temp[0][0], b_temp[0][0]);
        sub_matrix(count, a, a, a_temp[0][0], a_temp[1][1]);
        sub_matrix(count, b, b, b_temp[0][0], b_temp[1][1]);

        //p6:
        sub_matrix(count, a, a, a_temp[0][1], a_temp[1][1]);
        add_matrix(count, b, b, b_temp[1][0], b_temp[1][1]);
        int **p6 = div(count, a, b, a_temp[0][1], b_temp[1][0]);
        add_matrix(count, a, a, a_temp[0][1], a_temp[1][1]);
        sub_matrix(count, b, b, b_temp[1][0], b_temp[1][1]);

        //p7:
        sub_matrix(count, a, a, a_temp[0][0], a_temp[1][0]);
        add_matrix(count, b, b, b_temp[0][0], b_temp[0][1]);
        int **p7 = div(count, a, b, a_temp[0][0], b_temp[0][0]);
        add_matrix(count, a, a, a_temp[0][0], a_temp[1][0]);
        sub_matrix(count, b, b, b_temp[0][0], b_temp[0][1]);

        pair<int, int> c1(0, 0);
        pair<int, int> c2(0, count);
        pair<int, int> c3(count, 0);
        pair<int, int> c4(count, count);

        //c1:
        add_matrix(count, c, p5, c1, c1);
        add_matrix(count, c, p4, c1, c1);
        add_matrix(count, c, p6, c1, c1);
        sub_matrix(count, c, p2, c1, c1);

        //c2:
        add_matrix(count, c, p1, c2, c1);
        add_matrix(count, c, p2, c2, c1);

        //c3:
        add_matrix(count, c, p3, c3, c1);
        add_matrix(count, c, p4, c3, c1);

        //c4:
        add_matrix(count, c, p5, c4, c1);
        add_matrix(count, c, p1, c4, c1);
        sub_matrix(count, c, p3, c4, c1);
        sub_matrix(count, c, p7, c4, c1);

        erase2(p1, count);
        erase2(p2, count);
        erase2(p3, count);
        erase2(p4, count);
        erase2(p5, count);
        erase2(p6, count);
        erase2(p7, count);
    }
    return c;
}

int main()
{
    auto t1=std::chrono::steady_clock::now();
    int N = 1;
    while(N<NUM)
        N = N<<1;
    int **a = new int *[N];
    int **b = new int *[N];
    for (int i = 0; i < N; i++)
    {
        a[i] = new int[N]();
        b[i] = new int[N]();
    }
    for(int i=0; i<NUM; i++)
        for(int j=0; j<NUM; j++)
        {
            a[i][j] = i+j;
            b[i][j] = i+j+1;
        }
    pair<int, int> temp(0,0);
    int** c = div(N, a, b, temp, temp);
    show(a);
    show(b);
    show(c);
    erase2(a,N);
    erase2(b,N);
    erase2(c,N);
    auto t2=std::chrono::steady_clock::now();
    double dr_s=std::chrono::duration<double,std::micro>(t2-t1).count();
    cout<<"运行时间："<<dr_s<<"ns."<<endl;
}