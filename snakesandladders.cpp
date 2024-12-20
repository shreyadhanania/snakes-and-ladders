//C++ Project on Snakes and Ladders by Shreya Dhanania

#include<iostream> //standard I/O
#include<cstdlib>  //for dice roll 
#include<ctime>    //for dice roll 
#include <SFML/Audio.hpp>  //for sound effects
using namespace std;

#define MAX_PLAYERS 4

//class SoundManager
class SoundManager{
    public: 
    //Sound Buffers and Sound Objects for all 4 sounds 
      sf::SoundBuffer dice_buffer, snakes_buffer, ladders_buffer, winner_buffer;  
      sf::Sound dice_sound, snakes_sound, ladders_sound, winner_sound;

    void load_sounds();
    void play_dice_sound();
    void play_snakes_sound();
    void play_ladders_sound();
    void play_winner_sound();
};

//class Player
class Player{
    public:
      int current_position; 

      void initial_position(int in_position); 
      void move(SoundManager S_Manager);
      int get_position();
};

//class Board
class Board{
    public:
      int snakes[101] = {0};
      int ladders[101] = {0};

      void add_snake(int start, int end);
      void add_ladder(int start, int end);
      int update_position(Player &player, SoundManager S_Manager);
      void print_board(Player player[],int max_players);
};

// Function to load all sounds
void SoundManager :: load_sounds() {
    // Load each sound buffer from a file
      if (!dice_buffer.loadFromFile("Dice.mp3")) {
        cout << "Error loading dice sound!" << endl;
      }
      if (!snakes_buffer.loadFromFile("snakes.mp3")) {
        cout << "Error loading snake sound!" << endl;
      }
      if (!ladders_buffer.loadFromFile("ladders.mp3")) {
        cout << "Error loading ladder sound!" << endl;
      }
      if (!winner_buffer.loadFromFile("winner.mp3")) {
        cout<< "Error loading winner sound!" << endl;
      }

   // Associate each sound buffer with its sound
    dice_sound.setBuffer(dice_buffer);
    snakes_sound.setBuffer(snakes_buffer);
    ladders_sound.setBuffer(ladders_buffer);
    winner_sound.setBuffer(winner_buffer);
}   

// Function to play a specific sound
void SoundManager :: play_dice_sound() { 
    dice_sound.play();
    while (dice_sound.getStatus() == sf::Sound::Playing) {
        sf::sleep(sf::seconds(0.1f));  // wait for the sound to finish
    }
}
void SoundManager :: play_snakes_sound() { 
    snakes_sound.play();
    while (snakes_sound.getStatus() == sf::Sound::Playing) {
        sf::sleep(sf::seconds(0.1f));  // wait for the sound to finish
    }
}
void SoundManager :: play_ladders_sound() { 
    ladders_sound.play();
    while (ladders_sound.getStatus() == sf::Sound::Playing) {
        sf::sleep(sf::seconds(0.1f));  // wait for the sound to finish
    }
}
void SoundManager :: play_winner_sound() { 
    winner_sound.play();
    while (winner_sound.getStatus() == sf::Sound::Playing) {
        sf::sleep(sf::seconds(0.1f));  // wait for the sound to finish
    }
}

// Helper Function to roll the dice randomly between 1-6
int roll_dice(SoundManager S_Manager) {
    int dice = rand() % 6 + 1;
    S_Manager.play_dice_sound(); // Play sound when dice is rolled
    return dice;
}

//Member function of Player 
void Player:: initial_position(int in_position){
    current_position = in_position;
}

//Member function of Player 
void Player:: move(SoundManager S_Manager){
    int dice = roll_dice(S_Manager);
    cout<<dice << " is rolled!"<<endl;
    current_position = current_position + dice;
}

//Member function of Player 
int Player:: get_position(){
    if (current_position > 100){   //helps display winner on cell 100 if they go beyond 100
        current_position = 100;
    }
    return current_position;
}
  
//Member function of Board to add snake 
void Board:: add_snake(int start, int end){
    snakes[start] = end;
}

//Member function of Board to add ladder 
void Board:: add_ladder(int start, int end){
    ladders[start] = end;
}

//Member function of Board to update position of players after roll on the board
int Board:: update_position(Player &player, SoundManager S_Manager){
    int position = player.get_position();

    //check if there is a snake at the current position
    while (snakes[position] != 0) {
       cout << "Oops! Player encountered a 🐍. Moving down from " << position << " to " << snakes[position] << "." << endl;
       player.initial_position(snakes[position]); // Calculate position after snake encounter
       position = player.get_position();  // change position after snake encounter
       S_Manager.play_snakes_sound(); // Play sound when player encounters a snake
    }

    while (ladders[position] != 0) {
       cout << "Yay! Player encountered a 🪜. Going up from " << position << " to " << ladders[position] << "." << endl;
       player.initial_position(ladders[position]);  // calculate position after ladder encounter
       position = player.get_position();  // change position after ladder encounter
       S_Manager.play_ladders_sound(); // Play sound when player encounters a ladder
    }

    // Return the updated position of the player
    return player.get_position();
}

//Member function of Board to print the board with the correct position of players after each roll
void Board::print_board(Player player[],int max_players) {

    int player_positions[101] = {0};  //made the starting position of all players 0
    for (int i = 0; i < max_players; ++i) {
        player_positions[player[i].get_position()] = i + 1; //i+1 because i is starting from 0 and players from 1
    }

    int cell = 100;

    // Loop through the 10x10 matrix to print the board in a zigzag format 
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < 10; j++) {
                cout << "|";
                if (player_positions[cell] != 0) {
                    cout << "[P" << player_positions[cell] << "]"; // Mark player's position with [P_]
                }
                else if (snakes[cell] != 0) {
                    cout << " 🐍 "; // Display for snake
                } 
                else if (ladders[cell] != 0) {
                    cout << " 🪜  "; // Display for ladder
                } 
                else {
                    cout << " " << (cell < 10 ? " " : "") << cell << " "; // Display the cell number if no snake/ladder/player at that position
                }
                cell--;
            }
        } else {
            int temp = cell - 9;
            for (int j = 0; j < 10; j++) {
                cout << "|";
                if (player_positions[temp] != 0) {
                    cout << "[P" << player_positions[temp] << "]"; // Mark player's position with [P_]
                } 
                else if (snakes[temp] != 0) {
                    cout << " 🐍 "; // Display for snake
                } 
                else if (ladders[temp] != 0) {
                    cout << " 🪜  "; // Display for ladder
                } 
                else {
                    cout << " " << (temp < 10 ? " " : "") << temp << " "; // Display the cell number if no snake/ladder/player at that position
                }
                temp++;
            }
            cell -= 10;
        }
        cout << "|" << endl;

        for(int j = 0; j < 10; ++j){
            cout << "-----";
        }
        cout << endl;
    }
}

//Helper Function: set up Snakes & Ladders on the board using Board Class and member functions 
void snakes_ladders(Board &game_board) {
  game_board.add_snake(18,6);
  game_board.add_snake(29,7);
  game_board.add_snake(61,16);
  game_board.add_snake(72,47);
  game_board.add_snake(96,76);
    
  game_board.add_ladder(2,38);
  game_board.add_ladder(9,14);
  game_board.add_ladder(15,82);
  game_board.add_ladder(16,54);
  game_board.add_ladder(50,91);
  game_board.add_ladder(74,87);
}

//Helper Function --> Feature: Begin game only when player rolls 6
bool begin_gameplay(Player player, SoundManager S_Manager){
    int dice = roll_dice(S_Manager);
    cout << dice << " is rolled!" <<endl;

    if (dice == 6){
        cout << "Player rolled a 6 and can begin the game now!" << endl << endl;
        return true;
    }
    else{
        cout << "You can't begin until 6 is rolled!" << endl << endl;
        return false;
    }
}

//Helper Function --> Feature: Check if number of players is within limit (Valid range 2-4 players)
bool check_player_range(int max_players) {
    if (max_players > MAX_PLAYERS || max_players < 2) {
        cout << "Error: Number of players must be between 2 and " << MAX_PLAYERS << "." << endl;
        return false; 
    }
    return true;
}

//Helper Function to check if there is a winner 
bool winner(Player player, int player_number, SoundManager S_Manager) {
    if (player.get_position() == 100) {
        cout << "Congratulations! Player " << player_number << " won!" << endl;
        S_Manager.play_winner_sound(); // Play the winner sound
        return true;
    }
    return false;
}

//Helper Function to handle the main flow of the game
void game_flow(Board &game_board, Player player[], int max_players, SoundManager S_Manager) {
    bool begin[MAX_PLAYERS] = {0};  // setting up begin gameplay feature

    while (true) {
        for (int i = 0; i < max_players; i++) {  //loop allows players to take turns 
            cout << "Player " << (i + 1) << "'s turn:";  //display which player's turn to roll

            cout<<" Press enter to roll the dice...";  //Enter key to roll dice 
            cin.get();  

            if (!begin[i]){    
                if (begin_gameplay(player[i], S_Manager))  //checks if player rolled 6 enter the main game flow 
                    begin[i] = true;
                continue; //move to next player 
            }

            //main game flow
            player[i].move(S_Manager);   //game flow after 6 is rolled by player
            cout << "Player " << (i + 1) << " is now at position " << player[i].get_position() << "." << endl;
            game_board.update_position(player[i], S_Manager);
            game_board.print_board(player, max_players);
            cout << endl;

            if (winner(player[i], i+1, S_Manager)) //check for a winner
              return;
        }
    }
}

//main function
int main() {
    srand(time(0));  // to generate a random dice roll value between 1-6 

    // Load the sounds before the game begins
    SoundManager S_Manager;
    S_Manager.load_sounds();

    // set number of players by taking input of players 
    int max_players; 
    cout << "Enter the number of players: "; 
    cin >> max_players;
    cin.ignore();  //to ensure that the first chance of player 1 doesn't get played automatically 

    //Calling function --> checking the number of players
    if (!check_player_range(max_players)) {
        return 1;
    }

    // Players array with number of players 
    Player player[MAX_PLAYERS]; 

    //To make use of the board class in main 
    Board game_board;

    //Calling function --> to set up snakes and ladders on the baord 
    snakes_ladders(game_board);

    //Setting the start position of every player to 0 using Player member function 
    for (int i = 0; i < max_players; i++) {
        player[i].initial_position(0);
    }  

    cout<<"The inital game board is below."<<endl;   
    game_board.print_board(player, max_players);  //print game board 

    cout<<"=============================="<<endl;
    cout<<"Let the game begin!"<<endl;
    cout<<"Remember you can only start once you roll a 6!"<<endl<<endl;

    //call the game_flow function 
    game_flow(game_board, player, max_players, S_Manager);

    return 0;
}

