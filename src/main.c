#include <stdio.h>
#include <string.h>
typedef struct String String;

typedef struct card{
    char suit;
    int rank;
    struct card* next;
    struct card* prev;
};


void LD(char file[]){
    char tempDeck[104];
    FILE *in = fopen(file,"r");
    if(!in){
        printf("fejl\n");
    }
    int wordCount;
    fscanf(in,"%d ",&wordCount);

    for (int i = 0; i < wordCount; ++i) {
        fscanf(in,"%c\n",&tempDeck[i]);
        printf("%c\n",tempDeck[i]);
    }


    for (int i = 0; i < wordCount/2; ++i) {


    }

}

int Sl(){
}


int main(){
    LD("Deck");


}











