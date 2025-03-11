#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct SLL     
{
    int data;
    struct SLL *next;
}Node;
void add_begin(Node **);
void add_end(Node **);
void add_middle(Node **);
void reverse_data(Node *);
void print_reverse_recursion(Node *);
void print_reverse_loops(Node *);
void sort_data(Node *);
void print_records(Node *);
int count_records(Node *);
void insert_pos(Node**, int);
void deleteAllNodes(Node **hptr);

int main(void){
    int option;
    Node *headPtr = 0;
    

    while (1)
    {
        printf("Enter an option 15 to exit\n");
        printf("1. add begin\n2. add end\n3. add middle\n4. insert pos\n5. reverse data\n6. print reverse recursion\n7. print reverse loop\n8. sort data\n9. count\n10. Print records\n15. Exit\n");
        scanf("%d", &option);

        switch(option){
        case 1: add_begin(&headPtr);
            break;
        case 2: add_end(&headPtr);
            break;
        case 3: add_middle(&headPtr);
            break;
        case 4: 
            
            printf("Enter the position\n");
            int pos = 0;
            scanf("%d", &pos);
            insert_pos(&headPtr, pos);
            break;
        case 5: reverse_data(headPtr);
            break;
        case 6: print_reverse_recursion(headPtr);
            break;
        case 7: print_reverse_loops(headPtr);
            break;
        case 8: sort_data(headPtr);
            break;
        case 9: 
                
                count_records(headPtr);
                
            break;
        case 10: print_records(headPtr);
            break;
        case 15: exit(0);
                break;
        default: exit(0);
            break;
        }   
    }
    
}

void add_begin(Node **hptr){
    Node *new;
    new = malloc(sizeof(Node));
    scanf("%d", &new->data);
    new->next = (*hptr);
    (*hptr) = new;
}

void deleteAllNodes(Node **hptr){
    Node *ptr;
    if(*hptr == 0){
        printf("No records to delete\n");
        return;
    }
    while(ptr){
        ptr = *hptr;
        *hptr = (*hptr)->next;
        free(hptr);
    }
}
void deleteSingleNode(Node **hptr) {
    if (*hptr == NULL) {  
        printf("List is empty.\n");
        return;
    }

    Node *ptr = *hptr;
    Node *prev = NULL;
    int num = 0;

    printf("Enter the number which you want to delete\n");
    scanf("%d", &num);

    if (ptr->data == num) {
        *hptr = ptr->next;  // Update head pointer
        free(ptr);
        printf("Node with value %d deleted.\n", num);
        return;
    }

    while (ptr != NULL && ptr->data != num) {
        prev = ptr;
        ptr = ptr->next;
    }

    if (ptr == NULL) {
        printf("Node with value %d not found.\n", num);
        return;
    }

    prev->next = ptr->next;
    free(ptr);
    printf("Node with value %d deleted.\n", num);
}

void print_records(Node *hptr){
    if(hptr == 0){
        printf("No records\n");
        return;
    }

    while(hptr){
        printf("%d\n", hptr->data);
        hptr = hptr->next;
    }
}
void add_end(Node **hptr){
    printf("Enter a number to add at the end\n");
    Node *new = malloc(sizeof(Node));
    scanf("%d", &new->data);
    if(*hptr == 0){
        new->next = *hptr;
        (*hptr) = new;
        return;
    }
    Node *curr = *hptr;
    while(curr->next){
        curr = curr->next;
    }
    new->next = 0;
    curr->next = new;
}
void reverseData(Node *hptr){
    Node *ptr1, *ptr2;
    Node temp;

    ptr1 = ptr2 = hptr;
    if(hptr == NULL){
        printf("Nothing to swap\n");

    }

    int c = count_records(hptr);
    for(int i = 0; i < c/2; i++){
        ptr1 = hptr;
        for(int j = 0; j < c - i; j++){
            ptr2 = ptr2->next;
        }
        int temp = ptr1->data;
        ptr1->data = ptr2->data;
        ptr2->data = temp;

        ptr1 = ptr1->next;

    }

}
//also called sorted entry of nodes
void add_middle(Node **hptr){
    Node *new = malloc(sizeof(Node));
    printf("Enter the number create a sorted linked list\n");
    scanf("%d", &new->data);
    if(*hptr == 0 || (new->data < (*hptr)->data)){
        new->next = *hptr;
        *hptr = new;
        return;
    }
    Node *curr = *hptr;
    curr = curr->next;
    while((curr->next != 0) && (new->data > curr->next->data)){
        curr = curr->next;
    }
    new->next = curr->next;
    curr->next = new;
}
void reverse_data(Node *hptr){
    if(hptr == 0){
        printf("no records to reverse\n");
        return;
    }
    int c = count_records(hptr);
    Node *ptr1, *ptr2, temp;
    ptr1 = ptr2 = hptr;

    for(int i = 0; i < c/2; i++){
        for(int j = 0; j < c - i - 1; j++){
            ptr2 = ptr2->next;
        }
        //swap
        temp.data = ptr1->data;
        ptr1->data = ptr2->data;
        ptr2->data = temp.data;

        ptr2 = hptr;
        ptr1 = ptr1->next;
    }

}
void print_reverse_recursion(Node *hptr){
    if(hptr == 0){
        printf("No records to print\n");
        return;
    }
    print_reverse_recursion(hptr->next);
    printf("%d\n", hptr->data);
}
void print_reverse_loops(Node *hptr){
    Node *curr = hptr;
    if(hptr == 0){
        printf("No record to print in reverse loops\n"); return;
    }
    int c = count_records(hptr);
    for(int i = 0; i < c; i ++){
        for(int j = 0; j < c - i - 1; j++){
            curr = curr->next;
        }
        printf("%d\n", curr->data);
        curr = hptr;
    }
}
void sort_data(Node *hptr){
    if(hptr == 0){
        printf("No records to sort\n");
        return;
    }
    Node *ptr1, *ptr2, temp; 
    int c = count_records(hptr);
    ptr1 = ptr2 = hptr;
    for(int i = 0; i < c - 1; i++){
        ptr2 = ptr1->next;
        for(int j = 0; j < c - i - 1;j++){
            if(ptr1->data > ptr2->data){
                temp.data = ptr1->data;
                ptr1->data = ptr2->data;
                ptr2->data = temp.data;
            }
            ptr2 = ptr2->next;
        }
        //ptr2 = ptr1;
        ptr1 = ptr1->next;
    }
}
int count_records(Node *hptr){
    int count = 0;
    while(hptr){
        count++;
        hptr = hptr->next;
    }
    printf("Number of nodes = %d\n", count);
    return count;
}
void insert_pos(Node** hptr, int pos){

}