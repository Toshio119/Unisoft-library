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

#include <stddef.h>
#include <stdbool.h>
#include <setjmp.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <stdlib.h>

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
 long int UistrIn(char *__restrict str, long int size, const char *specifier);


/* getch: Read a character from standard input */
int getch(bool only_ch);


/* split: Split a string into tokens based on a given delimiter */
 char** split(const char *str, const char *delimiter, int *count);



/* Function to get the color code based on user input */
const char* getColorCode(const char *color);


 /* UistrHighlite print the line with the pattern highlighted in the specified color */
 void UistrHighlite(const char *line, const char *pattern, const char *color);


/* Uireadln: Prompt the user with a message and read a line of input into a dynamically allocated string */
 char *Uireadln(const char *prompt);


void println(const char *__restrict format, ...);

size_t strlen_sse(const char *str);


/* Uiclear: Clear console screen */
void Uiclear(void);


/* Uifile_read: Read a blocks of content of a file into a buffer */
 long int Uifile_read(char *__restrict buffer, size_t size, FILE *__restrict stream);

/* Uifilewrite: write blocks of the buffer content into a file */
 int Uifile_write(char *__restrict buffer, FILE *__restrict stream);


 int Uifile_append(const char *__restrict src, char *__restrict content);

/* This is a helper function needed for join function in Uiib.h */
size_t length(char **strings, int count, const char *delimiter);

 void UistrCaptilize(char *__restrict str);

 int UistrInsert(char *str , char *insert_str, long int pos, long int size_str);


/* UiLshift: Left shift an array of elements by one position */
 void UiLshift(void *arr, size_t datatype_size, size_t size);


/* UiRshift: Right shift an array of elements by one position */
 void UiRshift(void *arr, size_t datatype_size, size_t size);


/* UistrReverse: Reverse the sentence of a given string */
 char *UistrReverse(char *str);


/* UistrTrim: Trim the leading and trailing whitespace from a string */
 char *UistrTrim(char *__restrict str);

/* UistrTU: Convert a string to uppercase */
 char* UistrTU(char *__restrict str);

/* UistrTL: Convert a string to lowercase */
 char* UistrTL(char *__restrict str);

/*Uiloglist: store information for searching and printing data there can be only one list at a time */
_Bool Uiloglist(const char *data, int mode);

/* UistrRepc: Replace all occurrences of a character in a string with a another character */
 long int UistrRepc(char *__restrict str, const char oldchar, const char newchar);


/* UistrReps: Replace all occurrences of a substing in a string with a another substring */
 int UistrReps(char *__restrict str, long int strsize,const char *oldstr,const char *newstr);

/* UistrRep: Replace only one occurrence of a substing in a string with a another substring */
int UistrRep(char *__restrict str, long int strsize,const char *oldstr,const char *newstr);


/*UistrFilter: Filter out the unwanted substring's from a string*/
 int UistrFilter(char *__restrict str, const char *__restrict filter);

/*writeln: A low level function to write a line of string along with a newline */
 void writeln(const char *__restrict format);
/*readln: A low level function to read a line of string */
 long int readln(char *__restrict str, long int size);

/* Uistrjoin: Join an array of strings into a single string, separated by a delimiter */
 char* Uistrjoin(char **__restrict strings, int count, const char *__restrict delimiter);


int compare_long(const void *a, const void *b);


int compare_char(const void *a, const void *b);


int compare_float(const void *a, const void *b);

int compare_int(const void *a, const void *b);


int compare_double(const void *a, const void *b);


int compare_string(const void *a, const void *b);

/*  UiSort: sorts an array based on the given mode ('i' for int, 'd' for double, 'f' for float, 's' for string).
It uses the qsort function and corresponding comparison functions for different data types. */
 void UiSort(void *array, size_t length, const char mode);


bool is_odd(int x);

bool is_even(int x);

bool is_prime(int x);

int increment(int x);

int square(int x);

int filter_positive(int x);

int replace_if_negative(int x);

int factorial(int n);

/* Calculate the mean (average) of an array of integers */
double calculate_mean(int arr[], int n);


 void arrIn(int *arr, long size);

void filterNumbers(const char *input, char *output);

static int arrindex = 0;

static  int randomint(int min, int max);
/* buffer for the arrFormat function */
char buffer[1024];  
/* i had to put this here but it look's bad ....*/
/*compiler will not print any warning's  */


/* arrFormat: Formats an array of integers into a string */
 char *arrFormat(const int *arr, long size);

 int arrOut(int *arr, long len);


typedef struct store { 
    char shell1[100];
} store; // iam using this structure to orginize my code a bit

store globalstore; // Using a global variable to maintain the shell path across functions

void shelltype(const char *shell_path);
void clearpath(void);

const char *getshelltype(void);

/* Deltaexe: execute a shell command using fork and execl in a child process.
It handles errors during fork, execl, and waits for the child process to complete. */
  int Deltaexe(const char *command);


/* UiScannner: prompt the user with a message and read value from the standard input. */
  long double UiScanner(const char *__restrict prompt);


long double get_value(void);


/* setlimit: Enforce a minimum value of 1 and a maximum value for a given input. */
long double setlimit(long double Uiscan, double max);

/* setRange: Enforce a minimum and maximum value for a given input. */
long double setRange(long double Uiscan, double min, double max);

/* setlimit_err: Enforce a minimum value of 1 and a maximum value for a given input,
*           using a custom error message. */
long double setlimit_err(long double Uiscan, double max, const char *__restrict prompt);
/* setRange_err: Enforce a minimum and maximum value for a given input, using a
 *               custom error message. */
long double setRange_err(long double Uiscan, double min, double max, const char *__restrict prompt);


 int TrybySearch(int arr[], int n, int target);

/* UiRename : rename a file by copying its contents to a new file and deleting the old file.
It handles errors in file operations and ensures the old file is unlinked if the copy is successful.*/
 void UiRename(const char *__restrict oldfilename, const char *__restrict newfilename);


/* Uiwrite: write content to file in a particular index. */
 int Uiwrite(const char *__restrict filename, long int line, char *__restrict content);


/* UiFind: Find a file in a given directory. */
 int UiFind_file(const char *Directory, const char *Filename);


/* UiDirlist: list out in the console files in a given directory. */
 int UiDirlist(const char *Directory);


_Bool val = false;
/* exe_terminate: This is a function modifier for the logerror if this function is called log error will terminate the function*/
void exe_terminate(_Bool arg);

/* Abort: exit the program with a exit status 1 indicating failure */
__attribute__((noreturn)) void Abort(void);

void logerror(const char *__restrict msg);

void terminate(void);

 void Uifile_stat(const char *filename);


/* UiCountln: Count the no of lines of a given file */
 long int UiCountln(FILE *stream);

 static FILE *open(const char *filename, const char *mode);

FILE *ifstream(const char *filename);

FILE *ofstream(const char *filename);

/* Uigetime: get time of the system */
 int Uigetime(char *str, long int size);

/* UiGetSize: return the size of a file in bytes by seeking to the end of the file and using ftell.
 It handles errors in file opening and seeking operations. */
 long int UiGetSize(FILE *stream);

/* UiFilecpy: copy the contents of one file to another.
It handles errors in file opening and ensures all data is copied successfully. */
 int UiFilecpy(const char *__restrict src, const char *__restrict dest);


void dummy(void);


void Invalid(void);

void Error(void);


 void *new(long size);


 void delete(void *ptr);


 static void* resize(void* oldArray, size_t oldSize, size_t newSize, size_t elemSize);


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
 LinkedList* createLinkedList(void);


/* Add a node to the end of the linked list */
 int insertNode(LinkedList *__restrict list, int data, int at_end);


/* add a element at the end of the list */
int append(LinkedList *__restrict list, int data);

/* add a element to the beggning of the list */
int prepend(LinkedList *__restrict list, int data);

/* Remove a element from the list */
 int removeElement(LinkedList *__restrict list, int data);


/* Get size of the list */
size_t getSize(LinkedList *__restrict list);

/* print the content's of the list */
  void printList(LinkedList *__restrict list);


/* Free the allocated memory of the list */
 void freeList(LinkedList *__restrict list);


/* Merge Sort Functions for the linked list */
void splitList(liNode *__restrict source, liNode **__restrict frontRef, liNode **__restrict backRef);


liNode* sortedMerge(liNode *__restrict a, liNode *__restrict b);


liNode* mergeSort(liNode *__restrict head);


/* Sort the linked list using merge sort */
 void Sortlist(LinkedList *__restrict list);


#endif //UTILIB_H
