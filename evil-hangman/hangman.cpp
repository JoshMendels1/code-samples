/*
    hangman.cpp
        
    Method implementations for the hangman class.
    
    assignment: CSCI 262 Project - Evil Hangman        

    author: Josh Mendelsohn

    last modified: October 16, 2020
*/

#include "hangman.h"
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <string>
#include <map>

using namespace std;

// constructor
hangman::hangman() {
    ifstream inFile("dictionary.txt");


    if (!inFile) {
        cout << "Unable to open file";
        return; // terminate
    }

    map<int, int> word_lengths; // used for testing purposes

    while (!inFile.eof()){
        string word;
        inFile >> word;
        word_lengths[word.length()]++; // used for testing purposes
        all_words.push_back(word);
        if (word.length() == 29 || word.length() == 28) cout << word << endl;
    }

    for (int i = 0; i < 30; ++i) {
        cout << i << ": " << word_lengths[i] << endl;
    }
}


// start_new_game()
//
// Setup a new game of hangman.
void hangman::start_new_game(int num_guesses, int word_length) {

    this->num_guesses = num_guesses;
    current_family = "";
    remaining_words = {};

    for (int i = 0; i < word_length; ++i) {
        current_family.push_back('-');
    }

    for(string word : all_words){
        if (word.length() == word_length){
            remaining_words.push_back(word);
        }
    }
}


// process_guess()
//
// Process a player's guess - should return true/false depending on whether
// or not the guess was in the hidden word.  If the guess is incorrect, the
// remaining guess count is decreased.
bool hangman::process_guess(char c) {

    map<string, vector<string>> possible_families; // change this to a map of string, vedctor(string) for possible woprds AAAHHHH GTG

    for(string word : remaining_words){

        vector<int> indices;
        string word_family = current_family.substr(0, current_family.length()); // makes a copy of the current family

        for (int i = 0; i < word.length(); ++i) {
            if (word[i] == c){
                indices.push_back(i);
            }
        }

        for(int ndx : indices){
            word_family[ndx] = c;
        }

        possible_families[word_family].push_back(word);
    }

    string best_family = "";
    int best_count = 0;

    for(pair<string, vector<string>> p : possible_families){
        if (p.second.size() > best_count){ // should this be >= or >??????
            best_count = p.second.size();
            best_family = p.first;
        }
    }

    if (get_guesses_remaining() == 1 && possible_families[current_family].size() > 0){
        best_family = current_family;
    }

    current_family = best_family;
    if (current_family.find(c) == -1)
    {num_guesses--;}
    remaining_words = possible_families[best_family];
    guessed_letters.emplace(c);

    return current_family.find(c) != -1;
}


// get_display_word()
//
// Return a representation of the hidden word, with unguessed letters
// masked by '-' characters.
string hangman::get_display_word() {
    return current_family;
}


// get_guesses_remaining()
//
// Return the number of guesses remaining for the player.
int hangman::get_guesses_remaining() {
    return num_guesses;
}


// get_guessed_chars()
//
// What letters has the player already guessed?  Return in alphabetic order.
string hangman::get_guessed_chars() {
    string output;
    for (char c : guessed_letters){
        output += c;
    }
    return output;
}


// was_char_guessed()
//
// Return true if letter was already guessed.
bool hangman::was_char_guessed(char c) {
    return guessed_letters.count(c) >= 1;
}


// is_won()
//
// Return true if the game has been won by the player.
bool hangman::is_won() {
    return current_family.find('-') == -1;
}


// is_lost()
//
// Return true if the game has been lost.
bool hangman::is_lost() {
    return num_guesses <= 0;
}


// get_hidden_word
//
// Return the true hidden word to show the player.
string hangman::get_hidden_word() {
    int randNdx = rand() % remaining_words.size();

    return remaining_words[randNdx];
}


//get_possible_word_count
//
// Return the number of possible words left
int hangman::get_possible_word_count() {
    return remaining_words.size();
}
