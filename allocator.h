#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>

#include "dl_list.h"

#ifndef ALLOCATORLT_ALLOCATOR_H
#define ALLOCATORLT_ALLOCATOR_H

#ifndef container_of
#define container_of(ptr, type, member)	({			\
	const __typeof__( ((type *)0)->member ) __mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type, member) );})
#endif //container_of

using namespace std;

/*!
 *  \brief Структура, хранящая указатель на выделенную память
 *
 *  Экземпляр данной структуры возвращается командой alloc для доступа к выделенной памяти
 *
 */
class CleverPtr {
    void* data; ///< Хранит указатель типа void на выделенную память

public:
    void* get() const; ///< Возвращает указатель на выделенную память
    explicit CleverPtr(void* data): data(data){}
};

/*!
 *  \brief Основной класс аллокатора
 *
 *  Данный класс содержит методы для выделения и очищения памяти
 *
 */
class Allocator {
    private:
        char* memory;

public:
        /*!
            Конструктор по умолчанию, создает резерв памяти размером 100 байт
        */
        Allocator();

        /*!
            Конструктор, с одним параметром
            \param[in] size Размер резерва памяти из которого будет выделяться память
        */
        Allocator(int size);

        /*!
            Метод записывает в массив блоки памяти в зависимости от переданного состояния и возвращает их количество
            \param[in] blocks Вектор пар, в каждой из которых хранится сдвиг от начала памяти и размер блока
            \param[in] state состояние блоков по которому фильтруются блоки во время поиска (FREE/OCCUPIED)
        */
        int show_blocks(vector<pair<int, int>> *blocks, STATES state);

        /*!
            Метод, выделяющий память необходимого рамера
            \param[in] size Размер выделяемой памяти
            \param[out] Объект CleverPtr, в котором хранится указатель на выделенную память
        */
        CleverPtr alloc(int size);

        /*!
            Метод, очищающий занятый блок памяти
            \param[in] ссылка на объект CleverPtr, в котором хранится память,
            которую необходимо очистить
        */
        void free(CleverPtr&);

        /*!
            Метод, объединяющий свободные соседние блоки памяти,
            для получения одного блока большего размера
        */
        void defrag();
};


#endif //ALLOCATORLT_ALLOCATOR_H
