#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
void readFile(FILE *file, int result[3]);
int main (int argc, char **argv) {
    int option;
    bool cflag = false;
    bool wflag = false;
    bool lflag = false;



    while((option = getopt(argc, argv, "cwl")) != -1){
        switch(option){
            case 'c':
                //want number of bytes
                cflag = true;
                break;
            case 'w':
                //want number of words
                wflag = true;
                break;
            case 'l':
                //want number of lines
                lflag = true;
                break;
            default :
                printf("Error");


        }

    }
    if(lflag || wflag || cflag){ //there is atleast one flag
        int j = optind;
        int totalLines = 0;
        int totalWords = 0;
        int totalBytes = 0;
        bool displayTotal = false;
        if(optind + 1 <= argc - 1){
            displayTotal = true;
        }

        if(optind >= argc){ //added this for stdin

            int result[3];
            readFile(stdin, result);

            if(lflag){
                printf("%d   ", result[0]);
            }
            if(wflag){
                printf("%d   ", result[1]);
            }
            if(cflag){
                printf("%d   ", result[2]);
            }
            printf("\n");

        }//added this for stdin END
        while(j<argc){
            int result[3];
            FILE *file = fopen(argv[j], "r");
            readFile(file,result);


            if(lflag){
                printf("%d    ", result[0]);
                totalLines += result[0];

            }
            if(wflag){
                printf("%d    ",result[1]);
                totalWords += result[1];

            }
            if(cflag){
                printf("%d   ", result[2]);
                totalBytes += result[2];

            }	
            printf("%s \n", argv[j]);
            j++;
        }	

        if(displayTotal){
            if(totalLines != 0){
                printf("%d    ", totalLines);
            }
            if(totalWords != 0){
                printf("%d    ", totalWords);
            }
            if(totalBytes != 0){
                printf("%d    ", totalBytes);
            }
            printf("Total \n");

        }


    }


    else{
        //want all three


        int i = optind;
        bool displayTotal = false;
        int totalLines = 0;
        int totalWords = 0;
        int totalBytes = 0;
        if(optind + 1 <= argc - 1){
            displayTotal = true;
        }

        if(optind >= argc){
            int result[3];
            readFile(stdin, result);
            printf("%d   ", result[0]);
            printf("%d   ", result[1]);
            printf("%d   ", result[2]);
            printf("\n");


        }


        while(i<argc){
            int result[3];
            FILE *file = fopen(argv[i], "r");
            readFile(file, result);
            printf("%d    ",result[0]);
            totalLines += result[0];
            printf("%d    ",result[1]);
            totalWords += result[1];
            printf("%d    ", result[2]);
            totalBytes += result[2];
            printf("%s \n", argv[i]);
            i++;

        }
        if(displayTotal){
            printf("%d    ", totalLines);
            printf("%d    ", totalWords);
            printf("%d    ", totalBytes);
            printf("Total \n");



        }



    }
}
void readFile(FILE *file, int result[3]){
    //adding this now
    //adding this now
    //FILE *file = fopen(fileName, "r");
    char c=fgetc(file);
    if(c == EOF){
        result[0] = 0;
        result[1] = 0;
        result[2] = 0;
        return;
    }
    int numLines = 0;
    int numWords = 0;
    int numBytes = 0;

    if(!isspace(c)){
        numBytes++;

        while(!isspace(c)){
            c = fgetc(file);
            numBytes++;
        } //after this loop c = ' ' or a space character
        numWords++;
        while( c!= EOF){
            if(c == '\n'){
                numLines++;
            }
            char b = c;
            c = fgetc(file);
            if(c!=EOF){
                numBytes++;
            }
            if(isspace(b) && !isspace(c) && c!=EOF){
                numWords++;
            }

        }	

    }	// !isspace(c) condition closed
    if(isspace(c)){
        numBytes++;
        while( c!= EOF){
            if(c == '\n'){

                numLines++;
            }
            char b = c;
            c = fgetc(file);
            if(c!= EOF){
                numBytes++;}
            if(isspace(b) && !isspace(c) && c != EOF ){

                numWords++;
            }
        }



    }
    result[0] = numLines;
    result[1] = numWords;
    result[2] = numBytes;
    fclose(file);
}




