#include "player.hpp"
#include <string>
#include <vector>

using namespace std;
using namespace ariel;

namespace ariel{
    
    Player::Player(string newName) {
        name = newName;
        num_of_cards_taken = 0;
        numWin = 0;
        numCardsWin = 0;
        numDraw = 0;
        numCardsDraw = 0;
    }

    void Player::setName(string newName) {
        name = newName;
    }

    int Player::cardesTaken(){
        return num_of_cards_taken;
    }

    int Player::stacksize(){
        return packet.size();
    }

    string Player::to_string() {
        // [player: ("dor")]
        return "[Player: ("+name+")]";
    }
}