#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

typedef double StackElem_t;

#ifdef STACK_DEBUG
#define ON_DBG(...) __VA_ARGS__
#else
#define ON_DBG(...) 
#endif

#define CHICKEN01 NAN
#define CHICKEN02 NAN
#define CHICKEN11 11111111
#define CHICKEN22 22222222
#define STACK_MIN_CAPACITY 16
#define STACK_MAX_CAPACITY 1000
#define QUARTER_CAPACITY(stk) ((stk) -> capacity / 4)
#define RESIZE_COEFF 2
#define POIZON_STK_PTR ((StackElem_t *)1638)
#define POIZON_DBL NAN 

struct Stack_t
{
    unsigned long long chicken11;
    StackElem_t *data;
    StackElem_t *info;
    size_t size;
    size_t capacity;
    ON_DBG (const char *stack_name;
        const char *file_name;
        const char *func_name;
        int line;)
    unsigned long long chicken22;
};
        
enum StackErr_t {   
    STACK_OK,                   // ошибок нет
    STACK_BAD_PTR,              // стек не создан (calloc вернул NULL)
    EMPTY_STACK_BAD_SIZE,       // размеры size и capacity не 0 у пустого стека
    STACK_BAD_SIZE,             // size > capacity
    STACK_UNDERFLOW,            // стек пуст, невозможно выполнить pop()
    STACK_OVERFLOW              // стек переполнен, невозможно выполнить push()
};

// TODO возвращать все ошибки одним числом, коды ошибок это степени двойки
// сделать функцию которая обращает i-й бит числа в единицу
// чтобы вернуть накопленный код ошибки можно просто переводить полученное двоичное число в десятичное

StackErr_t StackInit(Stack_t *stk, size_t capacity
                ON_DBG(, const char *stack_name, const char *file_name, const char *func_name, int line));
StackErr_t StackIsEmpty(Stack_t *stk);                
StackErr_t StackVerify(Stack_t *stk);
void StackDump(Stack_t *stk);
void PrintShrtErrMsg(StackErr_t err);
StackErr_t StackPush(Stack_t *stk, StackElem_t value);
StackErr_t StackPop(Stack_t *stk, StackElem_t *ptr);
StackErr_t StackDestroy(Stack_t *stk);
StackErr_t ResizeUp(Stack_t *stk);
StackErr_t ResizeDown(Stack_t *stk);


#define STACK_INIT(stk, capacity) (StackInit(&(stk), (capacity) \
                                    ON_DBG(, #stk,              \
                                            __FILE__,           \
                                            __func__,       \
                                            __LINE__))) 


#ifdef STACK_DEBUG
#define ERROR_MSG(stk, err)     \
do                              \
{                               \
    if (err)                    \
    {                           \
        PrintShrtErrMsg(err);   \
        StackDump(stk);         \
    }                           \
} while (0) 

#else
#define ERROR_MSG(stk, err)     \
do                              \
{                               \
    if (err)                    \
        PrintShrtErrMsg(err);   \
} while (0)
#endif


//#define ASSERT_OK(stk) (assert(!StackVerify((stk))))

#endif