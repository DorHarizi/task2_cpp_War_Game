#include "game.hpp"
#include "player.hpp"
#include <string>
#include <algorithm>

#include <random>

using namespace ariel;
using namespace std;

namespace ariel{
    Game::Game(Player &player1, Player &player2): p1(player1), p2(player2){

        if ((p1.getName() == p2.getName())||(&player1 == &player2)){
            throw runtime_error("the game can't start with this players please try again with anthor players");
            return;
        }

        p1.setIsPlay(true);
        p2.setIsPlay(true);
        p1.getPacket().resize(26);
        p2.getPacket().resize(26);
        // p1.packet.resize(26);
        // p2.packet.resize(26);
        package.resize(52);


        string nameCards[] = {"Ace","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};
        int valueCards[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
        string typeCards[] = {"Diamond", "Clover", "Leaf", "Heart"};
        for(int i=0;i<3;i++){
            for(int j=0;j<13;j++){                
                package.push_back(Card(valueCards[j],typeCards[i], nameCards[j]));
            }
        }

        mt19937 rng(random_device{}());
        shuffle(package.begin(), package.end(), rng);
           for (size_t c = 0; c < 52; c++){
            if (c % 2 == 0){p1.getPacket().push_back(package[c]);
            p1.setNumOfCards(p1.getNumOfCard()+1);
            }
            else{p2.getPacket().push_back(package[c]);
             p2.setNumOfCards(p2.getNumOfCard()+1);}
            //   if (c % 2 == 0){p1.putCard(package[c]);}
            // else{p2.putCard(package[c]);}
           }
        p1.setCurrentCard(25);
        p2.setCurrentCard(25);
        finish = false;
        winner = "";
        logGame = "-------------------------------------------------------------------\n";
    }


    void Game::playTurn(){
        if(!finish){
            Card c1 = p1.getPacket()[static_cast<vector<Card>::size_type>(p1.getCurrentCard())];
            Card c2 = p2.getPacket()[static_cast<vector<Card>::size_type>(p2.getCurrentCard())];
            if(c1<c2){
                p2.getPacket().push_back(c1);
                p2.setNumOfCards(p2.getNumOfCard()+ 1);
                p1.getPacket().pop_back();
                p1.setNumOfCards(p1.getNumOfCard()-1);
                p2.setNumOfCards(p2.getNumOfCard()-1);
                lastTurn = p1.getName()+ " played: "+ c1.getName() + " of " + c1.getType()+" "+ p2.getName()+ " played: "+ c2.getName() + " of " + c2.getType()+"."+p2.getName()+" wins.\n";
                status += lastTurn;
                if(p1.stacksize() == 0){finish = true;winner = p2.getName();}
            }else{
                if(c1.getValue() == c2.getValue()){
                    bool tieGame = true;
                    lastTurn = p1.getName()+ " played: "+ c1.getName() + " of " + c1.getType()+" "+ p2.getName()+ " played: "+ c2.getName() + " of " + c2.getType()+". draw.";
                    while(tieGame){
                        int index1 = p1.getCurrentCard() -1;
                        int index2 = p2.getCurrentCard() -1;
                        if((index1 == -1) || (index2 == -1)){
                            Card c1_hiddenCard = p1.getPacket()[static_cast<vector<Card>::size_type>(p1.getCurrentCard())];
                            Card c2_hiddenCard = p2.getPacket()[static_cast<vector<Card>::size_type>(p2.getCurrentCard())];
                            if((c1_hiddenCard < c2_hiddenCard)){
                                p2.getPacket().push_back(c1);
                                p2.setNumOfCards(p2.getNumOfCard() + 1);
                                p1.getPacket().pop_back();
                                lastTurn += p2.getName()+" wins.\n";
                                finish = true;
                                winner = p2.getName();
                            }else{
                                if(c1_hiddenCard.getValue() == c2_hiddenCard.getValue()){
                                    if(p1.cardesTaken()<p2.cardesTaken()){
                                        cout <<"player:"<<p2.getName()<<"win"<<endl;
                                        winner = p2.getName();
                                    }
                                    else{
                                        if(p1.cardesTaken()> p2.cardesTaken()){
                                            cout <<"player:"<<p1.getName()<<"win"<<endl;
                                            winner = p1.getName();
                                        }else{
                                            cout <<"the result game is tie"<<endl;}
                                        
                                    }
                                }else{
                                    p1.getPacket().push_back(c2);
                                    p1.setNumOfCards(p1.getNumOfCard() + 1);
                                    p2.getPacket().pop_back();
                                    lastTurn += p1.getName()+" wins.\n";
                                    winner = p1.getName();
                                    finish = true;
                                }
                            }
                            tieGame = false;
                            logGame += lastTurn;
                        }
                        Card c1_hiddenCard = p1.getPacket()[static_cast<vector<Card>::size_type>(p1.getCurrentCard())];
                        Card c2_hiddenCard = p2.getPacket()[static_cast<vector<Card>::size_type>(p2.getCurrentCard())];
                        index1 --;
                        index2--;
                        Card c1_openingCard = p1.getPacket()[static_cast<vector<Card>::size_type>(p1.getCurrentCard())];
                        Card c2_openingCard = p2.getPacket()[static_cast<vector<Card>::size_type>(p2.getCurrentCard())];
                        if(c1_openingCard< c2_openingCard){
                            p2.getPacket().push_back(c1_openingCard);
                            p2.getPacket().push_back(c1_hiddenCard);
                            p2.setNumOfCards(p2.getNumOfCard() + 2);
                            p1.getPacket().pop_back();
                            p1.getPacket().pop_back();
                            p1.setNumOfCards(p1.getNumOfCard()-2);
                            p2.setNumOfCards(p2.getNumOfCard()-2);
                            if(p1.stacksize() == 0){finish = true;}
                            lastTurn += p2.getName()+" wins.\n";
                            logGame += lastTurn;
                            tieGame = false;
                        }else{
                            if(c2_openingCard < c1_openingCard){
                                p1.getPacket().push_back(c1_openingCard);
                                p1.getPacket().push_back(c1_hiddenCard);
                                p1.setNumOfCards(p1.getNumOfCard() + 2);
                                p2.getPacket().pop_back();
                                p2.getPacket().pop_back();
                                p1.setCurrentCard(p1.getCurrentCard() - 2);
                                p2.setCurrentCard(p2.getCurrentCard() - 2);
                                if(p1.stacksize() == 0){finish = true;}
                                lastTurn += p1.getName()+" wins.\n";
                                logGame += lastTurn;
                                tieGame = false;
                            }else{
                                p1.getPacket().pop_back();
                                p1.getPacket().pop_back();
                                p2.getPacket().pop_back();
                                p2.getPacket().pop_back();
                                p1.setCurrentCard(p1.getCurrentCard() - 2);
                                p2.setCurrentCard(p2.getCurrentCard() - 2);
                                lastTurn += p1.getName()+ " played: "+ c1.getName() + " of " + c1.getType()+" "+ p2.getName()+ " played: "+ c2.getName() + " of " + c2.getType()+". draw.";
                            }
                        }

                    }
                }else{
                    p1.getPacket().push_back(c2);
                    p1.setNumOfCards(p1.getNumOfCard() + 1);
                    p2.getPacket().pop_back();
                    p1.setCurrentCard(p1.getCurrentCard() - 1);
                    p2.setCurrentCard(p2.getCurrentCard() - 1);
                    lastTurn = p1.getName()+ " played: "+ c1.getName() + " of " + c1.getType()+" "+ p2.getName()+ " played: "+ c2.getName() + " of " + c2.getType()+"."+p1.getName()+" wins.\n";
                    status += lastTurn;
                    if(p2.stacksize() == 0){finish = true;winner = p1.getName();}
                }
            }
        }else{
            p1.getPacket().clear();
            p2.getPacket().clear();
            throw runtime_error("the game is over!");
            return;
        }
    }
    void Game::printLastTurn(){
        if(lastTurn == ""){
            cout << "No turns played yet. " << endl;
        }
        else{
            cout << lastTurn <<endl;
        }
    }
    void Game::playAll(){
        while(!finish){
            playTurn();
        }
    }
    void Game::printWiner(){cout << winner <<endl;}
    void Game::printLog(){
        cout << logGame << endl;
    }
    void Game::printStats(){}
}