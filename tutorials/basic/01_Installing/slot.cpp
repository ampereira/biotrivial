//
//  slot.cpp
//  IndielibTutorials
//
//  Created by André Pereira on 03/07/13.
//
//

#include "slot.h"

Slot::Slot (int _type, unsigned _index) {
    type = _type;
    index = _index;
}

bool Slot::givesPoints (void) {
	return gives_points;
}

void Slot::setPoints (bool points) {
	gives_points = points;
}

int Slot::getType (void) {
    return type;
}

unsigned Slot::getPosition (void) {
    return index;
}

vector<unsigned> Slot::getAdjacent (void) {
    return adjacents;
}

void Slot::setAdjacent (unsigned _index) {
    adjacents.push_back(_index);
}

bool Slot::operator==(Slot s) {
    return (index == s.getPosition());
}

bool Slot::operator!=(Slot s) {
    return (index != s.getPosition());
}

bool Slot::operator<(Slot s) {
    return (index < s.getPosition());
}

bool Slot::operator>(Slot s) {
    return (index > s.getPosition());
}

bool Slot::operator<=(Slot s) {
    return (index <= s.getPosition());
}

bool Slot::operator>=(Slot s) {
    return (index >= s.getPosition());
}




