#include <iostream>
#include <vector>
#include <string>

using namespace std; // Add this line

// Separate Bet class
class Bet {
public:
    string person;
    double amount;
    string outcome;
};

class BettingPool {
public:
    // Function to add a bet to the pool
    void AddBet(const string& person, double amount, const string& outcome) {
        bets.push_back({person, amount, outcome});
    }

    // Function to calculate the total pot
    double CalculateTotalPot() const {
        double totalPot = 0.0;
        for (const Bet& bet : bets) {
            totalPot += bet.amount;
        }
        return totalPot;
    }

    // Function to display pool information
    void DisplayPoolInfo() const {
        cout << "Betting Pool Information" << endl;
        cout << "Total Pot: $" << CalculateTotalPot() << endl;
        cout << "Bets:" << endl;
        for (const Bet& bet : bets) {
            cout << bet.person << " bet $" << bet.amount << " on " << bet.outcome << endl;
        }
    }

    // Function to clear all bets from the pool
    void ClearBets() {
        bets.clear();
    }

private:
    vector<Bet> bets;
};

int main() {
    // Create a betting pool
    BettingPool pool;

    // Add bets to the pool
    pool.AddBet("Alice", 50.0, "Team A");
    pool.AddBet("Bob", 30.0, "Team B");
    pool.AddBet("Charlie", 20.0, "Team A");

    // Display pool information
    pool.DisplayPoolInfo();

    // Clear all bets
    pool.ClearBets();

    return 0;
}
