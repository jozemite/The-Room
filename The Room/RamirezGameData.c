/*
 * The Room - Text Based Adventure Game
 * By: Jose Adan Ramirez (Jozemite Apps 2017)
 * Created on: 8/3/17
 *
 * The room is a text based adventure game that requires the user to
 * enter a series of command to guide themselves around and pass
 * the game.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "RamirezGameData.h"


location locations[] = {
        {0, "your living room. You can't leave through the front door.", "living room",
                kitchen, bathroom, NULL, NULL},

        {1, "the kitchen; there is a strange odor coming from the microwave.", "kitchen",
                NULL, NULL, livingRoom, NULL},

        {2, "the bathroom. There's a toilet and a giant hole on the wall.", "bathroom",
                NULL, NULL, NULL, livingRoom},
};


item items[] = {
        {"wire cutters", 0},
        {"padlock key",  0}
};


// description, used description, name, location, did use, item required,
// item rewarded, and examine required, used item description,
object objects[] = {
        {"The microwave seems to be tightly shut with wires.\nMaybe we could cut it with a tool.",
                "There is nothing unique about the microwave anymore.",
                "microwave", kitchen,  0, wireCutters, padLockKey, 0,
                "You used the wire cutters on the microwave to remove the wires.\nAs you open it, you"
                        "find a key inside of it. Looks like\nthe smell was from burnt metal. You hope it"
                        "still works."},

        {"There seems to be something clogging the toilet...\nYou reach your hand in there (gross!) only to feel "
                 "some kind of sharp tool.\nYou found a pair of wire cutters. (Whoosh!)",
                "The toilet is no longer clogged.",
                "toilet", bathroom, 0, NULL, wireCutters, 1, ""},

        {"The giant hole in the wall seems to be shut with a bunch of chains.\nUpon closer inspection, you notice "
                 "that there is a padlock that requires a key.", "What could've made this hole in the wall?",
                "giant hole", bathroom, 0, padLockKey, NULL, 0, ""},

        {"The front door is heavily locked by a bunch of chains. It doesn't seem\nlike you can do anything about it.",
                "", "front door", livingRoom, 0, NULL, NULL, 0, ""}
};


// Print the description of where the user is and what is around there.
void executeLook(const char *noun) {
    if (noun != NULL && strcmp(noun, "around") == 0) {
        printf("You are in %s", locations[playerLocation].description);
        printSurroundingLocations(locations[playerLocation]);
        printf("\n");
    } else {
        printf("I don't understand what you want to see.\n");
    }
}


void printSurroundingLocations(location currentLocation) {
    if (currentLocation.northLocation)
        printf("\nThe %s is north of you.", currentLocation.northLocation->name);
    if (currentLocation.eastLocation)
        printf("\nThe %s is east of you.", currentLocation.eastLocation->name);
    if (currentLocation.southLocation)
        printf("\nThe %s is south of you.", currentLocation.southLocation->name);
    if (currentLocation.westLocation)
        printf("\nThe %s is west of you.", currentLocation.westLocation->name);
}



// Decides where to move the user based on where they are or direction.
void executeGo(const char *noun) {
    unsigned i;

    for (i = 0; i < numOfLocations; i++) {

        // Do this if the user entered a valid location name
        if (noun != NULL && strcmp(noun, locations[i].name) == 0) {

            if (i == playerLocation) {
                printf("You are already there.\n");

            } else {

                // Only move if the room is connected to the current location
                if (locations[playerLocation].northLocation
                    && strcmp(noun, locations[playerLocation].northLocation->name) == 0) {

                    playerLocation = locations[playerLocation].northLocation->tag;
                    executeLook("around");
                    return;

                } else if (locations[playerLocation].eastLocation
                           && strcmp(noun, locations[playerLocation].eastLocation->name) == 0) {

                    playerLocation = locations[playerLocation].eastLocation->tag;
                    executeLook("around");
                    return;

                } else if (locations[playerLocation].southLocation
                           && strcmp(noun, locations[playerLocation].southLocation->name) == 0) {

                    playerLocation = locations[playerLocation].southLocation->tag;
                    executeLook("around");
                    return;

                } else if (locations[playerLocation].westLocation
                           && strcmp(noun, locations[playerLocation].westLocation->name) == 0) {

                    playerLocation = locations[playerLocation].westLocation->tag;
                    executeLook("around");
                    return;
                }

                printf("There is no location around you called '%s'.\n", noun);
            }

            return;

            // Do this if the user entered a valid direction
        } else if (noun != NULL
                   && (strcmp(noun, "north") == 0 || strcmp(noun, "North") == 0
                       || strcmp(noun, "east") == 0 || strcmp(noun, "East") == 0
                       || strcmp(noun, "south") == 0 || strcmp(noun, "South") == 0
                       || strcmp(noun, "west") == 0 || strcmp(noun, "West") == 0)) {

            // Only move if the room is connected to the current location in that direction
            if (locations[playerLocation].northLocation
                && (strcmp(noun, "north") == 0 || strcmp(noun, "North") == 0)) {

                playerLocation = locations[playerLocation].northLocation->tag;
                executeLook("around");
                return;

            } else if (locations[playerLocation].eastLocation
                       && (strcmp(noun, "east") == 0 || strcmp(noun, "East") == 0)) {

                playerLocation = locations[playerLocation].eastLocation->tag;
                executeLook("around");
                return;

            } else if (locations[playerLocation].southLocation
                       && (strcmp(noun, "south") == 0 || strcmp(noun, "South") == 0)) {

                playerLocation = locations[playerLocation].southLocation->tag;
                executeLook("around");
                return;

            } else if (locations[playerLocation].westLocation
                       && (strcmp(noun, "west") == 0 || strcmp(noun, "West") == 0)) {

                playerLocation = locations[playerLocation].westLocation->tag;
                executeLook("around");
                return;

            } else {
                printf("There is nowhere to go in that direction.\n");
            }

            return;
        }
    }

    printf("I don't understand where you want to go.\n");
}


// Checks the objects that are at the locations and see if you can do anything unique
invItem *executeExamine(const char *noun, invItem *backpack) {
    unsigned int i;

    for (i = 0; i < numOfObjects; i++) {

        if (noun != NULL && strcmp(noun, objects[i].name) == 0) {

            // Check if the item to examine is in the same room
            if (objects[i].location->tag == playerLocation) {

                objects[i].didUse ? printf("%s\n", objects[i].usedDescription)
                                  : printf("%s\n", objects[i].description);

                // Called if the user has the right item at the right place.
                if (objects[i].itemRequired != NULL) {
                    //
                    // Set the use to on and remove the item used
                    objects[i].didUse = 1;


                    // Called if the objects doesn't need an item and just examination
                    // For example, observing the toilet at the beginning gives you
                    // wire cutters and that's it.
                } else if (objects[i].itemRewarded != NULL
                    && objects[i].examineRequired
                    && objects[i].didUse == 0) {
                    objects[i].didUse = 1;
                    return inventoryItemPush(backpack, *objects[i].itemRewarded);
                }

            } else {
                printf("There is no %s to examine in here.\n", noun);
            }

            return backpack;
        }
    }

    printf("I don't understand what you want to examine.\n");
    return backpack;
}



void executeInventory(invItem *backpack) {
    printf("\n* INVENTORY *\n");

    if (strcmp(backpack->name, "") == 0) {
        printf("You have nothing in your backpack.\n");

    } else {
        invItem *tempItem;
        for (tempItem = backpack; tempItem; tempItem = tempItem->nextItem) {
            printf("%s\n", tempItem->name);
        }
    }
}



// Adds items to the user's inventory
invItem *inventoryItemPush(invItem *backpack, item newItem) {

    // That means it's the first item, so we want to replace the name
    if (strcmp(backpack->name, "") == 0) {
        backpack->name = newItem.name;

    } else {
        invItem *tempItem = malloc(sizeof(invItem));
        tempItem->name = newItem.name;
        tempItem->nextItem = NULL;

        invItem *lastItem;
        for (lastItem = backpack; lastItem; lastItem = lastItem->nextItem);
        tempItem->prevItem = lastItem;

        backpack->nextItem = tempItem;
    }

    return backpack;
}


// Removes items from the user's inventory
void inventoryItemPop(invItem *backpack, item removeItem) {

}