//
//  player.cpp
//  IndielibTutorials
//
//  Created by André Pereira on 03/07/13.
//
//

#include "player.h"
#include <iostream>
Player::Player (string _name, Questions *_questions, Table &_table, unsigned original_pos) {
	origin_flag = false;
    table = _table;
    name = _name;
    questions = _questions;
    position = original_pos;
    
    for (int i = 0; i < 5; ++i)
        types_completed[i] = false;
}

template<class T>
bool Player::findPreviousPosition (vector<T> vec, T value) {
    bool flag = false;
    
    for (int i = 0; i < vec.size(); ++i)
        if (value == vec[i])
            flag = true;
    
    return flag;
}

void Player::moveInCenterOutward (unsigned s, unsigned d) {
	if (s > 34) {
		unsigned current_outside = s;
		unsigned dd = d;
		
		if (d == 0) {
			possible_positions.push_back(table.getSlot(s));
			return;
		}
		
		if ((current_outside == 35 || current_outside == 40 || current_outside == 45 || current_outside == 50 || current_outside == 55)) {
			
			switch (current_outside) {
				case 35:
					moveInCircle(0, d - 1);
					break;
				case 40:
					moveInCircle(7, d - 1);
					break;
				case 45:
					moveInCircle(14, d - 1);
					break;
				case 50:
					moveInCircle(21, d - 1);
					break;
				case 55:
					moveInCircle(28, d - 1);
					break;
					
			}
		} else {
			moveInCenterOutward(s - 1, d - 1);
		}
		
	}
}

void Player::moveInCenterInward (unsigned s, unsigned d) {
	if (s > 34) {
		unsigned current_outside = s;
		unsigned dd = d;
		
		if (d == 0) {
			possible_positions.push_back(table.getSlot(s));
			return;
		}
		
		if ((current_outside == 39 || current_outside == 44 || current_outside == 49 || current_outside == 54 || current_outside == 59)) {
			
			if (current_outside != 39)
				moveInCenterOutward(39, d - 1);
			
			if (current_outside != 44)
				moveInCenterOutward(44, d - 1);
			
			if (current_outside != 49)
				moveInCenterOutward(49, d - 1);
			
			if (current_outside != 54)
				moveInCenterOutward(54, d - 1);
			
			if (current_outside != 59)
				moveInCenterOutward(59, d - 1);
		} else {
			moveInCenterInward(s + 1, d - 1);
		}

	}
}

void Player::moveInCircle (unsigned s, unsigned d) {
	if (s < 35) {
		unsigned current_right = s;
		unsigned dd = d;
		
		// move to the right
		while (dd) {
				switch (current_right) {
					case 0:
						moveInCenterInward(35, dd - 1);
						break;
					case 7:
						moveInCenterInward(40, dd - 1);
						break;
					case 14:
						moveInCenterInward(45, dd - 1);
						break;
					case 21:
						moveInCenterInward(50, dd - 1);
						break;
					case 28:
						moveInCenterInward(55, dd - 1);
						break;
				}
				
			if (current_right == 34)
				current_right = 0;
			else
				current_right++;
			
			dd--;
		}
		
		unsigned current_left = s;
		
		dd = d;
		
		// move to the left
		while (dd) {
			switch (current_left) {
				case 0:
					moveInCenterInward(35, dd - 1);
					break;
				case 7:
					moveInCenterInward(40, dd - 1);
					break;
				case 14:
					moveInCenterInward(45, dd - 1);
					break;
				case 21:
					moveInCenterInward(50, dd - 1);
					break;
				case 28:
					moveInCenterInward(55, dd - 1);
					break;
			}
			
			if (current_left == 0)
				current_left = 34;
			else
				current_left--;
			
			dd--;
		}
		possible_positions.push_back(table.getSlot(current_right));
		possible_positions.push_back(table.getSlot(current_left));
	}
}

vector<Slot> Player::availableMoves (void) {
	vector<Slot> moves;
	rolled = dice.roll();
    
	possible_positions.clear();
	
    if (position > 34) {
		moveInCenterInward(position, rolled);
		moveInCenterOutward(position, rolled);
	} else {
		moveInCircle(position, rolled);
	}
	
	moves.push_back(possible_positions[0]);
	
	for (int i = 1; i < possible_positions.size(); ++i) {
		unsigned flag = 0;
		for (int j = 0; j < moves.size(); ++j) {
			if (possible_positions[i].getPosition() == moves[j].getPosition())
				flag++;
		}
		if (flag == 0)
			moves.push_back(possible_positions[i]);
	}
    
    return moves;
}

unsigned Player::getRolled (void) {
	return rolled;
}

unsigned Player::getPosition (void) {
	return position;
}

bool Player::won (void) {
	bool win = true;
	
	for (int i = 0; i < 5; ++i) {
		if (!types_completed[i])
			win = false;
	}
			
	return win;
}

string Player::getName (void) {
	return name;
}

Question* Player::move (unsigned new_pos) {

	bool flag = false;
	
	for (int i = 0; i < possible_positions.size(); ++i)
		if (new_pos == possible_positions[i].getPosition())
			flag = true;

	if (flag)
		position = new_pos;
	else
		return NULL;
	
	if (table.getSlot(position).getType() != SPECIAL)
		current_question = questions->getQuestion(table.getSlot(position).getType());
	
		
	return current_question;
	
}

bool* Player::getCompleted (void) {
	return types_completed;
}

int Player::answer (string ans) {
	int result = -1;
	
	if(current_question->isCorrectAnswer(ans))
		result = 0;
	
	if (result == -1)
		return result;
	
	if (table.getSlot(position).givesPoints()) {
		types_completed[table.getSlot(position).getType()] = true;
		result = table.getSlot(position).getType() + 1;
	}
	
	return result;
}

int Player::answer (int ans) {
	int result = -1;
	
	if(current_question->isCorrectAnswer(ans))
		result = 0;
	
	if (result == -1)
		return result;
	
	if (table.getSlot(position).givesPoints()) {
		types_completed[table.getSlot(position).getType()] = true;
		result = table.getSlot(position).getType() + 1;
	}
	
	return result;
}
