#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>

#define CHARS_END '\0'

#define chars_joined(delimiter, chars1, ...) \
    chars_joined_va(delimiter, chars1, __VA_ARGS__, NULL)

void*
memory_alloc(unsigned long long nbytes)
{
    void* memory = malloc(nbytes);
    if (memory == NULL) perror("out of memory");
    return memory;
}

void
memory_dealloc(void* memory)
{
    free(memory);
}

void*
memory_realloc(void* memory, unsigned long long new_nbytes)
{
    void* new_memory = realloc(memory, new_nbytes);
    if (memory == NULL) perror("out of memory");
    return memory;
}

void*
memory_copy(void* dest, const void* source, unsigned long long nbytes)
{
    // unsigned char *dst = ((unsigned char*) dest);
    // const unsigned char *src = ((const unsigned char*) source);
    // for (int i = 0; i < nbytes; i++) {
    //     *dst = *src;
    //     dst++;
    //     src++;
    // }
    // return dest;
    return memcpy(dest, source, nbytes);
}

void*
memory_write(void* dest, int data, unsigned long long nbytes)
{
    // unsigned char *dst = ((unsigned char*) dest);
    // for (int i = 0; i < nbytes; i++) {
    //     *dst = ((unsigned char) data);
    //     dst++;
    // }
    // return dest;
    return memset(dest, data, nbytes);
}

char*
chars_alloc(unsigned long long length)
{
    char* chars = memory_alloc(length + sizeof(CHARS_END));
    chars[length] = CHARS_END;
    return chars;
}

unsigned long long
chars_length(const char* chars)
{
    // if (*chars == CHARS_END) return 0;
    // const char* chr = chars;
    // while (*chr) {
    //     if (*chr == CHARS_END) {
    //         break;
    //     }
    //     chr++;
    // }
    // return chr - chars;
    return strlen(chars);
}

void
chars_destroy(const char *chars)
{
    memory_dealloc((void*)chars);
}

long long
chars_compare(const char* chars1, const char* chars2)
{
    // while (*chars1 && *chars2 && *chars1 == *chars2) {
    //     chars1++;
    //     chars2++;
    // }
    // return *chars1 - *chars2;
    return strcmp(chars1, chars2);
}

bool
chars_equals(const char* chars1, const char* chars2)
{
    return chars_compare(chars1, chars2) == 0L;
}

char*
chars_copy(char* dest, const char* src, unsigned long long length)
{
    return memory_copy(dest, (void*)src, length);
}

bool
chars_is_empty(const char* chars)
{
    // return *chars == CHARS_END || chars_length(chars) == 0;
    return strlen(chars) == 0;
}

// char*
// chars_sub(const char* chars, const unsigned long long start, const unsigned long long end)
// {
//     unsigned long long length = end - start;
//     char* sub = chars_alloc(length);
//     chars_copy(sub, chars + start, length);
//     return sub;
// }

char*
chars_cloned(const char* chars)
{
    // return chars_sub(chars, 0, chars_length(chars));
    return strdup(chars);
}

char*
chars_concat_streching(char *streched, const char* chars)
{
    unsigned long long chars_len = chars_length(chars);
    char *new_chars;
    if (chars_len > 0) {
        unsigned long long streched_len = chars_length(streched);
        unsigned long long length = streched_len + chars_len;
        // streched = memory_realloc(streched, length + sizeof(CHARS_END));
        // chars_copy(streched + streched_len, chars, chars_len);
        // streched[length] = CHARS_END;
        new_chars = chars_alloc(length);
        chars_copy(new_chars, streched, streched_len);
        chars_copy(new_chars + streched_len, chars, chars_len);
        chars_destroy(streched);
    } else {
        new_chars = streched;
    }
    // return streched;
    return new_chars;
}

char*
chars_joined_va(const char* delimiter, const char* chars, ...)
{
    char* joined;
    va_list args;
    va_start(args, chars);
    joined = chars_cloned(chars);
    chars = va_arg(args, const char*);
    while (chars != NULL) {
        if (!chars_is_empty(chars)) {
            joined = chars_concat_streching(joined, delimiter);
            joined = chars_concat_streching(joined, chars);
        }
        chars = va_arg(args, const char*);
    }
    va_end(args);
    return joined;
}

void
test1()
{
    for (int idx = 1; idx < 1000; idx = idx + 100) {
        int length = idx * BUFSIZ / 2;
        char* chars = chars_alloc(length);
        memory_write(chars, 'x', length);
        assert(chars_length(chars) == length);
        chars_destroy(chars);
    }
}

void
test2()
{
    char *joined;

    joined = chars_joined("", "", "");
    assert(chars_equals(joined, ""));
    chars_destroy(joined);

    joined = chars_joined(",", "a", "");
    assert(chars_equals(joined, "a"));
    chars_destroy(joined);

    joined = chars_joined(",", "a", "b");
    assert(chars_equals(joined, "a,b"));
    chars_destroy(joined);

    joined = chars_joined("", "a", "b");
    assert(chars_equals(joined, "ab"));
    chars_destroy(joined);

    joined = chars_joined(" ", "a", "b");
    assert(chars_equals(joined, "a b"));
    chars_destroy(joined);

    joined = chars_joined(" ", "a", " ", "b");
    assert(chars_equals(joined, "a   b"));
    chars_destroy(joined);

    joined = chars_joined("/", "/home", "fbc", "code", "nest/core");
    assert(chars_equals(joined, "/home/fbc/code/nest/core"));
    chars_destroy(joined);
}

int
main(void)
{
    test1();
    test2();
    return 0;
}
