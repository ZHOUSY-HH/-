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

void erase2(int **&temp, const int &N)
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

pair<int, int> **new_temp()
{
    pair<int, int> **a_temp = new pair<int, int> *[2];
    for (int i = 0; i < 2; i++)
        a_temp[i] = new pair<int, int>[2];
    return a_temp;
}
void show_pair(pair<int, int> temp)
{
    cout<<"("<<temp.il<<","<<temp.jl<<")"<<endl;
}

/*参数说明：
1.add表示是否执行加法;
2.count表示矩阵大小;
3.num表示有多少个矩阵需要计算;
*/
void div(bool *add, int count, int num, const pair<int, int> &ap, pair<int, int> &bp, pair<int, int> *&cp, int **a, int **b, int **c)
{
    for (int div_num = 0; div_num < num; div_num++)
    {
        if (count == 2 )
        {
            if (add[div_num] == true)
                for (int i = 0; i < count; i++)
                    for (int j = 0; j < count; j++)
                        for (int k = 0; k < count; k++)
                        {
                            c[i + cp[div_num].il][j + cp[div_num].jl] += a[i + ap.il][k + ap.jl] * b[k + bp.il][j + bp.jl];
                        }
            else
                for (int i = 0; i < count; i++)
                    for (int j = 0; j < count; j++)
                        for (int k = 0; k < count; k++)
                        {
                            c[i + cp[div_num].il][j + cp[div_num].jl] -= a[i + ap.il][k + ap.jl] * b[k + bp.il][j + bp.jl];
                        }
        }
        else
        {
            pair<int, int> **a_temp = new_temp();
            pair<int, int> **b_temp = new_temp();
            pair<int, int> **c_temp = new_temp();

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

            c_temp[0][0].il = cp[div_num].il;
            c_temp[0][0].jl = cp[div_num].jl;
            c_temp[0][1].il = cp[div_num].il;
            c_temp[0][1].jl = cp[div_num].jl + count / 2;
            c_temp[1][0].il = cp[div_num].il + count / 2;
            c_temp[1][0].jl = cp[div_num].jl;
            c_temp[1][1].il = c_temp[1][0].il;
            c_temp[1][1].jl = c_temp[0][1].jl;

            count /= 2;

            bool *add_or_sub = new bool[2];
            pair<int, int> *p_ap = new pair<int, int>[2];

            //p1:
            sub_matrix(count, b, b, b_temp[0][1], b_temp[1][1]);
            add_or_sub[0] = add_or_sub[1] = add[div_num];
            p_ap[0] = c_temp[0][1];
            p_ap[1] = c_temp[1][1];
            div(add_or_sub, count, 2, a_temp[0][0], b_temp[0][1], p_ap, a, b, c);
            /*show_pair(a_temp[0][0]);
            show_pair(b_temp[0][1]);
            show(a);
            show(b);*/
            add_matrix(count, b, b, b_temp[0][1], b_temp[1][1]);
            /*cout<<add_or_sub[0]<<" "<<add_or_sub[1]<<" "<<num<<endl;
            show(c);
            show(b);*/
            //p2:
            add_matrix(count, a, a, a_temp[0][0], a_temp[0][1]);
            add_or_sub[0] = !add[div_num];
            add_or_sub[1] = add[div_num];
            p_ap[0] = c_temp[0][0];
            p_ap[1] = c_temp[0][1];
            div(add_or_sub, count, 2, a_temp[0][0], b_temp[1][1], p_ap, a, b, c);
            sub_matrix(count, a, a, a_temp[0][0], a_temp[0][1]);
            //p3:
            add_matrix(count, a, a, a_temp[1][0], a_temp[1][1]);
            add_or_sub[0] = add[div_num];
            add_or_sub[1] = !add[div_num];
            p_ap[0] = c_temp[1][0];
            p_ap[1] = c_temp[1][1];
            div(add_or_sub, count, 2, a_temp[1][0], b_temp[0][0], p_ap, a, b, c);
            sub_matrix(count, a, a, a_temp[1][0], a_temp[1][1]);
            //p4:
            sub_matrix(count, b, b, b_temp[1][0], b_temp[0][0]);
            add_or_sub[0] = add_or_sub[1] = add[div_num];
            p_ap[0] = c_temp[0][0];
            p_ap[1] = c_temp[1][0];
            div(add_or_sub, count, 2, a_temp[1][1], b_temp[1][0], p_ap, a, b, c);
            add_matrix(count, b, b, b_temp[1][0], b_temp[0][0]);
            //p5:
            add_matrix(count, a, a, a_temp[0][0], a_temp[1][1]);
            add_matrix(count, b, b, b_temp[0][0], b_temp[1][1]);
            add_or_sub[0] = add_or_sub[1] = add[div_num];
            p_ap[0] = c_temp[0][0];
            p_ap[1] = c_temp[1][1];
            div(add_or_sub, count, 2, a_temp[0][0], b_temp[0][0], p_ap, a, b, c);
            sub_matrix(count, a, a, a_temp[0][0], a_temp[1][1]);
            sub_matrix(count, b, b, b_temp[0][0], b_temp[1][1]);
            //p6:
            sub_matrix(count, a, a, a_temp[0][1], a_temp[1][1]);
            add_matrix(count, b, b, b_temp[1][0], b_temp[1][1]);
            add_or_sub[0] = add[div_num];
            p_ap[0] = c_temp[0][0];
            div(add_or_sub, count, 1, a_temp[0][1], b_temp[1][0], p_ap, a, b, c);
            add_matrix(count, a, a, a_temp[0][1], a_temp[1][1]);
            sub_matrix(count, b, b, b_temp[1][0], b_temp[1][1]);
            //p7:
            sub_matrix(count, a, a, a_temp[0][0], a_temp[1][0]);
            add_matrix(count, b, b, b_temp[0][0], b_temp[0][1]);
            add_or_sub[0] = !add[div_num];
            p_ap[0] = c_temp[1][1];
            div(add_or_sub, count, 1, a_temp[0][0], b_temp[0][0], p_ap, a, b, c);
            add_matrix(count, a, a, a_temp[0][0], a_temp[1][0]);
            sub_matrix(count, b, b, b_temp[0][0], b_temp[0][1]);

            delete[] p_ap;
            delete[] add_or_sub;
            erase3(a_temp);
            erase3(b_temp);
            erase3(c_temp);

            count *= 2;
        }
    }
}

int main()
{
    auto t1=std::chrono::steady_clock::now();
    int N = 1;
    while(N<NUM)
        N = N<<1;
    int **a = new int *[N];
    int **b = new int *[N];
    int **c = new int *[N];
    for (int i = 0; i < N; i++)
    {
        a[i] = new int[N]();
        b[i] = new int[N]();
        c[i] = new int[N]();
    }
    for(int i=0; i<NUM; i++)
        for(int j=0; j<NUM; j++)
        {
            a[i][j] = i+j;
            b[i][j] = i+j+1;
        }
    bool* add = new bool[2];
    add[0] = true;
    pair<int, int>* p_ap = new pair<int, int>[2];
    p_ap[0].il = p_ap[0].jl = 0;
    pair<int, int> ap(0,0);
    pair<int, int> bp(0,0);
    div(add, N, 1, ap, bp, p_ap, a, b, c);

    show(a);
    show(b);
    show(c);
    erase2(a,N);
    erase2(b,N);
    erase2(c,N);
    delete []add;
    delete []p_ap;
    auto t2=std::chrono::steady_clock::now();
    double dr_s=std::chrono::duration<double,std::micro>(t2-t1).count();
    cout<<"运行时间："<<dr_s<<"ns."<<endl;
}