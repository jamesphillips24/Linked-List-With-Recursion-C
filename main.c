#include <stdio.h>
#include <stdlib.h>

// James Phillips
// 6/20/24
// Program to do basic linked list operations using recursion
// instead of normal loops.

typedef struct node {
  int data;
  struct node* next;
} node;

node* insert(node* list, int d);
node* del(node* list ,int d);
void print(node *list);
void freeList(node* list);
void copy (node *q, node **s);

int main(){
  int number = 0, choice=0;
  node* pList = NULL;
  node* nList = NULL;
  
  // Let the user add values until they enter -1.
  while(choice!= 4)
  {
    // Get the operation.
    printf("\nDo you want to (1)insert, (2)delete, (3)Copy (4)quit.\n");
    scanf("%d", &choice);
    
    printf("Your choice is %d\n", choice);
    
    // Execute the operation.
    if (choice == 1)
    {
      // Get the number.
      printf("Enter the value to insert\n");
      scanf("%d", &number);
      pList = insert(pList, number);
              // Look at the list.
      printf("Items in linked list: ");
      print(pList);
      //printf("\n");
    }
    else if (choice == 2)
    { // Get the number.
      printf("Enter the value to delete.\n");
      scanf("%d", &number);
      pList = del(pList, number);
              // Look at the list.
      printf("Items in linked list: ");
      print(pList);
      //printf("\n");
    }
    else if (choice == 3)
    {
      if (nList)
        freeList(nList);
      
      copy(pList, &nList); //passing reference of nList as it is not returning anything
              // Look at the list.
      printf("Items in NEW linked list: ");
      print(nList);
      // printf("\n");
    }
      
    else
    {
      break;
    }
  }
  freeList(nList);
  freeList(pList);
  printf("\nBye..\n");
  return 0;
}

// Use recursion to loop through each element until d is in the correct position
struct node* insert(struct node* list, int d){
  // If we're at the end of the list or d is at its correct position
  if(list == NULL || d <= list->data){
    node* newNode = malloc(sizeof(node));
    newNode->data = d;
    newNode->next = list;
    return newNode;
  }

  // Call insert again, moving down the linked list by one
  list->next = insert(list->next, d);

  return list;
}

// Use recursion to loop through the list until d is found
struct node* del(struct node* list ,int d){
  // If we reach the end of the list (not found)
  if(list == NULL)
    return list;

  // If found, just skip it in the linked list and free it
  if(list->data == d){
    node* rest = list->next;

    free(list);

    return rest;
  }

  // Call del again, moving down the linked list
  list->next = del(list->next, d);

  return list;
}

// Loop through the linked list with recursion, printing for each value.
void print(node *list){
  // If we haven't reached the end of the list
  if(list != NULL){
    printf("->%d", list->data);
    print(list->next);
  }
  return;
}

// Loop through the linked list with recursion,
// Reach the end of the loop and then start freeing backwards
// or else the 'nexts' would be lost before we could access them.
void freeList(node* list){
  if(list != NULL){
    freeList(list->next);
    free(list);
  }
  return;
}

// Loop through the list using recursion, creating a new
// dynamic node for each node.
void copy ( struct node *q, struct node **s ){
  // While we're not at the end, create a new node and
  // connect it to the new list.
  if(q != NULL){
    *s = malloc(sizeof(node));
    (*s)->data = q->data;
    (*s)->next = NULL;
    copy(q->next, &(*s)->next);
  }
}