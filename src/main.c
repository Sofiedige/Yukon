#include <stdio.h>
void *malloc(size_t size);


typedef struct node{
    char suit;
    char rank;
    struct node* next;
    struct node* prev;
}node;

struct node* head = NULL;
struct node* prevNode=NULL;

struct node *addFirst(char suit, char rank){
    node *newNode = malloc(sizeof (node));
    newNode->suit=suit;
    newNode->rank=rank;
    newNode->next=NULL;
    newNode->prev=NULL;
    head = newNode;
    prevNode = newNode;
    return newNode;
}

struct node *addCard(char suit, char rank){
    node *newNode = malloc(sizeof (node));
    prevNode->next=newNode;
    newNode->rank=rank;
    newNode->suit=suit;
    newNode->next=NULL;
    newNode->prev=prevNode;
    prevNode = newNode;
    return newNode;
}

void print(node *head) {


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

    for (int i = 0; i < 104; ++i) {
        if (head == NULL) {
            addFirst(tempDeck[i], tempDeck[i + 1]);
        }
        if (head != NULL) {
            addCard(tempDeck[i], tempDeck[i + 1]);
        }
        i++;
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

    void LD(char file[]){
        createTempDeck(file);

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
    LD("Deck");
    //SW();
}











