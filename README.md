# ALLOCATOR

Аллокатор памяти, позволяющий выделять память заданного размера по принципу first-fit, управлять выделенной памятью и производить простейшую оптимизацию. 

## Начало работы

### Требования

С++11

### Использование

#### Подключить заголовочный файл:
```
#include "allocator.h"
```
#### Создать экземпляр класса Allocator:
```
Allocator allocator = Allocator(size);
```
где size — целочисленная переменная, определеяющая общий размер памяти, с которой будет работать аллокатор. 

#### Можно также использовать конструктор по умолчанию:
```
Allocator allocator = Allocator();
```
В этом случае будет выделено 100 байтов.

Для выделения заданного объема памяти из общего количества необходимо вызвать метод класса Allocator:
```
CleverPtr alloc(size_t size);
```
Данный метод вернет объект CleverPtr со ссылкой на выделенную память. 

Для удаления объекта из памяти необходимо использовать метод класса Allocator:

```
void free(CleverPtr&);
```
В качестве аргумента нужно передать ссылку на удаляемый объект CleverPtr


Для того, чтобы решить проблему фрагментации памяти, используется метод:
```
void defrag();
```

## Запуск тестов

Для запуска тестов достаточно:

#### Подключить файл

``` 
#include "tests.h" 
```
#### Создать экземпляр класса Test

```
Tests tests = Tests();
```
#### Вызвать метод run:

```
tests.run();
```

## Авторы
### Рахматова Валерия
### Шарапов Тимур
#### Особая благодарность Эльфу-торговцу
##### С наступающим 2020 годом! 