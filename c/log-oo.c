// clang log-oo.c -o log-oo -Wall -Wextra -pedantic -fsanitize=address,undefined
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// Types
typedef void* any;
typedef void (* FinalizeFunc)(any object);

// Object
#define OBJECT_TYPE(t) ((ObjectType*)(t))
#define OBJECT(o) ((Object*)(o))
typedef struct _ObjectType ObjectType;
typedef struct _Object Object;
struct _ObjectType
{
    FinalizeFunc finalize;
};

struct _Object
{
    ObjectType* type;
};

void object_initialize(any object)
{
    (void)(object);
}

void object_finalize(any object)
{
    free(object);
}

void object_unref(any object)
{
    OBJECT(object)->type->finalize(object);
}

// String
#define STRING(o) ((String*)(o))
typedef struct _String String;
struct _String
{
    Object object;
    char* content;
    int length;
};

void string_finalize(any object)
{
    String* string = STRING(object);
    free(string->content);
    object_finalize(string);
}

void string_initialize(String* string, char* content)
{
    object_initialize(string);
    string->content = strdup(content);
    string->length = strlen(content);
}

static ObjectType _string_type = {
    .finalize = string_finalize
};

String* string_new(char* content)
{
    String* string = malloc(sizeof (String));
    OBJECT(string)->type = &_string_type;
    string_initialize(string, content);
    return string;
}

void string_print(String* s, FILE* stream)
{
    fprintf(stream, "%s", s->content);
    fflush(stream);
}

// Log
#define LOG(o) ((Log*)(o))
typedef struct _Log Log;
struct _Log
{
    String string;
    char *domain;
};

void log_finalize(any object)
{
    Log* log = LOG(object);
    free(log->domain);
    string_finalize(STRING(log));
}

void log_initialize(Log* log, char* msg, char* domain)
{
    string_initialize(STRING(log), msg);
    log->domain = strdup(domain);
}

static ObjectType _log_type = {
    .finalize = log_finalize
};

String* log_new(char* msg, char* domain)
{
    Log* log = malloc(sizeof(Log));
    OBJECT(log)->type = &_log_type;
    log_initialize(log, msg, domain);
    return STRING(log);
}

void log_print(Log* log, FILE* stream)
{
    fprintf(stream, "[%s] ", log->domain);
    string_print(STRING(log), stream);
    fprintf(stream, "\n");
    fflush(stream);
}

int
main(void)
{
    String* log = log_new("file not found!", "system");
    log_print(LOG(log), stdout);
    object_unref(log);

    String* name = string_new("fabricio");
    string_print(name, stdout);
    object_unref(name);
    return 0;
}
