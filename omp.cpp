#include <iostream>
#include <omp.h>
#include <vector>
#include <iostream>
#include <chrono>
#include <fstream>


void Create(int size)
{
    int num = size * size;
    std::ofstream matrix1("matrix1.txt");
    for (size_t i = 0; i < num; i++) matrix1 << rand() % 100 << "\t";
    std::ofstream matrix2("matrix2.txt");
    for (size_t i = 0; i < num; i++) matrix2 << rand() % 100 << "\t";
    matrix1.close();
    matrix2.close();
}

void Read(std::vector<std::vector<int>>& M, const char* str, int size)
{
    int temp;
    size_t i = 0;
    size_t j = 0;
    std::ifstream matrix(str);
    while (matrix >> temp)
    {
        if (i < size)
        {
            M[i][j] = temp;
            j++;
            if (j == size)
            {
                i++;
                j = 0;
            }
        }
    }
    matrix.close();
}

std::vector<std::vector<int>> MatrixMul(const std::vector<std::vector<int>>& M1, const std::vector<std::vector<int>>& M2, int size)
{
    int number_of_threads = 2;
    std::vector<std::vector<int>> res(size, std::vector<int>(size));
    std::ofstream results("res.txt", std::ios::app);
    auto start = std::chrono::steady_clock::now();
# pragma omp parallel for num_threads(number_of_threads)
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
                res[i][j] += M1[i][k] * M2[k][j];
        }
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    results << "Размер: " << size << "x" << size << std::endl;
    results << "Время: " << elapsed.count() << std::endl;
    results << "Количество потоков:" << number_of_threads << std::endl;
    results << "\n";
    return res;
}

int main()
{
    int size = 1000;
    std::vector<std::vector<int>> M1(size, std::vector<int>(size));
    std::vector<std::vector<int>> M2(size, std::vector<int>(size));
    std::vector<std::vector<int>> res(size, std::vector<int>(size));
    Create(size);
    Read(M1, "matrix1.txt", size);
    Read(M2, "matrix2.txt", size);
    res = MatrixMul(M1, M2, size);
    std::ofstream out("result_c++.txt");
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++)
            out << res[i][j] << "\t";
    return 0;
}