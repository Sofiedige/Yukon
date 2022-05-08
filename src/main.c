#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

void QQ();
void *malloc(size_t size);
int strcmp (const char* str1, const char* str2);

typedef struct node{
    char suit;
    char rank;
    struct node* next;
    struct node* nextInC;
    struct node* prev;
    int isVisible;
}node;

node* arr[7];
struct node* head = NULL;
struct node* prevNode = NULL;
char tempDeck[104];
char message[15];
char lastCommand[100];
node* f[4];

struct node *addFirst(char rank, char suit){
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

struct node *addCard(char rank, char suit){
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
int file_exists(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    int is_exist = 0;
    if (fp != NULL)
    {
        is_exist = 1;
        fclose(fp); // close the file
    }
    return is_exist;
}

void createTempDeck(char file[]){
    FILE *in = fopen(file,"r");
    if(!file_exists(file)){
        printf("fejl\n");
    }

    for (int i = 0; i < 104; ++i) {
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
    //initialize foundations.
    f[0] = addCard('[',']');
    f[1] = addCard('[',']');
    f[2] = addCard('[',']');
    f[3] = addCard('[',']');

    //initialize first card
    arr[0] = head;
    arr[0]->isVisible = 1;
    arr[0]->prev = NULL;

    node *current;

    //fills each columns head.
    for (int i = 1; i < 7; i++) {
        arr[i] = arr[i - 1]->next;
        arr[i]->isVisible = 0;
        arr[i]->prev = NULL;
    }
    arr[0]->nextInC = NULL;
    node* last = arr[6];

    for(int i = 0; i < 10; i++){
        for (int j = 1; j < 7; ++j) {
            if(i > j+3){
                continue;
            }
            current = arr[j];
            node *temp = last->next;
            last = temp;

            while(current->nextInC != NULL){
                current = current->nextInC;
            }
            temp->prev = current;
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


int isValid(node* bigger, node* smaller){
    if(bigger==NULL){
        return 1;
    }
    if(smaller->rank == '[' && bigger->rank == 'A'){
        return 2;
    }

    int isSuitValid = 0, isRankValid = 0;

    //check for rank
    if(isdigit(smaller->rank)){
        if(smaller->rank == '9' && bigger->rank == 'T' || smaller->rank == bigger->rank - 1){
            isRankValid = 1;
        }
    }
    else{
        if(smaller->rank == 'A' && bigger->rank == '2' || smaller->rank == 'T' && bigger->rank == 'J' ||
           smaller->rank == 'J' && bigger->rank == 'Q' || smaller->rank == 'Q' && bigger->rank == 'K'){
            isRankValid = 1;
        }
    }

    //check for suit
    if(bigger->suit != smaller->suit){
        isSuitValid = 1;
    }
    if(bigger->suit == smaller->suit){
        isSuitValid = 2;
    }

    //if both valid, card can be moved
    if (isSuitValid == 1 && isRankValid == 1){
        return 1;
    }
    if (isSuitValid == 2 && isRankValid == 1){
        return 2;
    }
    else{
        return 0;
    }
}

void placeInFoundation(int fNo, int column, node* move, node* columnTail){
    node* foundation = f[fNo-1];
    if(foundation == NULL){
        //error message
    }

    if(isValid(move,foundation) == 2){
        //Omhandler hvor kortet var før
        if (columnTail->prev == NULL) {
            arr[column - 1] = NULL;
        }
        else{
            columnTail->prev->isVisible = 1;
            columnTail= columnTail->prev;
            columnTail->nextInC = NULL;
        }

        move->prev = foundation;
        f[fNo-1] = move;
    }
}
void moveFromFoundation(char input[]){
    char *fNumber = &input[1];
    int fNo = strtol(fNumber, NULL, 10);;
    node* destCard;
    node* fCard = f[fNo-1];
    char *destCol = &input[5];

    int destColumn = strtol(destCol, NULL, 10);
    destCard = arr[destColumn - 1];

    if (destCard != NULL) {
        while (destCard->nextInC != NULL) {
            destCard = destCard->nextInC;
        }
    }
    if(isValid(destCard,fCard) == 1) {
        f[fNo-1] = fCard->prev;

        if (destCard == NULL) {
            arr[destColumn - 1] = fCard;
        } else {
            fCard->prev = destCard;
            destCard->nextInC = fCard;
        }
    }
}

void moveCard(char input[]) {

    node *moveCard = NULL;
    node *destCard;
    int column, destColumn;
    char *col = &input[1];
    char *destCol = &input[8];
    //C4:5C->C3

    column = strtol(col, NULL, 10);
    node* current = arr[column - 1];

    //finder kort som skal rykkes
    while (current != NULL) {
        if (current->rank == input[3] && current->suit == input[4]) {
            moveCard = current;
            break;
        }
        else {
            current = current->nextInC;
        }
    }
    //hvis kortet ikke blev fundet, kommer der error besked.
    if (moveCard == NULL) {
        //print error message.
    }
    else {
        if (input[7] == 'F') {
            destColumn = strtol(&input[8], NULL, 10);
            placeInFoundation(destColumn, column, moveCard, current);
        }
        else {
            destColumn = strtol(destCol, NULL, 10);
            destCard = arr[destColumn - 1];
            //finder kortet som der lægges på.
            if (destCard != NULL) {
                while (destCard->nextInC != NULL) {
                    destCard = destCard->nextInC;
                }
            }

            if (isValid(destCard, moveCard) == 1) {
                //Omhandler hvor kortet var før
                if (current->prev == NULL) {
                    arr[column - 1] = NULL;
                } else {
                    current->prev->isVisible = 1;
                    current = current->prev;
                    current->nextInC = NULL;
                }
                //omhandler hvor kortet skal hen.
                if (destCard == NULL) {  //hvis dest-kolonnen er tom bliver det head for kolonnen.
                    moveCard->prev = NULL;
                    arr[destColumn - 1] = moveCard;
                } else {
                    moveCard->prev = destCard;
                    destCard->nextInC = moveCard;
                }

                //}
                //else { //print dette kort ikke kan rykkes
            }
        }
    }
}

void inputPrint(){
    printf("LAST COMMAND: %s\n", lastCommand);
    printf("MESSAGE: %s\n", message);
    printf("INPUT >");
}

char print(){
    char printArr[23][100];
    memset(printArr, 0, 23*100);
    node *current = arr[0];
    int count;
    int longest = 0;
    int countNotNull = 0;
    for(int j = 0; j < 7; j++) {
        current = arr[j];
        count = 0;
        countNotNull = 0;

        for(int i = 0; i < 22; i++){

            if (current != NULL && current->isVisible == 1) {
                sprintf(printArr[count], "%s %c%c ", printArr[count], current->rank, current->suit);
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
    printf("\n C1  C2  C3  C4  C5  C6  C7\n\n");
    for(int i = 0; i < 22; i++){
        if(i > longest)
            continue;
        if(i == 0){
            sprintf(printArr[i],"%s  %c%c F1", printArr[i], f[0]->rank, f[0]->suit);
        }
        if(i == 2){
            sprintf(printArr[i],"%s  %c%c F2", printArr[i], f[1]->rank, f[1]->suit);
        }
        if(i == 4){
            sprintf(printArr[i],"%s  %c%c F3", printArr[i], f[2]->rank, f[2]->suit);
        }
        if(i == 6){
            sprintf(printArr[i],"%s  %c%c F4", printArr[i], f[3]->rank, f[3]->suit);
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
        current_node = arr[i];

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
            printf("\n %c%c ", current_node->rank, current_node->suit);
            current_node = current_node->next;
            count=1;
        }
        else{
            printf(" %c%c ", current_node->rank, current_node->suit);
            current_node = current_node->next;
        }
    }
    printf("\n");
    inputPrint();
}

void bracketPrint(){
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
void LD(char file[]){
    createTempDeck(file);
    bracketPrint();
}

void StartScreen(){
    printf(" C1  C2  C3  C4  C5  C6  C7\n\n");

}



void ResetGame(){
    print();
}

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
int GetRandom(int lower, int upper){
        int num = (rand() %(upper - lower + 1)) + lower;
    return num;
}

void Shuffle(){
    node *notShuffledCurrent = head;
    node *shuffledHead = addCard('P','P');
    node *temp = shuffledHead->prev;
    temp->next=NULL;
    shuffledHead->prev=NULL;

    for (int i = 0; i < 51; ++i) {
        addCard('P','P');
    }
    node *shuffledCur = shuffledHead;
    while(notShuffledCurrent!=NULL){
    int num = GetRandom(0,51);

    for (int i = 0; i < num; ++i) {
        shuffledCur=shuffledCur->next;
    }
        while(shuffledCur->rank != 'P'){
            if(shuffledCur->next!=NULL){
                shuffledCur=shuffledCur->next;
            }else{
                shuffledCur=shuffledHead;
            }
        }
        shuffledCur->rank = notShuffledCurrent -> rank;
        shuffledCur->suit = notShuffledCurrent -> suit;

        notShuffledCurrent = notShuffledCurrent->next;
        shuffledCur=shuffledHead;
    }
    head=shuffledHead;
}



int main(){
    srand(time(0));
    char input[100];

    while(1) {
        scanf("%s", input);
        //fylder last command feltet
        for (int i = 0; i < 10; i++) {
            lastCommand[i] = input[i];
        }
        if (strcmp(input, "QQ") == 0) {
            QQ();
        }
        if (strcmp(input, "Q") == 0) {
            ResetGame();
        }
        if (strcmp(input, "P") == 0) {
            dealCards();
            print();
        }if(input[0] == 'L' && input[1] == 'D' && input[2]=='<' ){
            char input2[100];

            for (int i = 0; i < 100; ++i) {
                if(input[i+3]=='>'){
                    input2[i]='\0';
                    break;
                }
                input2[i]=input[i+3];
            }
            LD(input2);


        }if(strcmp(input,"LD")==0&& input[3]!='<'){
            LD("Deck");
        }if(strcmp(input,"SW")==0){
            SW();
        }if(strcmp(input,"SI")==0){
            twoSplit();
            bracketPrint();
        }if(input[7]=='C' || input[7]=='F'){
            moveCard(input);
            print();
        }if(strcmp(input,"SR")==0){
            Shuffle();
        }if(input[0]=='F'){
            moveFromFoundation(input);
            print();
        }//hvis input[1] == F så kør foundation metode.
    }



        //tømmer command igen.
        for (int i = 0; i<10 ; i++){
            lastCommand[i] = ' ';
        }
    }
}

//command to quit program.
void QQ(){
    exit(0);
}

//command to quit and starup game. Restart game.
