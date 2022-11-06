// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len): MemLen((len + (sizeof(TELEM) * 8 - 1)) / (sizeof(TELEM) * 8)), BitLen(len)
{
    if (len < 0) {
        throw new exception;
    }

    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.GetLength();
    MemLen = (BitLen + (sizeof(TELEM) * 8 - 1)) / (sizeof(TELEM) * 8);
    pMem = new TELEM[MemLen];

    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete [] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return (TELEM)n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return (TELEM)1 << ((TELEM)n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n > BitLen)
        throw new exception;
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n > BitLen)
        throw new exception;
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n > BitLen)
        throw new exception;
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{

    BitLen = bf.GetLength();
    MemLen = (BitLen + (sizeof(TELEM) * 8 - 1)) / (sizeof(TELEM) * 8);
    pMem = new TELEM[MemLen];

    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }


    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    
    if (BitLen != bf.BitLen)
        return 0;
    
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i]) {
            return 0;
        }
    }

    return 1;

}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return 1;

    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i]) {
            return 1;
        }
    }

    return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{

    TBitField res(max(bf.BitLen, BitLen));
    for (int i = 0; i < MemLen; i++) {
        res.pMem[i] |= pMem[i];
    }
    for (int i = 0; i < bf.MemLen; i++) {
        res.pMem[i] |= bf.pMem[i];
    }
    return res;

}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField res(max(bf.BitLen, BitLen));
    for (int i = 0; i < min(bf.MemLen, MemLen); i++) {
        res.pMem[i] = pMem[i] & bf.pMem[i];
    }
    return res;
}

TBitField TBitField::operator~(void) // отрицание
{

    TBitField res(BitLen);
    for (int i = 0; i < MemLen - 1; i++) {
        res.pMem[i] = ~pMem[i];
    }

    TELEM f = 0;
    for (int i = 0; i < (BitLen % (sizeof(TELEM) * 8)); i++)
        f |= GetMemMask(i);
    res.pMem[MemLen - 1] = (~pMem[MemLen - 1]) & f;

    return res;

}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{

    char c = ' ';
    while (c != '1' && c != '0')
        istr >> c;
    int i = 0;
    while (c == '1' || c == '0') {
        if (c == '1')
            bf.SetBit(i);
        if (c == '0')
            bf.ClrBit(i);
        i++;
        istr >> c;
    }

    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{

    char c;
    for (int i = 0; i < bf.BitLen; i++) {
        if (bf.GetBit(i) == 1)
            c = '1';
        else
            c = '0';
        ostr << c;
    }

    return ostr;
}
