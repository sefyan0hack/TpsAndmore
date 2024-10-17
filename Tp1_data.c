#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct  Poly
{
    float cof;
    int exp;
} Poly;

typedef struct Node
{
    Poly data;
    struct Node* next;
} Node;
typedef Node* list;

void ajoute(list *lst, Poly monom) {
    assert(lst != NULL);

    Node *newNode = malloc(sizeof(Node));
    newNode->data.cof = monom.cof;
    newNode->data.exp = monom.exp;
    newNode->next = NULL;

    if (*lst == NULL) {
        *lst = newNode;
    } else {
        Node *preCurr = NULL;
        Node *curr = *lst;

        while (curr != NULL && curr->data.exp > newNode->data.exp) {
            preCurr = curr;
            curr = curr->next;
        }

        if (curr != NULL && curr->data.exp == newNode->data.exp) {
            curr->data.cof += newNode->data.cof;
            free(newNode);
        } else {
            if (preCurr == NULL) {
                newNode->next = *lst;
                *lst = newNode;
            } else {
                preCurr->next = newNode;
                newNode->next = curr;
            }
        }
    }
}

void print(list lst){
    Node * cu = lst;
    while (cu != NULL)
    {
        printf(" %.2f x^%d", cu->data.cof, cu->data.exp);
        if(cu->next != NULL) printf(" + ");
        cu = cu->next;
    }
    printf("\n");
}

void saisie_monom(Poly* mono){
    printf("\nEnter Monom :\n");
    printf("a = ");
    scanf("%f", &mono->cof);
    printf("\nexp = ");
    scanf("%d", &mono->exp);
}

int main(){
    Poly a, b, c;
    list my_polynom;

    saisie_monom(&a);
    saisie_monom(&b);
    saisie_monom(&c);

    ajoute(&my_polynom, a);
    ajoute(&my_polynom, b);
    ajoute(&my_polynom, c);

    print(my_polynom);

    return 0;
}