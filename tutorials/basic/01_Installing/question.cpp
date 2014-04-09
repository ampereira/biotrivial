//
//  question.cpp
//  IndielibTutorials
//
//  Created by André Pereira on 03/07/13.
//
//

#include "question.h"

Question::Question (int _type) {
	id = ids;
	ids++;
    asked = false;
    correct_defined = false;
    type = _type;
    correct = 99;
}

Question::Question (void) {
	id = ids;
	ids++;
    asked = false;
    correct_defined = false;
    type = NO_TYPE;
    correct = 99;
}

int Question::getImageID() {
    return image_id;
}

void Question::setImageID(int id) {
    image_id = id;
}

Question::Question (string _question, vector<string> _answers, unsigned _correct, int _type) {
	id = ids;
	ids++;
    asked = false;
    correct_defined = true;
    question = _question;
    answers = _answers;
    correct = _correct;
    type = _type;
}

// esta e para as que se tem de acertar na palavra escrita
Question::Question (string _question, string _answer, int _type) {
	id = ids;
	ids++;
	asked = false;
	correct_defined = true;
	type = _type;
	answer = _answer;
	question = _question;
	correct = 99;
}

Question::Question (string _question, string _img1, unsigned _correct, int _type) {
	id = ids;
	ids++;
	asked = false;
	correct_defined = true;
	type = _type;
	question = _question;
	correct = _correct;
	image = _img1;
}

Question::Question (string _question, vector<string> _answers, unsigned _correct, int _type, string img) {
	id = ids;
	ids++;
    asked = false;
    correct_defined = true;
    question = _question;
    answers = _answers;
    correct = _correct;
    type = _type;
	image = img;
}

string Question::getQuestion (void) {
    return question;
}


string Question::getCorrect (void) {
	if (type == ACERTA_NA_PALAVRA)
		return answer;
	else if (type == IDENTIFICA || type == COMPLETA || type == RESPONDE) {
		return answers[correct];
	} else{
		stringstream ss;
		ss << correct;
		return ss.str();
	}
}

string Question::getImage (void) {
    return image;
}

unsigned Question::getId (void) {
    return id;
}

vector<string> Question::getAnswers (void) {
    return answers;
}

int Question::getType (void) {
    return type;
}

bool Question::isCorrectAnswer (unsigned answer_id) {
    if (answer_id == correct)
        return true;
    else
        return false;
}

char easytolower(char in){
	if(in<='Z' && in>='A')
		return in-('Z'-'z');
	return in;
}

bool Question::isCorrectAnswer(string _answer) {
	for (string::iterator i = _answer.begin(); i != _answer.end(); ++i) {
		char aux = *i;
		*i = easytolower(aux);
	}
	return !answer.compare(_answer);
}

bool Question::wasAsked (void) {
    return asked;
}

void Question::ask (void) {
    asked = true;
}

void Question::setQuestion (string _question) {
    question = _question;
}

bool Question::setAnswer (string _answer, bool iscorrect) {
    if (correct_defined)
        return false;
    else {
        answers.push_back(_answer);
        correct = answers.size() - 1;
        correct_defined = true;
        
        return true;
    }
}

