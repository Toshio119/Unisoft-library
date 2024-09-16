#ifndef UTILADT_H
#define UTILADT_H
/*
===================================================
       U!nisoft Libarary's 
       Utility at it's peak
---------------------------------------------------
  ##    ##  ##   ##        ##   #####
  ##    ##  ##   ##             ##   #
  ##    ##  ##   ##        ##   ##   #
  ##    ##  ##   ##        ##   #####
  ##    ##  ##   ##        ##   ##   #
  ##    ##       ##        ##   ##   #
    ####    ##   ########  ##   #####
---------------------------------------------------
© 2024 Unisoft .All rights reserved.
For support, contact: toshiojp119@gmail.com
===================================================
*/

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_SIZE 100
#define STD_TAB_SIZE 1000 
#define LOAD_FACTOR 0.75 

typedef struct {
    int *data;
    int front;
    int rear;
    int size;
} Queue;

typedef struct Noode {
    int data;
    struct Noode* left;
    struct Noode* right;
} treeNode;

typedef struct Node {
    char *key;
    char *value;
    struct Node *next;
} Node;

typedef struct {
    Node **buckets;
    size_t size;
    size_t count;
} HashTable;

Queue *createQueue(void) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (q == NULL) {
        perror("Failed to create queue");
        exit(EXIT_FAILURE);
    }

    q->data = (int *)malloc(QUEUE_SIZE * sizeof(int));
    if (q->data == NULL) {
        perror("Failed to allocate queue storage");
        free(q);
        exit(EXIT_FAILURE);
    }

    q->front = 0;
    q->rear = -1;
    q->size = 0;
    return q;
}


__attribute__((always_inline)) inline void enqueue(Queue *q, int value) {
    if (q->size == QUEUE_SIZE) {
        printf("Queue is full. Cannot enqueue %d\n", value);
        return;
    }

    q->rear = (q->rear + 1) % QUEUE_SIZE;
    q->data[q->rear] = value;
    q->size++;
}


__attribute__((always_inline)) inline int dequeue(Queue *q) {
    if (q->size == 0) {
        printf("Queue is empty. Cannot dequeue\n");
        return -1; 
    }

    int value = q->data[q->front];
    q->front = (q->front + 1) % QUEUE_SIZE;
    q->size--;
    return value;
}


__attribute__((always_inline)) inline int peek(Queue *q) {
    if (q->size == 0) {
        printf("Queue is empty. Cannot peek\n");
        return -1; 
    }

    return q->data[q->front];
}


__attribute__((always_inline)) inline void displayQueue(Queue *q) {
    if (q->size == 0) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue contents: ");
    for (int i = 0; i < q->size; i++) {
        printf("%d ", q->data[(q->front + i) % QUEUE_SIZE]);
    }
    printf("\n");
}


void freeQueue(Queue *q) {
    if (q != NULL) {
        free(q->data);
        free(q);
    }
}


treeNode *createNode(int data){
  treeNode *newnode = (treeNode*)malloc(sizeof(treeNode));
  if(!newnode){
    perror("Failed to create node");
    exit(1);
  } 
  newnode->data = data;
  newnode->left = NULL;
  newnode->right = NULL;
  return newnode;
}


treeNode *Tinsert(treeNode *root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = Tinsert(root->left, data);
    } else if(data > root->data) {
        root->right = Tinsert(root->right, data);
    }
    return root;
}


treeNode *biTsearch(treeNode *root, int data){
  if(!root || root->data == data){
    return root;
  }
  if(data < root->data){
    return biTsearch(root->left, data);
  } else {
    return biTsearch(root->right, data);
  }
}


treeNode *findMin(treeNode *root) {
    if (!root) {
        return NULL;
    }
    while (root->left) {
        root = root->left;
    }
    return root;
}


treeNode* findMax(treeNode* root) {
    if (!root) {
      return NULL;
    }
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}


treeNode* delete_node(treeNode* root, int data) {
    if (root == NULL) {
        return NULL;
    }
    if (data < root->data) {
        root->left = delete_node(root->left, data);
    } else if (data > root->data) {
        root->right = delete_node(root->right, data);
    } else {

        if (root->left == NULL) {
          treeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
          treeNode* temp = root->left;
            free(root);
            return temp;
        }
      treeNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete_node(root->right, temp->data);
    }
    return root;
}


__attribute__((always_inline)) inline void inorder(treeNode* root) {
  if (root != NULL) {
      inorder(root->left);
      printf("%d ", root->data);
      inorder(root->right);
  }
}


__attribute__((always_inline)) inline void preorder(treeNode* root) {
  if (root != NULL) {
      printf("%d ", root->data);
      preorder(root->left);
      preorder(root->right);
  }
}


__attribute__((always_inline)) inline void postorder(treeNode* root) {
  if (root != NULL) {
      postorder(root->left);
      postorder(root->right);
      printf("%d ", root->data);
  }
}

__attribute__((always_inline)) inline void freeTree(treeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}


__attribute__((always_inline)) inline unsigned long hash(const char *key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;  
    }
    return hash;
}

HashTable *createTable(size_t size) {
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    if (table == NULL) {
        perror("Failed to create hash table");
        exit(EXIT_FAILURE);
    }

    table->buckets = (Node **)calloc(size, sizeof(Node *));
    if (table->buckets == NULL) {
        perror("Failed to allocate buckets");
        free(table);
        exit(EXIT_FAILURE);
    }

    table->size = size;
    table->count = 0;
    return table;
}

__attribute__((always_inline)) inline void resize(HashTable *table);

__attribute__((always_inline)) inline void insert(HashTable *table, const char *key, const char *value) {
    unsigned long index = hash(key) % table->size;
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Failed to insert key-value pair");
        exit(EXIT_FAILURE);
    }

    newNode->key = strdup(key);
    newNode->value = strdup(value);
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
    table->count++;

    // Resize table if load factor exceeds threshold
    if ((double)table->count / table->size > LOAD_FACTOR) {
        resize(table);
    }
}

__attribute__((always_inline)) inline void resize(HashTable *table) {
    size_t newSize = table->size * 2;
    HashTable *newTable = createTable(newSize);

    for (size_t i = 0; i < table->size; i++) {
        Node *node = table->buckets[i];
        while (node) {
            insert(newTable, node->key, node->value);
            node = node->next;
        }
    }

    // Free old table
    for (size_t i = 0; i < table->size; i++) {
        Node *node = table->buckets[i];
        while (node) {
            Node *temp = node;
            node = node->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(table->buckets);
    table->buckets = newTable->buckets;
    table->size = newSize;
    free(newTable);
}


__attribute__((always_inline)) inline char *search(HashTable *table, const char *key) {
  unsigned long index = hash(key) % table->size;
  Node *node = table->buckets[index];
  while (node) {
      if (strcmp(node->key, key) == 0) {
          return node->value;
      }
      node = node->next;
  }
  return NULL;
}


__attribute__((always_inline)) inline void delete_table(HashTable *table, const char *key) {
  unsigned long index = hash(key) % table->size;
  Node *node = table->buckets[index];
  Node *prev = NULL;

  while (node) {
      if (strcmp(node->key, key) == 0) {
          if (prev) {
              prev->next = node->next;
          } else {
              table->buckets[index] = node->next;
          }
          free(node->key);
          free(node->value);
          free(node);
          table->count--;
          return;
      }
      prev = node;
      node = node->next;
  }
}

__attribute__((always_inline)) inline void freeTable(HashTable *table) {
    for (size_t i = 0; i < table->size; i++) {
        Node *node = table->buckets[i];
        while (node) {
            Node *temp = node;
            node = node->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}


#endif
