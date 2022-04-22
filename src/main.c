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

struct node *addFirst(char rank, char suit){
    node *newNode = malloc(sizeof (node));
    newNode->rank=rank;
    newNode->suit=suit;
    newNode->next=NULL;
    newNode->prev=NULL;
    head = newNode;
    prevNode = newNode;
    return newNode;
}

struct node *addCard(char rank, char suit){
    node *newNode = malloc(sizeof (node));
    newNode->rank=rank;
    newNode->suit=suit;
    newNode->next=NULL;
    newNode->prev=prevNode;
    return newNode;
}

void print(node *head) {
    struct node *arr[7];
    int j=1;
    node *currentNode = head->next;

    for (int i = 0; i < 7; ++i) {
        if(i==0){
            arr[i]=head;
            arr[i]->next=NULL;
            arr[i]->prev=NULL;
            currentNode=head->next;
        }
        if(i>0){
            arr[i]=currentNode;
            arr[i]->next=NULL;
            arr[i]->prev=NULL;
            currentNode = currentNode->next;
        }

    }

    for (int i = 0; i < 45; ++i) {
        if(i<=30) {
            if(j>6) {
                j=1;
            }
            arr[j]=currentNode;
            arr[j]->prev=arr[j];
            arr[j]->next=NULL;
            j++;
        }

        if(i>30&&i<=35) {
            if(j>5) {
                j=1;
            }
            arr[j+1]->prev=arr[j+1];
            arr[j+1]=currentNode;
            arr[j+1]->next=NULL;
            j++;
        }

        if(i>35&&i<=39) {
            if(j>4) {
                j=1;
            }
            arr[j+2]->prev=arr[j+2];
            arr[j+2]=currentNode;
            arr[j+2]->next=NULL;
            j++;
        }

        if(i>39&&i<=42) {
            if(j>3) {
                j=1;
            }
            arr[j+3]->prev=arr[j+3];
            arr[j+3]=currentNode;
            arr[j+3]->next=NULL;
            j++;
        }
        if(i>42&&i<=44) {
            if(j>2) {
                j=1;
            }
            arr[j+4]->prev=arr[j+4];
            arr[j+4]=currentNode;
            arr[j+4]->next=NULL;
            j++;
        }

        if(i>44) {
            if(j>1) {
                j=1;
            }
            arr[j+5]->prev=arr[j+4];
            arr[j+5]=currentNode;
            arr[j+5]->next=NULL;
            j++;
        }
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


void SW(char file[]) {
    createTempDeck(file);
    for (int i = 0; i < 104; ++i) {
        if (head == NULL) {
            addFirst(tempDeck[i], tempDeck[i + 1]);
        }
        if (head != NULL) {
            addCard(tempDeck[i], tempDeck[i + 1]);
        }
        i++;
    }
    printf("%s\n",addFirst(tempDeck[0],tempDeck[1]));
    printf("%c%c",tempDeck[0],tempDeck[1]);

}



    void LD(char file[]){
        node *current=head->next;
        createTempDeck(file);
        for (int i = 0; i < 104; ++i) {
            if (head==NULL) {
                addFirst("[", "]");
            }
            if (head!=NULL) {
                addCard("[", "]");
            }
            i++;
        }
        for (int i = 0; i < 52; ++i) {
            current=head->next;
                printf("%d%d\n",current->rank,current->suit);
                current=current->next;
        }




}

int Sl(){
}


int main(){
    printf("%s\n",addFirst(tempDeck[0],tempDeck[1]));
    printf("%c%c",tempDeck[0],tempDeck[1]);
}











