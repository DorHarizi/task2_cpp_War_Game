#pragma once

#include <string>
#include <vector>
#include "card.hpp"
using namespace std;
using namespace ariel;

namespace ariel{

    class Player{
        private:
            string name;
            int num_of_cards_taken;
            vector<Card> packet;
            int numWin;
            int numCardsWin;
            int numDraw;
            int numCardsDraw;

        public:
            Player(){
                name = "";
                num_of_cards_taken = 0;
                numWin = 0;
                numCardsWin = 0;
                numDraw = 0;
                numCardsDraw = 0;
            }

            Player(string);

            string getName(){return name;}
            vector<Card> getPacket(){return packet;}
            int cardesTaken();
            int stacksize();
            
            void setName(string);

            string to_string();
    };
}