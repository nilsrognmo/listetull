#include <stdio.h>

//Define a linked list node
typedef struct node {
    int val;
    struct node * next;
} node_t;

int main(){

    //Create a local variable which points to the first item of the list
    node_t * head = NULL;  //Declares a pointer "head" of type "node_t" and initializes it to NULL
    head = (node_t *) malloc(sizeof(node_t));  //Allocates memory for a new node using the "malloc" function. "sizeof(node_t)" calculates the size of the node_t structure
    if (head == NULL) {  //Checks if the memory allocation was successful. If head is still NULL after the malloc is asigned to the head pointer, it returns 1.
        return 1;
    }
    head->val = 3;  //Sets the "val" member of the node pointed to by "head" to 1. Assumes that node_t is a structure containing a member named "val"
    head->next = NULL; //Sets the "next" pointer of the node pointed to by "head" to "NULL". Indicates that there are currently no additional nodes in the linked list afer the head node.


    //Add another value at end of the list
    node_t * head1 = NULL;  //Declares a pointer "head" of type "node_t" and initializes it to NULL
    head1 = (node_t *) malloc(sizeof(node_t));  //Allocates memory for a new node using the "malloc" function. "sizeof(node_t)" calculates the size of the node_t structure
    if (head1 == NULL) {  //Checks if the memory allocation was successful. If head is still NULL after the malloc is asigned to the head pointer, it returns 1.
        return 1;
    }
    head1->val = 4;  //Sets the "val" member of the node pointed to by "head" to 1. Assumes that node_t is a structure containing a member named "val"
    head1->next = (node_t *) malloc(sizeof(node_t));
    head1->next->val = 5;
    head1->next->next = NULL;

    //Better way to add values to end of list. Uses a push function defined below.
    pushEnd(head1, 2);
    pushEnd(head1, 7);
    //Adds a value to the front of the list
    pushFront(&head1, 9);
    //Remove first item of the list
    pop(&head1);
    //Remove last item of the list
    remove_last(head1);
    //Remove specific item from list
    remove_by_index(&head1, 1);


    print_list(head1);


    return 0;
}


//Print list
void print_list(node_t * head) {
    node_t * current = head;

    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
}

//Better way to add value to end of list
void pushEnd(node_t * head, int val) {
    node_t * current = head;
    while (current->next != NULL) {//Iterates to end of list
        current = current->next;
    }
    //Adds a new value
    current->next = (node_t *) malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;
}

//Add value to beginning of the list
void pushFront(node_t ** head, int val) {
    node_t * new_node;
    new_node = (node_t *) malloc(sizeof(node_t));

    new_node->val = val;
    new_node->next = *head;
    *head = new_node;
}

//Remove first item of the list
int pop(node_t ** head) {
    int retval = -1;
    node_t * next_node = NULL;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}

//Remove last item of the list
int remove_last(node_t * head) {
    int retval = 0;
    /* if there is only one item in the list, remove it */
    if (head->next == NULL) {
        retval = head->val;
        free(head);
        return retval;
    }
    /* get to the second to last node in the list */
    node_t * current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    /* now current points to the second to last item of the list, so let's remove current->next */
    retval = current->next->val;
    free(current->next);
    current->next = NULL;
    return retval;
}

//Remove specific item from list
int remove_by_index(node_t ** head, int n) {
    int i = 0;
    int retval = -1;
    node_t * current = *head;
    node_t * temp_node = NULL;

    if (n == 0) {
        return pop(head);
    }

    for (i = 0; i < n-1; i++) {
        if (current->next == NULL) {
            return -1;
        }
        current = current->next;
    }

    if (current->next == NULL) {
        return -1;
    }

    temp_node = current->next;
    retval = temp_node->val;
    current->next = temp_node->next;
    free(temp_node);

    return retval;

}