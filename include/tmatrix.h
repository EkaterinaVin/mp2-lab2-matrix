// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных" 
// 
// Copyright (c) Сысоев А.В. 
// 
// 

#ifndef TDynamicMatrix_H 
#define TDynamicMatrix_H 

#include <iostream> 
#include <cassert> 
#include <cmath> 
using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор -  
// шаблонный вектор на динамической памяти 
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE)
            throw length_error("Vector size exceeded");
        pMem = new T[sz]();
        // {}; // У типа T д.б. констуктор по умолчанию 
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        if (sz > MAX_VECTOR_SIZE)
            throw length_error("Vector size exceeded");
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + v.sz, pMem);
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        sz = v.sz;
        pMem = nullptr;
        std::swap(pMem, v.pMem);
    }
    ~TDynamicVector()
    {
        if (pMem != nullptr)
            delete[] pMem;

        pMem = nullptr;
        sz = 0;
    }
    friend void swap(TDynamicVector& a, TDynamicVector& b) noexcept
    {
        std::swap(a.sz, b.sz);
        std::swap(a.pMem, b.pMem);
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v)
            return *this;
        TDynamicVector tmp(v);
        swap(*this, tmp);
        return *this;


    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        swap(*this, v);
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация 
    T& operator[](size_t ind)
    {
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        return pMem[ind];
    }
    // индексация с контролем 
    T& at(size_t ind)
    {
        if (ind >= sz || ind < 0)
            throw("Non-correct index");
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind >= sz || ind < 0)
            throw("Non-correct index");
        return pMem[ind];
    }

    // сравнение 
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (v.sz != sz)
            return false;
        for (size_t i = 0; i < sz; i++)
        {
            if (pMem[i] != v.pMem[i])
                return false;
        }
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        if (v.sz != sz)
            return true;
        for (size_t i = 0; i < sz; i++)
        {
            if (pMem[i] != v.pMem[i])
                return true;
        }
        return false;
    }

    // скалярные операции 
    TDynamicVector operator+(T val)
    {
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = pMem[i] + val;
        }
        return tmp;
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = pMem[i] - val;
        }
        return tmp;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = pMem[i] * val;
        }
        return tmp;
    }

    // векторные операции 
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw logic_error("Diferent sizes");
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = pMem[i] + v.pMem[i];
        }
        return tmp;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw logic_error("Diferent sizes");
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {

         tmp.pMem[i] = pMem[i] - v.pMem[i];
        }
        return tmp;
    }
  T operator*(const TDynamicVector& v) /*noexcept(noexcept(T()))*/
  {
      if (sz != v.sz)
          throw logic_error("Diferent sizes");
      T r = T();
      for (size_t i = 0; i < sz; i++) {
          r += pMem[i] * v.pMem[i];
      }
      return r;
  }

  /*friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }*/

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          istr >> v.pMem[i]; // требуется оператор>> для типа T
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
      return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (s > MAX_MATRIX_SIZE)
            throw length_error("Vector size exceeded");
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];
    using TDynamicVector<TDynamicVector<T>>::at;

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (m.sz != sz)
            return false;
        for (size_t i = 0; i < sz; i++)
        {
            if (pMem[i] != m.pMem[i])
                return false;
        }
        return true;
        
    }
    bool operator!=(const TDynamicMatrix& m) const noexcept
    {
        if (m.sz != sz)
            return true;
        for (size_t i = 0; i < sz; i++)
        {
            if (pMem[i] != m.pMem[i])
                return true;
        }
        return false;

    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix tmp(*this);

        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = tmp.pMem[i] * val;
        }

        return tmp;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.sz)
            throw logic_error("Diferent sizes");
        TDynamicVector<T> tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            tmp[i] = pMem[i] * v;
        }
        return tmp;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw logic_error("Diferent sizes");
        TDynamicMatrix tmp(*this);
        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = tmp.pMem[i] + m.pMem[i];
        }
        return tmp;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw logic_error("Diferent sizes");
        TDynamicMatrix tmp(*this);
        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = tmp.pMem[i] - m.pMem[i];
        }
        return tmp;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw logic_error("Diferent sizes");
        TDynamicMatrix tmp(*this);
        for (size_t i = 0; i < sz; i++)
        {
            for (size_t j = 0; j < sz; j++)
            {
                for (size_t k = 0; k < sz; k++)
                {
                    tmp.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
                }
            }
        }
        return tmp;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i];
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {

        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << "\n";
        return ostr;

    }
    size_t size() const noexcept { return sz; }
    
};

#endif
