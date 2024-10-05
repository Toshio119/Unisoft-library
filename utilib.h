/******************************************************************************
 *                                                                            *
 *                           Toshio's C Library: General utilities            *
 *                                                                            *
 *                        Created on: 22-07-2024                              *
 *                                                                            *
 *  Description: This is a C library that contains useful functions for       *
 *  C programs.                                                               *
 *  Notes: Let me know what functions to add more and iam sorry for           *                                                     
 *  not being able to write comment lines.these are the only ones that remain.*
 *                                                                            *
 ******************************************************************************/
#ifndef UTILIB_H
#define UTILIB_H

#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <setjmp.h>
#include <sys/wait.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <immintrin.h>
#include "utilGc.h"

#define true 1
#define false 0
#define bool _Bool
#define null ((void*)0)

#define with(ptr, cleanup_func, ...) \
for (int __done__ = ((ptr) ? 0 : (perror("Error"), 1)), \
     __cleanup_set = (cleanup_func) ? 0 : (fputs("Cleanup function is NULL\n", stderr), 1); \
     !__done__ && !__cleanup_set; \
     __done__ = (cleanup_func(ptr), 1))

#define error_at(x) ({ int __val = (x); (__val == -1 ? \
({\
fprintf(stderr,"Error at: (" __FILE__ " line: %d %s)\n",__LINE__, strerror(errno));\
exit(-1); -1;}) : __val); })

#define swap(x, y)        \
do {                      \
    __typeof__(x) _tmp = (x); \
    (x) = (y);            \
    (y) = _tmp;           \
} while (0)

#define size_arr(arr) (sizeof(arr) / sizeof(arr[0]))

#define file_opening_error 1
#define memory_allocation_error 2
#define  file_copy_error 3
#define RANDOMINT_MAX 1024

#define MAX(a, b, type) \
({                      \
    type _a = (a);      \
    type _b = (b);      \
    _a > _b ? _a : _b;  \
})


#define MIN(a, b, type) \
({                      \
    type _a = (a);      \
    type _b = (b);      \
    _a < _b ? _a : _b;  \
})

#define UiarrMap(arr, len, action) do{ \
   for(size_t i = 0; i < len; i++) { \
       (arr)[i] = (action((arr)[i])); \
    }  \
} while(0)

#define arrInln(arr, len) do{ \
   size_t i = -1; \
   while(++i < len && scanf("%d", &arr[i])); \
}while(0)

#define UiarrFilter(arr, len, condition) do { \
    size_t j = 0; \
    for(size_t i = 0; i < len; i++) { \
        if(condition((arr)[i])) {  \
            (arr)[j++] = (arr)[i]; \
        } \
    } \
  len = j; \
} while(0)

#define RED_COLOR "\33[1;31m"
#define GREEN_COLOR "\33[1;32m"
#define YELLOW_COLOR "\33[1;33m"
#define BLUE_COLOR "\33[1;34m"
#define MAGENTA_COLOR "\33[1;35m"
#define CYAN_COLOR "\33[1;36m"
#define RESET_COLOR "\33[00m"

#define UistrTarget(str, size, manipulation, search) do {       \
    if ((str) && (manipulation)) {                                \
        if ((search) != NULL) {                                   \
            char *found = strstr((str), (search));                \
            if (found != NULL) {                                  \
                char *end = found + strlen(search);               \
                char savedChar = *end;                            \
                *end = '\0';                                      \
                manipulation(found);                              \
                *end = savedChar;                                 \
            }                                                     \
        } else {                                                  \
            manipulation(str);                                    \
        }                                                         \
    }                                                             \
} while (0)

#define Typeof(var) _Generic((var), \
int: "<int>", \
unsigned int: "<unsigned int>", \
short: "<short>", \
unsigned short: "<unsigned short>", \
long: "<long>", \
unsigned long: "<unsigned long>", \
long long: "<long long>", \
unsigned long long: "<unsigned long long>", \
char: "<char>", \
unsigned char: "<unsigned char>", \
float: "<float>", \
double: "<double>", \
long double: "<long double>", \
void *: "<void*>", \
const void *: "<const void*>", \
char *: "char*", \
const char *: "<const char*>", \
default: "unknown")
      
#define __construct__ __attribute__((constructor)) 
#define __destruct__  __attribute__((destructor))
#define Prio_struct(prioritize) __attribute__((constructor(prioritize)))
#define Prio_destruct(prioritize) __attribute__((destructor(prioritize)))

#define Try do { int __err = setjmp(__jmpbuf); if (__err == 0) {
#define Catch(expression) } else if (__err == (expression)) {
#define Final } } while (0);
#define Throw(expression) longjmp(__jmpbuf, (expression))
jmp_buf __jmpbuf;


#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <setjmp.h>
#include <sys/wait.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <immintrin.h>
#include "UiGc.h"

#define true 1
#define false 0
#define bool _Bool
#define null ((void*)0)

#define with(ptr, cleanup_func, ...) \
for (int __done__ = ((ptr) ? 0 : (perror("Error"), 1)), \
     __cleanup_set = (cleanup_func) ? 0 : (fputs("Cleanup function is NULL\n", stderr), 1); \
     !__done__ && !__cleanup_set; \
     __done__ = (cleanup_func(ptr), 1))

#define error_at(x) ({ int __val = (x); (__val == -1 ? \
({\
fprintf(stderr,"Error at: (" __FILE__ " line: %d %s)\n",__LINE__, strerror(errno));\
exit(-1); -1;}) : __val); })

#define swap(x, y)        \
do {                      \
    __typeof__(x) _tmp = (x); \
    (x) = (y);            \
    (y) = _tmp;           \
} while (0)

#define size_arr(arr) (sizeof(arr) / sizeof(arr[0]))

#define file_opening_error 1
#define memory_allocation_error 2
#define  file_copy_error 3
#define RANDOMINT_MAX 1024

#define MAX(a, b, type) \
({                      \
    type _a = (a);      \
    type _b = (b);      \
    _a > _b ? _a : _b;  \
})


#define MIN(a, b, type) \
({                      \
    type _a = (a);      \
    type _b = (b);      \
    _a < _b ? _a : _b;  \
})

#define UiarrMap(arr, len, action) do{ \
   for(size_t i = 0; i < len; i++) { \
       (arr)[i] = (action((arr)[i])); \
    }  \
} while(0)

#define arrInln(arr, len) do{ \
   size_t i = -1; \
   while(++i < len && scanf("%d", &arr[i])); \
}while(0)

#define UiarrFilter(arr, len, condition) do { \
    size_t j = 0; \
    for(size_t i = 0; i < len; i++) { \
        if(condition((arr)[i])) {  \
            (arr)[j++] = (arr)[i]; \
        } \
    } \
  len = j; \
} while(0)

#define RED_COLOR "\33[1;31m"
#define GREEN_COLOR "\33[1;32m"
#define YELLOW_COLOR "\33[1;33m"
#define BLUE_COLOR "\33[1;34m"
#define MAGENTA_COLOR "\33[1;35m"
#define CYAN_COLOR "\33[1;36m"
#define RESET_COLOR "\33[00m"

#define UistrTarget(str, size, manipulation, search) do {       \
    if ((str) && (manipulation)) {                                \
        if ((search) != NULL) {                                   \
            char *found = strstr((str), (search));                \
            if (found != NULL) {                                  \
                char *end = found + strlen(search);               \
                char savedChar = *end;                            \
                *end = '\0';                                      \
                manipulation(found);                              \
                *end = savedChar;                                 \
            }                                                     \
        } else {                                                  \
            manipulation(str);                                    \
        }                                                         \
    }                                                             \
} while (0)

#define Typeof(var) _Generic((var), \
int: "<int>", \
unsigned int: "<unsigned int>", \
short: "<short>", \
unsigned short: "<unsigned short>", \
long: "<long>", \
unsigned long: "<unsigned long>", \
long long: "<long long>", \
unsigned long long: "<unsigned long long>", \
char: "<char>", \
unsigned char: "<unsigned char>", \
float: "<float>", \
double: "<double>", \
long double: "<long double>", \
void *: "<void*>", \
const void *: "<const void*>", \
char *: "char*", \
const char *: "<const char*>", \
default: "unknown")

#define __construct__ __attribute__((constructor)) 
#define __destruct__  __attribute__((destructor))
#define Prio_struct(prioritize) __attribute__((constructor(prioritize)))
#define Prio_destruct(prioritize) __attribute__((destructor(prioritize)))

#define Try do { int __err = setjmp(__jmpbuf); if (__err == 0) {
#define Catch(expression) } else if (__err == (expression)) {
#define Final } } while (0);
#define Throw(expression) longjmp(__jmpbuf, (expression))
jmp_buf __jmpbuf;


/* UistrIn: Read a string from standard input until a specified delimiter or maximum size is reached */
__attribute__((always_inline)) inline long int UistrIn(char *__restrict str, long int size, const char *specifier) {
    if (!str || size <= 0 || !specifier) 
        return -1;
    long int bytes_read = 0;
    char ch = '\0';
    fflush(stdout);
    if(read(0, str , size) <= 0){
        perror("Error");
        return -1;
    }
    bytes_read = strcspn(str, specifier);
    str[bytes_read] = '\0';
    return bytes_read;
}


/* getch: Read a character from standard input */
int getch(bool only_ch) {
    char ch, discard;
    if (read(0, &ch, 1) == EOF) 
        return -1; 
    if (only_ch) 
        while (read(0, &discard, 1) > 0 && discard != '\n');

    return ch;
}


/* split: Split a string into tokens based on a given delimiter */
__attribute__((always_inline)) inline char** split(const char *str, const char *delimiter, int *count) {
    if (!str || !delimiter || !count) 
      return NULL;
    char *temp = strdup(str);
    if (!temp)   //A special thanks to WindLother who has provided this split function
      return NULL;  // replit: @WindLother

    char **result = NULL;    
    *count = 0;

    char *token = strtok(temp, delimiter);
    while (token) {
        result = (char**)realloc(result, sizeof(char*) * (*count + 1));
        if(result == NULL) {
          Throw(memory_allocation_error);
        }
        result[*count] = strdup(token);
        (*count)++;
        token = strtok(NULL, delimiter);
    }
    result = (char**)realloc(result, sizeof(char*) * (*count + 1));
    result[*count] = NULL;

    free(temp);
    return result;
}



/* Function to get the color code based on user input */
const char* getColorCode(const char *color) {
    if (strcmp(color, "red") == 0) return RED_COLOR;
    if (strcmp(color, "green") == 0) return GREEN_COLOR;
    if (strcmp(color, "yellow") == 0) return YELLOW_COLOR;
    if (strcmp(color, "blue") == 0) return BLUE_COLOR;
    if (strcmp(color, "magenta") == 0) return MAGENTA_COLOR;
    if (strcmp(color, "cyan") == 0) return CYAN_COLOR;
    return RESET_COLOR;  // Default to no color if invalid input
}

 /* UistrHighlite print the line with the pattern highlighted in the specified color */
__attribute__((always_inline)) inline void UistrHighlite(const char *line, const char *pattern, const char *color) {
    if (!line || !pattern || !color) 
      return;
    const char *current = line;  
    const char *colorCode = getColorCode(color); 
    while ((current = strstr(current, pattern)) != NULL) {
        printf("%.*s", (int)(current - line), line);
        printf("%s%s%s", colorCode, pattern, RESET_COLOR);
        current += strlen(pattern);
        line = current;
    }
    printf("%s", line);
}

/* Uireadln: Prompt the user with a message and read a line of input into a dynamically allocated string */
__attribute__((always_inline)) inline char *Uireadln(const char *prompt) {
    if (!prompt) 
        return NULL;
    // Print the prompt to stdout
    fputs(prompt, stdout);
    fflush(stdout);  // Ensure prompt is flushed immediately

    size_t size = 128;
    char *buff = (char *)malloc(size);
    if (!buff) {
        Throw(memory_allocation_error);
        return NULL;
    }

    char ch;
    size_t len = 0;
    while ((read(0, &ch, 1)) != EOF && ch != '\n') {
        if (len + 1 >= size) {
            size *= 2;
            char *newptr = (char *)realloc(buff, size);
            if (!newptr) {
                free(buff);
                Throw(memory_allocation_error);
                return NULL;
            }
            buff = newptr;
        }
        buff[len++] = ch;
    }

    if (len == 0 && ch == EOF) {
        free(buff);
        return NULL;
    }

    buff[len] = '\0';
    return buff;
}


void println(const char *__restrict format, ...) {
    va_list args;
    va_list args_copy;

    va_start(args, format);

    va_copy(args_copy, args);
    long int length = vsnprintf(NULL, 0, format, args_copy);
    va_end(args_copy);

    char buffer[length + 2];

    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    buffer[length] = '\n';
    buffer[length + 1] = '\0';

    fwrite(buffer, sizeof(char), length + 1, stdout);
}

size_t strlen_sse(const char *str) {
    const char *start = str;
    __m128i zero = _mm_setzero_si128();
    while (1) {
         //This is not mine this is brought from stackoverflow
         // sorry i needed a fast way to get the length of a string and this is the fastest way i could find
        __m128i chunk = _mm_loadu_si128((const __m128i *)str);
        __m128i cmp = _mm_cmpeq_epi8(chunk, zero);
        int mask = _mm_movemask_epi8(cmp);
        if (mask != 0) {
            return (str - start) + __builtin_ctz(mask);
        }
        str += 16;
    }
}


/* Uiclear: Clear console screen */
void Uiclear(void) {
  fwrite("\033[2J\033[1;1H", sizeof(char), 11, stdout);  
  fwrite("\033c", sizeof(char), 3, stdout); 
}


/* Uifile_read: Read a blocks of content of a file into a buffer */
__attribute__((always_inline)) inline long int Uifile_read(char *__restrict buffer, size_t size, FILE *__restrict stream) {
    if(!buffer || size <= 0 || !stream)
      return -1;
    long int bytesRead = fread(buffer, 1, size - 1, stream);
    if (!bytesRead || ferror(stream)) 
        return perror("Error reading file"), -1;

    buffer[bytesRead] = '\0'; 
    return bytesRead;
}


/* Uifilewrite: write blocks of the buffer content into a file */
__attribute__((always_inline)) inline int Uifile_write(char *__restrict buffer, FILE *__restrict stream) {
    if(!buffer || !stream)
      return -1;
   if(fwrite(buffer, 1, strlen(buffer), stream) <= 0 || ferror(stream)) 
     return perror("Error reading file"), -1;

  return 0;
}

__attribute__((always_inline)) inline int Uifile_append(const char *__restrict src, char *__restrict content) {
    if(!src || !content)
        return -1;
    FILE *ptr = fopen(src, "a");
    if(ptr == NULL)
        return perror("append"), -1;
    fputs(content, ptr);
    fclose(ptr);
    return 0;
}

/* This is a helper function needed for join function in Uiib.h */
size_t length(char **strings, int count, const char *delimiter) {
  size_t total_length = 0;
  size_t delimiter_length = strlen_sse(delimiter);

  for (int i = 0; i < count; i++) {
      total_length += strlen_sse(strings[i]);
      if (i < count - 1) {
          total_length += delimiter_length;
      }
  }

  return total_length + 1; 
}

__attribute__((always_inline)) inline void UistrCaptilize(char *__restrict str) {
  if(!str)
    return;
  int word = 0;
  for(int i = 0;str[i];i++) {
    if(isspace(str[i])) {
      word = 0;
    } else {
      if(!word) {
        str[i] = toupper(str[i]);
        word = 1;
      } else {
        str[i] = tolower(str[i]);
      }
    }
  }
}


__attribute__((always_inline)) inline int UistrInsert(char *str , char *insert_str, long int pos, long int size_str) {
    if(!str || !insert_str || pos <= 0)
      return -1;
   long int len = strlen_sse(str);
   long int insert_len = strlen_sse(insert_str);
   (pos > len) ? pos = len : pos;
   char result[len + insert_len + 1];
   memcpy(result, str, pos);
   memcpy(result + pos, insert_str, insert_len);
   memcpy(result + pos + insert_len, str + pos, len - pos + 1);
   strncpy(str, result, size_str);
   return 0;
}


/* UiLshift: Left shift an array of elements by one position */
__attribute__((always_inline)) inline void UiLshift(void *arr, size_t datatype_size, size_t size) {
      if (!arr || size <= 0 || !datatype_size)
        return;

      void *temp = malloc(datatype_size);
      if (!temp) {
         Throw(memory_allocation_error);
         return;
      }
      memcpy(temp, arr, datatype_size); 

      memmove(arr, (char*)arr + datatype_size, (size - 1) * datatype_size);

      memcpy((char*)arr + (size - 1) * datatype_size, temp, datatype_size);
  free(temp);
}


/* UiRshift: Right shift an array of elements by one position */
__attribute__((always_inline)) inline void UiRshift(void *arr, size_t datatype_size, size_t size){
      if (!arr ||size <= 0 || !datatype_size)
        return;

      void *temp = malloc(datatype_size);
      if (!temp) {
        Throw(memory_allocation_error);
        return;
      } 
      memcpy(temp, (char*)arr + (size - 1) * datatype_size, datatype_size);

      memmove((char*)arr + datatype_size, arr, (size - 1) * datatype_size);

      memcpy(arr, temp, datatype_size);
  free(temp);
}


/* UistrReverse: Reverse the sentence of a given string */
__attribute__((always_inline)) inline char *UistrReverse(char *str) {
  if(!str)
     return NULL;
  long int len = strlen_sse(str);
  for (int i = 0; i < len / 2; i++) {
      char temp = str[i];
      str[i] = str[len - 1 - i];
      str[len - 1 - i] = temp;
  }
  return str;
}

/* UistrTrim: Trim the leading and trailing whitespace from a string */
__attribute__((always_inline)) inline char *UistrTrim(char *__restrict str) {
    if (!str) 
        return NULL;

    char *start = str, *end = str + strlen_sse(str) - 1;

    while (isspace(*start)) 
      start++;

    while (end > start && isspace(*end)) 
      end--;

      *(end + 1) = '\0';
    memmove(str, start, end - start + 2);
    return str;
}

/* UistrTU: Convert a string to uppercase */
__attribute__((always_inline)) inline char* UistrTU(char *__restrict str) {
  if(!str)
    return NULL;
  long int i = -1;
       while(str[++i] != '\0') 
         str[i] = toupper(str[i]);

      return str;
}

/* UistrTL: Convert a string to lowercase */
__attribute__((always_inline)) inline char* UistrTL(char *__restrict str) {
   if(!str)
      return NULL;
    long int i = -1;
       while(str[++i] != '\0') 
          str[i] = tolower(str[i]);

      return str;
}

/*Uiloglist: store information for searching and printing data there can be only one list at a time */
_Bool Uiloglist(const char *data, int mode) {
  static char history[1000][100];
  static int index = 0;
  _Bool found = false;
  switch (mode) {
   case 0: // Add data
        if (index < 1000) {
            strncpy(history[index], data, 99);
            history[index][99] = '\0'; 
            index++;
        } else {
            for (int j = 0; j < 999; j++) {
                strncpy(history[j], history[j + 1], 99);
                history[j][99] = '\0'; 
            }
            strncpy(history[999], data, 99);
            history[999][99] = '\0'; 
        }
        break;
  case 1: // print data
    fputs("History: ", stdout);
    for (int j = 0; j < index; j++)
      printf("%d. %s\n", j + 1, history[j]);
    break;
  case 2: // delete data
    for (int j = 0; j < 1000; j++) 
        history[j][0] = '\0'; 
    index = 0;
    break;
  case 3: // approximate search
        for (int j = 0; j < index; j++) {
            if (strstr(history[j], data) != NULL) {
                found = true;
                break;
            }
        } return found;
  case 4:// Search and delete data
       for (int j = 0; j < index; j++) {
         if (strstr(history[j], data) != NULL) {
             found = true;
        // Shift all subsequent entries up to fill the gap
        for (int k = j; k < index - 1; k++) {
            strncpy(history[k], history[k + 1], 99);
            history[k][99] = '\0'; // Ensure null-termination
        }
        // Clear the last entry and update the index
        history[index - 1][0] = '\0', index--;
        break; // Exit the loop once data is found and deleted
        }return found;
      }
  case 5: //Excat search
        for(int j = 0;j < index; j++)
          if(strncmp(history[j], data, 99) == 0) {
            found = true;
            break;
          }
     return found;
  }
}

/* UistrRepc: Replace all occurrences of a character in a string with a another character */
__attribute__((always_inline)) inline long int UistrRepc(char *__restrict str, const char oldchar, const char newchar) {
    if(!str || !oldchar || !newchar) 
       return -1;
    long int j = -1;
    while(str[++j] != '\0')
      if(str[j] == oldchar)
        str[j] = newchar;

  return j;
}


/* UistrReps: Replace all occurrences of a substing in a string with a another substring */
__attribute__((always_inline)) inline int UistrReps(char *__restrict str, long int strsize,const char *oldstr,const char *newstr) {
  if(!str || !oldstr || !newstr || strsize <= 0) // A special thanks to Code vault from youtube who has designed 
      return -1;                                  // This string replacement function youtube: @CodeVault
  char *Temp = NULL;
  // I have made some optimizations-
  // to make the code perform faster such as reducing function call's from strlen
  long int i = strlen_sse(newstr), j = strlen_sse(oldstr), k = 0;
  while((Temp = strstr(str, oldstr)) != NULL) {
  k = strlen_sse(Temp);
  if(strsize < k + (i - j) + 1)
    return -1;

  memmove(Temp + i, Temp + j, k - j + 1);
  memcpy(Temp, newstr, i);
  }
  return 0;
}

/* UistrRep: Replace only one occurrence of a substing in a string with a another substring */
__attribute__((always_inline)) inline int UistrRep(char *__restrict str, long int strsize,const char *oldstr,const char *newstr) {
    if(!str || !oldstr || !newstr || strsize <= 0)  
        return -1;                                   
    char *Temp = strstr(str, oldstr);
    if(!Temp)
      return -1;
    long int i = strlen_sse(newstr), j = strlen_sse(oldstr) , k = strlen_sse(Temp);
    if(strsize < k + (i - j) + 1)
      return -1;

    memmove(Temp + i, Temp + j, k - j + 1);
    memcpy(Temp, newstr, i);
    return 0;
}


/*UistrFilter: Filter out the unwanted substring's from a string*/
__attribute__((always_inline)) inline int UistrFilter(char *__restrict str, const char *__restrict filter) {
    if(!str || !filter)
      return -1;

  char *Temp = NULL;
  long int i = strlen_sse(filter), j = 0;
  while((Temp = strstr(str, filter)) != NULL) 
    j = strlen_sse(Temp),
    memmove(Temp, Temp + i, j - i + 1);

  return 0;
}

/*writeln: A low level function to write a line of string along with a newline */
__attribute__((always_inline)) inline void writeln(const char *__restrict format) {
    if(!format)
      return;
    fflush(stdout);
    if(write(1, format, strlen_sse(format)) <= 0 || write(1, "\n", 1) <= 0) 
      perror("write");

}

/*readln: A low level function to read a line of string */
__attribute__((always_inline)) inline long int readln(char *__restrict str, long int size) {
    if(!str || size <= 0)
      return  -1;

    fflush(stdout);
    long int bytes_read = 0;
    if((bytes_read = read(0, str , size)) <= 0) {
      perror("read");
      return -1;
    }
    str[bytes_read - 1] = '\0';
    return bytes_read;
}

/* Uistrjoin: Join an array of strings into a single string, separated by a delimiter */
__attribute__((always_inline)) inline char* Uistrjoin(char **__restrict strings, int count, const char *__restrict delimiter) {
      if(!strings || !delimiter || !count)
         return NULL;

        size_t total_length = length(strings, count, delimiter);
        char *result = (char*)malloc(total_length);
        if (result == NULL) {
            Throw(memory_allocation_error);
            exit(1);
        }

        result[0] = '\0'; 

       for (int i = 0; i < count; i++) {
        strcat(result, strings[i]);
          if (i < count - 1) 
        strcat(result, delimiter);
      }
       return result;
}


int compare_long(const void *a, const void *b){
    long a1 = *(const long *)a;
    long b1 = *(const long *)b;
    return (a1 > b1) - (a1 < b1);
}


int compare_char(const void *a, const void *b){
  char a1 = *(const char *)a;
  char b1 = *(const char *)b;
  return (a1 > b1) - (a1 < b1);
}


int compare_float(const void *a, const void *b){
  float a1 = *(const float *)a;
  float b1 = *(const float *)b;
  return (a1 > b1) - (a1 < b1);
}


int compare_int(const void *a, const void *b) {
  int a1 = *(const int *)a;
  int b1 = *(const int *)b;
  return (a1 > b1) - (a1 < b1);
}


int compare_double(const void *a, const void *b) {
  double a1 = *(const double *)a;
  double b1 = *(const double *)b;
  return (a1 > b1) - (a1 < b1);
}


int compare_string(const void *a, const void *b) {
  const char *a1 = *(const char **)a;
  const char *b1 = *(const char **)b;
  return -strcmp(a1, b1);
}

/*  UiSort: sorts an array based on the given mode ('i' for int, 'd' for double, 'f' for float, 's' for string).
It uses the qsort function and corresponding comparison functions for different data types. */
__attribute__((always_inline)) inline void UiSort(void *array, size_t length, const char mode) {
   if(!array || length <= 0 || !mode)
      return;

    switch (mode) {
        case 'i': // 'i' for integers 
            qsort(array, length, sizeof(int), compare_int);
            break;
        case 'd': // 'd' for doubles
            qsort(array, length, sizeof(double), compare_double);
            break;
        case 'f': // 'f' for floats
             qsort(array, length, sizeof(float), compare_float);
            break;
        case 's': // 's' for strings
            qsort(array, length, sizeof(char*), compare_string);
            break;
        case 'l': // 'l' for longs
            qsort(array, length, sizeof(long), compare_long);
            break;
        case 'c': // 'c' for charaters
            qsort(array, length, sizeof(char), compare_char);
           break;
        default:
            fprintf(stderr, "Invalid mode for Ui_qsort: %c\n", mode);
            break;
    }
}


bool is_odd(int x) { // for UiarrFilter
    return x % 2 != 0;
}

bool is_even(int x) { // for UiarrFilter
    return x % 2 == 0;
}

bool is_prime(int x) { // for UiarrFilter
   if(x < 2) return false;
   for(int i = 0; i <= sqrt(x); i++){
     if(x % i == 0) return false;
   }
   return true;
}

int increment(int x) { // for Uiarrmap
  return x + 1;
}

int square(int x) {  // for Uiarrmap
  return x * x;
}

int filter_positive(int x) {  // for Uiarrmap
  return (x > 0) ? x : 0;
}

int replace_if_negative(int x) {  // for Uiarrmap
  return (x < 0) ? -x : x;
}

int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

/* Calculate the mean (average) of an array of integers */
double calculate_mean(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return (double)sum / n;
}


__attribute__((always_inline)) inline void arrIn(int *arr, long size) {
    if (!arr || size <= 0)
       return;
    size_t count = 0;
    int num;
    char inputChar;
    while (count < size && scanf("%d", &num) == 1) {
        arr[count++] = num;
        inputChar = getchar();
        if (inputChar != ' ') 
            break;
    }
    while (inputChar != '\n' && inputChar != EOF) 
        inputChar = getchar();

} 

__attribute__((always_inline)) inline void filterNumbers(const char *input, char *output) {
  int j = 0;
  for (int i = 0; input[i] != '\0'; i++) 
      if (isdigit((unsigned char)input[i])) 
          output[j++] = input[i];

  output[j] = '\0'; 
}

static int arrindex = 0;

__attribute__((always_inline)) static inline int randomint(int min, int max) {
  if (min > max || min == max) 
      return -1; 
  if(max > 1024) {
    fputs("Error: Max value is greater than 1024 (greater than randomint max value)\n", stderr);
    return -1;
  }
  char arr[2024];
  char buff1[25], filtered[25];
  snprintf(buff1, sizeof(buff1), "%p", &arr[arrindex]); 
  filterNumbers(buff1, filtered);
  int addressAsInt = atoi(filtered);
  int range = max - min + 1;
  (arrindex == 2024) ? arrindex = 0 : arrindex++;
  return (addressAsInt % range) + min;
}

/* buffer for the arrFormat function */
char buffer[1024];  
/* i had to put this here but it look's bad ....*/
/*compiler will not print any warning's  */


/* arrFormat: Formats an array of integers into a string */
__attribute__((always_inline)) inline char *arrFormat(const int *arr, long size) {
    if(!arr || !size)
      return NULL;

    buffer[0] = '[';  
    size_t pos = 1;  
    for (size_t i = 0; i < size; i++) {
        pos += snprintf(buffer + pos, 1024 - pos, "%d", arr[i]);
        if (i < size - 1) {
            pos += snprintf(buffer + pos, 1024 - pos, ", ");
        }
    }

    snprintf(buffer + pos, 1024 - pos, "]");  
    return buffer;
}

__attribute__((always_inline)) inline int arrOut(int *arr, long len) {
  if (!arr || len <= 0)
      return -1;
  for (size_t i = 0; i < len; i++)
      if(arr[i] != 0)
      printf("%d ", arr[i]);

  fputs("\n", stdout);
return 0;
}


typedef struct store { 
    char shell1[100];
} store; // iam using this structure to orginize my code a bit

store globalstore; // Using a global variable to maintain the shell path across functions

void shelltype(const char *shell_path) {
    snprintf(globalstore.shell1, sizeof(globalstore.shell1), "%s", shell_path);
}

void clearpath(void) {
    globalstore.shell1[0] = '\0';
}

const char *getshelltype(void) {
    const char *str = "/bin/bash";
    if(globalstore.shell1[0] == '\0')
      return str;
    else 
       return globalstore.shell1;
}

/* Deltaexe: execute a shell command using fork and execl in a child process.
It handles errors during fork, execl, and waits for the child process to complete. */
__attribute__((always_inline)) inline int Deltaexe(const char *command) {
    if (command == NULL) { // Here iam also going to use fputs because iam just printing a string 
        fputs("Deltaexe: Command cannot be NULL\n", stderr);
        return -1;
    }

    pid_t pid = fork();  
    int status = 0, wpid = 0;

    switch (pid) {
        case -1:
            perror("fork");
            return -1;
        case 0:
            if (globalstore.shell1[0] != '\0') {
                execl(globalstore.shell1, globalstore.shell1, "-c", command, NULL);
                perror("execl");
                return -1;
            } else {
                execl("/bin/bash", "DeltaSys", "-c", command, NULL); 
                perror("execl");
                return -1;
            }
    }

    while ((wpid = waitpid(pid, &status, 0)) == -1 && errno == EINTR);

    if (wpid == -1) {
        perror("waitpid");
        return -1;
    }

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        fprintf(stderr, "Child process terminated by signal %d\n", WTERMSIG(status));
        return -1;
    } else { // Here Iam using fputs because iam just printing a string not a variable
        fputs("Child process did not exit normally\n", stderr);
        return -1;
    }
}


/* UiScannner: prompt the user with a message and read value from the standard input. */
__attribute__((always_inline)) inline long double UiScanner(const char *__restrict prompt) {
    if (!prompt) 
      return -1;

    char buff[75], *endptr = NULL;
    double value = 0;

    fputs(prompt, stdout);
    fflush(stdout);
    while (1) {
        if (fgets(buff, sizeof(buff), stdin) != NULL) {
            buff[strlen(buff) - 1] = '\0';  
            value = strtold(buff, &endptr);

            if (endptr != buff && *endptr == '\0') 
                return value;  

        } else {
            return perror(NULL), -1; 
        }
    }
}


long double get_value(void) { // Helper function
  char buff[75], *end = NULL;
  if(fgets(buff, 75,stdin) != NULL)
    return strtold(buff, &end);
  else
    return perror(NULL), -1;
}


/* setlimit: Enforce a minimum value of 1 and a maximum value for a given input. */
long double setlimit(long double Uiscan, double max) {
  while(Uiscan <= 0 || Uiscan > max) {
    printf("Invalid input .Please enter a number between 1 and %.1lf: ", max);
    Uiscan = get_value();
  }
  return Uiscan;
}

/* setRange: Enforce a minimum and maximum value for a given input. */
long double setRange(long double Uiscan, double min, double max) {
  while(Uiscan < min || Uiscan > max) {
    printf("Invalid input .Please enter a number between %.1lf and %.1lf: ", min, max);
    Uiscan = get_value();
  }
  return Uiscan;
}

/* setlimit_err: Enforce a minimum value of 1 and a maximum value for a given input,
*           using a custom error message. */
long double setlimit_err(long double Uiscan, double max, const char *__restrict prompt) {
  while(Uiscan <= 0 || Uiscan > max) {
    fputs(prompt, stdout);
    Uiscan = get_value();
  }
  return Uiscan;
}

/* setRange_err: Enforce a minimum and maximum value for a given input, using a
 *               custom error message. */
long double setRange_err(long double Uiscan, double min, double max, const char *__restrict prompt) {
  while(Uiscan < min || Uiscan > max) {
    fputs(prompt, stdout);
    Uiscan = get_value();
  }
  return Uiscan;
}


__attribute__((always_inline)) inline int TrybySearch(int arr[], int n, int target) {
    int start1 = 0, end1 = n / 3 - 1;
    int start2 = n / 3, end2 = 2 * (n / 3) - 1;
    int start3 = 2 * (n / 3), end3 = n - 1;
    while (start1 <= end1 || start2 <= end2 || start3 <= end3) {
        if (start1 <= end1 && (arr[start1++] == target || arr[end1--] == target)) 
            return 1;
        if (start2 <= end2 && (arr[start2++] == target || arr[end2--] == target))
            return 1;
        if (start3 <= end3 && (arr[start3++] == target || arr[end3--] == target)) 
            return 1;  
    } return -1; 
}

/* UiRename : rename a file by copying its contents to a new file and deleting the old file.
It handles errors in file operations and ensures the old file is unlinked if the copy is successful.*/
__attribute__((always_inline)) inline void UiRename(const char *__restrict oldfilename, const char *__restrict newfilename) {
  if(!oldfilename || !newfilename)
        return;

    FILE *ptr1 = NULL , *ptr2 = NULL;
    char str[1024];
    if ((ptr1 = fopen(newfilename,"w")) == NULL){ 
        perror(newfilename);
      return;
    } 
    if ((ptr2 = fopen(oldfilename,"r")) == NULL){
         perror(oldfilename);
      return;
    }
    while (fgets(str, 1024, ptr2) != NULL)
        fputs(str,ptr1);

    if (unlink(oldfilename) != 0) 
       perror("Error deleting old file");

    fclose(ptr1);
    fclose(ptr2);
}


/* Uiwrite: write content to file in a particular index. */
__attribute__((always_inline)) inline int Uiwrite(const char *__restrict filename, long int line, char *__restrict content) {
    if (!filename || line <= 0 || !content)
        return -1;

    char str[1024] = {0};
    long int line_count = 0, buffer_size = 100;
    FILE *ptr = NULL;
    char **lines = (char **)malloc(buffer_size * sizeof(char*)); 

    if (!lines) {
        perror("malloc");
        return -1;
    }

    if ((ptr = fopen(filename, "r+")) == NULL) {
        perror("fopen");
        free(lines);
        return -1;
    }

    while (fgets(str, sizeof(str), ptr) != NULL) {
        if (line_count >= buffer_size) {
            buffer_size *= 2;
            char **temp = (char **)realloc(lines, buffer_size * sizeof(char*));
            if (!temp) {
                Throw(memory_allocation_error);
                free(lines);
                fclose(ptr);
                return -1;
            }
            lines = temp;
        }

        lines[line_count] = strdup(str); 
        if (!lines[line_count]) {
            Throw(memory_allocation_error);
            for (int j = 0; j < line_count; j++) 
              free(lines[j]);

            free(lines);
            fclose(ptr);
            return -1;
        }
        line_count++;
    }

    if (fseek(ptr, 0, SEEK_SET) != 0) {
        perror("fseek");
        for (int j = 0; j < line_count; j++) 
          free(lines[j]);

        free(lines);
        fclose(ptr);
        return -1;
    }

    for (int j = 0; j < line - 1 && j < line_count; j++)
        fwrite(lines[j], sizeof(char), strlen_sse(lines[j]), ptr);

    fwrite(content, sizeof(char), strlen_sse(content), ptr);
    fputc('\n', ptr);

    for (int j = line - 1; j < line_count; j++)
        fwrite(lines[j], sizeof(char), strlen_sse(lines[j]), ptr);

    for (int j = 0; j < line_count; j++) 
        free(lines[j]);

    free(lines);
    fclose(ptr);
    return 0;
}


/* UiFind: Find a file in a given directory. */
__attribute__((always_inline)) inline int UiFind_file(const char *Directory, const char *Filename) {
  DIR *dir;
  struct dirent *entry;

  if ((dir = opendir(Directory)) == NULL) {
    perror("Error");
    return -1;
  }

  while ((entry = readdir(dir)) != NULL)
    if(strcmp(entry->d_name, Filename) == 0) {
      closedir(dir);
      return 0;
    }

  closedir(dir);
  return -1;
}


/* UiDirlist: list out in the console files in a given directory. */
__attribute__((always_inline)) inline int UiDirlist(const char *Directory) {
  DIR *dir;
  struct dirent *entry;

  if ((dir = opendir(Directory)) == NULL) {
    perror("Error");
    return -1;
  }

  while ((entry = readdir(dir)) != NULL)
    puts(entry->d_name);

  closedir(dir);
  return 0;
}


_Bool val = false;
/* exe_terminate: This is a function modifier for the logerror if this function is called log error will terminate the function*/
void exe_terminate(_Bool arg) {
   val = arg;
}

/* Abort: exit the program with a exit status 1 indicating failure */
__attribute__((noreturn)) void Abort(void) {
    exit(1);
}

void logerror(const char *__restrict msg) { 
  fwrite(msg, sizeof(char), strlen(msg), stderr);
  if(msg[0] != '\0' || !msg)
  fwrite(": ", sizeof(char), 2, stderr);

  switch(errno) { // do you know how much pain is counting string length manually ??
      case EPERM:     
        fwrite("Operation not permitted\n", sizeof(char), 25, stderr); 
        break;
      case ENOENT:    
        fwrite("No such file or directory\n", sizeof(char), 27, stderr); 
        break;
      case ESRCH:     
        fwrite("No such process\n", sizeof(char), 17, stderr); 
        break;
      case EINTR:     
        fwrite("Interrupted system call\n", sizeof(char), 24, stderr);
        break;
      case EIO:       
        fwrite("I/O error\n", sizeof(char), 11, stderr); 
        break;
      case ENXIO:     
        fwrite("No such device or address\n", sizeof(char), 29, stderr); 
        break;
      case E2BIG:     
        fwrite("Argument list too long\n", sizeof(char), 23, stderr); 
        break;
      case ENOEXEC:   
        fwrite("Exec format error\n", sizeof(char), 19, stderr); 
        break;
      case EBADF:     
        fwrite("Bad file number\n", sizeof(char), 16, stderr); 
        break;
      case ECHILD:    
        fwrite("No child processes\n", sizeof(char), 20, stderr); 
        break;
      case EAGAIN:    
        fwrite("Try again\n", sizeof(char), 11, stderr); 
        break;
      case ENOMEM:    
        fwrite("Out of memory\n", sizeof(char), 15, stderr); 
        break;
      case EACCES:    
        fwrite("Permission denied\n", sizeof(char), 18, stderr); 
        break;
      case EFAULT:    
        fwrite("Bad address\n", sizeof(char), 12, stderr); 
        break;
      case ENOTBLK:   
        fwrite("Block device required\n", sizeof(char), 23, stderr); 
        break;
      case EBUSY:     
        fwrite("Device or resource busy\n", sizeof(char), 25, stderr); 
        break;
      case EEXIST:    
        fwrite("File exists\n", sizeof(char), 12, stderr); 
        break;
      case EXDEV:     
        fwrite("Cross-device link\n", sizeof(char), 18, stderr); 
        break;
      case ENODEV:    
        fwrite("No such device\n", sizeof(char), 15, stderr); 
        break;
      case ENOTDIR:   
        fwrite("Not a directory\n", sizeof(char), 16, stderr); 
        break;
      case EISDIR:    
        fwrite("Is a directory\n", sizeof(char), 15, stderr); 
        break;
      case EINVAL:    
        fwrite("Invalid argument\n", sizeof(char), 17, stderr); 
        break;
      case ENFILE:    
        fwrite("File table overflow\n", sizeof(char), 21, stderr); 
        break;
      case EMFILE:   
        fwrite("Too many open files\n", sizeof(char), 20, stderr); 
        break;
      case ENOTTY:    
        fwrite("Not a typewriter\n", sizeof(char), 17, stderr); 
        break;
      case ETXTBSY:   
        fwrite("Text file busy\n", sizeof(char), 14, stderr); 
        break;
      case EFBIG:     
        fwrite("File too large\n", sizeof(char), 15, stderr); 
        break;
      case ENOSPC:    
        fwrite("No space left on device\n", sizeof(char), 26, stderr); 
        break;
      case ESPIPE:    
        fwrite("Illegal seek\n", sizeof(char), 13, stderr); 
        break;
      case EROFS:     
        fwrite("Read-only file system\n", sizeof(char), 23, stderr); 
        break;
      case EMLINK:    
        fwrite("Too many links\n", sizeof(char), 15, stderr); 
        break;
      case EPIPE:     
        fwrite("Broken pipe\n", sizeof(char), 12, stderr); 
        break;
      case EDOM:      
        fwrite("Math argument out of domain of func\n", sizeof(char), 36, stderr); 
        break;
      case ERANGE:    
        fwrite("Math result not representable\n", sizeof(char), 31, stderr); 
        break;
      case 0:        
        fwrite("Sucess\n", sizeof(char), 8, stderr); 
        break;
    default:
        fwrite("Unknown error\n", sizeof(char), 14, stderr);
    break;
  }

  if(val)
    Abort();
  else
    return;
}

__attribute__((noreturn)) void terminate(void) {
    (errno == 0) ? (exit(1)) : (logerror(""), exit(1));
}

__attribute__((always_inline)) inline void Uifile_stat(const char *filename) {
    struct stat file_stat;
    if (stat(filename, &file_stat) == -1) {
        perror("stat");
        return;
    } 
        printf("File: %s\n", filename);
        fputs("File type: ", stdout);
        if (S_ISREG(file_stat.st_mode)) {
            fputs("Regular file", stdout);
        } else if (S_ISDIR(file_stat.st_mode)) {
            fputs("Directory", stdout);
        } else if (S_ISCHR(file_stat.st_mode)) {
            fputs("Character device", stdout);
        } else if (S_ISBLK(file_stat.st_mode)) {
            fputs("Block device", stdout);
        } else if (S_ISFIFO(file_stat.st_mode)) {
            fputs("FIFO/pipe", stdout);
        } else if (S_ISLNK(file_stat.st_mode)) {
            fputs("Symbolic link", stdout);
        } else if (S_ISSOCK(file_stat.st_mode)) {
            fputs("Socket", stdout);
        } else {
            fputs("Unknown", stdout);
        }
        printf("\nSize: %lld bytes\n", (long long) file_stat.st_size);
        printf("Permissions: ");
        printf("Number of hard links: %ld\n", (long) file_stat.st_nlink);
        printf("Owner UID: %ld\n", (long) file_stat.st_uid);
        printf("Group GID: %ld\n", (long) file_stat.st_gid);
        printf("Last access time: %s", ctime(&file_stat.st_atime));
        printf("Last modification time: %s", ctime(&file_stat.st_mtime));
        printf("Last status change time: %s", ctime(&file_stat.st_ctime));
}


/* UiCountln: Count the no of lines of a given file */
__attribute__((always_inline)) inline long int UiCountln(FILE *stream){
    if(!stream)
      return -1;

    long int count = 0;
    char ch = '\0';
  while((ch = fgetc(stream)) != EOF)
    if(ch == '\n') 
       count++;

   if(count == 0)
     return perror("Error"), -1;
    rewind(stream);
  return count;
} 

__attribute__((always_inline)) inline static FILE *open(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) 
        Throw(file_opening_error);

    return file;
}

FILE *ifstream(const char *filename) {
    return open(filename, "r");
}

FILE *ofstream(const char *filename) {
    return open(filename, "w");
}


/* Uigetime: get time of the system */
__attribute__((always_inline)) inline int Uigetime(char *str, long int size) {
  if(!str || size <= 20)
    return fputs("Insufficient size of buffer for getime", stderr), -1;
  time_t rawtime;
  struct tm *timeinfo;
  time(&rawtime);
  timeinfo = localtime(&rawtime);

  if (strftime(str, size, "%H:%M:%S", timeinfo) == 0) {
      perror("Uigetime");
      return -1;
  }
  return 0; 
}

/* UiGetSize: return the size of a file in bytes by seeking to the end of the file and using ftell.
 It handles errors in file opening and seeking operations. */
__attribute__((always_inline)) inline long int UiGetSize(FILE *stream) {
    if(!stream)
      return -1;

    if(fseek(stream, 0, SEEK_END) != 0)
        return perror("Error: Unable to seek to end of file"), -1;

    long int fileSize = ftell(stream);
      rewind(stream);
    return fileSize;
}

/* UiFilecpy: copy the contents of one file to another.
It handles errors in file opening and ensures all data is copied successfully. */
__attribute__((always_inline)) inline int UiFilecpy(const char *__restrict src, const char *__restrict dest) {
  if(!src || !dest) 
      return -1;
    FILE *ptr1 = NULL , *ptr2 = NULL;
    if ((ptr1 = fopen(src, "r")) == NULL) {
       Throw(file_copy_error);
       return -1;
    } if((ptr2 = fopen(dest, "w")) == NULL) {
       Throw(file_copy_error);
       return -1;
    } 
    char buff[1024];
    long bytesRead = 0;
   while ((bytesRead = fread(buff, 1, sizeof(buff), ptr1)) > 0) {
     if (fwrite(buff, 1, bytesRead, ptr2) != bytesRead) {
        fclose(ptr1);
        fclose(ptr2);
        Throw(file_copy_error);
        return -1;
     }
   }

   if (ferror(ptr1)) {
     fclose(ptr1);
     fclose(ptr2);
     Throw(file_copy_error);
     return -1;
   }

    fclose(ptr1);
    fclose(ptr2);
}


__attribute__((noreturn)) void dummy(void) {
  fwrite("new: dummy pointer detected\n", sizeof(char), 28, stderr);
  exit(1);
}


__attribute__((noreturn)) void Invalid(void) {
  fwrite("new: Invalid input\n", sizeof(char), 20, stderr);
  exit(1);
}

__attribute__((noreturn)) void Error(void) {
  perror("new");
  exit(1);
}


__attribute__((always_inline)) inline void *new(long size) {
    if (size <= 0) 
        Invalid();

    void *ptr = malloc(size);
    if (ptr == NULL)
        Error();
    return ptr;
}


__attribute__((always_inline)) inline void delete(void *ptr) {
    if (ptr == NULL) 
        dummy();
     free(ptr);
     ptr = NULL;
}


__attribute__((always_inline)) inline static void* resize(void* oldArray, size_t oldSize, size_t newSize, size_t elemSize) {
    // Allocate new array
    void* newArray = new(newSize * elemSize);

    size_t copySize = (oldSize < newSize) ? oldSize : newSize;
    memcpy(newArray, oldArray, copySize * elemSize);

    if (newSize > oldSize) {
        memset((char*)newArray + oldSize * elemSize, 0, (newSize - oldSize) * elemSize);
    }  
     free(oldArray);
  return newArray;
}


typedef struct liNode {
    int data;
    struct liNode* next;
} liNode;

typedef struct LinkedList {
    liNode* head;
    liNode* tail;
    size_t size;
} LinkedList;


/* Create a linked list usage: Linked list *<label> = createLinkedList(); */
__attribute__((always_inline)) inline LinkedList* createLinkedList(void) {
    LinkedList *__restrict list = (LinkedList*)malloc(sizeof(LinkedList));
    if(list == NULL) {
       fputs("Error: Memory allocation failed.\n", stderr);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}


/* Add a node to the end of the linked list */
__attribute__((always_inline)) inline int insertNode(LinkedList *__restrict list, int data, int at_end) { //Helper function 
    if (list == NULL) {
        fputs("Error: List is NULL.\n", stderr);
        return -1;
    }

    liNode* newNode = (liNode*)malloc(sizeof(liNode));
    if (newNode == NULL){
        fputs("Error: Memory allocation failed.\n", stderr);
    }
    newNode->data = data;
    newNode->next = NULL;

    if (list->size == 0) {
        list->head = newNode;
        list->tail = newNode;
    } else if (at_end) {
        list->tail->next = newNode;
        list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head = newNode;
    }

    list->size++;
    return 0;
}


/* add a element at the end of the list */
int append(LinkedList *__restrict list, int data) {
    return insertNode(list, data, 1);
}


/* add a element to the beggning of the list */
int prepend(LinkedList *__restrict list, int data) {
    return insertNode(list, data, 0);
}


/* Remove a element from the list */
__attribute__((always_inline)) inline int removeElement(LinkedList *__restrict list, int data) {
    if (list == NULL || list->head == NULL) {
        fputs("Error: List is NULL or empty.\n", stderr);
        return -1;
    }

    liNode* current = list->head;
    liNode* previous = NULL;

    while (current) {
        if (current->data == data) {
            if (previous) {
                previous->next = current->next;
            } else {
                list->head = current->next;
            }

            if (current == list->tail) {
                list->tail = previous;
            }

            free(current);
            list->size--;
            return 0;
        }

        previous = current;
        current = current->next;
    }
    fputs("Error: Element not found in the list.\n", stderr);
    return -1;
}


/* Get size of the list */
size_t getSize(LinkedList *__restrict list) {
    return (list != NULL) ? list->size : 0;
}


/* print the content's of the list */
__attribute__((always_inline)) inline void printList(LinkedList *__restrict list) {
    if (list == NULL) {
        fputs("Error: List is NULL.\n", stderr);
        return;
    }

    liNode* current = list->head;
    fputs("[", stdout);
    while (current) {
        printf("%d", current->data);
        if (current->next) fputs(", ", stdout);
        current = current->next;
    }
    fputs("]\n", stdout);
}


/* Free the allocated memory of the list */
__attribute__((always_inline)) inline void freeList(LinkedList *__restrict list) {
    if (list == NULL) {
        fputs("Error: List is NULL.\n", stderr);
        return;
    }

    liNode* current = list->head;
    while (current) {
        liNode* nextNode = current->next;
        free(current);
        current = nextNode;
    } 
    free(list);
}


/* Merge Sort Functions for the linked list */
void splitList(liNode *__restrict source, liNode **__restrict frontRef, liNode **__restrict backRef) { //Helper function 1
    liNode* fast;
    liNode* slow;
    if (source == NULL || source->next == NULL) {
        *frontRef = source;
        *backRef = NULL;
    } else {
        slow = source;
        fast = source->next;

        while (fast != NULL) {
            fast = fast->next;
            if (fast != NULL) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *frontRef = source;
        *backRef = slow->next;
        slow->next = NULL;
    }
}


liNode* sortedMerge(liNode *__restrict a, liNode *__restrict b) { //Helper function 2
    if (a == NULL) return b;
    if (b == NULL) return a;

    if (a->data <= b->data) {
        a->next = sortedMerge(a->next, b);
        return a;
    } else {
        b->next = sortedMerge(a, b->next);
        return b;
    }
}


liNode* mergeSort(liNode *__restrict head) { //Helper function 3
    if (head == NULL || head->next == NULL) {
        return head;
    }

    liNode* a;
    liNode* b;
    splitList(head, &a, &b);

    a = mergeSort(a);
    b = mergeSort(b);

    return sortedMerge(a, b);
}


/* Sort the linked list using merge sort */
__attribute__((always_inline)) inline void Sortlist(LinkedList *__restrict list) {
    if (list == NULL || list->head == NULL) {
        return;
    }
    list->head = mergeSort(list->head);

    // Update tail
    liNode* current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    list->tail = current;
}


#endif //UTILIB_H
