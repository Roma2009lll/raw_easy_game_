#include<iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include<unordered_map>
#include<map>
using namespace std;




enum Suit {
    HEARTS,
    DIAMONDS,    
    CLUBS,       
    SPADES       
};
enum Rank {
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    TEN = 10,
    JACK = 11,
    QUEEN = 12,
    KING = 13,
    ACE = 14
};
enum HandRank {
    HIGH_CARD = 0,
    PAIR = 1,
    TWO_PAIR = 2,
    THREE_OF_KIND = 3,
    STRAIGHT = 4,
    FLUSH = 5,
    FULL_HOUSE = 6,
    FOUR_OF_KIND = 7,
    STRAIGHT_FLUSH = 8,
    ROYAL_FLUSH = 9
};
enum CompareResult {
    PLAYER1_WINS = 1,
    PLAYER2_WINS = 2,
    TIE = 0
};
class Card {
private:
    Suit s1;
    Rank r1;
public:
    Card(Rank r, Suit s): s1(s), r1(r){}

    Suit getSuit() {
        return this->s1;

    }
    Rank getRank() {
        return this->r1;

    }
    
   friend  ostream& operator << ( ostream& os,const Card& a2);
   friend  bool operator==(const Card& a1, const Card& a2);
   friend bool operator<(const Card& a1, const Card& a2);
   friend bool operator>(const Card& a1, const Card& a2);
};
ostream& operator << (ostream& os, const Card& a2) {
    os<< "Rank:" << a2.r1 << " Suit:" << a2.s1 << endl;
    return os;
}


bool operator==(const Card& a1, const Card& a2) {

    if (a1.r1 == a2.r1) {
        return true;

    }
    else {
        return false;


    }



}

class Deck {
private:
    vector<Card> decks;
public:
    Deck() {

        decks.reserve(52);
        Suit s0[] = { HEARTS,DIAMONDS,CLUBS,SPADES };
        Rank r0[] = { TWO ,THREE ,FOUR ,FIVE ,SIX ,SEVEN ,EIGHT ,NINE ,TEN,JACK,QUEEN, KING , ACE };
        for (Suit p : s0) {
            for (Rank p1 : r0) {
                decks.push_back(Card(p1,p));

            }
        }
    }

    void shuffle0() {
        random_device rd;
        mt19937 g(rd());
        std::shuffle(decks.begin(), decks.end(), g);



    }

   Card* get_card() {
        if (!decks.empty()) {
            Card* p0 = new Card(decks.back());
            decks.pop_back();
            return p0;


        }
        
        cout << "Deck is empty" << endl;
        return nullptr;

        
   }
   int get_size() {
       return decks.size();

   }
   void display() {
       for (auto p : decks) {
           cout << "Rank:" << p.getRank() << " Suit:" <<p.getSuit() << endl;
       }
   }
};






bool operator<(const Card& a1, const Card& a2) {
    return a1.r1 < a2.r1;
}

bool operator>(const Card& a1, const Card& a2) {
    return a1.r1 > a2.r1;
}


map<Rank, int> count(vector<Card>& hand) {
    map<Rank, int> count;
    for (auto p : hand) {
        count[p.getRank()]++;

    }
    return count;
}
bool isPair(vector<Card>& hand) {
    map<Rank, int> count0 = count(hand);
    for (auto it = count0.begin(); it != count0.end(); it++) {
        if (it->second > 1) {
            return true;


        }
    }
    return false;
}
bool isTwoPair(vector<Card>& hand) {
    map<Rank, int> count0 = count(hand);
    int true0 = 0;
    for (auto it = count0.begin(); it != count0.end(); it++) {
        if (it->second == 2) {
            true0++;
            

        }
    }
    return true0 == 2;
   

}
bool isThreeOfKind(vector<Card>& hand) {
    map<Rank, int> count0 = count(hand);
    int true0 = 0;
    for (auto it = count0.begin(); it != count0.end(); it++) {
        if (it->second ==3) {
            
            true0++;

        }
    }
    return true0==3;
}

bool isStraight(vector<Card>& hand) {
    std::sort(hand.begin(), hand.end(), [](Card& a, Card& b) {
        Rank a1 = a.getRank();
        Rank b1 = b.getRank();
        return a1 < b1;//що тут робиться

    });

    for (int i = 0; i < hand.size()-1; i++) {
        Rank a1 = hand[i+1].getRank();
        Rank b1 = hand[i].getRank();
        if (a1 - b1 != 1) {
            return false;

        }
    }
    return true;
}

bool isFlush(vector<Card>& hand) {
    Suit temp = hand[0].getSuit();


    for (auto p : hand) {
        Suit temp0 = p.getSuit();
        if (temp != temp0) {
            return false;

        }

    }
    return true;

}
bool isFullHouse(vector<Card>& hand) {
    map<Rank, int> count0 = count(hand);
    bool isPair = false;
    bool isTree = false;
    for (auto p : count0) {
        if (p.second == 2) {
            isPair = true;
        }
        if (p.second == 3) {
            isTree = true;
        }
    }
    return isPair && isTree;
}
bool isFourOfKind(vector<Card>& hand) {
    map<Rank, int> count0 = count(hand);
    int true0 = 0;
    for (auto it = count0.begin(); it != count0.end(); it++) {
        if (it->second ==4 ) {
            return true;

        }
    }
    return false;
   
}
bool isStraightFlush(vector<Card>& hand) {
    return isStraight(hand) && isFlush(hand);
    
}
bool isRoyalFlush(vector<Card>& hand) {
    if (!isStraightFlush(hand)) return false;
    Rank maxRank = hand[0].getRank();
    for (auto& c : hand) {
        if (c.getRank() > maxRank) {
            maxRank = c.getRank();
        }
    }
    return maxRank == ACE;  
}


HandRank evaluete(vector<Card>& hand) {
    std::sort(hand.begin(), hand.end(), [](Card& a, Card& b) {
        Rank a1 = a.getRank();
        Rank b1 = b.getRank();
        return a1 > b1;

    });
    if (isRoyalFlush(hand)) return ROYAL_FLUSH;
    if (isStraightFlush(hand)) return STRAIGHT_FLUSH;
    if (isFourOfKind(hand)) return FOUR_OF_KIND;
    if (isFullHouse(hand)) return FULL_HOUSE;
    if (isFlush(hand)) return FLUSH;
    if (isStraight(hand)) return STRAIGHT;
    if (isThreeOfKind(hand)) return THREE_OF_KIND;
    if (isTwoPair(hand)) return TWO_PAIR;
    if (isPair(hand)) return PAIR;
    return HIGH_CARD;





}

Rank getHighestRank(vector<Card>& hand) {
    Rank temp = hand[0].getRank();

    for (auto p : hand) {
        Rank temp0 = p.getRank();

        if (temp0 > temp) {
            temp = temp0;

        }

    }
    return temp;


}

Rank getPairRank(vector<Card>& hand) {
    map<Rank, int> count0 = count(hand);
    for (auto it = count0.begin(); it != count0.end(); it++) {
        if (it->second == 2) {
            
            return it->first;


        }
    }
    return TWO;
    

}
CompareResult compareHighCard(vector<Card>& hand1, vector<Card>& hand2) {
    std::sort(hand1.begin(), hand1.end(), [](Card& a, Card& b) {
        Rank a1 = a.getRank();
        Rank b1 = b.getRank();
        return a1 > b1;

    });
    std::sort(hand2.begin(), hand2.end(), [](Card& a, Card& b) {
        Rank a1 = a.getRank();
        Rank b1 = b.getRank();
        return a1 > b1;

    });
    for (int i = 0; i < hand1.size(); i++) {
        if (hand1[i] > hand2[i]) {
            return PLAYER1_WINS;

        }
        if (hand1[i] < hand2[i]) {
            return PLAYER2_WINS;

        }



    }
    return TIE;


}

CompareResult comparePairs(vector<Card>& hand1, vector<Card>& hand2) {
    Rank a1 = getPairRank(hand1);
    Rank a2= getPairRank(hand2);
    if (a1 > a2) {
        return PLAYER1_WINS;
    }
    if (a1 < a2) {
        return PLAYER2_WINS;
    }
    return compareHighCard(hand1, hand2);
}

Rank get_ThreeOfKindRank(vector<Card>& hand) {
    map<Rank, int> count0 = count(hand);
    int true0 = 0;
    for (auto it = count0.begin(); it != count0.end(); it++) {
        if (it->second == 3) {

            return it->first;


        }
    }
    return TWO;
}

CompareResult compareThreeOfKind(vector<Card>& hand1, vector<Card>& hand2) {
    Rank a1 = get_ThreeOfKindRank(hand1);
    Rank a2 = get_ThreeOfKindRank(hand2);
    if (a1 > a2) {
        return PLAYER1_WINS;
    }
    if (a1 < a2) {
        return PLAYER2_WINS;
    }
    return compareHighCard(hand1, hand2);
}

Rank get_FourOfKind(vector<Card>& hand) {
    map<Rank, int> count0 = count(hand);
    int true0 = 0;
    for (auto it = count0.begin(); it != count0.end(); it++) {
        if (it->second == 4) {

            return it->first;


        }
    }
    return TWO;
}
CompareResult compareFourOfKind(vector<Card>& hand1, vector<Card>& hand2) {
    Rank a1 = get_FourOfKind(hand1);
    Rank a2 = get_FourOfKind(hand2);
    if (a1 > a2) {
        return PLAYER1_WINS;
    }
    if (a1 < a2) {
        return PLAYER2_WINS;
    }
    return compareHighCard(hand1, hand2);
}

CompareResult game(vector<Card>& hand1,vector<Card>& hand2) {
    HandRank rank1 = evaluete(hand1);
    HandRank rank2 = evaluete(hand2);
    if (rank1 > rank2) {
        return PLAYER1_WINS;

    }
    if(rank1 < rank2){
        return PLAYER2_WINS;
    }

    switch (rank1) {
    case PAIR:
        return comparePairs(hand1, hand2);

    case THREE_OF_KIND:
        return compareThreeOfKind(hand1, hand2);

    case FOUR_OF_KIND:
        return compareFourOfKind(hand1, hand2);

    case HIGH_CARD:
        return compareHighCard(hand1,hand2);
    case FLUSH:   
        return compareHighCard(hand1, hand2);
    case STRAIGHT:  
        return compareHighCard(hand1, hand2);
    case STRAIGHT_FLUSH:
        return compareHighCard(hand1, hand2);
    case ROYAL_FLUSH: 
        
        return compareHighCard(hand1, hand2);

    case TWO_PAIR:
        
        return compareHighCard(hand1, hand2);
       

    default:
        return TIE;  
    }


}


string handRankToString(HandRank rank) {
    switch (rank) {
    case ROYAL_FLUSH: return "Royal Flush";
    case STRAIGHT_FLUSH: return "Straight Flush";
    case FOUR_OF_KIND: return "Four of a Kind";
    case FULL_HOUSE: return "Full House";
    case FLUSH: return "Flush";
    case STRAIGHT: return "Straight";
    case THREE_OF_KIND: return "Three of a Kind";
    case TWO_PAIR: return "Two Pair";
    case PAIR: return "Pair";
    case HIGH_CARD: return "High Card";
    default: return "Unknown";
    }
}
string Suit_to_string(Suit s1) {
    switch (s1) {
    case 0:
        return "HEARTS";
    case 1:
        return "DIAMONDS";
    case 2:
        return "CLUBS";
    case 3:
        return "SPADES";
   
    }
}

void display_hand(const vector<Card*>& hand0, string name) {
    cout << "Player:" << name << endl;
    for (int i = 0; i < hand0.size(); i++) {
        cout <<"Rank:" << hand0[i]->getRank() << endl;
        cout << "Suit:" << Suit_to_string(hand0[i]->getSuit()) << endl;
    }
   
}

void play_game() {
    while (1) {
        string str;
        cout << "Start game(stop enter stop)" << endl;
        cin >> str;
        if (str == "stop") {
            break;

        }
        else {
            cout << "========== NEW GAME ==========" << endl;
            Deck deck;
            deck.shuffle0();
            vector<Card*> player1;
            player1.reserve(5);
            vector<Card*> computer;
            computer.reserve(5);
            for (int i = 0; i < 4; i++) {
                player1.push_back(deck.get_card());
                computer.push_back(deck.get_card());
            }
            display_hand(player1, "Your");
            vector<Card> player1_copy;
            player1_copy.reserve(player1.size());
            for (int i = 0; i < player1.size(); i++) {
                player1_copy.push_back(*player1[i]);

            }
            vector<Card>computer_copy;
            computer_copy.reserve(computer.size());
            for (int i = 0; i < computer.size(); i++) {
                computer_copy.push_back(*computer[i]);

            }
            HandRank rank1 = evaluete(player1_copy);
            cout << "Your hand:" << handRankToString(rank1) << endl;
            display_hand(computer,"Openent");
            HandRank rank2 = evaluete(computer_copy);
            cout << "Computer hand:" << handRankToString(rank2) << endl;
            CompareResult res= game(player1_copy,computer_copy);

            if (res == PLAYER1_WINS) {
                cout << "You won" << endl;

            }
            else if (res == PLAYER2_WINS) {
                cout << "Computer won" << endl;
            }
            else
            {
                cout << "Tie" << endl;
            }

            for (auto p : player1) {
                delete p;
            }
            for (auto p0 : computer) {
                delete p0;
            }
            cout << "Thanks for playing!" << endl;



        }

    }
}


int main() {
    play_game();
    return 0;
}





