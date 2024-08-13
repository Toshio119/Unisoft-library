/******************************************************************************
 *                                                                            *
 *                           Toshio's C Library                               *
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
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <setjmp.h>
#include <sys/wait.h>

#define scuInput(x, y, max) \
  while (scanf(x, &y) != 1 || y <= 0 || y > max) { \
    printf("Invalid input. Please try again.\n"); \
    while (getchar() != '\n'); \
  }


#define ranInput(x, y, min, max) \
  while (scanf(x, &y) != 1 || y < min || y > max) { \
    printf("Invalid input. Please try again.\n"); \
    while (getchar() != '\n'); \
  }


#define errInput(x, y, max, prompt)\
    while (scanf(x, &y) != 1 || y <= 0 || y > max) { \
        printf(prompt); \
        while (getchar() != '\n'); \
}

#define with(ptr, cleanup) \
 for (int __done__ = ((ptr) ? 0 : (perror("Error"), 1)); !__done__; __done__ = (cleanup(ptr), 1))

#define swap(x, y)        \
do {                      \
    __typeof__(x) _tmp = (x); \
    (x) = (y);            \
    (y) = _tmp;           \
} while (0)

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

#define size_arr(arr) (sizeof(arr) / sizeof((arr)[0]))

#define Try do { int __err = setjmp(__jmpbuf); if (__err == 0) {
#define Catch(expression) } else if (__err == (expression)) {
#define Final } } while (0);
#define Throw(expression) longjmp(__jmpbuf, (expression))
jmp_buf __jmpbuf;

/* Read a string from standard input until a specified delimiter or maximum size is reached */
__attribute__((always_inline)) inline long int utilstrIn(char *str, size_t size, const char specifier) {
    if (!str || size <= 0) 
        return -1;
    size_t i = 0;
    char ch = '\0';

    switch (specifier) {
        case ' ': 
            while ((ch = fgetc(stdin)) != EOF && i < size - 1 && ch != ' ' && ch != '\n') 
                str[i++] = ch;

             str[i] = '\0';
          return i;
        default: 
            while ((ch = fgetc(stdin)) != EOF && i < size - 1 && ch != specifier) 
                 str[i++] = ch;

             str[i] = '\0';
          return i;
    }
}


/* Split a string into tokens based on a given delimiter */
__attribute__((always_inline)) inline char** split(const char *str, const char *delimiter, int *count) {
    if (!str || !delimiter || !count) 
      return NULL;
    char *temp = strdup(str);
    if (!temp)   //A special  thanks to WindLother who has provided this split function
      return NULL;  

    char **result = NULL;    
    *count = 0;

    char *token = strtok(temp, delimiter);
    while (token) {
        result = (char**)realloc(result, sizeof(char*) * (*count + 1));
        result[*count] = strdup(token);
        (*count)++;
        token = strtok(NULL, delimiter);
    }
    result = (char**)realloc(result, sizeof(char*) * (*count + 1));
    result[*count] = NULL;

    free(temp);
    return result;
}

/* Prompt the user with a message and read a line of input into a dynamically allocated string */
__attribute__((always_inline)) inline long int utilreadln(const char *__restrict prompt, char **str) {
  if (!prompt || !str) 
    return -1;

  fputs(prompt, stdout);

  size_t size = 128, len = 0;
  char *buff = (char *)malloc(size), ch = '\0';
  
  if (!buff) 
    return -1;
  
  while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
    if (len + 1 >= size) {
      size *= 2;
      char *newptr = (char*)realloc(buff, size);
      if (!newptr) {
        free(buff);
        return -1;
      }
      buff = newptr;
    }
    buff[len++] = ch;
  }

  if (len == 0 && ch == EOF) {
    free(buff);
    return -1;
  }

  buff[len] = '\0';
  *str = buff;

  return len;
}

/* Clear console screen */
__attribute__((always_inline)) inline void utilclear(void) {
  fputs("\033[2J\033[1;1H", stdout); fputs("\033c", stdout);
}

/* Read a content of a file into a buffer */
__attribute__((always_inline)) inline long int utilfile_read(char *buffer, size_t size, FILE *file) {
    if(!buffer || size <= 0 || !file)
      return -1;
    long int bytesRead = fread(buffer, 1, size - 1, file);
    if (bytesRead == 0 || ferror(file)) {
        perror("Error reading file");
        return -1;
    }
    buffer[bytesRead] = '\0'; 
    return bytesRead;
}


/* This is a helper function needed for join function in utilib.h */
size_t length(char **strings, int count, const char *delimiter) {
  size_t total_length = 0;
  size_t delimiter_length = strlen(delimiter);

  for (int i = 0; i < count; i++) {
      total_length += strlen(strings[i]);
      if (i < count - 1) {
          total_length += delimiter_length;
      }
  }

  return total_length + 1; 
}

/* Left shift an array of elements by one position */
__attribute__((always_inline)) inline void utilLshift(void *arr, size_t datatype_size, size_t size) {
      if (size <= 0)
        return;

      void *temp = malloc(datatype_size);
      if (!temp) 
         return;
      memcpy(temp, arr, datatype_size); 
  
      memmove(arr, (char*)arr + datatype_size, (size - 1) * datatype_size);

      memcpy((char*)arr + (size - 1) * datatype_size, temp, datatype_size);
  free(temp);
}

/* Right shift an array of elements by one position */
__attribute__((always_inline)) inline void utilRshift(void *arr, size_t datatype_size, size_t size){
      if (size <= 0)
        return;
     
      void *temp = malloc(datatype_size);
      if (!temp) 
        return; 
      memcpy(temp, (char*)arr + (size - 1) * datatype_size, datatype_size);

      memmove((char*)arr + datatype_size, arr, (size - 1) * datatype_size);

      memcpy(arr, temp, datatype_size);
  free(temp);
}


/* Trim leading and trailing whitespace from a string */
__attribute__((always_inline)) inline void utilstrTrim(char *__restrict str , size_t len) {
    if (!str || len <= 0) 
        return;
  
    char *start = str, *end = str + len - 1;
    
    while (isspace(*start)) 
      start++;
  
    while (end > start && isspace(*end)) 
      end--;
  
      *(end + 1) = '\0';
    memmove(str, start, end - start + 2);
}

/* Convert a string to uppercase */
__attribute__((always_inline)) inline char* utilstrTu(char *__restrict str, size_t len) {
  if(!str || len <= 0)
    return NULL;
       for(size_t i = 0; i < len; i++)
         str[i] = toupper(str[i]);
      return str;
}

/* Convert a string to lowercase */
__attribute__((always_inline)) inline char* utilstrLo(char *__restrict str, size_t len) {
   if(!str || len <= 0)
      return NULL;
       for(size_t i = 0; i < len; i++)
         str[i] = tolower(str[i]);
      return str;
}

/* Replace all occurrences of a character in a string with another character */
__attribute__((always_inline)) inline long int utilstrRepc(char *str, const char oldchar, const char newchar) {
    if(!str || !oldchar || !newchar) 
       return -1;
    long int j = 0;
    for (j = 0; str[j] != '\0'; j++) 
            (str[j] == oldchar) ? str[j] = newchar : 0;
  return j;
}


/* Join an array of strings into a single string, separated by a delimiter */
__attribute__((always_inline)) inline char* utilstrjoin(char **strings, int count, const char *delimiter) {
      if(!strings || !delimiter || !count)
         return NULL;

        size_t total_length = length(strings, count, delimiter);
        char *result = (char*)malloc(total_length);
        if (result == NULL) {
        perror("malloc failed");
         exit(EXIT_FAILURE);
        }

        result[0] = '\0'; 

       for (int i = 0; i < count; i++) {
        strcat(result, strings[i]);
          if (i < count - 1) 
        strcat(result, delimiter);
      }
       return result;
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
  return strcmp(a1, b1);
}

// This function sorts an array based on the given mode ('i' for int, 'd' for double, 'f' for float, 's' for string).
// It uses the qsort function and corresponding comparison functions for different data types.
__attribute__((always_inline)) inline void utilSort(void *array, size_t length, const char mode) {
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
            qsort(array, length, sizeof(char *), compare_string);
            break;
        default:
            fprintf(stderr, "Invalid mode for util_qsort: %c\n", mode);
            break;
    }
}

// This function executes a shell command using fork and execl in a child process.
// It handles errors during fork, execl, and waits for the child process to complete.
__attribute__((always_inline)) inline int Deltaexe(const char *command) {
  if (command == NULL) { // Here iam also going to use fputs because iam just printing a string 
      fputs("Deltaexe: Command's cannot be NULL\n", stderr);
      return -1;
  }
  
    pid_t pid = fork();  
    int status = 0, wpid = 0;

    switch (pid) {
        case -1:
            perror("fork");
            return -1;
        case 0:
            execl("/bin/bash", "DeltaSys", "-c", command, NULL); 
            perror("execl");
            return -1;
    }

    while ((wpid = waitpid(pid, &status, 0)) == -1 && errno == EINTR);

    if (wpid == -1) 
      return perror("waitpid"),-1;
    
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        fprintf(stderr, "child process terminated by signal %d\n", WTERMSIG(status));
        return -1;
    } else { // Here Iam using fputs because iam just printing a string not a variable
        fputs("child process did not exit normally\n", stderr);
        return -1;
    }
}

// This function prompts the user with a message and reads a double value from standard input.
__attribute__((always_inline)) inline double utilScan(const char *__restrict prompt) {
    if (!prompt) 
      return -1;

    char buff[75], *endptr = NULL;
    double value = 0;
  
    fputs(prompt, stdout);

    while (1) {
        if (fgets(buff, sizeof(buff), stdin) != NULL) {
            buff[strlen(buff) - 1] = '\0';  
            value = strtod(buff, &endptr);

            if (endptr != buff && *endptr == '\0') 
                return value;  

        } else {
            return -1; 
        }
    }
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

// This function renames a file by copying its contents to a new file and deleting the old file.
// It handles errors in file operations and ensures the old file is unlinked if the copy is successful.
__attribute__((always_inline)) inline void utilRename(const char *__restrict oldfilename, const char *__restrict newfilename) {
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
    while (fgets(str,1024,ptr2) != NULL)
        fputs(str,ptr1);
  
    if (unlink(oldfilename) != 0) 
       perror("Error deleting old file");
    
    fclose(ptr1);
    fclose(ptr2);
}

// This function returns the size of a file in bytes by seeking to the end of the file and using ftell.
// It handles errors in file opening and seeking operations.
__attribute__((always_inline)) inline long int utilGetSize(const char *__restrict filename) {
    if(!filename)
      return -1;
    FILE *ptr = NULL;
    if ((ptr = fopen(filename,"rb")) == NULL) 
        return perror("Error: Unable to open file"), -1;

    if(fseek(ptr, 0, SEEK_END) != 0)
        return perror("Error: Unable to seek to end of file"), -1;

    long int fileSize = ftell(ptr);
    fclose(ptr);
    return fileSize;
}

// This function copies the contents of one file to another.
// It handles errors in file opening and ensures all data is copied successfully.
__attribute__((always_inline)) inline void utilFilecpy(const char *src, const char *dest) {
  if(!src || !dest) 
      return;
  
    FILE *ptr1 = NULL , *ptr2 = NULL;
    char str[1024];
  
     if ((ptr1 = fopen(src, "r")) == NULL) {
       perror(src);
       return;
    } if((ptr2 = fopen(dest, "w")) == NULL) {
       perror(dest);
       return;
    } while (fgets(str,1024,ptr1) != NULL) 
        fputs(str,ptr2);
    
    fclose(ptr1);
    fclose(ptr2);
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

//Create a linked list 
__attribute__((always_inline)) inline LinkedList* createLinkedList(void) {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list == NULL) {
        fputs("Error: Memory allocation for linked list failed.\n", stderr);
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

__attribute__((always_inline)) inline int insertNode(LinkedList* list, int data, int at_end) {
    if (list == NULL) {
        fputs("Error: List is NULL.\n", stderr);
        return -1;
    }

    liNode* newNode = (liNode*)malloc(sizeof(liNode));
    if (newNode == NULL) {
        fputs("Error: Memory allocation for node failed.\n", stderr);
        return -1;
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

//add a element at the end of the list
__attribute__((always_inline)) inline int append(LinkedList* list, int data) {
    return insertNode(list, data, 1);
}

//add a element to the beggning of the list
__attribute__((always_inline)) inline int prepend(LinkedList* list, int data) {
    return insertNode(list, data, 0);
}

// Remove a element from the list 
__attribute__((always_inline)) inline int removeElement(LinkedList* list, int data) {
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

//Get size of the list
__attribute__((always_inline)) inline size_t getSize(LinkedList* list) {
    return (list != NULL) ? list->size : 0;
}

//print the content's of the list 
__attribute__((always_inline)) inline void printList(LinkedList* list) {
    if (list == NULL) {
        fputs("Error: List is NULL.\n", stderr);
        return;
    }

    liNode* current = list->head;
    printf("[");
    while (current) {
        printf("%d", current->data);
        if (current->next) printf(", ");
        current = current->next;
    }
    printf("]\n");
}

// Free the allocated memory of the list 
__attribute__((always_inline)) inline void freeList(LinkedList* list) {
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
// Merge Sort Functions for the linked list


void splitList(liNode* source, liNode** frontRef, liNode** backRef) { //Helper function 1
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


liNode* sortedMerge(liNode* a, liNode* b) { //Helper function 2
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


liNode* mergeSort(liNode* head) { //Helper function 3
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

// Sort the linked list using merge sort
__attribute__((always_inline)) inline void Sortlist(LinkedList* list) {
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


#endif 
