/*
    main.cpp
        
    Implements the user interface for hangman.
    
    assignment: CSCI 262 Project - Evil Hangman        

    author: Josh Mendelsohn

    last modified: October 16, 2020
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>

#include "hangman.h"

using namespace std;

// helper function prototypes
int get_integer(string prompt); // return a positive integer
char get_letter(string prompt); // return a valid lowercase letter
bool get_yesno(string prompt);  // return true == yes / false == no
vector<string> get_visuals(string prompt);   // returns the vector responsible for visuals
string trim(string s);          // remove leading/trailing whitespace

int main() {
    cout << "Welcome to Hangman!" << endl;
    cout << "===================" << endl << endl;

    // get the hangman object
    hangman game;
    
    // Keep playing the game until the user decides otherwise
    while (true) {

        int word_length = get_integer("How long of a word would you like to guess?");
        cout << endl;
        while (word_length != 28 && word_length != 29 && word_length != 24 && !(word_length >= 2 && word_length <= 22)){
            word_length = get_integer("Please input a valid word length (2 - 22, 24, 28, or 29).");
        }

        int num_guesses = get_integer("How many guesses would you like?");
        cout << endl;

        bool see_possible_words = get_yesno("Do you want to see how many possible words remain for each turn? (y/n)");
        cout << endl;

        bool visual_hang_man = get_yesno("Would you like to see a visual of the game (y/n)?");
        cout << endl;

        vector<string> visuals;
        if (visual_hang_man) {
            visuals = get_visuals("What style would you like (0/1, input 's' to see styles)?");
        }

        game.start_new_game(num_guesses, word_length);

        while (!game.is_won() && !game.is_lost()) {

            if (visual_hang_man){
                int guesses_used = num_guesses - game.get_guesses_remaining();
                if(guesses_used <= visuals.size() - 2){
                    cout << visuals[guesses_used];
                }
                else{
                    cout << visuals[visuals.size() - 1];
                }
            }

            cout << endl;
            cout << "Your word is: " << game.get_display_word() << endl;

            string already_guessed = game.get_guessed_chars();
            if (already_guessed.size() == 0) {
                cout << "You have not yet guessed any letters." << endl;
            } else {
                cout << "You have already guessed these letters: ";
                cout << already_guessed << endl;
            }

            if (see_possible_words){
                cout << "There are " << game.get_possible_word_count() << " possible words remaining." << endl;
            }

            cout << "You have " << game.get_guesses_remaining();
            cout << " guesses remaining." << endl << endl;

            char guess = get_letter("What is your next guess?");
            while (game.was_char_guessed(guess)) {
                cout << endl << "You already guessed that!" << endl;
                guess = get_letter("What is your next guess?");
            }
            cout << endl;

            bool good_guess = game.process_guess(guess);
            if (good_guess) {
                cout << "Good guess!" << endl;
            } else {
                cout << "Sorry, that letter isn't in the word." << endl;
            }

            if (game.is_won()) {
                cout << "Congratulations! You won the game!" << endl;
                cout << "The word was \"" << game.get_display_word() << "\"." << endl;
            }

            if (game.is_lost()) {
                cout << "Oh no! You lost!!!" << endl;
                cout << "My secret word was: " << game.get_hidden_word() << endl;
            }
        }

        cout << endl;
        if (!get_yesno("Would you like to play again (y/n)?")) break;
    }

    cout << endl << "Thank you for playing Hangman." << endl;

    return 0;
}

// Prompt for a positive integer response, re-prompting if invalid
// input is given. This is not super-robust - it really should work
// harder to filter out responses like "123foo", but oh well.
int get_integer(string msg) {
    while (true) {
        string input;    
        int result = 0;

        cout << msg << endl;
        getline(cin, input);

        result = atoi(input.c_str());
        if (result > 0) return result;

        cout << "I didn't understand that. Please enter a positive integer.";
        cout << endl;
    }
}
    
// Prompt for a letter of the alphabet, re-prompting if invalid
// input is given.
char get_letter(string msg) {
    while (true) {
        string input;    
 
        cout << msg << endl;
        getline(cin, input);

        input = trim(input);

        if (input.size() == 1) {
            char result = tolower(input[0]);
            if (result >= 'a' && result <= 'z') return result;
        }
        
        cout << "I didn't understand that. ";
        cout << "Please enter a letter of the alphabet.";
        cout << endl;
    }
}


// Prompt for a yes/no response, re-prompting if invalid
// input is given.
bool get_yesno(string msg) {
    while (true) {
        string input;    
 
        cout << msg << endl;
        getline(cin, input);

        input = trim(input);
        for (int i = 0; i < input.size(); i++) {
            input[i] = tolower(input[i]);
        }

        if (input == "y" || input == "yes") return true;
        if (input == "n" || input == "no") return false;
        
        cout << "I didn't understand that. ";
        cout << "Please enter y(es) or n(o).";
        cout << endl;
    }
}

string trim(string s) {
    int a, b;

    for (a = 0; a < s.size() && isspace(s[a]); a++);
    for (b = s.size() - 1; b >= a && isspace(s[b]); b--);
    
    return s.substr(a, b - a + 1);
}

vector<string> get_visuals(string prompt){
    while (true) {
        string input;
        vector<string> visuals;

        cout << prompt << endl;
        getline(cin, input);

        input = trim(input);

        if (input == "s") {
            cout << "Style 0:"
                    "  +----+     \n"
                    "  |    |     \n"
                    "  |    O     \n"
                    "  |  / | \\  \n"
                    "  |   / \\   \n"
                    "  |          \n"
                    "============ \n"
                    "             \n"
                    "Style 1:     \n"
                    "   ||============+          \n"
                    "   ||            |          \n"
                    "   ||         _______       \n"
                    "   ||        /       \\     \n"
                    "   ||       |  o   o  |     \n"
                    "   ||       |   ___   |     \n"
                    "   ||        \\_______/     \n"
                    "   ||        _ ===== _      \n"
                    "   ||       /         \\    \n"
                    "   ||      |           |    \n"
                    "   ||      |__|     |__|    \n"
                    "   ||      | |       | |    \n"
                    "   ||      | |       | |    \n"
                    "   ||      | |       | |    \n"
                    "   ||      \\@/_______\\@/  \n"
                    "   ||       |         |     \n"
                    "   ||       |   / \\   |    \n"
                    "   ||       |   | |   |     \n"
                    "   ||       |   | |   |     \n"
                    "   ||       |   | |   |     \n"
                    "   ||       |___| |___|     \n"
                    "   ||     /_____| |_____\\  \n"
                    "   ||                       \n"
                    "  ||||                      \n"
                    "|==========================|\n"
                    "                            \n";
        }
        if (input == "0"){
            visuals.push_back("  +----+     \n"
                              "  |    |     \n"
                              "  |          \n"
                              "  |          \n"
                              "  |          \n"
                              "  |          \n"
                              "============");
            visuals.push_back("  +----+     \n"
                              "  |    |     \n"
                              "  |    O     \n"
                              "  |          \n"
                              "  |          \n"
                              "  |          \n"
                              "============");
            visuals.push_back("  +----+     \n"
                              "  |    |     \n"
                              "  |    O     \n"
                              "  |    |     \n"
                              "  |          \n"
                              "  |          \n"
                              "============");
            visuals.push_back("  +----+     \n"
                              "  |    |     \n"
                              "  |    O     \n"
                              "  |  / |     \n"
                              "  |          \n"
                              "  |          \n"
                              "============");
            visuals.push_back("  +----+     \n"
                              "  |    |     \n"
                              "  |    O     \n"
                              "  |  / | \\  \n"
                              "  |          \n"
                              "  |          \n"
                              "============");
            visuals.push_back("  +----+     \n"
                              "  |    |     \n"
                              "  |    O     \n"
                              "  |  / | \\  \n"
                              "  |   /      \n"
                              "  |          \n"
                              "============");
            visuals.push_back("  +----+     \n"
                              "  |    |     \n"
                              "  |    O     \n"
                              "  |  / | \\  \n"
                              "  |   / \\   \n"
                              "  |          \n"
                              "============");

            return visuals;
        }
        if (input == "1"){
            visuals.push_back("   ||============+\n"
                              "   ||            |\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "  ||||\n"
                              "|==========================|");

            visuals.push_back("   ||============+\n"
                              "   ||            |\n"
                              "   ||         _______\n"
                              "   ||        /       \\\n"
                              "   ||       |         |\n"
                              "   ||       |         |\n"
                              "   ||        \\_______/\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "  ||||\n"
                              "|==========================|");

            visuals.push_back("   ||============+\n"
                              "   ||            |\n"
                              "   ||         _______\n"
                              "   ||        /       \\\n"
                              "   ||       |  o      |\n"
                              "   ||       |         |\n"
                              "   ||        \\_______/\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "  ||||\n"
                              "|==========================|");

            visuals.push_back("   ||============+\n"
                              "   ||            |\n"
                              "   ||         _______\n"
                              "   ||        /       \\\n"
                              "   ||       |  o   o  |\n"
                              "   ||       |         |\n"
                              "   ||        \\_______/\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "  ||||\n"
                              "|==========================|");

            visuals.push_back("   ||============+\n"
                              "   ||            |\n"
                              "   ||         _______\n"
                              "   ||        /       \\\n"
                              "   ||       |  o   o  |\n"
                              "   ||       |   ___   |\n"
                              "   ||        \\_______/\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "   ||\n"
                              "  ||||\n"
                              "|==========================|");

            visuals.push_back("   ||============+\n"
                              "   ||            |\n"
                              "   ||         _______\n"
                              "   ||        /       \\\n"
                              "   ||       |  o   o  |\n"
                              "   ||       |   ___   |\n"
                              "   ||        \\_______/\n"
                              "   ||          =====\n"
                              "   ||    \n"
                              "   ||     \n"
                              "   ||     \n"
                              "   ||     \n"
                              "   ||    \n"
                              "   ||      \n"
                              "   ||    \n"
                              "   ||     \n"
                              "   ||      \n"
                              "   ||       \n"
                              "   ||      \n"
                              "   ||      \n"
                              "   ||      \n"
                              "   ||     \n"
                              "   ||\n"
                              "  ||||\n"
                              "|==========================|");

            visuals.push_back("   ||============+\n"
                              "   ||            |\n"
                              "   ||         _______\n"
                              "   ||        /       \\\n"
                              "   ||       |  o   o  |\n"
                              "   ||       |   ___   |\n"
                              "   ||        \\_______/\n"
                              "   ||        _ ===== _\n"
                              "   ||       /         \\\n"
                              "   ||      |           |\n"
                              "   ||      |__|     |__|\n"
                              "   ||        |       |\n"
                              "   ||        |       |\n"
                              "   ||        |_______|\n"
                              "   ||    \n"
                              "   ||     \n"
                              "   ||      \n"
                              "   ||       \n"
                              "   ||      \n"
                              "   ||      \n"
                              "   ||      \n"
                              "   ||     \n"
                              "   ||\n"
                              "  ||||\n"
                              "|==========================|");

            visuals.push_back("   ||============+\n"
                              "   ||            |\n"
                              "   ||         _______\n"
                              "   ||        /       \\\n"
                              "   ||       |  o   o  |\n"
                              "   ||       |   ___   |\n"
                              "   ||        \\_______/\n"
                              "   ||        _ ===== _\n"
                              "   ||       /         \\\n"
                              "   ||      |           |\n"
                              "   ||      |__|     |__|\n"
                              "   ||      | |      |\n"
                              "   ||      | |      |\n"
                              "   ||      | |______|\n"
                              "   ||    \n"
                              "   ||     \n"
                              "   ||      \n"
                              "   ||       \n"
                              "   ||      \n"
                              "   ||      \n"
                              "   ||      \n"
                              "   ||     \n"
                              "   ||\n"
                              "  ||||\n"
                              "|==========================|");

            visuals.push_back("   ||============+\n"
                              "   ||            |\n"
                              "   ||         _______\n"
                              "   ||        /       \\\n"
                              "   ||       |  o   o  |\n"
                              "   ||       |   ___   |\n"
                              "   ||        \\_______/\n"
                              "   ||        _ ===== _\n"
                              "   ||       /         \\\n"
                              "   ||      |           |\n"
                              "   ||      |__|     |__|\n"
                              "   ||      | |       | |\n"
                              "   ||      | |       | |\n"
                              "   ||      | |_______| |\n"
                              "   ||    \n"
                              "   ||     \n"
                              "   ||      \n"
                              "   ||       \n"
                              "   ||      \n"
                              "   ||      \n"
                              "   ||      \n"
                              "   ||     \n"
                              "   ||\n"
                              "  ||||\n"
                              "|==========================|");

            visuals.push_back("   ||============+\n"
                              "   ||            |\n"
                              "   ||         _______\n"
                              "   ||        /       \\\n"
                              "   ||       |  o   o  |\n"
                              "   ||       |   ___   |\n"
                              "   ||        \\_______/\n"
                              "   ||        _ ===== _\n"
                              "   ||       /         \\\n"
                              "   ||      |           |\n"
                              "   ||      |__|     |__|\n"
                              "   ||      | |       | |\n"
                              "   ||      | |       | |\n"
                              "   ||      | |       | |\n"
                              "   ||        _________\n"
                              "   ||       |         |\n"
                              "   ||       |___/ \\___|\n"
                              "   ||       \n"
                              "   ||      \n"
                              "   ||      \n"
                              "   ||      \n"
                              "   ||     \n"
                              "   ||\n"
                              "  ||||\n"
                              "|==========================|");

            visuals.push_back("   ||============+\n"
                              "   ||            |\n"
                              "   ||         _______\n"
                              "   ||        /       \\\n"
                              "   ||       |  o   o  |\n"
                              "   ||       |   ___   |\n"
                              "   ||        \\_______/\n"
                              "   ||        _ ===== _\n"
                              "   ||       /         \\\n"
                              "   ||      |           |\n"
                              "   ||      |__|     |__|\n"
                              "   ||      | |       | |\n"
                              "   ||      | |       | |\n"
                              "   ||      | |       | |\n"
                              "   ||        _________\n"
                              "   ||       |         |\n"
                              "   ||       |   / \\___|\n"
                              "   ||       |   |\n"
                              "   ||       |   |\n"
                              "   ||       |   |\n"
                              "   ||       |___| \n"
                              "   ||     \n"
                              "   ||\n"
                              "  ||||\n"
                              "|==========================|");

            visuals.push_back("   ||============+\n"
                              "   ||            |\n"
                              "   ||         _______\n"
                              "   ||        /       \\\n"
                              "   ||       |  o   o  |\n"
                              "   ||       |   ___   |\n"
                              "   ||        \\_______/\n"
                              "   ||        _ ===== _\n"
                              "   ||       /         \\\n"
                              "   ||      |           |\n"
                              "   ||      |__|     |__|\n"
                              "   ||      | |       | |\n"
                              "   ||      | |       | |\n"
                              "   ||      | |       | |\n"
                              "   ||        _________\n"
                              "   ||       |         |\n"
                              "   ||       |   / \\   |\n"
                              "   ||       |   | |   |\n"
                              "   ||       |   | |   |\n"
                              "   ||       |   | |   |\n"
                              "   ||       |___| |___| \n"
                              "   ||     \n"
                              "   ||\n"
                              "  ||||\n"
                              "|==========================|");

            visuals.push_back("   ||============+\n"
                              "   ||            |\n"
                              "   ||         _______\n"
                              "   ||        /       \\\n"
                              "   ||       |  o   o  |\n"
                              "   ||       |   ___   |\n"
                              "   ||        \\_______/\n"
                              "   ||        _ ===== _\n"
                              "   ||       /         \\\n"
                              "   ||      |           |\n"
                              "   ||      |__|     |__|\n"
                              "   ||      | |       | |\n"
                              "   ||      | |       | |\n"
                              "   ||      | |       | |\n"
                              "   ||      \\@/________\n"
                              "   ||       |         |\n"
                              "   ||       |   / \\   |\n"
                              "   ||       |   | |   |\n"
                              "   ||       |   | |   |\n"
                              "   ||       |   | |   |\n"
                              "   ||       |___| |___| \n"
                              "   ||     \n"
                              "   ||\n"
                              "  ||||\n"
                              "|==========================|");

            visuals.push_back("   ||============+\n"
                              "   ||            |\n"
                              "   ||         _______\n"
                              "   ||        /       \\\n"
                              "   ||       |  o   o  |\n"
                              "   ||       |   ___   |\n"
                              "   ||        \\_______/\n"
                              "   ||        _ ===== _\n"
                              "   ||       /         \\\n"
                              "   ||      |           |\n"
                              "   ||      |__|     |__|\n"
                              "   ||      | |       | |\n"
                              "   ||      | |       | |\n"
                              "   ||      | |       | |\n"
                              "   ||      \\@/_______\\@/\n"
                              "   ||       |         |\n"
                              "   ||       |   / \\   |\n"
                              "   ||       |   | |   |\n"
                              "   ||       |   | |   |\n"
                              "   ||       |   | |   |\n"
                              "   ||       |___| |___| \n"
                              "   ||     \n"
                              "   ||\n"
                              "  ||||\n"
                              "|==========================|");

            visuals.push_back("   ||============+\n"
                              "   ||            |\n"
                              "   ||         _______\n"
                              "   ||        /       \\\n"
                              "   ||       |  o   o  |\n"
                              "   ||       |   ___   |\n"
                              "   ||        \\_______/\n"
                              "   ||        _ ===== _\n"
                              "   ||       /         \\\n"
                              "   ||      |           |\n"
                              "   ||      |__|     |__|\n"
                              "   ||      | |       | |\n"
                              "   ||      | |       | |\n"
                              "   ||      | |       | |\n"
                              "   ||      \\@/_______\\@/\n"
                              "   ||       |         |\n"
                              "   ||       |   / \\   |\n"
                              "   ||       |   | |   |\n"
                              "   ||       |   | |   |\n"
                              "   ||       |   | |   |\n"
                              "   ||       |___| |___| \n"
                              "   ||     /_____|\n"
                              "   ||\n"
                              "  ||||\n"
                              "|==========================|");

            visuals.push_back("   ||============+\n"
                              "   ||            |\n"
                              "   ||         _______\n"
                              "   ||        /       \\\n"
                              "   ||       |  o   o  |\n"
                              "   ||       |   ___   |\n"
                              "   ||        \\_______/\n"
                              "   ||        _ ===== _\n"
                              "   ||       /         \\\n"
                              "   ||      |           |\n"
                              "   ||      |__|     |__|\n"
                              "   ||      | |       | |\n"
                              "   ||      | |       | |\n"
                              "   ||      | |       | |\n"
                              "   ||      \\@/_______\\@/\n"
                              "   ||       |         |\n"
                              "   ||       |   / \\   |\n"
                              "   ||       |   | |   |\n"
                              "   ||       |   | |   |\n"
                              "   ||       |   | |   |\n"
                              "   ||       |___| |___| \n"
                              "   ||     /_____| |_____\\\n"
                              "   ||\n"
                              "  ||||\n"
                              "|==========================|");

            return visuals;
        }

        cout << "I didn't understand that. ";
        cout << "Please enter 0 or 1.";
        cout << endl;
    }

}