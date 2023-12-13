#include <iostream>
#include<fstream>
#include "Matrix.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

//случайные матрицы
void set_rand(int a, Matrix &t){
    for (int i=0; i<a; i++){
        for (int j=0; j<a; j++){
            t.set_cell(i, j, rand()%1000);
        }
    }
}

int main(){
    auto t_1 = steady_clock::now();
    auto t_2 = steady_clock::now();
    int size;
    int step = 250;
    cout << "slow" << endl;
    //медленное умножение
    for (int i=1; i<8; i++){
        size = step * i;
        Matrix t1(size);
        set_rand(size, t1);
        Matrix t2(size);
        set_rand(size, t2);
        t_1 = steady_clock::now();
        Matrix::multi_slow(t1, t2);
        t_2 = steady_clock::now();
        cout /*<< "Time for size " << size << ": "*/ << duration<double>(t_2 - t_1).count() << endl; 
    }
    //быстрое умножение
    cout << "fast" << endl;
    for (int i=1; i<8; i++){
        size = step * i;
        Matrix t1(size);
        set_rand(size, t1);
        Matrix t2(size);
        set_rand(size, t2);
        t_1 = steady_clock::now();
        t1 * t2;
        t_2 = steady_clock::now();
        cout /*<< "Time for size " << size << ": "*/ << duration<double>(t_2 - t_1).count() << endl; 
    }
}