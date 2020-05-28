#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <dirent.h>
#include <stdarg.h>
#include <sys/time.h>
#include <wchar.h>
#include <string.h>

#if defined __x86_64__ && !defined __ILP32__
#   define CPU_REGISTERS_WIDTH 64
#else
#   define CPU_REGISTERS_WIDTH 32
#endif

#define AS_STRING(arg) #arg
#define BYTE_OR_BYTES(size) ((size > 1) ? "s" : "")
#define SHOW(type) type_show(AS_STRING(type), sizeof(type))

static bool
is_vogal(const char chr)
{
    return chr == 'a' || chr == 'A' ||
        chr == 'e' || chr == 'E' ||
        chr == 'i' || chr == 'I' ||
        chr == 'o' || chr == 'O' ||
        chr == 'u' || chr == 'U';
}

static bool
is_consonant(const char chr)
{
    return !is_vogal(chr);
}

static bool
last(const char *noun, const char *suffix)
{
    const int len = strlen(suffix);
    const int pos = strlen(noun) - len;
    return strncmp(noun + pos, suffix, len) == 0;
}

/*
static char*
concat(const char *string1, const char *string2)
{
    const int len1 = strlen(string1);
    const int len2 = strlen(string2);
    const int len = len1 + len2;
    char *concat = malloc(sizeof(char) * len + 1);
    memcpy(concat, string1, len1);
    memcpy(concat + len1, string2, len2);
    concat[len] = 0;
    return concat;
}
*/

typedef struct _List List;
struct _List
{
    char *text;
    int length;
    List *next;
};

static List*
list_last(List *list)
{
    if (list) {
        while(list->next)
            list = list->next;
    }
    return list;
}

static List*
list_append(List *list, char *string)
{
    List *node;
    node = malloc(sizeof (List));
    node->text = strdup(string);
    node->length = strlen(string);
    node->next = NULL;
    if (list) {
        List *last = list_last(list);
        last->next = node;
        return list;
    } else {
        return node;
    }
}

static void
list_finalize(List *list)
{
    while (list) {
        List *next = list->next;
        free(list->text);
        free(list);
        list = next;
    }
}

static char*
concat(const char *string, ...)
{
    int length = 1, pos = 0;
    List *list = NULL;
    List *tmp;
    va_list args;
    char *concat;
    va_start(args, string);
    while(string != NULL) {
        list = list_append(list, string);
        length = length + strlen(string);
        string = va_arg(args, const char *);
    }
    va_end(args);
    concat = malloc(sizeof(char) * length);
    tmp = list;
    while (tmp) {
        memcpy(concat + pos, tmp->text, tmp->length);
        pos = pos + tmp->length;
        tmp = tmp->next;
    }
    concat[length] = 0;
    list_finalize(list);
    return concat;
}

static char*
plural(const char *noun)
{
    const char *plural;
    if (last(noun, "s") || last(noun, "ss") || last(noun, "sh") || last(noun, "x") || last(noun, "z")) {
        plural = concat(noun, "es");
    } else if (last(noun, "y") && is_consonant(last))
}

static char*
fill(const char chr, int length)
{
    char line[length + 1];
    for (int idx = 0; idx <= length; idx++) {
        line[idx] = chr;
    }
    line[length + 1] = 0;
    return strdup(line);
}

static void
type_show(const char *name, long size)
{
    const char *points = fill('.', 20 - strlen(name));
    printf(
        "%s%s: %2ld byte%s (%ld bits)\n",
        name,
        points,
        size,
        BYTE_OR_BYTES(size),
        size * 8
    );
    free(points);
}

static void
cpu_show()
{
    printf("%-20s: %d bits\n", "CPU registers width", CPU_REGISTERS_WIDTH);
}

static void
primitive_types_show()
{
    SHOW(char);
    SHOW(signed char);
    SHOW(unsigned char);
    SHOW(short int);
    SHOW(signed short int);
    SHOW(unsigned short int);
    SHOW(short);
    SHOW(signed short);
    SHOW(unsigned short);
    SHOW(int);
    SHOW(signed int);
    SHOW(unsigned int);
    SHOW(long int);
    SHOW(signed long int);
    SHOW(unsigned long int);
    SHOW(long);
    SHOW(signed long);
    SHOW(unsigned long);
    SHOW(long long);
    SHOW(signed long long);
    SHOW(unsigned long long);
    SHOW(float);
    SHOW(double);
    SHOW(long double);
}

static void
fast_types_show()
{
    SHOW(int_fast8_t);
    SHOW(uint_fast8_t);
    SHOW(int_fast16_t);
    SHOW(uint_fast16_t);
    SHOW(int_fast32_t);
    SHOW(uint_fast32_t);
    SHOW(int_fast64_t);
    SHOW(uint_fast64_t);
}

static void
other_types_show()
{
    SHOW(void *);
    SHOW(wchar_t);
    SHOW(size_t);
    SHOW(ssize_t);
    SHOW(fpos_t);
    SHOW(time_t);
    SHOW(va_list);
}

int
main(void)
{
    printf("# CPU Information\n");
    printf("---------------------------------------------------------------\n");
    cpu_show();
    printf("\n# Primitive types\n");
    printf("---------------------------------------------------------------\n");
    primitive_types_show();
    printf("\n# Fast types\n");
    printf("---------------------------------------------------------------\n");
    fast_types_show();
    printf("\n# Other types\n");
    printf("---------------------------------------------------------------\n");
    other_types_show();
    return EXIT_SUCCESS;
}
