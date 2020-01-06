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
 *  \brief Структура, которая хранит указатель на выделенную память
 *
 *  Экземпляр данной структуры возвращается командой alloc для доступа к выделенной памяти
 *
 */
class CleverPtr {
    void* data; ///< Хранит указатель типа void на выделенную память
	//Allocator *owner;
	//int counter = 0;
public:
    void* get() const; ///< Возвращает указатель на выделенную память
	explicit CleverPtr(void* data) : data(data) {}
    //explicit CleverPtr(void* data, int c): data(data), owner(getGlobalAllocator()) {}
	//~CleverPtr() { if (counter == 0) owner->free(*this); }
};

/*!
 *  \brief Основной класс аллокатора
 *
 *  Данный класс содержит методы выделения и очищения памяти
 *
 */
class Allocator {
    private:
        void* memory;
        void* list_memory;
        dl_list *head;

        void* list_memory_flag;

        int MEMORY_DELIMITER = 2;
        void* list_alloc();
public:
        /*!
            Конструктор по умолчанию, создающий резерв памяти в размере 100 байтов
        */
        Allocator();
		~Allocator();

        /*!
            Конструктор с одним параметром
            \param[in] size Размер резервной памяти для выделения
        */
        Allocator(int size);

        /*!
            Метод записывает в массив блоки памяти в зависимости от переданного состояния и возвращает их количество
            \param[out] blocks Вектор чисел, каждое из которых - размер блока
            \param[in] state состояние блоков по которому фильтруются блоки во время поиска (FREE/OCCUPIED)
            \return количество найденных блоков
        */
		int show_blocks(vector<pair<void*, int>>* blocks, STATES state);

        /*!
            Метод, выделяющий память необходимого размера
            \param[in] size Размер выделяемой памяти
            \return Объект CleverPtr, хранящий указатель на выделенную память
        */
        CleverPtr alloc(int size);

        /*!
            Метод, очищающий занятый блок памяти
            \param[in] ссылка на объект CleverPtr, в котором хранится память,
            которую необходимо очистить
        */
        void free(CleverPtr&);

        /*!
            Метод для дефрагментации основного блока памяти
        */
        void defrag();
};


#endif //ALLOCATORLT_ALLOCATOR_H
