#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct DLL
{
    int data;
    struct DLL *next;
    struct DLL *prev;
}Node;

void add_begin(Node **);
void add_end(Node **);
void print_records(Node *);
void delete_node(Node **);
void delete_all(Node **);
// void insert_pos(Node **);
void reverse_data(Node *);
// void sort_data(Node *);
// void reverse_link(Node **);
void traverse_reverse(Node *);

int main(){
    int option;
    Node *headptr = 0;

    for(;;){
        printf("Enter an option 15 to exit\n");
        printf("1. add begin\n2. add end\n3. add middle\n4. insert pos\n5. reverse data\n6. traverse reverse\n7. reverse using swap\n8. sort data\n9. count\n10. Print records\n11. Delete all\n15. Exit\n");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            add_begin(&headptr);
            break;
        case 2: add_end(&headptr);
            break;
        case 6: traverse_reverse(headptr);
            break;
        case 7: reverse_data(headptr);
            break;
        case 10:
            print_records(headptr);
            break;
        case 11:
            delete_all(&headptr);
        case 12:
            delete_node(&headptr);
            break;
        default:
            break;
        }
    }
}
int count(Node *hptr){
    int count = 0;
    if(hptr == 0){
        return 0;
    }
    while(hptr){
        count++;
        hptr = hptr->next;
    }
    return count;
}
void reverse_data(Node *hptr){
    if(hptr == 0){
        printf("Nothing to print\n");
        return;
    }
    Node *ptr1, *ptr2;
    ptr2 = hptr;
    ptr1 = hptr;

    int c = count(hptr);
    //moves the pointer to the last node
    while(ptr2->next){
        ptr2 = ptr2->next;
    }
    for(int i = 0; i < c/2; i++){
        int temp = ptr1->data;
        ptr1->data = ptr2->data;
        ptr2->data = temp;
        ptr1 = ptr1->next;
        ptr2 = ptr2->prev;
    }

}
void add_begin(Node **hptr) {
    Node *new = (Node*)malloc(sizeof(Node));
    if (new == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    printf("Enter a number to add at the beginning\n");
    scanf("%d", &new->data);

    new->prev = NULL;
    new->next = *hptr;

    if (*hptr != NULL) {
        (*hptr)->prev = new;
    }

    *hptr = new;
}

void print_records(Node *hptr){
    if(hptr == 0){
        printf("There are no records to print\n");
        return;
    }

    while(hptr){
        printf("%d\t", hptr->data);
        hptr = hptr -> next;
    }
    printf("\n");

}
void traverse_reverse(Node *hptr){
    if(hptr == 0){
        printf("Nothing to print\n");
        return;
    }
    while(hptr->next){
        hptr = hptr->next;
    }

    while(hptr){
        printf("%d\t", hptr->data);
        hptr = hptr->prev;
    }
    printf("\n");
}

void add_end(Node **hptr){
    Node *new = NULL;
    new = malloc(sizeof(Node));
    printf("Enter the number to add at the end\n");
    scanf("%d", &new->data);
    new->next = 0;
    if(*hptr == 0){
        new->prev = 0;
        (*hptr) = new;
        return;
    }
    Node *temp = *hptr;
    while(temp->next){
        temp = temp->next;
    }
    temp->next = new;
    new->prev = temp;
}

void delete_all(Node **hptr){
    if(*hptr == 0){
        printf("No records to print\n");
        return;
    }

    Node *temp =0;

    while(*hptr){
        temp = *hptr;
        *hptr = (*hptr)->next;
        free(temp);
    }
}

void delete_node(Node **hptr) {
    if (*hptr == NULL) {
        printf("No records to delete\n");
        return;
    }

    printf("Enter a number you want to delete\n");
    int num = 0;
    scanf("%d", &num);

    Node *temp = *hptr;

    // Case 1: Deleting the first node
    if (temp->data == num) {
        *hptr = temp->next;  // Move head pointer
        if (*hptr != NULL) {  // Check before accessing prev
            (*hptr)->prev = NULL;
        }
        free(temp);
        return;
    }

    // Traverse the list to find the node
    while (temp != NULL && temp->data != num) {
        temp = temp->next;
    }

    // Case 2: Node not found
    if (temp == NULL) {
        printf("No records found\n");
        return;
    }

    // Case 3: Node found in the middle or at the end
    if (temp->next != NULL) {  // If it's NOT the last node
        temp->next->prev = temp->prev;
    }

    if (temp->prev != NULL) {  // If it's NOT the first node
        temp->prev->next = temp->next;
    }

    free(temp);
}
