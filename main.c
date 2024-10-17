#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct Node {
    int data;
    struct Node* next;
} Node;
typedef Node* List;

void inssert_debut(List* list ,int data){
    Node* n = (Node*) malloc(sizeof(Node));
    n->data = data;
    
    if(list == NULL){
        *list = n;
        (*list)->next = NULL;
    }else{
        Node* tmp = *list;
        *list = n;
        (*list)->next = tmp;
    }
}

void inssert_fin(List* list ,int data){
    Node* n = (Node*) malloc(sizeof(Node));
    n->data = data;
    n->next = NULL;

    Node * cu = *list;
    while (cu->next != NULL)
        cu = cu->next;
    
    cu->next = n;
}

void inssert_avant(List* list, unsigned int elem, int data){
    Node* n = (Node*) malloc(sizeof(Node));
    n->data = data;

    if (elem == 0) {
        n->next = *list;
        *list = n;
        return;
    }

    Node * cu = *list;
    for (unsigned int i = 0; i < elem -1; i++)
    {
        assert(cu != NULL);
        cu = cu->next;
    }
    n->next = cu->next;
    cu->next = n;
}

void inssert_apres(List* list, unsigned int elem, int data){
    Node* n = (Node*) malloc(sizeof(Node));
    n->data = data;

    Node * cu = *list;
    for (unsigned int i = 0; i < elem; i++)
    {
        assert(cu != NULL);
        cu = cu->next;
    }
    Node * tmp = cu->next ;
    cu->next = n;
    n->next = tmp;
}
void print(List list){
    Node * cu = list;
    while (cu != NULL)
    {
        printf(" %d ", cu->data);
        cu = cu->next;
    }
    printf("\n");
}

int main(){
    List malist = NULL;
    inssert_debut(&malist, 20);
    inssert_fin(&malist,10);
    inssert_fin(&malist,100);
    inssert_debut(&malist, 200);
    inssert_avant(&malist, 2, 90);
    inssert_apres(&malist, 10, 900);

    print(malist);
    return 0;
}