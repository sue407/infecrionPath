//
//  ifs_element.c
//  InfestPath
//
//  Created by Juyeop Kim on 2020/10/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ifct_element.h"

typedef enum place {
    Seoul,          //0
    Jeju,           //1
    Tokyo,          //2
    LosAngeles,     //3
    NewYork,        //4
    Texas,          //5
    Toronto,        //6
    Paris,          //7
    Nice,           //8
    Rome,           //9
    Milan,          //10
    London,         //11
    Manchester,     //12
    Basel,          //13
    Luzern,         //14
    Munich,         //15
    Frankfurt,      //16
    Berlin,         //17
    Barcelona,      //18
    Madrid,         //19
    Amsterdam,      //20
    Stockholm,      //21
    Oslo,           //22
    Hanoi,          //23
    Bangkok,        //24
    KualaLumpur,    //25
    Singapore,      //26
    Sydney,         //27
    SaoPaulo,       //28
    Cairo,          //29
    Beijing,        //30
    Nairobi,        //31
    Cancun,         //32
    BuenosAires,    //33
    Reykjavik,      //34
    Glasgow,        //35
    Warsow,         //36
    Istanbul,       //37
    Dubai,          //38
    CapeTown        //39
} place_t;

char countryName[N_PLACE+1][MAX_PLACENAME] =
        {   "Seoul",
            "Jeju",
            "Tokyo",
            "LosAngeles",
            "NewYork",
            "Texas",
            "Toronto",
            "Paris",
            "Nice",
            "Rome",
            "Milan",
            "London",
            "Manchester",
            "Basel",
            "Luzern",
            "Munich",
            "Frankfurt",
            "Berlin",
            "Barcelona",
            "Madrid",
            "Amsterdam",
            "Stockholm",
            "Oslo",
            "Hanoi",
            "Bangkok",
            "KualaLumpur",
            "Singapore",
            "Sydney",
            "SaoPaulo",
            "Cairo",
            "Beijing",
            "Nairobi",
            "Cancun",
            "BuenosAires",
            "Reykjavik",
            "Glasgow",
            "Warsow",
            "Istanbul",
            "Dubai",
            "CapeTown",
            "Unrecognized"
        };

typedef struct {
    int index;
    int age;
    int detected_time;
    place_t history_place[N_HISTORY];
} ifct_ele_t;

void* ifctele_genElement(int index, int age, unsigned int detected_time, int history_place[N_HISTORY]) {
    ifct_ele_t* new_ifct_ele = malloc(sizeof(ifct_ele_t));
    new_ifct_ele->index = index;
    new_ifct_ele->age = age;
    new_ifct_ele->detected_time = detected_time;
    for (int i = 0; i < N_HISTORY; i++) {
        new_ifct_ele->history_place[i] = history_place[i];
    }
    return new_ifct_ele;
}

void ifctele_printElement(void* obj) {
    ifct_ele_t *ele = (ifct_ele_t *) obj;
    printf("\nindex: %d\n"
           "age: %d\n"
           "detected time: %d\n", ele->index, ele->age, ele->detected_time);
    printf("history place: ");
    for (int i = 0; i < N_HISTORY; i++) {
        printf("%s ", ifctele_getPlaceName(ele->history_place[i]));
    }
    printf("\n");
}

unsigned int ifctele_getinfestedTime(void* obj) {
    return ((ifct_ele_t *) obj)->detected_time;
}

int ifctele_getAge(void* obj) {
    return ((ifct_ele_t *) obj)->age;
}

char* ifctele_getPlaceName(int placeIndex) {
    return countryName[placeIndex];
}

int ifctele_getHistPlaceIndex(void* obj, int index) {
    return ((ifct_ele_t *) obj)->history_place[index];
}
