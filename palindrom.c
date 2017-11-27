//
// Created by Omer on 27/11/2017.
//

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node_t *Node;

struct node_t {
    int data;
    Node next;
};

int countElements(Node head) {
    if (head == NULL) return 0;
    Node element = head->next;
    int amount_of_elements = 1;
    while (element != NULL) {
        amount_of_elements++;
        element = element->next;
    }
    return amount_of_elements;
}

void checkIfPalindrom(Node *node1, Node node2, int number_elements, int *
result) {
    if (number_elements == 0) {
        *result = 1;
        return;
    }

    // getting to end of the end of the list
    checkIfPalindrom(node1, node2->next, number_elements - 1, result);

    // compares recursivly with node1 and does head++
    if ((*node1)->data == node2->data && *result) {
        *node1 = (*node1)->next;
        return;
    }
    *result = 0;

}

bool isPalindrome(Node head) {
    if (head->next == NULL) return true;
    Node p2 = head;
    Node *p1 = &head;
    int result;
    checkIfPalindrom(p1, p2, countElements(head), &result);
    if (result == 0) return false;
    else return true;
}

int main() {

    struct node_t node1;
    struct node_t node2;
    struct node_t node3;
    struct node_t node4;
    struct node_t node5;
    struct node_t node6;

    node1.data = 1;
    node1.next = &node2;

    node2.data = 1;
    node2.next = &node3;

    node3.data = 11;
    node3.next = &node4;

    node4.data = 11;
    node4.next = &node5;

    node5.data = 1;
    node5.next = &node6;

    node6.data = 1;
    node6.next = NULL;

    int result = isPalindrome(&node1);
    printf("%d", result);

    return 0;
}