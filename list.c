#include <stdio.h> 
#include <stdlib.h> 


typedef struct Node{
    int data;
    struct Node* next;
} Node;


Node* create_ll(Node* head); 
Node* display(Node* head); 
Node* insert_beg(Node* head); 
Node* insert_end(Node* head); 
Node* insert_before(Node* head); 
Node* insert_after(Node* head); 
Node* delete_beg(Node* head); 
Node* delete_end(Node* head); 
Node* delete_node(Node* head); 
Node* delete_after(Node* head); 
Node* delete_list(Node* head); 
Node* sort_list(Node* head);

int main(int argc, char *argv[]) {
    Node* start = NULL;
    int option;
    do {
      printf("\n\n *****MAIN MENU *****");
      printf("\n 1:  Create a list");
      printf("\n 2:  Display the list");
      printf("\n 3:  Add a node at the beginning");
      printf("\n 4:  Add a node at the end");
      printf("\n 5:  Add a node before a given node");
      printf("\n 6:  Add a node after a given node");
      printf("\n 7:  Delete a node from the beginning");
      printf("\n 8:  Delete a node from the end");
      printf("\n 9:  Delete a given node");
      printf("\n 10: Delete a node after a given node");
      printf("\n 11: Delete the entire list");
      printf("\n 12: Sort the list");
      printf("\n 13: EXIT");
      printf("\n\n Enter your option : "); 
      scanf("%d", &option);
      switch(option){
         case 1: start = create_ll(start);
            printf("\n LINKED LIST CREATED");
            break;
         case 2: start = display(start);
            break;
         case 3: start = insert_beg(start);
            break;
         case 4: start = insert_end(start);
            break;
         case 5: start = insert_before(start);
            break;
         case 6: start = insert_after(start);
            break;
         case 7: start = delete_beg(start);
            break;
         case 8: start = delete_end(start);
            break;
         case 9: start = delete_node(start);
            break;
         case 10: start = delete_after(start);
            break;
         case 11: start = delete_list(start);
            printf("\n LINKED LIST DELETED");
         break;
            case 12: start = sort_list(start);
         break; 
      }
   } while(option !=13); 
   return 0;
}

Node* create_ll(Node* head){
   Node* new_node, *ptr; 
   int num;
   printf("\n Enter -1 to end"); 
   printf("\n Enter the data : "); 
   scanf("%d", &num); 
   while(num!=-1){
      new_node = (Node* head)malloc(sizeof(Node)); 
      new_node->data=num;
      if(head==NULL){
         new_node->next = NULL; 
         head = new_node;
      } 
      else {
         ptr=head;
         while(ptr->next!=NULL) 
            ptr=ptr->next; 
         ptr->next = new_node; 
         new_node->next=NULL;
      }
      printf("\n Enter the data : ");
      scanf("%d", &num);
   }
   return head;
}

Node* display(Node* head){
   Node* ptr; ptr = head; 
   while(ptr != NULL) {
      printf("\t %d", ptr->data); 
      ptr = ptr->next;
   }
   return head;
}

Node* insert_beg(Node* head){
   Node* new_node;
   int num;
   printf("\n Enter the data : ");
   scanf("%d", &num);
   new_node = (Node* head)malloc(sizeof(Node)); 
   new_node->data = num;
   new_node->next = head;
   head = new_node;
   return head;
}

Node* insert_end(Node* head){
   Node* ptr, *new_node;
   int num;
   printf("\n Enter the data : ");
   scanf("%d", &num);
   new_node = (Node* head)malloc(sizeof(Node)); 
   new_node->data = num;
   new_node->next = NULL;
   ptr = head;
   while(ptr->next != NULL) 
      ptr = ptr->next;
   ptr->next = new_node; 
   return head;
}

Node* insert_before(Node* head){
   Node* new_node, *ptr, *preptr;
   int num, val;
   printf("\n Enter the data : ");
   scanf("%d", &num);
   printf("\n Enter the value before which the data has to be inserted : "); 
   scanf("%d", &val);
   new_node = (Node* head)malloc(sizeof(Node));
   new_node->data = num;
   ptr = head;
   while(ptr->data != val) {
      preptr = ptr;
      ptr = ptr->next;
   }
   preptr->next = new_node; 
   new_node->next = ptr; 
   return head;
}

Node* insert_after(Node* head){
   Node* new_node, *ptr, *preptr;
   int num, val;
   printf("\n Enter the data : ");
   scanf("%d", &num);
   printf("\n Enter the value after which the data has to be inserted : "); 
   scanf("%d", &val);
   new_node = (Node* head)malloc(sizeof(Node));
   new_node->data = num;
   ptr = head;
   preptr = ptr;
   while(preptr->data != val) {
      preptr = ptr;
      ptr = ptr->next;
   }
   preptr->next=new_node; 
   new_node->next = ptr; 
   return head;
}

Node* delete_beg(Node* head){
   Node* ptr;
   ptr = head;
   head = head->next; 
   free(ptr);
   return head;
}

Node* delete_end(Node* head){
   Node* ptr, *preptr; 
   ptr = head;
   while(ptr->next != NULL) {
      preptr = ptr;
      ptr = ptr->next;
   }
   preptr->next = NULL; 
   free(ptr);
   return head;
}

Node* delete_node(Node* head){
   Node* ptr, *preptr;
   int val;
   printf("\n Enter the value of the node which has to be deleted : "); scanf("%d", &val);
   ptr = head;
   if(ptr->data == val){
      head = delete_beg(head); 
      return head;
   } else {
      while(ptr->data != val){
         preptr = ptr;
         ptr = ptr->next;
      }
      preptr->next = ptr->next; 
      free(ptr);
      return head;
   }
}

Node* delete_after(Node* head){
   Node* ptr, *preptr;
   int val;
   printf("\n Enter the value after which the node has to deleted : "); 
   scanf("%d", &val);
   ptr = head;
   preptr = ptr;
   while(preptr->data != val){
      preptr = ptr;
      ptr = ptr->next;
   }
   preptr->next=ptr->next; 
   free(ptr);
   return head;
}

Node* delete_list(Node* head){
   Node* ptr;
   if(head!=NULL){ 
      ptr=head;
      while(ptr != NULL){
         printf("\n %d is to be deleted next", ptr->data); head = delete_beg(ptr);
         ptr = head;
      }
   }
   return head;
}

Node* sort_list(Node* head){
   Node* ptr1, *ptr2; 
   int temp;
   ptr1 = head;
   while(ptr1->next != NULL) {
      ptr2 = ptr1->next; 
      while(ptr2 != NULL) {
         if(ptr1->data > ptr2->data) {
            temp = ptr1->data;
            ptr1->data = ptr2->data; 
            ptr2->data = temp;
         }
         ptr2 = ptr2->next;
      }
      ptr1 = ptr1->next;
   }
   return head;  // Had to be added
}
