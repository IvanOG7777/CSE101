//
// Created by elder on 3/31/2026.
//

#include "List.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct NodeObj {
    ListElement data;
    struct NodeObj *next;
    struct NodeObj *prev;
} NodeObj;

typedef NodeObj *Node;

typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int index;
    int length;
} ListObj;


Node newNode(ListElement data) {
    Node newNode = malloc(sizeof(NodeObj));

    assert(newNode != NULL);

    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void freeNode(Node *pN) {
    if (pN == NULL) {
        fprintf(stderr, "Node Error: freeNode(): NULL node reference\n");
        exit(EXIT_FAILURE);
    }
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

List newList() {
    List newList = malloc(sizeof(ListObj));

    assert(newList != NULL);

    newList->front = NULL;
    newList->back = NULL;
    newList->cursor = NULL;
    newList->length = 0;
    newList->index = -1;

    return newList;
}

void freeList(List *pL) {
    if (pL == NULL) {
        fprintf(stderr, "List Error: freeList(): NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    if (*pL == NULL) {
        return;
    }

    Node current = (*pL)->front;
    int freeCount = 0;

    while (current != NULL) {
        Node temp = current->next;
        freeNode(&current);
        current = temp;
        freeCount++;
    }

    if (pL != NULL && *pL != NULL) {
        free(*pL);
        *pL = NULL;
    }
}

int length(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: length(): NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    return L->length;
}

int position(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: position(): NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->index == -1) {
        return -1;
    }
    return L->index;
}

ListElement front(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: front(): NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}

ListElement back(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: back(): NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    return L->back->data;
}

ListElement get(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: get(): NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    return L->cursor->data;
}

bool equals(List A, List B) {
    if (A == NULL) {
        fprintf(stderr, "List Error: equals(): NULL A list reference\n");
        exit(EXIT_FAILURE);
    }

    if (B == NULL) {
        fprintf(stderr, "List Error: equals(): NULL B list reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(A) != length(B)) return false;

    int positionA = position(A);
    int positionB = position(B);

    moveFront(A);
    moveFront(B);

    while (position(A) >= 0 && position(B) >= 0) {
        if (get(A) != get(B)) {
            return false;
        }
        moveNext(A);
        moveNext(B);
    }

    if (positionA >= 0) {
        moveFront(A);
        for (int i = 0; i < positionA; i++) {
            moveNext(A);
        }
    }

    if (positionB >= 0) {
        moveFront(B);
        for (int i = 0; i < positionB; i++) {
            moveNext(B);
        }
    }
    return true;
}

void clear(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: clear(): NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    Node current = L->front;
    while (current != NULL) {
        Node temp = current->next;
        freeNode(&current);
        current = temp;
    }

    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;
}

void set(List L, ListElement x) {
    if (L == NULL) {
        fprintf(stderr, "List Error: set(): NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) > 0 && position(L) >= 0) {
        L->cursor->data = x;
    } else {
        return;
    }
}

void moveFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: moveFront(): NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->length <= 0) {
        return;
    }
    L->cursor = L->front;
    L->index = 0;
}

void moveBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: moveBack(): NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->length <= 0) {
        printf("List is empty\n");
        return;
    }

    L->cursor = L->back;
    L->index = L->length - 1;
}

void movePrev(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: movePrev(): NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor == NULL) {
        printf("Lists cursor is NULL returning early\n");
        return;
    }

    if (L->cursor == L->front && L->index == 0) {
        L->cursor = NULL;
        L->index = -1;
        return;
    }
    if (L->index >= 0 && L->cursor != L->front) {
        L->cursor = L->cursor->prev;
        L->index--;
        printf("Moved cursor back once\n");
    }
}

void moveNext(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: moveNext(): NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor == NULL) {
        printf("Lists cursor is NULL, returning early\n");
        return;
    }

    if (L->cursor == L->back) {
        L->cursor = NULL;
        L->index = -1;
        return;
    }

    if (L->index >= 0 && L->cursor != L->back) {
        L->cursor = L->cursor->next;
        L->index++;
    }
}

void prepend(List L, ListElement data) {
    if (L == NULL) {
        fprintf(stderr, "List Error: prepend(): NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    Node nNode = newNode(data);

    if (L->length == 0) {
        L->front = nNode;
        L->back = nNode;
        L->length++;
        return;
    }

    Node temp = L->front;
    L->front = nNode;
    L->front->next = temp;
    temp->prev = L->front;
    L->length++;

    if (L->cursor != NULL) {
        L->index++;
    }
}

void append(List L, ListElement data) {
    if (L == NULL) {
        fprintf(stderr, "List Error: append(): NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    Node nNode = newNode(data);

    if (L->length == 0) {
        L->front = nNode;
        L->back = nNode;
        L->length++;
        return;
    }

    Node temp = L->back;
    L->back = nNode;
    L->back->prev = temp;
    temp->next = L->back;
    L->length++;
}

void insertBefore(List L, ListElement data) {
    if (L == NULL) {
        fprintf(stderr, "List Error: insertBefore(): NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor == NULL) {
        fprintf(stderr, "List Error: insertBefore(): cursor is undefined\n");
        exit(EXIT_FAILURE);
    }

    if (L->index == 0) {
        prepend(L, data);
        return;
    }

    Node nNode = newNode(data);
    Node beforeCursor = L->cursor->prev;

    nNode->prev = beforeCursor;
    nNode->next = L->cursor;
    beforeCursor->next = nNode;
    L->cursor->prev = nNode;

    L->length++;
    L->index++;
}

void insertAfter(List L, ListElement data) {
    if (L == NULL) {
        fprintf(stderr, "List Error: insertAfter(): NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    Node nNode = newNode(data);

    if (L->cursor == L->back) {
        Node tempBack = L->back;
        tempBack->next = nNode;
        nNode->prev = tempBack;
        L->back = nNode;
    } else {
        Node afterCursor = L->cursor->next; // holds all nodes after cursor
        L->cursor->next = nNode;
        nNode->prev = L->cursor;
        nNode->next = afterCursor;
        afterCursor->prev = nNode;
    }
    L->length++;
}

void deleteFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: deleteFront(): NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->length == 1) {
        freeNode(&L->front);
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->length = 0;
        L->index = -1;
        return;
    }

    if (L->length > 1) {
        Node newFront = L->front->next;
        Node tempFront = L->front;

        freeNode(&L->front);

        L->front = newFront;
        L->front->prev = NULL;
        L->length--;

        if (L->cursor == tempFront) {
            L->cursor = NULL;
            L->index = -1;
        } else if (L->cursor != NULL) {
            L->index--;
        }
    }
}


void deleteBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: deleteBack(): NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->length == 1) {
        freeNode(&L->front);
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->length = 0;
        L->index = -1;
        return;
    }

    if (L->length > 1) {
        Node newBack = L->back->prev;
        Node tempBack = L->back;

        freeNode(&L->back);

        L->back = newBack;
        L->back->next = NULL;
        L->length--;

        if (L->cursor == tempBack) {
            L->cursor = NULL;
            L->index = -1;
        }
    }
}

void delete(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: delete(): NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor == NULL) {
        return;
    }

    if (L->length == 1 && L->index == 0) {
        freeNode(&L->cursor);
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->length = 0;
        L->index = -1;
        return;
    }

    if (L->cursor == L->front) {
        Node newFront = L->front->next;
        newFront->prev = NULL;
        freeNode(&L->cursor);

        L->front = newFront;
        L->cursor = NULL;
        L->index = -1;
        L->length--;
        return;
    }


    if (L->cursor == L->back) {
        Node newBack = L->back->prev;
        newBack->next = NULL;

        freeNode(&L->cursor);

        L->back = newBack;
        L->cursor = NULL;
        L->index = -1;
        L->length--;
        return;
    }

    Node beforeCursor = L->cursor->prev;
    Node afterCursor = L->cursor->next;

    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;

    freeNode(&L->cursor);
    L->cursor = NULL;
    L->index = -1;
    L->length--;
}

void printList(FILE *out, List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: printList(): NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    if (out == NULL) {
        fprintf(stderr, "FILE* Error: printList(): NULL FILE reference\n");
        exit(EXIT_FAILURE);
    }

    fputc('(', out);

    moveFront(L);
    while (position(L) >= 0) {
        if (position(L) == length(L) - 1) {
            fprintf(out, "%d", get(L));
        } else {
            fprintf(out, "%d, ", get(L));
        }
        moveNext(L);
    }

    fprintf(out, ")");
}

List copyList(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: copyList(): NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    List nList = newList();

    assert(nList != NULL);

    int oldPosition = position(L);
    Node oldCursor = L->cursor;

    moveFront(L);
    while (position(L) >= 0) {
        append(nList, get(L));
        moveNext(L);
    }

    L->index = oldPosition;
    L->cursor = oldCursor;

    return nList;
}

List join(List A, List B) {
    if (A == NULL) {
        fprintf(stderr, "List Error: joinList(): NULL list A reference\n");
        exit(EXIT_FAILURE);
    }

    if (B == NULL) {
        fprintf(stderr, "List Error: joinList(): NULL list B reference\n");
        exit(EXIT_FAILURE);
    }

    List nList = newList();

    assert(nList != NULL);

    int oldCursorAPosition = position(A);
    int oldCursorBPosition = position(B);

    Node oldCursorANode = A->cursor;
    Node oldCursorBNode = B->cursor;

    moveFront(A);
    moveFront(B);

    while (position(A) >= 0) {
        append(nList, get(A));
        moveNext(A);
    }

    while (position(B) >= 0) {
        append(nList, get(B));
        moveNext(B);
    }


    A->index = oldCursorAPosition;
    A->cursor = oldCursorANode;

    B->index = oldCursorBPosition;
    B->cursor = oldCursorBNode;

    return nList;
}

List split(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: split(): NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    List nList = newList();

    assert(nList != NULL);

    while (position(L) > 0) {
        append(nList, front(L));
        deleteFront(L);
    }

    return nList;
}
