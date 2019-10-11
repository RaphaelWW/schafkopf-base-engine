/*
 * sauspielsession.cpp
 *
 *  Created on: Oct 3, 2019
 *      Author: raphael
 */

#include <vector>
#include <algorithm>

#include "game.hpp"
#include "../Exception/illegalgameexception.hpp"

using namespace std;

int findMitspieler(vector<Card>* handCards, Farbe farbe);
bool containsSpielsau(vector<Card> handCards, Farbe farbe);

SauspielSession::SauspielSession(vector<Card>* handCards, CommonKnowledge* common, bool simulation) :
		GameSession(handCards, common, simulation), m_farbe(common->spiel.farbe) {

	m_mitspieler = findMitspieler(handCards, m_farbe);
	if (m_mitspieler == common->spieler) {
		throw IllegalGameException(string("Player initiated Sauspiel with himself."));
	}
}

int findMitspieler(vector<Card>* handCards, Farbe farbe) {
	for (int i = 0; i < 4; i++) {
		if (containsSpielsau(handCards[i], farbe)) {
			return i;
		}
	}
	throw runtime_error("Card deck is incomplete.");
}

bool containsSpielsau(vector<Card> handCards, Farbe farbe) {
	return find_if(handCards.begin(), handCards.end(),
			[farbe](Card card) {return card.schlag == A && card.farbe == farbe;}) != handCards.end();
}

vector<Card> SauspielSession::getPossible(vector<Card> handCards) {
	if (getOpenCards().empty()) {
		//Es darf nie mit einer Karte der Spielfarbe außer der Sau herausgegangen werden.
		if (containsSpielsau(handCards, m_farbe)) {
			for (unsigned int i = 0; i < handCards.size(); i++) {
				if (handCards[i].schlag != A && handCards[i].farbe == m_farbe) {
					handCards.erase(handCards.begin() + i);
				}
			}
		}
		return handCards;
	}

	Card firstCard = getOpenCards().front();
	if (isTrumpf(firstCard)) {
		std::vector<Card> trumpf = findAllTrumpf(handCards);
		if (!trumpf.empty()) {
			return trumpf;
		}
		return handCards;
	}

	if (containsSpielsau(handCards, m_farbe)) {
		//Wenn die Sau angespielt wird, muss sie gelegt werden.
		if (firstCard.farbe == m_farbe) {
			vector<Card> onlySau;
			Card card;
			card.schlag = A;
			card.farbe = m_farbe;
			onlySau.push_back(card);
			return onlySau;
		} else {
			//Wenn die Sau nicht angespielt wird, darf sie nicht gelegt werden.
			for (unsigned int i = 0; i < handCards.size(); i++) {
				if (handCards[i].schlag == A && handCards[i].farbe == m_farbe) {
					handCards.erase(handCards.begin() + i);
					return handCards;
				}
			}
		}
	}

	std::vector<Card> cardsInFarbe = findAllInFarbe(handCards, firstCard.farbe);
	if (!cardsInFarbe.empty()) {
		return cardsInFarbe;
	}
	return handCards;
}

bool SauspielSession::isTrumpf(Card card) {
	return card.farbe == HERZ || card.schlag == O || card.schlag == U;
}

//is card2 higher Trumpf than card1, should only be called if both are Trumpf
bool SauspielSession::isCardHigherTrumpf(Card card1, Card card2) {
	if (card1.schlag == O) {
		if (card2.schlag == O && card1.farbe < card2.farbe) {
			return true;
		} else {
			return false;
		}
	} else if (card1.schlag == U) {
		return card2.schlag == O || (card2.schlag == U && card1.farbe < card2.farbe);
	} else if (card2.schlag == O || card2.schlag == U) {
		return true;
	} else {
		return card1.schlag < card2.schlag;
	}
}

bool* SauspielSession::determineGameWinner() {
	bool* winner = new bool[4];
	int spielerPoints = getPoints()[getSpieler()] + getPoints()[m_mitspieler];
	if (spielerPoints > 60) {
		winner[0] = false;
		winner[1] = false;
		winner[2] = false;
		winner[3] = false;
		winner[getSpieler()] = true;
		winner[m_mitspieler] = true;
	} else {
		winner[0] = true;
		winner[1] = true;
		winner[2] = true;
		winner[3] = true;
		winner[getSpieler()] = false;
		winner[m_mitspieler] = false;
	}
	return winner;
}
