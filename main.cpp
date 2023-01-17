#include <iostream>
#include <cstdlib>

//#define abs(a) ((a<0)?(-a):(a))
using namespace std;

void display_board(char board[10][10]) {
    int nbr = 9;
    for (int i = 0; i <= 30; i++) {
        int type = i % 3;
        if (i == 2) cout << 10; //number 10
        else if ((i + 1) % 3 == 0) { //every third line
            cout << nbr << " "; //numbers on the left side of board (0-9)
            --nbr;
        } //space before (0-9) numbers and board
        else cout << "  "; //space before board in places without numbers
        if (type == 0) cout << "+";
        else cout << "|"; //only the first column

        for (int j = 0; j < 10; j++) {
            if (type == 0) cout << "-----+";
            else {
                char c = board[i / 3][j];
                if (c == '.') //shot mark
                    cout << c << c << c << c << c; //creating shoot struct
                else
                    cout << " " << c << c << c << " "; //creating pawn struct

            }
            if (type != 0) cout << "|";
        } //whole interior

        cout << endl;
    }
    cout << "     A     B     C     D     E     F     G     H     I     J"; //letteral column
}



/*
 *    SPRAWDZANIE
 */

char board[10][10]; //main board in game

bool sprawdzanie(char column, char column_beginO, int line, int line_beginO, bool delete_old, char letter){


 /**data of our move*/
            int d = (abs(line_beginO - line) > 0) ? abs(line - line_beginO) : abs(column - column_beginO);
            //d is our value of cells we moved, which is needed for loop, if its bigger than 0, we moved diagonal OR we moved only increasing our number of line - horizontally, else
            //if our value of line does not change it means we moved vertically,
            //d is free standing for columns and for lines
            int dist_line = line - line_beginO; //distance between old position and new move position
            int dist_column = column - column_beginO; //same as ^^

            int dir_line = (dist_line == 0) ? 0 : ((dist_line > 0) ? 1 : -1);
            int dir_column = (dist_column == 0) ? 0 : ((dist_column > 0) ? 1 : -1);
            //  if (dist_line==0) dir_line = 0; else if (dist_line>0) dist_line = 1, else (for negative values) its = -1

            int act_line = line; //our actual line
            int act_column = column;
            bool succesfull_move = 1;
            /**END*/

            if ((abs(dist_line) == (abs(dist_column))) || ((abs(dist_column)) == 0) || ((abs(dist_line)) == 0)) { //checking if its a //**queen**// valid move
//                columns and lines have the same increasing number
//                cout << "d:" << d << endl;
//                cout << "dir_line:" << dir_line << endl;
//                cout << "dir_column:" << dir_column << endl;

                int act_line = line_beginO; //our actual line
                int act_column = column_beginO; //our actual column cause we don't wanna mess up orginals

                for (int i = 1; i < d; i++) {

                    act_line += dir_line; //if our dir_line is positive it means we're gonna move vertical, if its 0 we're moving ONLY with columns (horizontally)
                    act_column += dir_column; //analogously as for dir_line
                    // so we are checking positions UNTIL value of line and our column is not same as value of our occupied position
//                    cout << "ITERATION: " << char(act_column+65) << 10-act_line << endl;
                    if ((board[act_line][act_column] == '#') || (board[act_line][act_column] == 'O') || (board[act_line][act_column] == '.')) {
                        cout << "You can not skip-over other pawns!" << endl;
                        succesfull_move = 0;
                         break; //leaving the loop checking our move validaiton
                    }
                }
                 
                if(succesfull_move) { //if our move is valid
                    if(delete_old)
                      board[line_beginO][column_beginO] = ' '; //removing last position                      
                    board[line][column] = letter; //rewriting pawn
                    display_board(board); //showing the board
                    cout<<endl;
                    return 1;
                }

            } else cout << "I is not a queen-star move!" << endl;

        return 0;
}

// 1-> poprawny
// 0-> zly





int main() {
	
	cout<<"Player without valid moves loses"<<endl;
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            board[i][j] = ' '; //marking board array as a ' '(space)
    board[0][3] = '#';
    board[0][6] = '#';
    board[3][0] = '#';
    board[3][9] = '#';
    board[6][0] = 'O';
    board[6][9] = 'O';
    board[9][3] = 'O';
    board[9][6] = 'O';
    //initial array arrangement
    ///|0 1 2 3 4 5 6 7 8 9|
    //0|      #     #      |10
    //1|                   |9
    //2|                   |8
    //3|#                 #|7
    //4|                   |6
    //5|                   |5
    //6|O                 O|4
    //7|                   |3
    //8|                   |2
    //9|      O     O      |1
    ///|A B C D E F G H I J

    display_board(board);

    int line, line_beginO, line_beginH, line_shot, lineShot_begin;
    char column, column_beginO, colShot_begin, column_shot, column_beginH;

    cout << endl << "The 'O' player turn. Choose from board:";

    while (1) //main loop for changing players
    {
        /**OOOOOOOOOOO!PLAYER_1!OOOOOOOOOOO**/
        while (1) /** choosing the pawn **/ {
            cout << endl << "Column of the pawn You want to move: ";
            cin >> column_beginO;
            column_beginO -= 65; //taking char A as a number 0 using ascii
            cout << "Line of  the pawn You want to move: ";
            cin >> line_beginO;
            line_beginO = 10 - line_beginO; //counting from 10-0
            if (board[line_beginO][column_beginO] != 'O') //checking move validation
                cout << "Invalid data - try again ";
            else break; /**poprawiona wersja**/
        }

        bool succesfull_move = 0;
        /** making move **/
        while (1) {
            cout << endl << "Column where You want to move: ";
            cin >> column;
            column -= 65; //input char as a number in array
            cout << "Line where You want to move: ";
            cin >> line;
            line = 10 - line; //reverse counting
        if(sprawdzanie(column, column_beginO, line, line_beginO, true, 'O') || column>75 || line>10)
            break;

        }
//        /*************taking a shot*****************///OPTION FOR CHOOSING PAWN THAT IS GOING TO SHOOT
//        while (1) //choosing which pawn gonna shoot
//        {
//            cout << endl << "Take a shot" << endl;
//            cout << "Choose a pawn. ";
//            cout << "Column: ";
//            cin >> colShot_begin;
//            colShot_begin -= 65;
//            cout << "Line: ";
//            cin >> lineShot_begin;
//            lineShot_begin = 10 - lineShot_begin;
//            if (board[lineShot_begin][colShot_begin] != 'O') //checking if the player choose correct pawn
//                cout << "Invalid data";
//            else break; //ending loop for correct data
//        }

        while (1) //choosing where the pawn gonna shoot
        {
            cout << "Column where You want to shoot: ";
            cin >> column_shot;
            cout << "Line where You want to shoot: ";
            cin >> line_shot;
            column_shot -= 65; //input char as a number in array
            line_shot = 10 - line_shot; //reverse counting
            if(sprawdzanie(column_shot, column, line_shot, line, false, '.'))
            	break;
        }


		cout<<endl<<"The '#' Player turn. Choose from board:";

        /**################!PLAYER_2!################**/
        while (1) /** choosing the pawn **/ {
            cout << endl << "Column of the pawn You want to move: ";
            cin >> column_beginH;
            column_beginH -= 65; //taking char A as a number 0 using ascii
            cout << "Line of  the pawn You want to move: ";
            cin >> line_beginH;
            line_beginH = 10 - line_beginH; //counting from 10-0
            if (board[line_beginH][column_beginH] != '#') //checking move validation
                cout << "Invalid data - try again ";
            else break; 
        }

        /** making move **/
        while (1) {
            cout << endl << "Column where You want to move: ";
            cin >> column;
            column -= 65; //input char as a number in array
            cout << "Line where You want to move: ";
            cin >> line;
            line = 10 - line; //reverse counting
        if(sprawdzanie(column, column_beginH, line, line_beginH, true, '#'))
            break;

        }

        /*************taking a shot*****************///OPTION FOR CHOOSING PAWN THAT IS GOING TO SHOOT
//        while (1) //choosing which pawn gonna shoot
//        {
//            cout << endl << "Take a shot" << endl;
//            cout << "Choose a pawn. ";
//            cout << "Column: ";
//            cin >> colShot_begin;
//            colShot_begin -= 65;
//            cout << "Line: ";
//            cin >> lineShot_begin;
//            lineShot_begin = 10 - lineShot_begin;
//            if (board[lineShot_begin][colShot_begin] != '#') //checking if the player choose correct pawn
//                cout << "Invalid data";
//            else break; //ending loop for correct data
//        }

        while (1) //choosing where the pawn gonna shoot
        {
            cout << "Column where You want to shoot: ";
            cin >> column_shot;
            cout << "Line where You want to shoot: ";
            cin >> line_shot;
            column_shot -= 65; //input char as a number in array
            line_shot = 10 - line_shot; //reverse counting
            if(sprawdzanie(column_shot, column, line_shot, line, false, '.'))
            	break;
        }
        cout<<endl<<"The 'O' Player turn. Choose from board:";

    }

    return 0;
}
