#include <stdio.h>
void *malloc(size_t size);


typedef struct node{
    char suit;
    char rank;
    struct node* next;
    struct node* prev;
    int isVisible;
}node;

struct node* head = NULL;
struct node* prevNode = NULL;

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

    //sætter forrige nodes next til newNode
    //prevNode = head;
    prevNode->next=newNode;

    newNode->rank=rank;
    newNode->suit=suit;
    newNode->next=NULL;
    newNode->prev=prevNode;

    prevNode = newNode;

    return newNode;
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

    for (int j = 0; j < 104; ++j) {
        if (head == NULL) {
            addFirst(tempDeck[j], tempDeck[j + 1]);
        }
        if (head != NULL) {
            addCard(tempDeck[j], tempDeck[j + 1]);
        }
        j++;
    }
}
void makeNotVisible (){
    node *current = head;
    while (current != NULL){
        current -> isVisible = 0;
        current = current->next;
    }
}

void print(node *head) {
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


void SW(char file[]) {
    createTempDeck(file);

    struct node *arr[7];
    int j=1;
    for (int i = 0; i < 52; ++i) {

    }

    printf("%s\n",addFirst(tempDeck[0],tempDeck[1]));
    printf("%c%c\n",tempDeck[0],tempDeck[1]);
    printf("%s\n", addCard(tempDeck[2],tempDeck[3]));

}

    void LD(char file[]){
        //node *current=head->next;
        createTempDeck(file);
        node *current = head;

        //skal

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
    createTempDeck("Deck");
    print(head);
    //SW("Deck");
}

