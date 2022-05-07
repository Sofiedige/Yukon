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

/*
int isValid(node* dest, node* move){
    int isSuitValid = 0, isRankValid = 0;

    //check for rank


    //check for suit
    if(dest->suit == move->suit){
        return 0;
    }
    else

} */

/*

void moveCard(){
    char input[9];
    scanf("%s",input);
    printf("%s", input);
    node* moveCard;
    node* destCard;

    if(input[0]=='C'){
        node* current = &arr[input[1]];
        while (current->nextInC != NULL){
            if (current->nextInC->rank == input[3] && current->nextInC->suit == input[4]){
                moveCard = current->nextInC;
                destCard = &arr[input[8]];
                if(destCard == NULL){  //hvis kollonen er tom

                }
                else{
                while (destCard->nextInC != NULL){
                    destCard = destCard->nextInC;
                }
                if(destCard->suit == 0)
                }
            }
            current = current->nextInC;
        }
    }
    //tag også stilling til om en kolonne bliver tom så head = NULL
    //og hvis der tilføjes noget i en tom kolonne bliver det lig head.

}
*/
void inputPrint(){
    printf("LAST COMMAND: %s\n", "Last command");
    printf("MESSAGE: %s\n", "Message");
    printf("INPUT >");
}

char print(){
    char printArr[23][100];
    memset(printArr, 0, 23*100);
    node *current = &arr[0];
    int count;
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
    printf(" C1  C2  C3  C4  C5  C6  C7\n\n");
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
    inputPrint();
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
    printf(" C1  C2  C3  C4  C5  C6  C7\n\n");

    int count = 0;
    int foundation = 0;

    node *current_node = head;
    while ( current_node != NULL) {
        count++;
        if(count > 7) {
            if(foundation == 0){
                printf("\t[] F1");            }
            if(foundation == 2){
                printf("\t[] F2");            }
            if(foundation == 4){
                printf("\t[] F3");            }
            if(foundation == 6){
                printf("\t[] F4");
            }
            foundation++;
            printf("\n %c%c ", current_node->suit, current_node->rank);
            current_node = current_node->next;
            count=1;
        }
        else{
            printf(" %c%c ", current_node->suit, current_node->rank);
            current_node = current_node->next;
        }
    }
    printf("\n");
    inputPrint();
}

void LD(){
    createTempDeck("Deck");
    printf(" C1  C2  C3  C4  C5  C6  C7\n\n");

    int foundation = 0;
    int count = 0;
    node *current_node = head;
    while (current_node != NULL) {
        count++;
        if (count > 7) {
            if(foundation == 0){
                printf("\t[] F1");            }
            if(foundation == 2){
                printf("\t[] F2");            }
            if(foundation == 4){
                printf("\t[] F3");            }
            if(foundation == 6){
                printf("\t[] F4");
            }
            foundation++;
            printf("\n [] ");
            current_node = current_node->next;

            count = 1;
            continue;
        }
        printf(" [] ");
        current_node = current_node->next;
    }
    printf("\n");
    inputPrint();
}

void StartScreen(){
    printf(" C1  C2  C3  C4  C5  C6  C7\n\n");

}



void ResetGame(){
    print();
}

int Sl(){
}
int strcmp (const char* str1, const char* str2);
void twoSplit () {
    int len = 52;
    node *current = head;
//kan være brugerens input, sætter det bare til halvdelen
    int hopCount = (len / 2)-1;
    for (int i = 0; i < hopCount; i++) {
        current = current->next;
    }

    // Now cut at current
    node *frontSplit = current;
    node *backSplit = current->next;
    frontSplit->next = NULL;
    backSplit->prev = NULL;

    int counter = 0;
    head = NULL;
    node* temp = NULL;

    while (frontSplit != NULL || backSplit != NULL) {
        counter++;

        if (head == NULL) {
            head = frontSplit;
            temp = frontSplit;

            //current = shuffleHead;
            //prevNode = frontSplit;
            frontSplit = frontSplit->prev;
            temp->prev = NULL;
        } else {
            if (counter % 2 == 1) {
                //current = backSplit;
                temp->next=frontSplit;
                if (frontSplit->prev != NULL) {
                    frontSplit = frontSplit->prev;
                    frontSplit->next = NULL;
                } else
                    frontSplit = NULL;
                temp->next->prev = temp;
                temp=temp->next;
                temp->next=NULL;

            } else {
                //current = frontSplit;
                temp->next=backSplit;
                if (backSplit->next != NULL) {
                    backSplit = backSplit->next;
                    backSplit->prev = NULL;
                }else
                    backSplit = NULL;
                temp->next->prev = temp;
                temp=temp->next;
                temp->next=NULL;

            }
        }
        //current = current->next;
    }

}
int main(){

    char input[10];
    while(1){
        scanf("%s",input);
        if(strcmp(input,"QQ")==0){
            QQ();
        }if(strcmp(input,"Q")==0){
            ResetGame();
        }if(strcmp(input,"P")==0){
            dealCards();
            print();
        }if(strcmp(input,"LD")==0){
            LD();
        }if(strcmp(input,"SW")==0){
            SW();
        }if(strcmp(input,"SI")==0){
            twoSplit();
        }
    }

    //moveCard();
    LD();
    SW();
    twoSplit();
    //createTempDeck("Deck");
    dealCards();
    //cardStartVisibility();
    //print();
    printf("\n");
    print();
    ResetGame();

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
