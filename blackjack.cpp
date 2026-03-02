#include <iostream>
#include <random>
#include <ctime>
using namespace std;

// Convert card index (0–51) to Blackjack value
int cardValue(int card) {
    int rank = card % 13;    
    if (rank == 0) return 11;      // Ace
    else if (rank >= 10) return 10; // J, Q, K
    else return rank + 1;          // 2–10
}

// Convert card index to name (no <string> used)
void printCard(int card) {
    const char* ranks[13] = {
        "A","2","3","4","5","6","7","8","9","10","J","Q","K"
    };
    const char* suits[4] = {"S","H","D","C"};

    cout << ranks[card % 13] << suits[card / 13];
}

// Calculate hand value (with Ace adjustment)
int handValue(int hand[], int count) {
    int total = 0;
    int aces = 0;

    for (int i = 0; i < count; i++) {
        int v = cardValue(hand[i]);
        total += v;
        if (v == 11) aces++;
    }

    // Reduce Ace from 11 → 1 if needed
    while (total > 21 && aces > 0) {
        total -= 10;
        aces--;
    }

    return total;
}

int main() {
    // Deck
    int deck[52];
    for (int i = 0; i < 52; i++) deck[i] = i;

    // RNG shuffle (manual Fisher–Yates)
    mt19937 rng(time(0));
    for (int i = 51; i > 0; i--) {
        uniform_int_distribution<int> dist(0, i);
        int j = dist(rng);
        int t = deck[i];
        deck[i] = deck[j];
        deck[j] = t;
    }

    // Hands
    int player[12], dealer[12];
    int pCount = 0, dCount = 0;
    int deckPos = 0;

    // Initial deal
    player[pCount++] = deck[deckPos++];
    dealer[dCount++] = deck[deckPos++];
    player[pCount++] = deck[deckPos++];
    dealer[dCount++] = deck[deckPos++];

    cout << "Dealer shows: ";
    printCard(dealer[0]);
    cout << "\n";

    bool playerBust = false;

    // Player turn
    while (true) {
        cout << "\nYour hand: ";
        for (int i = 0; i < pCount; i++) {
            printCard(player[i]);
            cout << " ";
        }
        cout << "(value = " << handValue(player, pCount) << ")\n";

        if (handValue(player, pCount) > 21) {
            cout << "You bust!\n";
            playerBust = true;
            break;
        }

        cout << "Hit or stand (h/s)? ";
        char c;
        cin >> c;

        if (c == 's' || c == 'S')
            break;

        player[pCount++] = deck[deckPos++];
    }

    // Dealer turn
    if (!playerBust) {
        cout << "\nDealer's hand: ";
        for (int i = 0; i < dCount; i++) {
            printCard(dealer[i]);
            cout << " ";
        }
        cout << "(value = " << handValue(dealer, dCount) << ")\n";

        while (handValue(dealer, dCount) < 17) {
            dealer[dCount++] = deck[deckPos++];
            cout << "Dealer hits: ";
            printCard(dealer[dCount - 1]);
            cout << "\n";
        }

        cout << "Dealer final value = " << handValue(dealer, dCount) << "\n";
    }

    // Results
    int pVal = handValue(player, pCount);
    int dVal = handValue(dealer, dCount);

    cout << "\n=== Result ===\n";

    if (playerBust)
        cout << "Dealer wins!\n";
    else if (dVal > 21)
        cout << "Dealer busts — you win!\n";
    else if (pVal > dVal)
        cout << "You win!\n";
    else if (pVal < dVal)
        cout << "Dealer wins!\n";
    else
        cout << "Tie!\n";

    return 0;
}
