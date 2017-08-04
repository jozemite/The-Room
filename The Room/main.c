/*
 * The Room - Text Based Adventure Game
 * By: Jose Adan Ramirez (Jozemite Apps 2017)
 * Created on: 8/3/17
 *
 * The room is a text based adventure game that requires the user to
 * enter a series of command to guide themselves around and pass
 * the game.
 *
 * There is a game guide located at the end of the file.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "RamirezGameData.h"


// Holds the user command of what the user types in
static char userCommand[100];


void printIntroduction();
static int getInput();
static int parseAndExecute(invItem *backpack);


int main() {

    // Will hold the user's items
    invItem *backpack = malloc(sizeof(invItem));
    backpack->name = "";
    backpack->nextItem = NULL;
    backpack->prevItem = NULL;

    printIntroduction();
    executeLook("around");

    // This will continuously prompt the user for a command until they quit
    while (getInput() && parseAndExecute(backpack));

    printf("\nGoodbye! Thank you for playing The Room.\n");

    return 0;
}



void printIntroduction() {
    printf("\n\n--------------------------------------------------------------");
    printf("\n-------------------- Welcome to The Room! --------------------");
    printf("\n--------------------------------------------------------------\n");

    printf("\nThis is a text based adventure game. You will have to enter a series\n");
    printf("of commands to guide yourself around.\n");

    printf("\n* ACCEPTABLE COMMANDS *\n");
    printf("Look around : Gives a description of where you currently are.\n");
    printf("Go [location] : Goes to a given location if accessible.\n");
    printf("Go [direction] : Goes to a given direction if accessible.\n");
    printf("Examine [object] : Gives additional information about an object.\n");
    printf("Inventory : Displays a list of items you currently have.\n");
    printf("Quit : Exits the game.\n");

    printf("\n* STORY *");
    printf("\nOne stormy night, you unexpectedly wake up to the sound of metal banging\n");
    printf("against each other. You go into the living only to see that your\n");
    printf("only exit out of your apartment has been completely locked with chains.\n");
    printf("You suddenly realize that you have no way out.\n\n");
}



static int getInput() {
    printf("\nEnter Command -> ");
    return fgets(userCommand, sizeof(userCommand), stdin) != NULL;
}



// Will execute the commands of the user
static int parseAndExecute(invItem *backpack) {
    // The verb is the first part of the command
    char *verb = strtok(userCommand, " \n");

    // The noun is the 2nd part of the command, such as the name of a location
    char *noun = strtok(NULL, "\n");

    if (verb != NULL) {
        if (strcmp(verb, "look") == 0 || strcmp(verb, "Look") == 0) {
            executeLook(noun);

        } else if (strcmp(verb, "go") == 0 || strcmp(verb, "Go") == 0) {
            executeGo(noun);

        } else if (strcmp(verb, "examine") == 0 || strcmp(verb, "Examine") == 0) {
            backpack = executeExamine(noun, backpack);

        } else if (strcmp(verb, "inventory") == 0 || strcmp(verb, "Inventory") == 0) {
            executeInventory(backpack);

        } else if (strcmp(verb, "quit") == 0 || strcmp(verb, "Quit") == 0) {
            return 0;

        } else {
            printf("I don't recognize the command '%s'\n", verb);
        }
    }

    return 1;
}




/* -----Game Guide -----
 *
 * -Part 1: Your Apartment-
 * The game starts in the living room, you must go east to the bathroom and
 * examine the toilet. You will find wire cutters. Go west to the living room
 * and go north to the kitchen. Examine the microwave to use the wire cutters
 * on it. You will find a padlock key inside of it. Go south to the living room
 * and go back to the bathroom. Examine the giant hole to use the padlock key
 * and escape your apartment.
 *
 */