// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if ((len <= -1)) {
		throw - 1;
	}
		BitLen = len;
		MemLen = (len + 31) >> 5;
		pMem = new TELEM[MemLen];
		if (pMem != NULL) {
			for (int i = 0; i < MemLen; i++) {
				pMem[i] = 0;
			}
		}
	
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL) {
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
		}
	}
}

TBitField::~TBitField()
{
	delete[]pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n > -1)&(n < BitLen)) {
		return n >> 5;
	}
	else throw - 1;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n > -1)&(n < BitLen))
	return 1<<(n&31);
	else throw - 1;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n > -1)&(n < BitLen))
	 {
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	}
	else throw - 1;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n > -1)&(n < BitLen))
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	else throw - 1;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if((n>-1)&(n<BitLen))
  return pMem[GetMemIndex(n)] & GetMemMask(n);
	else throw - 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this == &bf) {
		return *this;
	}
	else {
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		delete[] pMem;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
		}
	}
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int res = 1;
	if (this == &bf) {
		return res;
	}
	else {
		if ((BitLen == bf.BitLen)&&(MemLen==bf.MemLen)) {
			for (int i = 0; i < MemLen; i++) {
				if (pMem[i] != bf.pMem[i]) {
					res = 0;
					break;
				}
			}
		}
		else res = 0;
	}
	return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int res = 0;
	if (this == &bf) {
		return res;
	}
	else {
		if ((BitLen == bf.BitLen) && (MemLen == bf.MemLen)) {
			for (int i = 0; i < MemLen; i++) {
				if (pMem[i] != bf.pMem[i]) {
					res = 1;
					break;
				}
			}
		}
		else res = 1;
	}
	return res;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int i;
	int len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	 TBitField res(len);
	 for (i = 0; i <MemLen; i++) {
		 res.pMem[i] = pMem[i];
	}
	 for (i = 0; i < bf.MemLen; i++) {
		 res.pMem[i] |= bf.pMem[i];
	 }
	 return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int i;
	int len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField res(len);
	for (i = 0; i < MemLen; i++) {
		res.pMem[i] = pMem[i];
	}
	for (i = 0; i < bf.MemLen; i++) {
		res.pMem[i] &= bf.pMem[i];
	}
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	int len = BitLen;
	TBitField res(len);
	for (int i = 0; i < res.MemLen; i++) {
		res.pMem[i] = ~pMem[i];
	}
	return res;
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
