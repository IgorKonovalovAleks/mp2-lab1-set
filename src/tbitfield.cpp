// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len): MemLen(len), BitLen(32)
{
    pMem = new TELEM;
    *pMem = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    pMem = new TELEM;
    *pMem = 0;

    for (int i = 0; i < bf.GetLength(); i++) {
        *pMem |= bf.GetBit(i);
    }
}

TBitField::~TBitField()
{
    delete pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return BitLen - MemLen + n;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    int N = GetMemIndex(n);

    return TELEM();
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return MemLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    *pMem |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    *pMem &= (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  return *pMem & GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{

    *pMem = 0;
    for (int i = 0; i < bf.GetLength(); i++) {
        *pMem |= bf.GetBit(i);
    }


    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    for (int i = 0; i < GetLength(); i++) {

    }

    return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    return TBitField(0);
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    return TBitField(0);
}

TBitField TBitField::operator~(void) // отрицание
{
    return TBitField(0);
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    return ostr;
}
