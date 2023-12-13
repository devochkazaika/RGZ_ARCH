#include <iostream>
#include<fstream>
#include "Matrix.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

class Matrix{
    public:
        int n, m;             //размер n-кол-во колонок, m-кол-во столбцов
        int **mat;            //матрица
        int **Tmat;           //транспонированная матрица
        Matrix(int a) : Matrix(a, a){}
        Matrix(int a, int b){
            n = a;
            m = b;
            mat = new int*[n];
            Tmat = new int*[m];
            for (int i=0; i<n; i++){        //создание матрицы
                mat[i] = new int[m];
            }
            for (int i=0; i<m; i++){        //создание транспонированной матрицы
                Tmat[i] = new int[n];
            }
        }
        void set_cell(int i, int j, int value){ //сеттер для ячеек матрицы
            mat[i][j] = value;
            Tmat[j][i] = value;
        }
        int get_cell(int i, int j) const{       //геттер для ячеек матрицы
            return mat[i][j];
        }

        Matrix operator *(Matrix b){            //умножение матрицы на трансп матрицу
            Matrix temp(this->n, b.m);
            if (this->m != b.n) throw std::invalid_argument("not same sizes");
            int sum = 0;
            for (int i=0; i<this->n; i++){
                for (int q=0; q<b.m; q++){
                    sum = 0;
                    for (int j=0; j<b.n; j++){
                        sum += this->mat[i][j] * b.Tmat[q][j];
                    }
                    temp.set_cell(i, q, sum);
                }
                sum = 0;
            }
            return temp;
        }

        static Matrix multi_slow(Matrix a, Matrix b){       //обычное умножение матриц
            Matrix temp(a.n, b.m);
            if (a.m != b.n) throw std::invalid_argument("not same sizes");
            int sum = 0;
            for (int i=0; i<a.n; i++){
                for (int q=0; q<b.m; q++){
                    sum = 0;
                    for (int j=0; j<b.n; j++){
                        sum += a.mat[i][j] * b.mat[j][q];
                    }
                    temp.set_cell(i, q, sum);
                }
                sum = 0;
            }
            return temp;
        }
        
        static void print(Matrix a){        //вывод матрицы
            for (int i=0; i<a.n; i++){
                for (int j=0; j<a.m; j++){
                    cout << a.mat[i][j] << " ";
                }
                cout << endl;
            }
        }

        static Matrix input(ifstream &text){    //чтение матрицы из файла(для тестов)
            int a, value;
            text >> a;
            Matrix temp(a);
            for (int i=0; i<a; i++){
                for (int j=0; j<a; j++){
                    text >> value;
                    temp.set_cell(i, j, value);
                }
            }
            text.close();
            return temp;
        }

};

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