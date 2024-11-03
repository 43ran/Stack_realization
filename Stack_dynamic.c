#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_DELTA 10 // На сколько изменяется стек

typedef int Data;

typedef struct
{
    int n;    // Номер первой пустой ячейки массива
    int size; // Размер стека
    Data *a;  // Сам стек
} Stack;

Stack *stack_create(int size);
void stack_push(Stack *s, Data x);
Data stack_pop(Stack *s);
Data stack_get(Stack *s);
void stack_print(Stack *s);
int stack_size(Stack *s);
int stack_is_empty(Stack *s);
void stack_clear(Stack *s);
Stack *stack_destroy(Stack *s);
Stack *stack_create(int size);

// Инициализация стека и выделение первоначальной памяти (size)
Stack *stack_create(int size)
{
    Stack *sp = malloc(sizeof(Stack));
    sp->n = 0;
    sp->size = size;
    sp->a = malloc(sp->size * sizeof(Data));
    return sp;
}

// Push функция
void stack_push(Stack *s, Data x)
{
    int size = stack_size(s);
    // Если стек полон, то выделим еще MEMORY_DELTA ячеек
    if (size == s->size)
    {
        s->a = realloc(s->a, (s->size + MEMORY_DELTA) * sizeof(Data));
        s->size += MEMORY_DELTA;
    }
    s->a[s->n] = x;
    s->n += 1; // Добавили элемент -> увеличили указатель на пустой элемент.
}
// Pop функция
Data stack_pop(Stack *s)
{
    if (stack_is_empty(s)) // Если стек пуст и происходит pop - вернуть 0;
        return 0;
    Data res = s->a[s->n - 1];
    s->n -= 1;
    // Если в стеке больше MEMORY_DELTA "Простаивающих" ячеек, то уменьшить размер стека на MEMORY_DELTA;
    if (s->size - s->n > MEMORY_DELTA)
    {
        s->a = realloc(s->a, (s->size - MEMORY_DELTA) * sizeof(Data));
        s->size -= MEMORY_DELTA;
    }
    return res;
}
// get функция - получить значенеи с верхушки стека, при этом не изменяя стек
Data stack_get(Stack *s)
{
    if (stack_is_empty(s) == 1)
        return 0;
    return s->a[s->n - 1];
}
// Проверка, пуст ли стек
int stack_is_empty(Stack *s)
{
    return (s->n == 0) ? 1 : 0;
}
// Печать содержимого стека
void stack_print(Stack *s)
{
    for (int i = 0; i < s->n; i++)
        printf("%d ", s->a[i]);
    printf("\n");
}
// Определение текущего размера стека
int stack_size(Stack *s)
{
    return s->n;
}
// Очистка стека с сохранением самого стека и выделенной под него памяти
void stack_clear(Stack *s)
{
    s->a = realloc(s->a, MEMORY_DELTA);
    s->n = 0;
    s->size = 10;
}
// Удаление стека и очистка памяти
Stack *stack_destroy(Stack *s)
{
    free(s->a);
    free(s);
    return NULL;
}
int main()
{
    char *sk_open = "([{<";
    char *sk_close = ")]}>";
    char sk;
    int flag = 0;
    Stack *hub = stack_create(10);
    // Посимвольно считываем символы, пока не наткнемся на \n
    while ((sk = getchar()) != '\n')
    {
        if (strchr(sk_open, sk) != NULL) // Если скобка открывающая - добавляем в стек
            stack_push(hub, sk);
        else
        {
            if (strchr(sk_close, sk) - sk_close != strchr(sk_open, stack_pop(hub)) - sk_open) // Если скобка закрывающая, то сравниваем, соответствует ли закрывающая скобка открывающей
            {
                flag = 1;
                break;
            }
        }
    }
    if (flag == 0 && stack_is_empty(hub) == 1)
        printf("YES");
    else
        printf("NO");
    stack_destroy(hub);
    return 0;
}