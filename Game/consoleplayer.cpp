/*
 * consoleplayer.cpp
 *
 *  Created on: Oct 13, 2019
 *      Author: raphael
 */

#include <vector>
#include <iostream>
#include <stdexcept>
#include <string>

#include "consoleplayer.hpp"

using namespace std;

void printCards(vector<Card> cards, string msg);
void printCard(Card card);
Farbe enterSauspielFarbe();

Spiel ConsolePlayer::vote(GameSituation sit) {
	m_spielAnnounced = false;
	m_sit = sit;
	printCards(*sit.handCards, string("Deine Karten"));
	Spiel spiel;

	cout << "Willst du ein Sauspiel spielen?(y/n)" << endl;
	char answer;
	cin >> answer;

	switch (answer) {
	case 'y':
		spiel.type = Sauspiel;
		spiel.farbe = enterSauspielFarbe();
		break;
	case 'n':
		spiel.type = None;
	default:
		invalid_argument("Other value than 'y' or 'n' entered");
	}

	return spiel;
}

Card ConsolePlayer::placeCard(vector<Card> possibleCards) {
	if (!m_spielAnnounced) {
		Card card;
		card.schlag = A;
		card.farbe = m_sit.common->spiel.farbe;
		cout << "Spieler " << m_sit.common->spieler << " spielt mit: ";
		printCard(card);
		cout << endl;
		m_spielAnnounced = true;
	}

	printCards(m_sit.common->last, string("Kompletter Stich"));

	cout << endl;
	printCards(*m_sit.handCards, string("Deine Karten"));
	printCards(m_sit.common->current, string("Gelegte Karten"));
	printCards(possibleCards, string("Mögliche Karten"));
	cout << "Gib die Position der Karte ein, die du legen willst (Beginn bei 0)." << endl;

	int input;
	cin >> input;
	return possibleCards[input];
}

void printCards(vector<Card> cards, string msg) {
	cout << msg << ": ";
	for (Card card : cards) {
		printCard(card);
		cout<<" ";
	}
	cout << endl;
}

void printCard(Card card) {
	switch (card.farbe) {
	case SCHELLEN:
		cout << "Schellen";
		break;
	case HERZ:
		cout << "Herz";
		break;
	case GRAS:
		cout << "Gras";
		break;
	case EICHEL:
		cout << "Eichel";
	}

	cout << " ";

	switch (card.schlag) {
	case SIEBEN:
		cout << "7";
		break;
	case ACHT:
		cout << "8";
		break;
	case NEUN:
		cout << "9";
		break;
	case ZEHN:
		cout << "10";
		break;
	case U:
		cout << "U";
		break;
	case O:
		cout << "O";
		break;
	case K:
		cout << "K";
		break;
	case A:
		cout << "A";
	}
	cout << ";";
}

Farbe enterSauspielFarbe() {
	cout << "Auf welche Sau willst du spielen?(E,G,S)" << endl;
	char answer;
	cin >> answer;
	switch (answer) {
	case 'E':
		return EICHEL;
	case 'G':
		return GRAS;
	case 'S':
		return SCHELLEN;
	default:
		throw invalid_argument("Invalid Farbe entered");
	}
}

