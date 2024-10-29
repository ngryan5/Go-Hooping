/*
 * Author: Ryan Nguyen
 * Program description: This is a program for a terminal based game that is inspired by the NBA all-star 3pt contest. The game supports 2 players where each player is attempting to score as many 3pt
 * 	shots as possible from 5 racks of basketballs on different spots on the 3-pt line. One of these racks is the "money-ball rack" where each ball is worth double the amount of a normal ball and each player
 * 	will be able to pick where that rack goes. There are also two "starry balls" that are further back and placed in between racks 2 and 3 and racks 3 and 4 that are worth 3 points. 
 */
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

/*
    Function: chooseMoneyBallRack
    Description: Prompts the user to choose where they want the money-ball rack.
    Returns: int (1-5) representing where the money ball rack is on the court.
*/
int chooseMoneyBallRack() {
    int moneyBallRack;
    do {
        cout << "Where do you want to put your money-ball rack? Enter 1-5: ";
        cin >> moneyBallRack;
        if (moneyBallRack < 1 || moneyBallRack > 5) {
            cout << "Invalid input, try again." << endl;
        }
    } while (moneyBallRack < 1 || moneyBallRack > 5);

    return moneyBallRack;
}

/*
    Function: chooseShootingCapability
    Description: Prompts the user to enter their shooting capability (1-99), which determines their chance of making each shot.
    Returns: int (1-99) representing the shooting capability.
*/
int chooseShootingCapability() {
    int shootingCapability;
    do {
        cout << "Enter your shooting capability (1-99): ";
        cin >> shootingCapability;
        if (shootingCapability < 1 || shootingCapability > 99) {
            cout << "Invalid input, try again." << endl;
        }
    } while (shootingCapability < 1 || shootingCapability > 99);

    return shootingCapability;
}

/*
    Function: shotSuccessful
    Description: Determines if a shot is successful based on the shooting capability.
    Parameters: shootingCapability (int) - player's shooting capability percentage.
    Returns: bool - true if the shot is successful, false otherwise.
*/
bool shotSuccessful(int shootingCapability) {
    return rand() % 100 < shootingCapability;
}

/*
    Function: simulateRack
    Description: Simulates shooting for a given rack, updating the score and recording results for each shot.
    Parameters: 
        - position (int): The rack position (1-5).
        - isMoneyBallRack (bool): Whether the current rack is the money-ball rack.
        - results (char[]): Array to store the results of each shot.
        - rackScore (int&): Reference to store the rack score.
        - shootingCapability (int): Player's shooting capability percentage.
*/
void simulateRack(int position, bool isMoneyBallRack, char results[], int &rackScore, int shootingCapability) {
    rackScore = 0;

    for (int i = 0; i < 5; i++) {
        bool success = shotSuccessful(shootingCapability);

        if (isMoneyBallRack) {
            results[i] = success ? 'M' : '_';
            rackScore += success ? 2 : 0;
        } else {
            if (i == 4) {
                results[i] = success ? 'M' : '_';
                rackScore += success ? 2 : 0;
            } else {
                results[i] = success ? 'X' : '_';
                rackScore += success ? 1 : 0;
            }
        }
    }
}

/*
    Function: simulateStarryBall
    Description: Simulates shooting the starry ball, which is worth 3 points.
    Parameters:
        - isStarryRack (bool): Whether the starry ball should be simulated for the current rack.
        - rackScore (int&): Reference to store the score.
        - shootingCapability (int): Player's shooting capability percentage.
*/
void simulateStarryBall(bool isStarryRack, int &rackScore, int shootingCapability) {
    if (isStarryRack) {
        bool success = shotSuccessful(shootingCapability);
        if (success) {
            cout << "Starry: S | 3 pts" << endl;
            rackScore += 3;
        } else {
            cout << "Starry: _ | 0 pts" << endl;
        }
    }
}

/*
    Function: displayRackResults
    Description: Displays the results of a given rack, including whether the starry ball was made.
    Parameters:
        - results (char[]): Array storing the results of each shot in the rack.
        - rackScore (int): The score for the current rack.
        - isStarryRack (bool): Whether the starry ball should be simulated for the current rack.
        - shootingCapability (int): Player's shooting capability percentage.
*/
void displayRackResults(char results[], int rackScore, bool isStarryRack, int shootingCapability) {
    cout << "Rack: ";
    for (int i = 0; i < 5; i++) {
        cout << results[i] << " ";
    }
    cout << "| " << rackScore << " pts" << endl;

    simulateStarryBall(isStarryRack, rackScore, shootingCapability);
}

/*
    Function: playRound
    Description: Simulates playing a round for a single player.
    Parameters:
        - totalScore (int&): Reference to store the player's total score.
        - moneyBallRack (int): The position of the money-ball rack.
        - playerNumber (int): The player's number (e.g., Player 1, Player 2).
*/
void playRound(int &totalScore, int moneyBallRack, int playerNumber) {
    totalScore = 0;
    char results[5];
    int rackScore = 0;
    int shootingCapability = chooseShootingCapability();

    for (int i = 1; i <= 5; i++) {
        bool isMoneyBallRack = (i == moneyBallRack);
        bool isStarryRack = (i == 2 || i == 3);

        simulateRack(i, isMoneyBallRack, results, rackScore, shootingCapability);
        displayRackResults(results, rackScore, isStarryRack, shootingCapability);

        totalScore += rackScore;
    }

    cout << "Total score for Player " << playerNumber << ": " << totalScore << " pts" << endl;
}

/*
    Function: declareWinner
    Description: Determines and announces the player with the highest score.
    Parameters:
        - scores (int[]): Array containing the scores of all players.
        - N (int): Number of players.
*/
void declareWinner(int scores[], int N) {
    int highestScore = scores[0];
    for (int i = 1; i < N; i++) {
        if (scores[i] > highestScore) {
            highestScore = scores[i];
        }
    }

    cout << "Highest score is: " << highestScore << endl;
}

/*
    Function: playAgain
    Description: Prompts the user if they want to play another round.
    Returns: bool - true if the user wants to play again, false otherwise.
*/
bool playAgain() {
    int choice;
    do {
        cout << "Do you want to play again? (1-yes, 0-no): ";
        cin >> choice;
        if (choice != 1 && choice != 0) {
            cout << "Sorry, that’s not a valid input." << endl;
        }
    } while (choice != 1 && choice != 0);

    return choice == 1;
}

int main() {
    srand(time(nullptr));

    bool keepPlaying = true;
    while (keepPlaying) {
        int N;
        cout << "Enter the number of players: ";
        cin >> N;

        if (N < 2) {
            cout << "Number of players must be at least 2." << endl;
            continue;
        }

        int* scores = new int[N];
        for (int i = 0; i < N; i++) {
            cout << "Player " << i + 1 << ", it's your turn!" << endl;
            int moneyBallRack = chooseMoneyBallRack();
            playRound(scores[i], moneyBallRack, i + 1);
        }

        declareWinner(scores, N);
        delete[] scores;

        keepPlaying = playAgain();
    }

    cout << "Thanks for playing!" << endl;
    return 0;
}
