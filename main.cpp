//#include "BitArray.h"
//#pragma once
#include <iostream>
#include <string>
#include <math.h>
#include <list>
#include <vector>
#include <limits>
#include <tuple>
#include <cassert>
#include <stdexcept>
using namespace std;

class BitArray
{
public:
	BitArray() {
		bites = (bool*)calloc(8, sizeof(bool));
		len = 8;
	}
	~BitArray() {
		delete[] bites;
		len = 0;
	}

	//Конструирует массив, хранящий заданное количество бит.
	//Первые sizeof(long) бит можно инициализровать с помощью параметра value.
	explicit BitArray(int num_bits, unsigned long value = 0) {
		if (num_bits > 0) {
			bites = (bool*)calloc(num_bits, sizeof(bool));
			for (int i = 0; i < value; i++) {
				bites[i] = 1;
			}
			len = num_bits;
		}
		else
			std::cout << "Bitset must contain more than 0 elemets" << endl;
	}
	/*{
		if (num_bits > 0) {
			bites = (bool*)calloc(num_bits, sizeof(bool));
			for (int i = 0; i < num_bits; i++) {
				if (value == 0)
					bites[i] = 0;
				else {
					if (value == 1)
						bites[i] = 1;
					else
						std::cout << "Bites must be 1 or 0" << endl;
				}
			}
			len = num_bits;
		}
		else
			std::cout << "Bitset must contain more than 0 elemets" << endl;
	}*/

	BitArray(const BitArray& b) {
		unsigned int size = sizeof(b.bites);
		bites = (bool*)malloc(size);
		for (unsigned int i = 0; i < size; i++) {
			bites[i] = b.bites[i];
		}
	}

	//Обменивает значения двух битовых массивов.
	void swap(BitArray& b) {
		if (sizeof(bites) == sizeof(b.bites)) {
			bool temp = 0;
			for (unsigned int i = 0; i < sizeof(bites); i++) {
				temp = bites[i];
				bites[i] = b.bites[i];
				b.bites[i] = temp;
			}
			//free(temp);
		}
		else {
			throw std::out_of_range("Bitsets must be equal");
		}
	}

	BitArray& operator=(const BitArray& b) {
		if (sizeof(bites) == sizeof(b.bites)) {
			for (unsigned int i = 0; i < sizeof(bites); i++)
				bites[i] = b.bites[i];
		}
		else {
			free(bites);
			bites = (bool*)malloc(sizeof(b.bites));
			for (unsigned int i = 0; i < sizeof(bites); i++)
				bites[i] = b.bites[i];
		}
		return *this;
	}
	//Изменяет размер массива. В случае расширения, новые элементы инициализируются значением value.
	void resize(int num_bits, bool value = false) {
		if (num_bits == 0) {
			free(bites);
		}
		else {
			bites = (bool*)realloc(bites, num_bits);
			//unsigned int* al = (unsigned int*)realloc(bites, sizeof(bool) / 8 * num_bits);
			for (unsigned int i = len; i < num_bits; i++) {
				if (value == 0)
					bites[i] = 0;
				else
					bites[i] = 1;
			}
			len = num_bits;
		}

	}
	//Очищает массив.
	void clear() {
		free(bites);
	}
	//Добавляет новый бит в конец массива. В случае необходимости происходит перераспределение памяти.
	void push_back(bool bit) {
		bool flag = 1;
		for (unsigned int i = 0; i < len; i++) {
			if (i == NULL) {
				flag = 0;
				bites[i] = bit;
			}
			if (flag == 0) {
				break;
			}
		}
	}
	//Битовые операции над массивами.
	//Работают только на массивах одинакового размера.
	//Обоснование реакции на параметр неверного размера входит в задачу.
	BitArray& operator&=(const BitArray& b) {
		for (unsigned int i = 0; i < sizeof(bites); i++) {
			bites[i] &= b.bites[i];
		}
		return *this;
	}
	BitArray& operator|=(const BitArray& b) {
		for (unsigned int i = 0; i < sizeof(bites); i++) {
			bites[i] |= b.bites[i];
		}
		return *this;
	}
	BitArray& operator^=(const BitArray& b) {
		for (unsigned int i = 0; i < sizeof(bites); i++) {
			bites[i] ^= b.bites[i];
		}
		return *this;
	}

	//Битовый сдвиг с заполнением нулями.
	BitArray& operator<<=(int n) {
		for (unsigned int i = 0; i < sizeof(bites); i++) {
			bites[i] <<= n;
		}
		return *this;
	}
	BitArray& operator>>=(int n) {
		for (unsigned int i = 0; i < sizeof(bites); i++) {
			bites[i] <<= n;
		}
		return *this;
	}
	BitArray operator<<(int n) const {
		for (int i = len - 1; i >= n; i--) {
			bites[i] = bites[i - n];
		}
		for (int i = 0; i < n; i++) {
			bites[i] = false; // Заполняем освободившиеся позиции нулями
		}
		return *this;
	}
	BitArray operator>>(int n) const {
		for (int i = 0; i < len - n; i++) {
			bites[i] = bites[i + n];
		}
		for (int i = len - n; i < len; i++) {
			bites[i] = false; // Заполняем освободившиеся позиции нулями
		}
		return *this;
	}

	//Устанавливает бит с индексом n в значение val.
	//BitArray& set(int n, bool val = true) {
	//	//int move = n % 32;
	//	//int idx = n / 32;
	//	if (val == 0 && (bites[idx] >> move & 1))
	//		bites[idx] -= (1 << move);
	//	else
	//		bites[idx] |= (val << move);
	//}
	//Заполняет массив истиной.
	BitArray& set() {
		for (unsigned int i = 0; i < len; i++) {
			bites[i] = 1;
		}
		return *this;
	}

	//Устанавливает бит с индексом n в значение false.
	BitArray& reset(int n) {
		bites[n] = false;
		return *this;
	}
	//Заполняет массив ложью.
	BitArray& reset() {
		for (int i = 0; i < len; i++)
			bites[i] = false;
		return *this;
	}

	//true, если массив содержит истинный бит.
	bool any() const {
		for (int i = 0; i < len; i++) {
			if (bites[i] == 0) {
				continue;
			}
			else {
				if (bites[i] == 1) {
					return true;
				}
			}
		}
		return false;
	}
	//true, если все биты массива ложны.
	bool none() const {
		return (!this->any());
	}
	//Битовая инверсия
	BitArray operator~() const {
		for (int i = 0; i < len; i++) {
			if (bites[i] == true)
				bites[i] = false;
			else
				bites[i] = true;
			//bites[i] = ~bites[i];
		}
		return *this;
	}
	//Подсчитывает количество единичных бит.
	int count() const {
		int count = 0;
		for (int i = 0; i < size(); i++)
			if (bites[i] == 1)
				count++;
		return count;
	}

	//Возвращает значение бита по индексу i.
	bool operator[](int i) const {
		return bites[i];
	}

	int size() const {
		//return sizeof(bites);
		return len;
	}
	bool empty() const {
		if (sizeof(bites == 0)) {
			return true;
		}
		else {
			return false;
		}
	}

	//Возвращает строковое представление массива.
	std::string to_string() const {
		std::string str = "";
		for (unsigned int i = 0; i < len; i++) {
			if (bites[i] == true)
				str += '1';
			if (bites[i] == false)
				str += '0';
		}
		return str;
	}
//private:
	bool* bites;
	int len;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
	BitArray bites0(8, 8), bites1(8, 4);

	for (int i = 0; i < bites1.len; i++)
		cout << bites1[i];
	cout << endl;
	
	~bites1;

	for (int i = 0; i < bites1.len; i++)
		cout << bites1[i];
	cout << endl;
	//cout << bites1.count() << endl;
	bites1.clea r();
	for (int i = 0; i < bites1.len; i++)
		cout << bites1[i];
	cout << endl;
	//cout << bites0.to_string();

	//cout << bites0.bites[0] << endl;
	//cout << bites1.bites[0] << endl;
	//bites0.swap(bites1);
	//cout << bites0.bites[0] << endl;
	//cout << bites1.bites[0] << endl;
	//bites1.resize(16);
	//cout << bites1[15] << endl;
	//cout << bites1.to_string() << endl;
	//cout << bites0[0] << bites0[1] << bites0[2] << endl;
	//bites1.reset(1);
	//cout << bites1[0] << bites1[1] << bites1[2] << endl;
	////bites1.reset();
	//cout << bites1[0] << bites1[1] << bites1[2] << endl;
	//bites0 = bites1;
	//cout << bites0[0] << bites0[1] << bites0[2] << endl;

	return 0;
}
