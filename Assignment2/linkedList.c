#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
  int data;
  struct Node *next;
};

struct Node *listInsert(struct Node *head, int data);
struct Node *mergeLists(struct Node *l1, struct Node *l2);
void printList(struct Node *head);
void mergeHelper(struct Node* dest, struct Node* from);

int main(int argc, char *argv[]) {
  struct Node *list1 = NULL;
  struct Node *list2 = NULL;
  int i = 1;
  char *errorMsg = "Pass in arguments in the format: <list 1 ints seperated by spaces> "
    ", <list 2 ints seperated by spaces>"; 
  if (argc == 1) {
    puts(errorMsg);
    return 1;
  }
  while (strcmp(argv[i], ",")) {
    list1 = listInsert(list1, atoi(argv[i]));
    i++;
    if (!argv[i]) {
      puts(errorMsg);
      return 1;
    }
  }
  i++;
  while (argv[i] != NULL) {
    list2 = listInsert(list2, atoi(argv[i]));
    i++;
  }

  struct Node *list3 = mergeLists(list1, list2);
  printList(list1);
  printList(list2);
  printList(list3);
}

void mergeHelper(struct Node* dest, struct Node* from) {
  if (from == NULL) {
    return;
  }
  else {
  struct Node* temp = from;
  from = from->next;
  temp->next = dest;
  dest = temp;
  }
}
// adds to the begining of the linked list (also in class slides)
struct Node *listInsert(struct Node *head, int data) {
  struct Node *new = malloc(sizeof(struct Node));
  new->data = data;
  new->next = head;
  return new;
}

void printList(struct Node *head) {
  if (head == NULL) {
    return;
  }
  struct Node *curr = head;
  while (curr->next != NULL) {
    printf("%d->", curr->data);
    curr = curr->next;
  }
  printf("%d \n", curr->data);
}

struct Node *mergeLists(struct Node *l1, struct Node *l2) {
  struct Node temp;
  struct Node *tempP = &temp;
  temp.next = NULL;
  while(1) {
    if (l1 == NULL) {
        if (l2 == NULL){
            print("both lists are empty")
            return l1;
        }
        tempP->next = l2;
        break;
    }
    else if (l2 = NULL) {
        tempP->next = l1;
        break;
    }
    if (l1->data <= l2->data) {
        mergeHelper(tempP->next, l1);
    }
    else {
        mergeHelper(tempP->next, l2);
    }
    tempP = tempP->next;
  }
  return (temp.next);
}
