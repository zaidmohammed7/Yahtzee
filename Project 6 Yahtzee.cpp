/****************************
 * Program 6: Yahtzee
 *
 * Course: CS 141, Fall 2022
 * System: WindowsOS using Clion
 * Student Author: Zaid Khan Mohammed
 * *** **********************/


/*
 * Instructions for Playing Yahtzee:
 *
 * 1. Roll the dice: The game will roll five dice for you.
 * 2. Keep Dice: Specify which dice to keep by entering their indices (e.g., "125").
 *    - To stop rolling, enter 's' or 'S'.
 * 3. Select a Row: Choose a scoring option by entering a number from 1 to 13.
 *    - If the row has been played, you will be prompted to select another.
 * 4. The game continues until all rows are filled.
 * 5. At the end, your total score will be displayed.
 *
 * Enjoy the game!
 */


// include statements
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <vector>
#include <limits>
#include <cstring>
#include <algorithm>


using namespace std;



//#################################################################################################
// Row class to store info on all rows
class Row{
private:
    // data to store in row
    string rowName;
    int rowScore=0;
    bool rowPlayedStatus=0;
public:
    // getter and setter functions
    void setName(string name){rowName=name;}
    string getName(){return rowName;}
    void setScore(int score){rowScore=score;}
    int getScore(){return rowScore;}
    void setStatus(int status){rowPlayedStatus=status;}
    bool getStatus(){return rowPlayedStatus;}

};

//#################################################################################################
// Dice class to store info on each dice
class Dice{
private:
    int value;
    bool keepStatus=0;

public:
    //Randomly assigns a value between from 1 to 6 to the dice.
    void roll();
    int reveal() {return value;}
    void setValue(int value) {this->value = value;}
    void keep(){this->keepStatus=1;}
    void dontKeep(){this->keepStatus=0;}
    bool getKeepStatus(){ return keepStatus;}

};
// roll function
void Dice::roll() {
    // making sure dice gets value from 1-6
    setValue((rand()%6)+1);
}

//#################################################################################################
// hand class to store info on all dice
const int HAND_SIZE = 5;

class Hand {
public:

    //Display the value of the five dice
    void show();
    void play();
    Dice* getDice(int diceNum);

    //selection is the string of dice numbers that the player wants to keep.
    //For example, "125" means that player wants to keep the first, second, and fifth dice, and roll the rest.
    void setSelection(string selection);

    Hand();
    // array that stores 5 dice objects
    Dice arrDice[5];

private:
};
// show function
void Hand::show() {
    for (int i=0;i<5;++i){
        cout<<arrDice[i].reveal()<<" ";
    }
    cout<<endl;
}
// function to roll dice that user doesn't want to keep
void Hand::play() {
    for (int i=0;i<5;++i){
        if (arrDice[i].getKeepStatus()==0){
            arrDice[i].roll();
        }
    }
}
// function that returns address of a given dice
Dice *Hand::getDice(int diceNum) {
    return &arrDice[diceNum];
}


void Hand::setSelection(std::string selection) {
    for (int i=0;i<selection.size();++i){
        arrDice[(selection.at(i)-'0'-1)].keep();
    }
}


Hand::Hand() {
    
    for (int i=0;i<5;++i){

        arrDice[i].dontKeep();
    }
}

//######################################################################


//List of rows in the board
const int ONES = 0;
const int TWOS = 1;
const int THREES = 2;
const int FOURS = 3;
const int FIVES = 4;
const int SIXES = 5;
const int THREE_OF_KIND = 6;
const int FOUR_OF_KIND = 7;
const int FULL_HOUSE = 8;
const int SMALL_STRAIGHT = 9;
const int LARGE_STRAIGHT = 10;
const int CHANCE = 11;
const int YAHTZEE = 12;

const int BOARD_SIZE=13;
// game class to store info on all rows and their scores
class Game {

public:
    //calcScore returns a score of a hand (5 dice) for given row in the board.
    //Note the rows are indexed from zero.
    //For example if the hand is 2 1 1 5 1 then calcScore(hand, ONES) returns 3 and  calcScore(hand, TWOS) returns 2.
    int calcScore(Hand* hand, int row);
    //Display the board
    void show();
    //Returns the score of the upper part of the board
    int getUpperScore();
    //Returns the score of the lower part of the board
    int getLowerScore();
    //Returns the bonus points
    int getBonusScore();
    //Returns the total score
    int getTotalScore();
    //Play a hand based on the selected row
    void play(Hand* hand, int row);
    //Check to see if a row has been played or not (returns true if a row has been played)
    bool isPlayed(int row);
    //Check to see if all rows haven been played or not (returns true if all rows have been played)
    bool isFinished();

    // array to store all row objects
    Row arrRow[13];

private:
};

int Game::calcScore(Hand *hand, int row) {
    // initialising score to 0
    int score=0;
    // incrementing score based on hand and row played
    if (row == ONES) {
        for (int i = 0; i < 5; ++i) {
            if (hand->arrDice[i].reveal() == 1) { score += 1; }
        }
    }
    else if (row == TWOS) {
        for (int i = 0; i < 5; ++i) {
            if (hand->arrDice[i].reveal() == 2) { score += 2; }
        }
    }
    else if (row == THREES) {
        for (int i = 0; i < 5; ++i) {
            if (hand->arrDice[i].reveal() == 3) { score += 3; }
        }
    }
    else if (row == FOURS) {
        for (int i = 0; i < 5; ++i) {
            if (hand->arrDice[i].reveal() == 4) { score += 4; }
        }
    }
    else if (row == FIVES) {
        for (int i = 0; i < 5; ++i) {
            if (hand->arrDice[i].reveal() == 5) { score += 5; }
        }
    }
    else if (row == SIXES) {
        for (int i = 0; i < 5; ++i) {
            if (hand->arrDice[i].reveal() == 6) { score += 6; }
        }
    }
    else if (row==THREE_OF_KIND){
        // initialising counters for each time a number shows up in hand
        int ctr1=0;
        int ctr2=0;
        int ctr3=0;
        int ctr4=0;
        int ctr5=0;
        int ctr6=0;
        for (int i=0;i<5;++i){
            if (hand->arrDice[i].reveal()==1){
                ctr1++;
            }
            else if (hand->arrDice[i].reveal()==2){
                ctr2++;
            }
            else if (hand->arrDice[i].reveal()==3){
                ctr3++;
            }
            else if (hand->arrDice[i].reveal()==4){
                ctr4++;
            }
            else if (hand->arrDice[i].reveal()==5){
                ctr5++;
            }
            else if (hand->arrDice[i].reveal()==6){
                ctr6++;
            }
        }
        // checking if any number appeared 3 times and setting score to sum of all dice
        if (ctr1>=3 || ctr2>=3 || ctr3>=3 || ctr4>=3 || ctr5>=3 || ctr6>=3) {
            for (int i = 0; i < 5; ++i) {
                score += hand->arrDice[i].reveal();
            }
        }
    }
    else if (row==FOUR_OF_KIND){
        // same process as 'three of a kind'
        int ctr1=0;
        int ctr2=0;
        int ctr3=0;
        int ctr4=0;
        int ctr5=0;
        int ctr6=0;
        for (int i=0;i<5;++i){
            if (hand->arrDice[i].reveal()==1){
                ctr1++;
            }
            else if (hand->arrDice[i].reveal()==2){
                ctr2++;
            }
            else if (hand->arrDice[i].reveal()==3){
                ctr3++;
            }
            else if (hand->arrDice[i].reveal()==4){
                ctr4++;
            }
            else if (hand->arrDice[i].reveal()==5){
                ctr5++;
            }
            else if (hand->arrDice[i].reveal()==6){
                ctr6++;
            }
        }
        // checking if any number appeared 3 times and setting score to sum of all dice
        if (ctr1>=4 || ctr2>=4 || ctr3>=4 || ctr4>=4 || ctr5>=4 || ctr6>=4) {
            for (int i = 0; i < 5; ++i) {
                score += hand->arrDice[i].reveal();
            }
        }
    }
    else if (row==FULL_HOUSE){
        // initialising counters for each time a number shows up
        int ctr1=0;
        int ctr2=0;
        int ctr3=0;
        int ctr4=0;
        int ctr5=0;
        int ctr6=0;
        for (int i=0;i<5;++i){
            if (hand->arrDice[i].reveal()==1){
                ctr1++;
            }
            else if (hand->arrDice[i].reveal()==2){
                ctr2++;
            }
            else if (hand->arrDice[i].reveal()==3){
                ctr3++;
            }
            else if (hand->arrDice[i].reveal()==4){
                ctr4++;
            }
            else if (hand->arrDice[i].reveal()==5){
                ctr5++;
            }
            else if (hand->arrDice[i].reveal()==6){
                ctr6++;
            }
        }
        // pushing counters into a vector and iterating through it twice to check if one number appears thrice and another twice
        vector<int> vecCtr;
        vecCtr.push_back(ctr1);
        vecCtr.push_back(ctr2);
        vecCtr.push_back(ctr3);
        vecCtr.push_back(ctr4);
        vecCtr.push_back(ctr5);
        vecCtr.push_back(ctr6);
        if (ctr1==3 || ctr2==3 || ctr3==3 || ctr4==3 || ctr5==3 || ctr6==3){
            for (int i=0;i<vecCtr.size();++i){
                if (vecCtr.at(i)==2){score=25;} // setting score to 25
            }
        }
        // counting a YAHTZEE as a full house too and setting score to 25
        if (ctr1==5 || ctr2==5 || ctr3==5 || ctr4==5 || ctr5==5 || ctr6==5){score=25;}
    }
    else if (row==SMALL_STRAIGHT){
        // setting counters for each number
        int ctr1=0;
        int ctr2=0;
        int ctr3=0;
        int ctr4=0;
        int ctr5=0;
        int ctr6=0;
        for (int i=0;i<5;++i){
            if (hand->arrDice[i].reveal()==1){
                ctr1++;
            }
            else if (hand->arrDice[i].reveal()==2){
                ctr2++;
            }
            else if (hand->arrDice[i].reveal()==3){
                ctr3++;
            }
            else if (hand->arrDice[i].reveal()==4){
                ctr4++;
            }
            else if (hand->arrDice[i].reveal()==5){
                ctr5++;
            }
            else if (hand->arrDice[i].reveal()==6){
                ctr6++;
            }
        }
        // checking through possible cases of small straight and setting score as 30
        if ((ctr1>=1 && ctr2>=1 && ctr3>=1 && ctr4>=1) || (ctr2>=1 && ctr3>=1 && ctr4>=1 && ctr5>=1) || (ctr3>=1 && ctr4>=1 && ctr5>=1 && ctr6>=1)){score=30;}
    }
    else if (row==LARGE_STRAIGHT){
        // similar process as small straight
        int ctr1=0;
        int ctr2=0;
        int ctr3=0;
        int ctr4=0;
        int ctr5=0;
        int ctr6=0;
        for (int i=0;i<5;++i){
            if (hand->arrDice[i].reveal()==1){
                ctr1++;
            }
            else if (hand->arrDice[i].reveal()==2){
                ctr2++;
            }
            else if (hand->arrDice[i].reveal()==3){
                ctr3++;
            }
            else if (hand->arrDice[i].reveal()==4){
                ctr4++;
            }
            else if (hand->arrDice[i].reveal()==5){
                ctr5++;
            }
            else if (hand->arrDice[i].reveal()==6){
                ctr6++;
            }
        }
        if ((ctr1>=1 && ctr2>=1 && ctr3>=1 && ctr4>=1 && ctr5>=1) || (ctr2>=1 && ctr3>=1 && ctr4>=1 && ctr5>=1 && ctr6>=1)){score=40;}
    }
    else if (row==CHANCE){
        // simply calculating sum of all dice
        for (int i=0;i<5;++i){
            score+=hand->arrDice[i].reveal();
        }
    }
    else if (row==YAHTZEE){
        // similar process as 'three of a kind' and 'four of a kind'
        int ctr1=0;
        int ctr2=0;
        int ctr3=0;
        int ctr4=0;
        int ctr5=0;
        int ctr6=0;
        for (int i=0;i<5;++i){
            if (hand->arrDice[i].reveal()==1){
                ctr1++;
            }
            else if (hand->arrDice[i].reveal()==2){
                ctr2++;
            }
            else if (hand->arrDice[i].reveal()==3){
                ctr3++;
            }
            else if (hand->arrDice[i].reveal()==4){
                ctr4++;
            }
            else if (hand->arrDice[i].reveal()==5){
                ctr5++;
            }
            else if (hand->arrDice[i].reveal()==6){
                ctr6++;
            }
        }
        if (ctr1==5 || ctr2==5 || ctr3==5 || ctr4==5 || ctr5==5 || ctr6==5){score=50;} // setting score to 50
    }
    return score;
}


// function to show board and scores
void Game::show() {
    cout<<"1.  Ones:                "; if (!isPlayed(0)){cout<<"-\n";} else {cout<<arrRow[0].getScore()<<endl;}
    cout<<"2.  Twos:                "; if (!isPlayed(1)){cout<<"-\n";} else {cout<<arrRow[1].getScore()<<endl;}
    cout<<"3.  Threes:              "; if (!isPlayed(2)){cout<<"-\n";} else {cout<<arrRow[2].getScore()<<endl;}
    cout<<"4.  Fours:               "; if (!isPlayed(3)){cout<<"-\n";} else {cout<<arrRow[3].getScore()<<endl;}
    cout<<"5.  Fives:               "; if (!isPlayed(4)){cout<<"-\n";} else {cout<<arrRow[4].getScore()<<endl;}
    cout<<"6.  Sixes:               "; if (!isPlayed(5)){cout<<"-\n";} else {cout<<arrRow[5].getScore()<<endl;}
    cout<<"    Sum:                 "<<getUpperScore()<<endl;
    cout<<"    Bonus:               "<<getBonusScore()<<endl;
    cout<<"7.  Three of a kind:     "; if (!isPlayed(6)){cout<<"-\n";} else {cout<<arrRow[6].getScore()<<endl;}
    cout<<"8.  Four of a kind:      "; if (!isPlayed(7)){cout<<"-\n";} else {cout<<arrRow[7].getScore()<<endl;}
    cout<<"9.  Full house:          "; if (!isPlayed(8)){cout<<"-\n";} else {cout<<arrRow[8].getScore()<<endl;}
    cout<<"10. Small straight:      "; if (!isPlayed(9)){cout<<"-\n";} else {cout<<arrRow[9].getScore()<<endl;}
    cout<<"11. Large Straight:      "; if (!isPlayed(10)){cout<<"-\n";} else {cout<<arrRow[10].getScore()<<endl;}
    cout<<"12. Chance:              "; if (!isPlayed(11)){cout<<"-\n";} else {cout<<arrRow[11].getScore()<<endl;}
    cout<<"13. Yahtzee:             "; if (!isPlayed(12)){cout<<"-\n";} else {cout<<arrRow[12].getScore()<<endl;}
    cout<<"Total:                   "<<getTotalScore()<<endl;
}


int Game::getUpperScore() {
    // getting score from first six rows
    int upperScore=0;
    for (int i=0;i<6;++i){
        upperScore+= arrRow[i].getScore();
    }
    return upperScore;
}


int Game::getLowerScore() {
    // getting score from last 7 rows
    int lowerScore=0;
    for (int i=6;i<13;++i){
        lowerScore+= arrRow[i].getScore();
    }
    return lowerScore;
}


int Game::getBonusScore() {
    // checking of upper score was above 63 and setting bonus accordingly
    int bonusScore=0;
    if (getUpperScore()>63){bonusScore+=35;}
    return bonusScore;
}


int Game::getTotalScore() {
    // getting total score
    int totalScore= getUpperScore()+ getLowerScore()+ getBonusScore();
    return totalScore;
}


void Game::play(Hand *hand, int row) {
    // calculating the score and updating row object in the vector
    int score=calcScore(hand, row);
    arrRow[row].setScore(score);
    arrRow[row].setStatus(1);
}


bool Game::isPlayed(int row) {
    // checking if row was already played
    if (arrRow[row].getStatus()==0){return false;}
    else {return true;}
}


bool Game::isFinished() {
    // checking if all rows were played
    for (int i=0;i<13;++i){
        if (arrRow[i].getStatus()==0){return 0;}
    }
    return 1;
}

//#######################################################################################

//The run function is the main loop of your program
void run() {
    // declaring class objects and hand pointer
    Hand hand;
    Hand* handPtr=&hand;
    Game game;
    // setting row names
    game.arrRow[0].setName("Ones");
    game.arrRow[1].setName("Twos");
    game.arrRow[2].setName("Threes");
    game.arrRow[3].setName("Fours");
    game.arrRow[4].setName("Fives");
    game.arrRow[5].setName("Sixes");
    game.arrRow[6].setName("Three of a kind");
    game.arrRow[7].setName("Four of a kind");
    game.arrRow[8].setName("Full house");
    game.arrRow[9].setName("Small straight");
    game.arrRow[10].setName("Large straight");
    game.arrRow[11].setName("Chance");
    game.arrRow[12].setName("Yahtzee");
    string diceKept;
    int rowPlayed;
    //Game *gamePtr=&game;
    // running loop till all rows are played
    while (!game.isFinished()) {
        // setting all dice to roll
        for (int j=0;j<5;++j){
            hand.arrDice[j].dontKeep();
        }
        hand.play();
        game.show();
        // displaying hand and asking user dice to keep
        for (int i = 0; i < 2; ++i) {
            cout << "Hand: ";
            hand.play();
            hand.show();
            for (int j=0;j<5;++j){
                hand.arrDice[j].dontKeep();
            }
            cout << "Keep Dice (s to stop rolling): ";
            cin >> diceKept;
            // breaking out if user enters 's'
            if (diceKept == "s" || diceKept=="S") { break; }
            hand.setSelection(diceKept);
        }
        if (diceKept!="s") {
            cout << "Hand: ";
            hand.play();
            hand.show();
        }
        // asking user which row to play
        cout << "Select a combination to play: ";
        cin >> rowPlayed;
        // jumping to start of loop if user enters invalid response
        if (rowPlayed>13 || rowPlayed<1){ continue;}
        // adjusting row to match row index
        rowPlayed--;
        // loop to print message if user tries to play a row that has already been played
        while (game.arrRow[rowPlayed].getStatus()){
            cout<<"This combination has been played. Select another one: ";
            cin>>rowPlayed;
            rowPlayed--;
        }
        // playing the row
        game.play(handPtr, rowPlayed);
    }
    // displaying the board and total score one last time
    game.show();

}


// function to test cases
void test_case() {
    Game game;
    Hand hand1;
    Hand* hand = &hand1;
    hand->getDice(0)->setValue(1);
    hand->getDice(1)->setValue(2);
    hand->getDice(2)->setValue(3);
    hand->getDice(3)->setValue(4);
    hand->getDice(4)->setValue(5);

    bool check1 = true;
    if (game.calcScore(hand, LARGE_STRAIGHT) != 40) {
        check1 = false;
    }
    if (check1) {
        cout << "check 1 passed\n";
    }

    hand->getDice(0)->setValue(2);
    hand->getDice(1)->setValue(6);
    hand->getDice(2)->setValue(4);
    hand->getDice(3)->setValue(3);
    hand->getDice(4)->setValue(5);

    bool check2 = true;
    if (game.calcScore(hand, LARGE_STRAIGHT) != 40) {
        check2 = false;
    }

    if (check2) {
        cout << "check 2 passed\n";
    }

    hand->getDice(0)->setValue(3);
    hand->getDice(1)->setValue(2);
    hand->getDice(2)->setValue(5);
    hand->getDice(3)->setValue(6);
    hand->getDice(4)->setValue(3);

    bool check3 = true;
    if (game.calcScore(hand, LARGE_STRAIGHT) != 0) {
        check3 = false;
    }

    if (check3) {
        cout << "check 3 passed\n";
    }

    hand->getDice(0)->setValue(1);
    hand->getDice(1)->setValue(2);
    hand->getDice(2)->setValue(3);
    hand->getDice(3)->setValue(4);
    hand->getDice(4)->setValue(6);

    bool check4 = true;
    if (game.calcScore(hand, LARGE_STRAIGHT) != 0) {
        check4 = false;
    }

    if (check4) {
        cout << "check 4 passed\n";
    }


}


int main() {
    srand(time(0));
    run();
    test_case();
    return 0;}
