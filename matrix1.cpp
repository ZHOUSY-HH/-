#include <iostream>
#include <chrono>

using namespace std;

const int N = 300;

int **matrix(int **a, int **b)
{
    int **temp = new int *[N];
    for (int i = 0; i < N; i++)
        temp[i] = new int[N]();
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                temp[i][j] += a[i][k] * b[k][j];
    return temp;
}

void erase2(int **&temp)
{
    for (int i = 0; i < N; i++)
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
    cout<<endl;
}

int main()
{
    auto t1=std::chrono::steady_clock::now();
    int **a = new int *[N];
    int **b = new int *[N];
    for (int i = 0; i < N; i++)
    {
        a[i] = new int[N]();
        b[i] = new int[N]();
    }
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
        {
            a[i][j] = i+j;
            b[i][j] = i+j+1;
        }
    int** temp = matrix(a,b);
    show(a);
    show(b);
    show(temp);
    erase2(a);
    erase2(b);
    erase2(temp);
    auto t2=std::chrono::steady_clock::now();
    double dr_s=std::chrono::duration<double,std::micro>(t2-t1).count();
    cout<<"运行时间："<<dr_s<<"ns."<<endl;
}