#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <cstdint>

typedef double StackElem_t;
typedef uint64_t Canary_t;

#ifdef STACK_DEBUG
#define ON_DBG(...) __VA_ARGS__
#else
#define ON_DBG(...)
#endif

#define CHICKEN_LOWER 0xDEADDEADDEADDEAD
#define CHICKEN_UPPER 0x00D01BAEBD01BAEB
#define CHICKEN_LEFT 0xDEADDEADDEADDEAD
#define CHICKEN_RIGHT 0xFACEFEEDFACEFEED
#define STACK_MIN_CAPACITY 16
#define STACK_MAX_CAPACITY 1000
#define QUARTER_CAPACITY(stk) ((stk) -> capacity / 4)
#define RESIZE_COEFF 2
#define POIZON_DATA_PTR ((StackElem_t *)1638)
#define POIZON_BUF_PTR ((Canary_t *)666)
#define POIZON_DBL NAN

//struct Stack_t
//{
//    unsigned long long chicken_left;
//    StackElem_t *buf;
//    StackElem_t *data;
//    size_t size;
//    size_t capacity;
//    ON_DBG (const char *stack_name;
//        const char *file_name;
//        const char *func_name;
//        int line;)
//    unsigned long long chicken_right;
//};

struct Stack_t{
    unsigned long long chicken_left;
    Canary_t *buf;
    StackElem_t *data;
    size_t size;
    size_t capacity;
    ON_DBG (const char *stack_name;
        const char *file_name;
        const char *func_name;
        int line;)
    unsigned long long chicken_right;
};

enum StackErr_t {
    STACK_OK,                           // ошибок нет
    STACK_BAD_PTR,                      // стек не создан (calloc вернул NULL)
    EMPTY_STACK_BAD_SIZE,               // размеры size и capacity не 0 у пустого стека
    STACK_BAD_SIZE,                     // size > capacity
    STACK_STRUCT_LEFT_CHICKEN_ATTACKED, // атакована курица слева от структуры стека
    STACK_STRUCT_RIGHT_CHICKEN_ATTACKED,// атакована курица справа от структуры стека
    STACK_DATA_LOWER_CHICKEN_ATTACKED,  // атакована курица внизу стека
    STACK_DATA_UPPER_CHICKEN_ATTACKED,  // атакована курица наверху стека
    STACK_UNDERFLOW,                    // стек пуст, невозможно выполнить pop()
    STACK_OVERFLOW                      // стек переполнен, невозможно выполнить push()
};

// TODO возвращать все ошибки одним числом, коды ошибок это степени двойки
// сделать функцию которая обращает i-й бит числа в единицу
// чтобы вернуть накопленный код ошибки можно просто переводить полученное двоичное число в десятичное

StackErr_t StackCTor(Stack_t *stk, size_t capacity
                ON_DBG(, const char *stack_name, const char *file_name, const char *func_name, int line));
StackErr_t StackChickenCheck(Stack_t *stk);
StackErr_t StackIsEmpty(Stack_t *stk);
StackErr_t StackVerify(Stack_t *stk);
void StackDump(Stack_t *stk);
void PrintShrtErrMsg(StackErr_t err);
StackErr_t StackPush(Stack_t *stk, StackElem_t value);
StackErr_t StackPop(Stack_t *stk, StackElem_t *ptr);
StackErr_t StackDTor(Stack_t *stk);
StackErr_t ResizeUp(Stack_t *stk);
StackErr_t ResizeDown(Stack_t *stk);
StackErr_t StackStructChickenCheck(Stack_t *stk);
StackErr_t StackDataChickenCheck(Stack_t *stk);
//int DblCmp(StackElem_t a, StackElem_t b);


#define STACK_CTOR(stk, capacity) (StackCTor(&(stk), (capacity) \
                                    ON_DBG(, #stk,              \
                                            __FILE__,           \
                                            __func__,           \
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

#endif#include "Stack.h"

//StackErr_t StackCTor(Stack_t *stk, size_t capacity
//                ON_DBG(, const char *stack_name, const char *file_name, const char *func_name, int line))
//{
//    printf("Initiating Stack\n");
//
//    StackErr_t err = StackIsEmpty(stk);
//    stk -> buf = (StackElem_t *) calloc(capacity + 2, sizeof(StackElem_t));
//    stk -> data = stk -> buf + 1;
//
//    *(stk -> buf) = CHICKEN_LOWER;
//    *(stk -> buf + capacity + 1) = CHICKEN_UPPER;
//
//    stk -> capacity = capacity;
//
//    stk -> chicken_left = CHICKEN_LEFT;
//    stk -> chicken_right = CHICKEN_RIGHT;
//
//    err = StackVerify(stk);
//
//    ON_DBG (stk -> stack_name = stack_name;
//            stk -> file_name = file_name;
//            stk -> func_name = func_name;
//            stk -> line = line;)
//
//    for (size_t i = 0; i < (stk -> capacity); i++)
//    {
//        (stk -> data)[i] = POIZON_DBL;
//    }
//    StackDump(stk);
//    return err;
//}
//
//StackErr_t StackDTor(Stack_t *stk)
//{
//    StackErr_t err = StackVerify(stk);
//
//    if (err)
//        return err;
//
//    printf("Destroying Stack\n");
//    StackDump(stk);
//
//    for (size_t i = 0; i < stk -> capacity + 2; i++)
//    {
//        (stk -> buf)[i] = POIZON_DBL;
//    }
//
//    free(stk -> buf);
//    stk -> buf = POIZON_STK_PTR;
//    stk -> data = POIZON_STK_PTR;
//
//    return STACK_OK;
//}
//




//StackErr_t StackInitNew(Stack_t *stk, size_t capacity
//                ON_DBG(, const char *stack_name, const char *file_name, const char *func_name, int line))
//{
//    StackErr_t err = StackIsEmpty(stk);
//
//    uint8_t *temp_ptr = (uint8_t *)calloc(capacity * sizeof(StackElem_t) + 2 * sizeof(Canary_t));
//    if (temp_ptr)
//        stk -> buf = temp_ptr;
//}#include "Stack.h"

//int DblCmp(StackElem_t a, StackElem_t b)
//{
//    const double EPSILON = 1e-14;
//
//    if (fabs(a - b) < EPSILON)
//        return 0;
//    else if (a > b)
//        return 1;
//    else
//        return -1;
//}

StackErr_t StackStructChickenCheck(Stack_t *stk)
{
    if (stk -> chicken_left != CHICKEN_LEFT)
        return STACK_STRUCT_LEFT_CHICKEN_ATTACKED;
    else if (stk -> chicken_right != CHICKEN_RIGHT)
        return STACK_STRUCT_RIGHT_CHICKEN_ATTACKED;
    else
        return STACK_OK;
}

//StackErr_t StackDataChickenCheck(Stack_t *stk)
//{
//    size_t capacity = stk -> capacity;
//
//    if (DblCmp(*(stk -> buf), CHICKEN_LOWER) != 0 || isnan(*(stk -> buf)))
//        return STACK_DATA_LOWER_CHICKEN_ATTACKED;
//    else if (DblCmp(*(stk -> buf + capacity + 1), CHICKEN_UPPER) != 0 || isnan(*(stk -> buf + capacity + 1)))
//        return STACK_DATA_UPPER_CHICKEN_ATTACKED;
//    else
//        return STACK_OK;
//}

StackErr_t StackDataChickenCheck(Stack_t *stk)
{
    size_t capacity = stk -> capacity;
    Canary_t *buf = stk -> buf;

    if (buf[0] != CHICKEN_LOWER)
        return STACK_DATA_LOWER_CHICKEN_ATTACKED;
    else if (buf[capacity + 1] != CHICKEN_UPPER)
        return STACK_DATA_UPPER_CHICKEN_ATTACKED;
    else
        return STACK_OK;
}

StackErr_t StackIsEmpty(Stack_t *stk)
{
    if (!stk)
        return STACK_BAD_PTR;

    StackErr_t err = StackStructChickenCheck(stk);
    if (err)
        return err;

    size_t size = stk -> size;
    size_t capacity = stk -> capacity;

    if (size != 0 && capacity != 0)
        return EMPTY_STACK_BAD_SIZE;
    else
        return STACK_OK;
}

StackErr_t StackVerify(Stack_t *stk)
{
    if ((!stk) || !(stk -> buf))
        return STACK_BAD_PTR;

    StackErr_t err = StackStructChickenCheck(stk);
    if (err)
        return err;

    err = StackDataChickenCheck(stk);
    if (err)
        return err;

    size_t size = stk -> size;
    size_t capacity = stk -> capacity;

    if (size > capacity)
        return STACK_BAD_SIZE;

    return STACK_OK;
}

void StackDump(Stack_t *stk)
{
    #ifdef STACK_DEBUG

    const char *name = stk -> stack_name;
    Canary_t *buf = stk -> buf;
    StackElem_t *data = stk -> data;
    const char *func = stk -> func_name;
    const char *file = stk -> file_name;
    int line = stk -> line;
    size_t capacity = stk -> capacity;
    size_t size = stk -> size;
    unsigned long long chicken_left = stk -> chicken_left;
    unsigned long long chicken_right = stk -> chicken_right;

    printf("STACK_DUMP\n");
    printf("****************************************\n");
    printf("Stack_t <%s> [%p], %s at %s: %d\n", name, stk, func, file, line);
    printf("{\n");
    printf("chicken_left = %llu\n", chicken_left);
    printf("chicken_left = %llu\n", chicken_right);
    printf("capacity     = %lu\n", capacity);
    printf("size         = %lu\n", size);
    printf("buf[%p]\n", buf);
    if (buf)
    {
        printf("    {\n");
        printf("    [ChickenLower] = %lu\n", (Canary_t)buf[0]);
        for (size_t i = 0; i < size; i++)
            printf("    *[%lu] = %lg\n", i, data[i]);
        for (size_t j = size; j < capacity; j++)
            printf("     [%lu] = %lg (POIZON)\n", j, data[j]);
        printf("    [ChickenUpper] = %lu\n", (Canary_t)buf[capacity + 1]);
        printf("    }\n");
    }
    printf("}\n");
    printf("****************************************\n\n");

    #endif
}

void PrintShrtErrMsg(StackErr_t err)
{
    switch(err)
    {
        case STACK_OK:
            break;

        case STACK_BAD_PTR:
            printf("Error: failed to allocate memory for stack\n");
            break;

        case EMPTY_STACK_BAD_SIZE:
            printf("Error: (invalid Stack) empty Stack has capacity and size unequal to 0\n");
            break;

        case STACK_BAD_SIZE:
            printf("Error: size > capacity\n");
            break;

        case STACK_STRUCT_LEFT_CHICKEN_ATTACKED:
            printf("Danger: Stack Struct left chicken got attacked\n");
            break;

        case STACK_STRUCT_RIGHT_CHICKEN_ATTACKED:
            printf("Danger: Stack Struct left chicken got attacked\n");
            break;

        case STACK_DATA_LOWER_CHICKEN_ATTACKED:
            printf("Danger: Stack Data lower chicken got attacked\n");
            break;

        case STACK_DATA_UPPER_CHICKEN_ATTACKED:
            printf("Danger: Stack Data upper chicken got attacked\n");
            break;

        case STACK_UNDERFLOW:
            printf("Stack UnderFlow: cannot do pop() from an empty Stack\n");
            break;

        case STACK_OVERFLOW:
            printf("Stack OverFlow: cannot push() to an overflowing Stack\n");
            break;

        default:
            ;
    }
}
#include "Stack.h"

StackErr_t StackPush(Stack_t *stk, StackElem_t value)
{
    StackErr_t err = StackVerify(stk);
    err = STACK_OK;

    if ((stk -> size) == (stk -> capacity))
        err = ResizeUp(stk);

    if (err)
        return err;

    stk -> data[stk -> size++] = value;

    err = StackVerify(stk);
    return err;
}

StackErr_t StackPop(Stack_t *stk, StackElem_t *ptr)
{
    StackErr_t err = StackVerify(stk);

    if ((stk -> size) == 0)
        return STACK_UNDERFLOW;

    if ((stk -> size) <= (QUARTER_CAPACITY(stk)) && (stk -> size) > STACK_MIN_CAPACITY)
        err = ResizeDown(stk);

    if (err)
        return err;

    *ptr = (stk -> data[--(stk -> size)]);
    stk -> data[(stk -> size)] = POIZON_DBL;

    err = StackVerify(stk);
    return err;
}//#include "Stack.h"

//StackErr_t ResizeUp(Stack_t *stk)
//{
//    StackErr_t err = StackVerify(stk);
//
//    StackElem_t *temp = (StackElem_t *)realloc(stk -> buf, (stk -> capacity + 2) * sizeof(StackElem_t) * RESIZE_COEFF);
//    if (temp)
//    {
//        stk -> buf = temp;
//        stk -> data = temp + 1;
//    }
//
//    err = StackVerify(stk);
//    if (err)
//        return err;
//
//    if (stk -> capacity * RESIZE_COEFF > STACK_MAX_CAPACITY)
//        return STACK_OVERFLOW;
//
//    stk -> capacity *= RESIZE_COEFF;
//
//    for (size_t i = stk -> size; i < stk -> capacity; i++)
//    {
//        (stk -> data)[i] = POIZON_DBL;
//    }
//    (stk -> buf)[stk -> capacity + 1] = CHICKEN_UPPER;
//
//    err = StackVerify(stk);
//    return err;
//}
//
//StackErr_t ResizeDown(Stack_t *stk)
//{
//    StackErr_t err = StackVerify(stk);
//
//    StackElem_t *temp = (StackElem_t *)realloc(stk -> buf, (stk -> capacity + 2) * sizeof(StackElem_t) / RESIZE_COEFF);
//    if (temp)
//    {
//        stk -> buf = temp;
//        stk -> data = temp + 1;
//    }
//
//    err = StackVerify(stk);
//    if (err)
//        return err;
//
//    stk -> capacity /= RESIZE_COEFF;
//    *(stk -> data + stk -> capacity + 1) = CHICKEN_UPPER;
//
//    err = StackVerify(stk);
//    return err;
//}#include "Stack.h"

StackErr_t StackCTor(Stack_t *stk, size_t capacity
                ON_DBG(, const char *stack_name, const char *file_name, const char *func_name, int line))
{
    StackErr_t err = StackIsEmpty(stk);

    uint8_t *temp_ptr = (uint8_t *)calloc(capacity * sizeof(StackElem_t) + 2 * sizeof(Canary_t), 1);
    if (temp_ptr)
        stk -> buf = (Canary_t *)temp_ptr;
    *(stk -> buf) = CHICKEN_LOWER;
    stk -> data = (StackElem_t *)(temp_ptr + sizeof(Canary_t));
    *(stk -> buf + capacity + 1) = CHICKEN_UPPER;

    stk -> capacity = capacity;

    stk -> chicken_left = CHICKEN_LEFT;
    stk -> chicken_right = CHICKEN_RIGHT;

    err = StackVerify(stk);

    ON_DBG (stk -> stack_name = stack_name;
            stk -> file_name = file_name;
            stk -> func_name = func_name;
            stk -> line = line;)

    for (size_t i = 0; i < (stk -> capacity); i++)
    {
        (stk -> data)[i] = POIZON_DBL;
    }
    StackDump(stk);
    return err;
}

StackErr_t ResizeUp(Stack_t *stk)
{
    StackErr_t err = StackVerify(stk);

    uint8_t *temp = (uint8_t *)realloc(stk -> buf, ((stk -> capacity) * sizeof(StackElem_t) + 2 * sizeof(Canary_t))* RESIZE_COEFF);
    if (temp)
    {
        stk -> buf = (Canary_t *)temp;
        stk -> data = (StackElem_t *)(temp + sizeof(Canary_t));
    }

    err = StackVerify(stk);
    if (err)
        return err;

    if (stk -> capacity * RESIZE_COEFF > STACK_MAX_CAPACITY)
        return STACK_OVERFLOW;

    stk -> capacity *= RESIZE_COEFF;

    for (size_t i = stk -> size; i < stk -> capacity; i++)
    {
        (stk -> data)[i] = POIZON_DBL;
    }
    (stk -> buf)[stk -> capacity + 1] = CHICKEN_UPPER;

    err = StackVerify(stk);
    return err;
}

StackErr_t ResizeDown(Stack_t *stk)
{
    StackErr_t err = StackVerify(stk);

    uint8_t *temp = (uint8_t *)realloc(stk -> buf, ((stk -> capacity) * sizeof(StackElem_t) + 2 * sizeof(Canary_t )) / RESIZE_COEFF);
    if (temp)
    {
        stk -> buf = (Canary_t *)temp;
        stk -> data = (StackElem_t *)temp + 1;
    }

    err = StackVerify(stk);
    if (err)
        return err;

    stk -> capacity /= RESIZE_COEFF;
    (stk -> buf)[stk -> capacity + 1] = CHICKEN_UPPER;

    err = StackVerify(stk);
    return err;
}

StackErr_t StackDTor(Stack_t *stk)
{
    StackErr_t err = StackVerify(stk);

    if (err)
        return err;

    printf("Destroying Stack\n");
    StackDump(stk);

    for (size_t i = 0; i < stk -> capacity; i++)
    {
        stk -> data[i] = POIZON_DBL;
    }

    free(stk -> buf);
    stk -> buf = POIZON_BUF_PTR;
    stk -> data = POIZON_DATA_PTR;

    return STACK_OK;
}#include "Stack.h"

int main(void)
{
    Stack_t stk1 = {};
    size_t capacity = 2;

    StackErr_t err = STACK_CTOR(stk1, capacity);
    ERROR_MSG(&stk1, err);

    err = StackPush(&stk1, 30);
    printf("Push 30\n");
    ERROR_MSG(&stk1, err);

    err = StackPush(&stk1, 40);
    printf("Push 40\n");
    ERROR_MSG(&stk1, err);

    err = StackPush(&stk1, 50);
    printf("Push 50\n");
    ERROR_MSG(&stk1, err);

    StackElem_t x = 0;
    err = StackPop(&stk1, &x);
    printf("Pop %lg\n", x);
    ERROR_MSG(&stk1, err);

    StackElem_t y = 0;
    err = StackPop(&stk1, &y);
    printf("Pop %lg\n", y);
    ERROR_MSG(&stk1, err);

    StackElem_t z = 0;
    err = StackPop(&stk1, &z);
    printf("Pop %lg\n", z);
    ERROR_MSG(&stk1, err);

    StackElem_t X = 0;
    err = StackPop(&stk1, &X);
    printf("Pop %lg\n", X);
    ERROR_MSG(&stk1, err);

    err = StackDTor(&stk1);

    return 0;
}