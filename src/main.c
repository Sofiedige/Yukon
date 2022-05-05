#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

void QQ();
void *malloc(size_t size);


typedef struct node{
    char suit;
    char rank;
    struct node* next;
    struct node* nextInC;
    struct node* prev;
    int isVisible;
}node;

node arr[7];
struct node* head = NULL;
struct node* prevNode = NULL;
char tempDeck[104];

struct node *addFirst(char suit, char rank){
    node *newNode = malloc(sizeof (node));
    newNode->suit=suit;
    newNode->rank=rank;
    newNode->next=NULL;
    newNode->prev=NULL;
    newNode->nextInC = NULL;
    head = newNode;
    prevNode = newNode;
    return newNode;
}

struct node *addCard(char suit, char rank){
    node *newNode = malloc(sizeof (node));

    //sætter forrige nodes next til newNode
    //prevNode = head;
    prevNode->next=newNode;

    newNode->rank=rank;
    newNode->suit=suit;
    newNode->next=NULL;
    newNode->nextInC = NULL;
    newNode->prev=prevNode;

    prevNode = newNode;

    return newNode;
}

void createTempDeck(char file[]){
    FILE *in = fopen(file,"r");
    if(!in){
        printf("fejl\n");
    }
    int wordCount;
    fscanf(in,"%d ",&wordCount);

    for (int i = 0; i < wordCount; ++i) {
        fscanf(in,"%c\n",&tempDeck[i]);
    }

    for (int j = 0; j < 104; ++j) {
        if (head == NULL) {
            addFirst(tempDeck[j], tempDeck[j + 1]);
        } else {
            addCard(tempDeck[j], tempDeck[j + 1]);
        }
        j++;
    }
}

void dealCards() {
    arr[0] = *head;
    arr[0].isVisible = 1;
    node *current;

    //fills each columns head.
    for (int i = 1; i < 7; i++) {
        arr[i] = *arr[i - 1].next;
        arr[i].isVisible = 0;
    }
    arr[0].nextInC = NULL;
    node* last = &arr[6];

    for(int i = 0; i < 10; i++){
        for (int j = 1; j < 7; ++j) {
            if(i > j+3){
                continue;
            }
            current = &arr[j];
            node *temp = last->next;
            last = temp;

            while(current->nextInC != NULL){
                current = current->nextInC;
            }
            current->nextInC = temp;

            if(i >= j-1){
                current->nextInC->isVisible = 1;
            }
            else{
                current->nextInC->isVisible = 0;
            }
        }
    }
}

void print(){
    char printArr[23][100];
    memset(printArr, 0, 23*100);
    node *current = &arr[0];
    int count = 0;
    int longest = 0;
    int countNotNull = 0;
    for(int j = 0; j < 7; j++) {
        current = &arr[j];
        count = 0;
        countNotNull = 0;

        for(int i = 0; i < 22; i++){

            if (current != NULL && current->isVisible == 1) {
                sprintf(printArr[count], "%s %c%c ", printArr[count], current->suit, current->rank);
                current = current->nextInC;
                countNotNull++;
            } else if (current != NULL && current->isVisible == 0) {
                sprintf(printArr[count],"%s [] ", printArr[count]);
                current = current->nextInC;
                countNotNull++;
            } else {
                sprintf(printArr[count], "%s    ", printArr[count]);
            }
            if(countNotNull > longest)
                longest = countNotNull;
            count++;
        }
    }
    printf(" C1  C2  C3  C4  C5  C6  C7\n");
    for(int i = 0; i < 22; i++){
        if(i > longest)
            continue;
        if(i == 0){
            sprintf(printArr[i],"%s  %c%c F1", printArr[i], 't', 't');
        }
        if(i == 2){
            sprintf(printArr[i],"%s  %c%c F2", printArr[i], 't', 't');
        }
        if(i == 4){
            sprintf(printArr[i],"%s  %c%c F3", printArr[i], 't', 't');
        }
        if(i == 6){
            sprintf(printArr[i],"%s  %c%c F4", printArr[i], 't', 't');
        }
        sprintf(printArr[i],"%s\n", printArr[i]);
        printf("%s",printArr[i]);
    }
    printf("LAST COMMAND: %s\n", "Last command");
    printf("MESSAGE: %s\n", "Message");
    printf("INPUT >");

}

void SWtest() {
    int count = 0;
    node *current_node;
    for (int i = 0; i < 7; i++) {
        current_node = &arr[i];

        while (current_node != NULL) {
            count++;
            if (count > 7) {
                printf("\n%c%c ", current_node->suit, current_node->rank);
                current_node = current_node->nextInC;
                count = 1;
            } else {
                printf("%c%c ", current_node->suit, current_node->rank);
                current_node = current_node->nextInC;
            }
        }
    }
}
void SW() {
    int count = 0;
    node *current_node = head;
    while ( current_node != NULL) {
        count++;
        if(count > 7) {
            printf("\n%c%c ", current_node->suit, current_node->rank);
            current_node = current_node->next;
            count=1;
        }
        else{
            printf("%c%c ", current_node->suit, current_node->rank);
            current_node = current_node->next;
        }
    }
}

void LD(){
    createTempDeck("Deck");

    int count = 0;
    node *current_node = head;
    while (current_node != NULL) {
        count++;
        if (count > 7) {
            printf("\n[]");
            current_node = current_node->next;
            count = 1;
        } else {
            printf("[]");
            current_node = current_node->next;
        }
    }
}

int Sl(){
}

int main(){

    LD();
    //SW();

    //createTempDeck("Deck");
    dealCards();
    //cardStartVisibility();
    //print();
    printf("\n");
    print();


    /*node *current;
    current = &arr[5];
    while (current !=NULL){
        printf("%c%c",current->suit,current->rank);
        //printf("%d ",current->nextInC);
        current = current->nextInC;
    }*/

    //printf("\n\n");
    //SWtest();
    //printf("\n%c%c ", arr[0].suit, arr[0].rank);

}

//command to quit program.
void QQ(){
    exit(0);
}

//command to quit and starup game. Restart game.
void Q(){

}