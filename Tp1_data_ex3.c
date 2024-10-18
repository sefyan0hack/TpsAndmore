#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define TAB_SIZE 10

typedef struct 
{
    char* nom;
    int age;
} donnee;

typedef struct maillon{
    donnee *data;
    struct maillon * svt;
} maillon, *liste;

void insert_debuit(liste l, const char* nom, int age){
    donnee * n = malloc(sizeof(donnee));
    
    n->age = age;
    n->nom = strdup(nom);

    if(l == NULL){
        l = n;
        l->svt = NULL;
    }
    else{
        maillon *t = l->svt;

    }
}