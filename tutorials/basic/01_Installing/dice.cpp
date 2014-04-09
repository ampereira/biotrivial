//
//  dice.cpp
//  IndielibTutorials
//
//  Created by André Pereira on 03/07/13.
//
//

#include "dice.h"

unsigned Dice::roll (void) {
	srand(time(NULL));
    return rand() % 6 + 1;
}