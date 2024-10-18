#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define TAB_SIZE 10

typedef struct Node
{
    int val;
    int col;
    struct Node* next;
} Node;

typedef Node* list;

void push_back(list * lst, Node monom){
    assert(lst != NULL);
    Node *newNode = malloc(sizeof(Node));
    newNode->col = monom.col;
    newNode->val = monom.val;
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
//i * col + j
list * creuse_Mat(int* mat, int col, int row){
    list* Mat = malloc(sizeof(list) * row);
    for (int i = 0; i < row; i++)
    {
        Mat[i] = NULL;
    }
    
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if(mat[i * col + j] != 0){
                Node n;
                n.val = mat[i * col + j];
                n.col = j;
                push_back(&Mat[i], n);
            }
        }
        
    }
    return Mat;
}
void print(list lst){
    Node * cu = lst;
    static int i = 0;
    while (cu != NULL)
    {
        printf(" [%d][%d] = %d  ", i, cu->col, cu->val);
        cu = cu->next;
    }
    printf("\n");
    i++;
}
int main(){

    int m[3][3] = {
        {0,1,1},
        {0,1,0},
        {1,2,0}
    };
    list * newM = creuse_Mat(&m[0][0], 3, 3);

    for (int i = 0; i < 3; i++)
    {
        print(newM[i]);
        printf("\n");
    }
    

}