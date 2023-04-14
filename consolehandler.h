#ifndef CONSOLE_HANDLER
#define CONSOLE_HANDLER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
required folders:
./data
./data/manual

required files:
./data/version.txt
./data/credits.txt
./data/manual/index.txt

Every folder inside manual, including manual, must have a 'index.txt'.

If you so desire, you may change the name of the files and folders, on the definitions below.

Treat the return code as a way to run different things
*/

int handleArgs(int argc,char *argv[]);

void noArgument();

void unknownArgument(char* arg);

int run(char *argv);

void printHelp();

void printVersion();

void printManual(char* arg);

#define CONSOLE_HANDLER_RUN "-r"
#define CONSOLE_HANDLER_HELP "-h"
#define CONSOLE_HANDLER_VERSION "-v"
#define CONSOLE_HANDLER_MANUAL "-m"

#define CONSOLE_HANDLER_EXTENTION ".txt"

#define CONSOLE_HANDLER_DATA_FOLDER "data/"
#define CONSOLE_HANDLER_MANUAL_FOLDER "manual/"

#define CONSOLE_HANDLER_VERSION_FILE "version"
#define CONSOLE_HANDLER_CREDITS "credits"
#define CONSOLE_HANDLER_INDEX "index"

#define CONSOLE_HANDLER_LINE_MAX_SIZE 150

#define CONSOLE_HANDLER_NO_ARGUMENT "\nPlease, use an argument:\n'%s' to run the program\n'%s' to see all avaliable basic arguments\n\n"
#define CONSOLE_HANDLER_UNKNOWN_ARGUMENT "\nArgument '%s' does not exist.\nPlease use '%s' to list all basic arguments.\n\n"
#define CONSOLE_HANDLER_HELP_RUN "'%s'\tRuns the program\n"
#define CONSOLE_HANDLER_HELP_HELP "'%s'\tPrints this screen\n"
#define CONSOLE_HANDLER_HELP_VERSION "'%s'\tPrints the current version, and its contributors\n"
#define CONSOLE_HANDLER_HELP_MANUAL "'%s ?'\tPrints the manual for something\n"

#define CONSOLE_HANDLER_VERSION_NOT_FOUND "\nVersion file not found :(\n\n"
#define CONSOLE_HANDLER_CREDITS_NOT_FOUND "\nCredits file not found :(\n\n"
#define CONSOLE_HANDLER_MANUALS_NOT_FOUND "\nNo manual file or folder found :(\n\n"

#define CONSOLE_HANDLER_RUNNING "\nRunning (%d)\n\n"
#define CONSOLE_HANDLER_DEFAULT_RETURN_CODE -1

int handleArgs(int argc,char *argv[]){
    if(argc <= 1){
        noArgument();
    }
    else if(strcmp(argv[1],CONSOLE_HANDLER_RUN) == 0){
        if(argc <= 2){
            return run("");
        }
        else{
            return run(argv[2]);
        }
    }
    else if(strcmp(argv[1],CONSOLE_HANDLER_HELP) == 0){
        printHelp();
    }
    else if(strcmp(argv[1],CONSOLE_HANDLER_VERSION) == 0){
        printVersion();
    }
    else if(strcmp(argv[1],CONSOLE_HANDLER_MANUAL) == 0){
        if(argc <= 2){
            printManual(CONSOLE_HANDLER_INDEX);
        }
        else{
            printManual(argv[2]);
        }
    }
    else{
        unknownArgument(argv[1]);
    }
    
    return CONSOLE_HANDLER_DEFAULT_RETURN_CODE;
}

void noArgument(){
    printf(CONSOLE_HANDLER_NO_ARGUMENT,CONSOLE_HANDLER_RUN,CONSOLE_HANDLER_HELP);
}

void unknownArgument(char* arg){
    printf(CONSOLE_HANDLER_UNKNOWN_ARGUMENT,arg,CONSOLE_HANDLER_HELP);
}

int run(char *argv){
    int code = 0;
    if(strcmp(argv,"") != 0){
        code = atoi(argv);
    }
    printf(CONSOLE_HANDLER_RUNNING,code);
    return code;
}

void printHelp(){
    printf(CONSOLE_HANDLER_HELP_RUN,CONSOLE_HANDLER_RUN);
    printf(CONSOLE_HANDLER_HELP_HELP,CONSOLE_HANDLER_HELP);
    printf(CONSOLE_HANDLER_HELP_VERSION,CONSOLE_HANDLER_VERSION);
    printf(CONSOLE_HANDLER_HELP_MANUAL,CONSOLE_HANDLER_MANUAL);
}

int printFile(char* path,char* notFound){
    FILE *fptr;

    fptr = fopen(path, "r");

    int status = 0;

    if(fptr != NULL){
        status = 1;
        char content[CONSOLE_HANDLER_LINE_MAX_SIZE];

        printf("\n");
        while(!feof(fptr)){
            fgets(content,CONSOLE_HANDLER_LINE_MAX_SIZE,fptr);

            printf("%s",content);
        }
        printf("\n\n");
    }
    else{
        if(notFound != NULL){
            printf("%s",notFound);
        }
    }

    fclose(fptr);
    return status;
}

void printVersion(){
    char pth[200];

    strcpy(pth,CONSOLE_HANDLER_DATA_FOLDER);
    strcat(pth,CONSOLE_HANDLER_VERSION_FILE);
    strcat(pth,CONSOLE_HANDLER_EXTENTION);

    printFile(pth,CONSOLE_HANDLER_VERSION_NOT_FOUND);

    strcpy(pth,CONSOLE_HANDLER_DATA_FOLDER);
    strcat(pth,CONSOLE_HANDLER_CREDITS);
    strcat(pth,CONSOLE_HANDLER_EXTENTION);

    printFile(pth,CONSOLE_HANDLER_CREDITS_NOT_FOUND);
}

void printManual(char* arg){
    char pth[200];

    strcpy(pth,CONSOLE_HANDLER_DATA_FOLDER);
    strcat(pth,CONSOLE_HANDLER_MANUAL_FOLDER);
    strcat(pth,arg);
    strcat(pth,CONSOLE_HANDLER_EXTENTION);

    if(printFile(pth,NULL) == 0){
        strcpy(pth,CONSOLE_HANDLER_DATA_FOLDER);
        strcat(pth,CONSOLE_HANDLER_MANUAL_FOLDER);
        strcat(pth,arg);
        strcat(pth,"/");
        strcat(pth,CONSOLE_HANDLER_INDEX);
        strcat(pth,CONSOLE_HANDLER_EXTENTION);

        printFile(pth,CONSOLE_HANDLER_MANUALS_NOT_FOUND);
    }
}

#endif