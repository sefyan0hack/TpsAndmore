#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

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
int list_size(list lst){
    if(lst == NULL) return -1;

    int count = 0;
    Node * curr = lst;
    while (curr != NULL)
    {
        count++;
        curr = curr->next;
    }

    return count;
}
Node* list_at(list lst, int index){
    assert(index >= 0);

    if(index >= list_size(lst)) return NULL;

    int i = 0;
    Node * curr = lst;
    while (curr != NULL)
    {
        if(i++ == index) break;
        curr = curr->next;
    }

    return curr;
}
void push_back(list * lst, Poly monom){
    assert(lst != NULL);
    Node *newNode = malloc(sizeof(Node));
    newNode->data.cof = monom.cof;
    newNode->data.exp = monom.exp;
    newNode->next = NULL;

    if (*lst == NULL) {
        *lst = newNode;
    }else {
        Node *curr = *lst;

        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
}

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

list list_copy(list lst){
    list newL = NULL;
    if(lst == NULL){
        return newL;
    }

    Node * curr = lst;
    while (curr != NULL)
    {
        Poly new = {curr->data.cof, curr->data.exp};
        push_back(&newL, new);
        curr = curr->next;
    }
    return newL;
}

list polynme_add(list l, list r){
    list new = NULL;
    if(l == NULL || r == NULL) return new;

    int lsize = list_size(l);
    int rsize = list_size(r);

    if( lsize == 0 ) return list_copy(r);
    if( rsize == 0 ) return list_copy(l);

    Node * curr = l;
    for(int i = 0; i < max(lsize, rsize) ; i++){
        float l_cof_i = 0.0f;

        float r_cof_i = 0.0f;

        Node* l_i = list_at(l, i);
        Node* r_i = list_at(r, i);

        if(l_i){
            l_cof_i = l_i->data.cof;
        }
        if(r_i){
            r_cof_i = r_i->data.cof;
        }

        Poly n = { l_cof_i + r_cof_i, max(lsize, rsize) - i};
        push_back(&new, n);
    }
    return new;
}
list derive(list lst){
    list new = NULL;
    if(lst == NULL ) return new;

    int lst_size = list_size(lst);

    for (int i = 0; i < lst_size ; i++)
    {
        Node * curr = list_at(lst, i);
        Poly n = { curr->data.cof * curr->data.exp, curr->data.exp - 1};
        push_back(&new, n);
    }

    return new;
}
int main(){
    Poly a = {1,1}, b = {1,2}, c = {1,3};
    list my_polynom = NULL;
    list cpy = NULL;

    Poly n = { 10, 10};
    saisie_monom(&a);
    saisie_monom(&b);
    saisie_monom(&c);

    ajoute(&my_polynom, a);
    ajoute(&my_polynom, b);
    ajoute(&my_polynom, c);

    print(my_polynom);

    printf("-----------------------\n");
    cpy = list_copy(my_polynom);
    print(cpy);
    printf("-----------------------\n");

    print(polynme_add(my_polynom, cpy));
    print(derive(my_polynom));
    return 0;
}