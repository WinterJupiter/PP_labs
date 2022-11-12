#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

const int size = 100;

void create()
{
    srand(time(0));
    int first[size][size] = { 0 };
    int second[size][size] = { 0 };
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            first[i][j] = rand() % 100;
            second[i][j] = rand() % 100;
        }
    std::ofstream f_first("D:\\matrix1.txt", std::ios::trunc);
    if (f_first.is_open())
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                f_first << " " << second[i][j] << std::endl;
    f_first.close();
    std::ofstream f_second("D:\\matrix2.txt", std::ios::trunc);
    if (f_second.is_open())
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                f_second << second[i][j] << std::endl;
    f_second.close();
}


void task()
{
    int first[size][size] = { 0 };
    int second[size][size] = { 0 };
    int result[size][size] = { 0 };
    std::ifstream f_first("D:\\matrix1.txt");
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            f_first >> first[i][j];
    f_first.close();
    std::ifstream f_second("D:\\matrix2.txt");
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            f_second >> second[i][j];
    f_second.close();

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            for (int k = 0; k < size; k++)
                result[i][j] += first[i][k] * second[k][j];

    std::ofstream f_result("D:\\result_c++.txt", std::ios::trunc);
    if (f_result.is_open())
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
            {
                f_result << result[i][j] << ' ';
                f_result << std::endl;
            }
    f_result.close();
}


int main()
{
    int a[10];
    for (int j = 0; j < 10; ++j)
    {
        create();
        auto begin = std::chrono::steady_clock::now();
        task();
        auto end = std::chrono::steady_clock::now();
        auto dif = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        a[j] = dif.count();
    }
    
    int sum = 0;
    std::ofstream out("D:\\res.txt", std::ios::app);
    if (out.is_open())
    {
        for (int i = 0; i < 10; i++)
        {
            out << a[i] << std::endl;
            sum += a[i];
        }
        int t = sum / 10;
        out << "\nСреднее: " << t << std::endl << std::endl;
    }
    out.close();
    return 0;
}
