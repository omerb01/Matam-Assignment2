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

int getLength(Node head) {
    int result = 0;
    while (head != NULL) {
        result++;
        head = head->next;
    }

    return result;
}

bool isPalindrome(Node head) {
    if(head == NULL) return true;

    int n = getLength(head);

    Node p1 = head;
    Node p2 = head->next;
    Node temp;

    int i;
    if (n % 2 == 1) i = 0;
    else i = 1;

    while (i < n / 2) {
        temp = p2->next;
        p2->next = p1;
        p1 = p2;
        p2 = temp;
        i++;
    }
    if (n % 2 == 1) p1 = p1->next;

    while (p1 != NULL && p2 != NULL) {
        if (p1->data != p2->data) return false;
        p1 = p1->next;
        p2 = p2->next;
    }

    return true;
}

int main() {

    struct node_t node1;
    struct node_t node2;
    struct node_t node3;
    struct node_t node4;
    struct node_t node5;
    struct node_t node6;

    node1.data = 11;
    node1.next = &node2;

    node2.data = 11;
    node2.next = &node3;

    node3.data = 121;
    node3.next = &node4;

    node4.data = 12;
    node4.next = &node5;

    node5.data = 11;
    node5.next = &node6;

    node6.data = 11;
    node6.next = NULL;

    int result = isPalindrome(&node1);
    printf("%d", result);

    return 0;
}