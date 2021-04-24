#include <iostream>
using namespace std;

char board[9] = {'*', '*', '*', '*', '*', '*', '*', '*', '*'};
// determines whether the board format is 0-indexed or 1-indexed
int index_adjustment;

// User = 'X'
// CPU = 'O'
char user[2] = {'X', 'O'};

// Winning States
int winning_states[8][3] = {
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8},
    {0, 3, 6},
    {1, 4, 7},
    {2, 5, 8},
    {0, 4, 8},
    {2, 4, 6}
};

// State Values for CPU
const int WIN = 10;
const int DRAW = 0;
const int LOSS = -10;
int idx;


bool check_win(int x) {
    for (auto p : winning_states) {
        if (board[p[0]] == user[x] && board[p[0]] == board[p[1]] && board[p[0]] == board[p[2]]) {
            return true;
        }
    }
    return false;
}


void print_board() {
    cout << "\n#### BOARD ####\n";
    for (int i = 0, count = 1; i < 9; ++i, ++count) {
        cout << board[i] << " ";
        if (count % 3 == 0) {
            cout << "\n";
        }
    }
}


bool is_full() {
    int ret = 0;
    for (int i = 0; i < 9; ++i) {
        if (board[i] != '*') ++ret;
    }
    return ret == 9;
}


// User: flag = false
// CPU: flag = true
int minimax(bool flag) {
    if (check_win(1)) return WIN;
    else if (check_win(0)) return LOSS;
    else if (is_full()) return DRAW;

    int score[9] = {0};
    int value = 0;
    int min_value = 1000;
    int max_value = -1000;

    for (int i = 0; i < 9; ++i) {
        if (board[i] == '*') {
            if (min_value > max_value) {
                if (flag) {
                    board[i] = 'O';
                    value = minimax(false);
                } else {
                    board[i] = 'X';
                    value = minimax(true);
                }
                board[i] = '*';
                score[i] = value;
            }
        }
    }

    if (flag) {
        max_value = -1000;
        for (int i = 0; i < 9; ++i) {
            if (score[i] > max_value && score[i]) {
                max_value = score[i];
                idx = i;
            }
        }
        return max_value;
    }

    // if flag == false
    min_value = 1000;
    for (int i = 0; i < 9; ++i) {
        if (score[i] < min_value && score[i]) {
            min_value = score[i];
            idx = i;
        }
    }
    return min_value;
}


void user_move() {
    print_board();
    int user_move;
    while (1) {
        cout << "Enter your move: ";
        cin >> user_move; 
        user_move -= index_adjustment;
        if (board[user_move] != '*') {
            cout << "Invalid Move!\n";
            continue;
        } else {
            board[user_move] = 'X';
            return;
        }
    }
    cout << "\n";
}

void cpu_move() {
    print_board();
    minimax(true);
    cout << "CPU Move: " << idx + index_adjustment << "\n";
    board[idx] = 'O';
}

bool check_state() {
    cout << "\n";
    if (is_full()) {
        print_board();
        cout << "#### DRAW ####\n";
        return 1;
    } else if (check_win(0)) {
        print_board();
        cout << "#### USER WON ####\n";
        return 1;
    } else if (check_win(1)) {
        print_board();
        cout << "#### CPU WON ####\n";
        return 1;
    }
    return 0;
}

int main() {
    cout << "##### TIC TAC TOE #####\n";
    cout << "User: 'X' | CPU: 'O'\n\n";

    cout << "Select:\n(0) 0-Indexed Game.\n(1) 1-Indexed Game.\n";
    cin >> index_adjustment;
    
    cout << "#### BOARD FORMAT ####\n";
    int format_count = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << format_count++ + index_adjustment << " ";
        }
        cout << "\n";
    }

    cout << "\nSelect:\n(1) User Goes First.\n(2) CPU Goes First.\n";

    int user_choice;
    cin >> user_choice;

    if (user_choice == 1) {
        user_move();
    }

    while (!check_state()) {
        cpu_move();
        if (check_state()) break;
        user_move();
    }

    return 0;
}