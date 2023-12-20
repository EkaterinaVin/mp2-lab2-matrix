// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
#include <ctime>
//---------------------------------------------------------------------------

void main()
{
  TDynamicMatrix<int> a(5), b(5), c(5);
  TDynamicVector<int> a1(5), b1(5), c1(5);
  int i, j;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование класс работы с векторами"
      << endl;
  for (i = 0; i < 5; i++)
      {
          a1[i] = i * 10;
          b1[i] = i * 10 * 100;
      }
  c1 = a1 + b1;
  cout << "Vector a1 = " << endl << a1 << endl;
  cout << "Vector b1 = " << endl << b1 << endl;
  cout << "Vector c1 = a1 + b1" << endl << c1 << endl;
  cout << "Тестирование класс работы с матрицами"
    << endl;
  for (i = 0; i < 5; i++)
    for (j = i; j < 5; j++ )
    {
      a[i][j] =  i * 10 + j;
      b[i][j] = (i * 10 + j) * 100;
    }
  c = a + b;
  cout << "Matrix a = " << endl << a << endl;
  cout << "Matrix b = " << endl << b << endl;
  cout << "Matrix c = a + b" << endl << c << endl;
  
 
  unsigned int start_time = clock(); // начальное время
  int n = 3000;
  TDynamicMatrix<int> x(n), y(n), z(n);
  for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
      {
          x[i][j] = i * 10 + j;
          y[i][j] = (i * 10 + j) * 100;
      }
  z = x + y;  unsigned int end_time = clock(); // конечное время
  unsigned int search_time = end_time - start_time;
  cout << "time s 3000: " << search_time;
  unsigned int start_time1 = clock(); 
  z = x * y;  unsigned int end_time1 = clock(); // конечное время
  unsigned int search_time1 = end_time1 - start_time1;
  cout << "time p 3000: " << search_time1;
}
//---------------------------------------------------------------------------
