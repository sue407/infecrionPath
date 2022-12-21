//
//  main.c
//  infestPath
//
//  Created by Juyeop Kim on 2022/10/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ifct_element.h"
#include "ifct_database.h"

#define MENU_PATIENT        1
#define MENU_PLACE          2
#define MENU_AGE            3
#define MENU_TRACK          4
#define MENU_EXIT           0

#define TIME_HIDE           2


int trackInfester(int patient_no, int *detected_time, int *place) {
    void *obj = ifctdb_getData(patient_no);
    unsigned int infestedTime = ifctele_getinfestedTime(obj);
    int infester_no = -1;
    for (int i = 0; i < ifctdb_len(); i++) {
        if (i == patient_no) {
            continue;
        }
        
    }
    if (infester_no == -1) {
        printf("%d is first-time infester\n", patient_no);
    } else {
        printf("%d infested by %d\n", patient_no, infester_no);
        trackInfester(infester_no, NULL, NULL);
    }
}

int main(int argc, const char *argv[]) {

    int menu_selection;
    void *ifct_element;
    FILE *fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];

    //------------- 1. loading patient info file ------------------------------
    //1-1. FILE pointer open
    if (argc != 2) {
        printf("[ERROR] syntax : infestPath (file path).");
        return -1;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("[ERROR] Failed to open database file!! (%s)\n", argv[1]);
        return -1;
    }

    //1-2. loading each patient informations
    char buf[1024];
    char *ptr;
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        ptr = strtok(buf, " ");
        pIndex = atoi(ptr);
        ptr = strtok(NULL, " ");
        age = atoi(ptr);
        ptr = strtok(NULL, " ");
        time = atoi(ptr);
        for (int i = 0; i < 5; i++) {
            ptr = strtok(NULL, " ");
            placeHist[i] = atoi(ptr);
        }
        void *ele = ifctele_genElement(pIndex, age, time, placeHist);
        ifctdb_addTail(ele);
    }

    //1-3. FILE pointer close
    fclose(fp);

    do {
        printf("\n=============== INFECTION PATH MANAGEMENT PROGRAM (No. of patients : %i) =============\n",
               ifctdb_len());
        printf("1. Print details about a patient.\n");                      //MENU_PATIENT
        printf("2. Print list of patients infected at a history_place.\n");        //MENU_PLACE
        printf("3. Print list of patients in a range of age.\n");          //MENU_AGE
        printf("4. Track the root of the infection\n");                     //MENU_TRACK
        printf("0. Exit.\n");                                               //MENU_EXIT
        printf("=============== ------------------------------------------------------- =============\n\n");

        printf("Select a menu :");
        scanf("%d", &menu_selection);
        fflush(stdin);

        switch (menu_selection) {
            case MENU_EXIT:
                printf("Exiting the program... Bye bye.\n");
                break;

            case MENU_PATIENT: {
                int index;
                printf("Enter the index(0 ~ %d): ", ifctdb_len() - 1);
                scanf("%d", &index);
                void *obj = ifctdb_getData(index);
                ifctele_printElement(obj);
                break;
            }


            case MENU_PLACE: {
                int time;
                printf("Enter the time: ");
                scanf("%d", &time);
                for (int i = 0; i < ifctdb_len(); i++) {
                    void *obj = ifctdb_getData(i);
                    if (ifctele_getinfestedTime(obj) == time) {
                        ifctele_printElement(obj);
                    }
                }
                break;
            }


            case MENU_AGE: {
                int min_age, max_age;
                printf("Enter the min age: ");
                scanf("%d", &min_age);
                printf("Enter the max age: ");
                scanf("%d", &max_age);
                for (int i = 0; i < ifctdb_len(); i++) {
                    void *obj = ifctdb_getData(i);
                    if (min_age <= ifctele_getAge(obj) && ifctele_getAge(obj) <= max_age) {
                        ifctele_printElement(obj);
                    }
                }
                break;
            }

            case MENU_TRACK: {
                int patience_no;
                printf("Enter the patience no(0 ~ %d): ", ifctdb_len() - 1);
                scanf("%d", &patience_no);
                trackInfester(patience_no, NULL, NULL);
                break;
            }

            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        }

    } while (menu_selection != 0);


    return 0;
}
