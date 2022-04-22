#include <stdio.h>
#include <string.h>
typedef struct String String;
void *malloc(size_t size);


typedef struct node{
    char suit;
    char rank;
    struct node* next;
}node;
node* head = NULL;

struct node *addFirst(char rank, char suit){
    node *newNode = malloc(sizeof (node));
    newNode->rank=rank;
    newNode->suit=suit;
    newNode->next=NULL;
    head = newNode;
    return newNode;
}

struct node *addCard(char rank, char suit){
    node *newNode = malloc(sizeof (node));
    newNode->rank=rank;
    newNode->suit=suit;
    newNode->next=NULL;
    return newNode;
}

void print(node *head) {
    node *currentNode = head;
    while (currentNode != NULL) {

        printf("%c%c ", currentNode->rank,currentNode->suit);

    }
}
char tempDeck[104];

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
}


void LD(char file[]){
    createTempDeck(file);
    for (int i = 0; i < 104; ++i) {
        if (!head) {
            addFirst(tempDeck[i], tempDeck[i + 1]);
        }
        if (head) {
        addCard(tempDeck[i], tempDeck[i + 1]);
        }
        i++;
    }
}







int Sl(){
}


int main(){
    LD("Deck");


}











