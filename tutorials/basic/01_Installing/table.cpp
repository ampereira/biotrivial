//
//  table.cpp
//  IndielibTutorials
//
//  Created by André Pereira on 03/07/13.
//
//

#include "table.h"

Table::Table (void) {
    
}

void Table::addSlot (Slot slot) {
    slots.push_back(slot);
}

Slot Table::getSlot (unsigned _index) {
    return slots[_index];
}

void Table::buildTable (void) {
    
    for (int i = 0; i < 60; ++i) {
        
        Slot *slot;
        
        // slots with questions DISTINGUE
        if (i == 0 || i == 4 || i == 13 || i ==15 || i == 23 || i == 30 || i == 36 || i == 40 || i == 48 || i == 54 || i == 57) {
            slot = new Slot (DISTINGUE, i);
        } else {
            // slots with questions IDENTIFICA
            if (i == 1 || i == 12 || i == 17 || i == 25 || i == 28 || i == 34 || i == 35 || i == 44 || i == 46 || i == 52 || i == 58) {
                slot = new Slot (IDENTIFICA, i);
            } else {
                // slots with questions COMPLETA
                if (i == 5 || i == 7 || i == 11 || i == 20 || i == 22 || i == 33 || i == 37 || i == 43 || i == 49 || i == 51 || i == 55) {
                    slot = new Slot (COMPLETA, i);
                } else {
                    // slots with questions RESPONDE
                    if (i == 6 || i == 8 || i == 14 || i == 19 || i == 24 || i == 32 || i == 38 || i == 41 || i == 47 || i == 50 || i == 59) {
                        slot = new Slot (RESPONDE, i);
                    } else {
                        // slots with questions ACERTA_NA_PALAVRA
                        if (i == 3 || i == 9 || i == 16 || i == 21 || i == 27 || i == 29 || i == 39 || i == 42 || i == 45 || i == 53 || i == 56) {
                            slot = new Slot (ACERTA_NA_PALAVRA, i);
                        } else {
                            if (i == 2 || i == 10 || i == 18 || i == 26 || i == 31) {
                                slot = new Slot (SPECIAL, i);
                            } 
                        }
                    }
                }
            }
        }
        
        switch (i) {
            case 0:
                slot->setAdjacent(34);
                slot->setAdjacent(1);
                slot->setAdjacent(35);
                break;
                
            case 7:
                slot->setAdjacent(6);
                slot->setAdjacent(8);
                slot->setAdjacent(40);
                break;
                
            case 14:
                slot->setAdjacent(13);
                slot->setAdjacent(15);
                slot->setAdjacent(45);
                break;
                
            case 21:
                slot->setAdjacent(20);
                slot->setAdjacent(22);
                slot->setAdjacent(50);
                break;
                
            case 28:
                slot->setAdjacent(27);
                slot->setAdjacent(29);
                slot->setAdjacent(55);
                break;
                
            case 35:
                slot->setAdjacent(i - 1);
                slot->setAdjacent(i + 1);
                slot->setAdjacent(0);
                break;
                
            case 39:
                slot->setAdjacent(38);
                slot->setAdjacent(44);
                slot->setAdjacent(49);
                slot->setAdjacent(54);
                slot->setAdjacent(59);
                break;
                
            case 40:
                slot->setAdjacent(i - 1);
                slot->setAdjacent(i + 1);
                slot->setAdjacent(7);
                break;
                
            case 44:
                slot->setAdjacent(39);
                slot->setAdjacent(43);
                slot->setAdjacent(49);
                slot->setAdjacent(54);
                slot->setAdjacent(59);
                break;
                
            case 45:
                slot->setAdjacent(i - 1);
                slot->setAdjacent(i + 1);
                slot->setAdjacent(14);
                break;
                
            case 49:
                slot->setAdjacent(39);
                slot->setAdjacent(44);
                slot->setAdjacent(48);
                slot->setAdjacent(54);
                slot->setAdjacent(59);
                break;
                
            case 50:
                slot->setAdjacent(i - 1);
                slot->setAdjacent(i + 1);
                slot->setAdjacent(21);
                break;
                
            case 54:
                slot->setAdjacent(39);
                slot->setAdjacent(44);
                slot->setAdjacent(49);
                slot->setAdjacent(53);
                slot->setAdjacent(59);
                break;
                
            case 55:
                slot->setAdjacent(i - 1);
                slot->setAdjacent(i + 1);
                slot->setAdjacent(28);
                break;
                
            case 59:
                slot->setAdjacent(39);
                slot->setAdjacent(44);
                slot->setAdjacent(49);
                slot->setAdjacent(54);
                slot->setAdjacent(58);
                break;
                
            default:
                slot->setAdjacent(i - 1);
                slot->setAdjacent(i + 1);
                break;
        }
		
		if (i > 34 || i == 0 || i == 7 || i == 14 || i == 21 || i == 28)
			slot->setPoints(true);
		else
			slot->setPoints(false);
        
        slots.push_back(*slot);
    }
}
