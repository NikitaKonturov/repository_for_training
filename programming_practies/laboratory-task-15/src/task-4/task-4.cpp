#include"task-4.hpp"


void getSizesForMtrx(size_t& rows, size_t& columns)
{
    int64_t sRows = 1;
    int64_t sColumns = 1;
    std::cout << "Введите количество строк матрицы: ";
    std::cin >> sRows;
    std::cout << std::endl;
    std::cout << "Введите количетво столбцов матрицы: ";
    std::cin >> sColumns;
    if(sRows <= 0 || sColumns <= 0) {
        throw std::invalid_argument("Matrix sizes must be natural...");
    } 
    rows = sRows;
    columns = sColumns;
}

void filMtrx(std::vector<std::vector<int>>& mtrx, int32_t leftBrd, int32_t rightBrd)
{
    for(auto& i : mtrx) {
        for(auto& j : i) {
            j = leftBrd  + (std::rand() % (rightBrd - leftBrd + 1));
        }
    }
}

void deleteRowAndColumnWhisMaxEllement(std::vector<std::vector<int>>& mtrx)
{
    std::vector<std::vector<int>>::iterator rowWithMaxElement = std::max_element(mtrx.begin(), mtrx.end(), [](std::vector<int>& first, std::vector<int>& second){return (*std::max_element(first.begin(), first.end())) < (*std::max_element(second.begin(), second.end()));});
    
    
    size_t columnWithMaxElement = std::distance((*rowWithMaxElement).begin(), std::max_element((*rowWithMaxElement).begin(), (*rowWithMaxElement).end()));
    
    mtrx.erase(rowWithMaxElement);
    for(auto& row : mtrx) {
        row.erase(row.begin() + columnWithMaxElement);
    }
}

void qsortVectors(std::vector<std::vector<int>>& mtrx, size_t left, size_t right)
{
    if(mtrx.size() == 1) {
        return;
    }
    size_t begin = left;
    size_t end = right;

    int mid = std::accumulate(mtrx[(begin + end) / 2].begin(), mtrx[(begin + end) / 2].end(), 0);
    
    while(begin <= end) {
        while (std::accumulate(mtrx[begin].begin(), mtrx[begin].end(), 0) <  mid) {
            ++begin;
        }
        while (std::accumulate(mtrx[end].begin(), mtrx[end].end(), 0) >  mid) {
            --end;
        }
        if(begin <= end) {
            std::swap(mtrx[begin], mtrx[end]);
            ++begin;
            --end;
        }
    }

    if (end > left) {
        qsortVectors(mtrx, left, end);
    }
    if (begin < right) {
        qsortVectors(mtrx, begin, right);
    }
}

void fourthTask() 
{
    std::srand(time(0));
    size_t columns = 1;
    size_t rows = 1;
    int32_t begin = 0;
    int32_t end = 1;

    getSizesForMtrx(rows, columns);

    std::vector<std::vector<int>> mtrx(rows, std::vector<int>(columns));

    std::cout << "Введите границы диапазона заполнения: ";
    std::cin >> begin >> end;
    std::cout << std::endl;
    if(begin > end) {
        std::swap(begin, end);
    }
    
    filMtrx(mtrx, begin, end);

    std::cout << "Матрица заполненная случайным образом: " << std::endl;

    std::for_each(mtrx.begin(), mtrx.end(), [](const std::vector<int>& i){
                                                    std::for_each(i.begin(), i.end(), []( const int& j){std::cout << std::setw(3) << j << " ";});
                                                    std::cout << std::endl;
                                                    });

    std::cout << "#######################################################" << std::endl;

    deleteRowAndColumnWhisMaxEllement(mtrx);

    std::cout << "Матрица после удаления строки и столбца с максимальным элементом: " << std::endl;
    std::for_each(mtrx.begin(), mtrx.end(), [](const std::vector<int>& i){
                                                    std::for_each(i.begin(), i.end(), []( const int& j){std::cout <<  std::setw(3) << j << " ";});
                                                    std::cout << std::endl;
                                                    });

    std::cout << "#######################################################" << std::endl;

    qsortVectors(mtrx, 0, (mtrx.size()-1));

    std::cout << "Матрица после сортировки строк: " << std::endl; 
    std::for_each(mtrx.begin(), mtrx.end(), [](const std::vector<int>& i){
                                                    std::for_each(i.begin(), i.end(), []( const int& j){std::cout <<  std::setw(3) << j << " ";});
                                                    std::cout << std::endl;
                                                    });

    std::cout << "#######################################################" << std::endl;
}
