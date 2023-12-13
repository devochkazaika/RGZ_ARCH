#include <iostream>
#include<fstream>
#include "Matrix.h"

void test_1(){
    ifstream file1("file_test/1.txt");
    ifstream file2("file_test/2.txt");
    Matrix t1 = Matrix::input(file1) ;
    Matrix t2 = Matrix::input(file2) ; 
    Matrix t3 = t1 * t2;
    Matrix::print(t3);
}

void test_2(){
    ifstream file1("file_test/3.txt");
    ifstream file2("file_test/4.txt");
    Matrix t1 = Matrix::input(file1) ;
    Matrix t2 = Matrix::input(file2) ; 
    Matrix t3 = t1 * t2;
    Matrix::print(t3);
}

void test_3(){
    ifstream file1("file_test/1.txt");
    ifstream file2("file_test/4.txt");
    Matrix t1 = Matrix::input(file1) ;
    Matrix t2 = Matrix::input(file2) ; 
    Matrix t3 = t1 * t2;
    Matrix::print(t3);
}

int main(){
    try{
        test_2();
    }
    catch (std::invalid_argument& e)
    {
        cerr << e.what() << endl;
        return -1;
    }
}