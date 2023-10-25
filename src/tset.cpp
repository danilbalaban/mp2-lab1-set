// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(1)
{
    if (mp > 0) {
        MaxPower = mp;
        BitField = TBitField(MaxPower);
    }
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(1)
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(1)
{
    MaxPower = bf.GetLength();
    BitField = bf;
}

TSet::operator TBitField()
{
    return FAKE_BITFIELD;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if ((BitField.GetBit(Elem)) == 1) return true;
    return false;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0) throw "Err";
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0) throw "Err";
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
    BitField = s.BitField;
    MaxPower = s.MaxPower;
    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
    return (BitField == s.BitField);
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    return (BitField != s.BitField);
}

TSet TSet::operator+(const TSet& s) // объединение
{
    TSet tmp(BitField | s.BitField);
    return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet res(Elem > MaxPower ? Elem : MaxPower);
    res.BitField = BitField;
    res.InsElem(Elem);
    return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet res(*this);
    res.DelElem(Elem);
    return res;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    TSet tmp(BitField & s.BitField);
    return tmp;

}

TSet TSet::operator~(void) // дополнение
{
    TSet tmp(~BitField);
    return tmp;

}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    int tmp;
    char ch;
    do {
        istr >> ch;
    } while (ch != '{');
    do {
        istr >> tmp;
        s.InsElem(tmp);
        do {
            istr >> ch;
        } while (ch != ',' && ch != '}');
    } while (ch != '}');
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    bool flag = false;
    int tmp = s.GetMaxPower();
    for (int i = 0; i < tmp; ++i)
        if (s.IsMember(i))
            flag = true;
    if (flag) {
        ostr << "{ ";
        for (int i = 0; i < s.MaxPower; ++i)
            if (s.IsMember(i))
                ostr << i << "; ";
        ostr << "}";
    }
    else
        ostr << "0";
    return ostr;
}
