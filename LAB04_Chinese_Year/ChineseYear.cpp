#include <iostream>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <string>

#include "ChineseYear.hpp"

#define CYCLE_YEARS    12

using namespace std;

// Casts to silence compilation warnings
static char *G_animals[CYCLE_YEARS + 1] = 
                    {(char *)"Rat",
                     (char *)"Ox",
                     (char *)"Tiger",
                     (char *)"Rabbit",
                     (char *)"Dragon",
                     (char *)"Snake",
                     (char *)"Horse",
                     (char *)"Goat",
                     (char *)"Monkey",
                     (char *)"Rooster",
                     (char *)"Dog",
                     (char *)"Pig",
                     NULL};

//
// --   Utility functions
//
static int animal_pos(string animal) {
    int         i = 0;
    const char *a = animal.c_str();

    G_animals[CYCLE_YEARS] = (char *)a;
    while (strcasecmp(G_animals[i], (char *)a)) {
      i++;
    }
    if (i == CYCLE_YEARS) {
      return -1;
    }
    return i;
}

static bool valid_animal(string animal) {
    return (animal_pos(animal) == -1 ? false : true);
}

static string animal(int pos) {
    if ((pos >= 0) && (pos < CYCLE_YEARS)) {
      return string(G_animals[pos]);
    }
    return NULL;
}

// 
// From now on, it’s you turn to write the code for constructors,
// operators and friend functions …`
//
