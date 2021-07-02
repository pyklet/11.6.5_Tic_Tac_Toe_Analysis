#include <iostream>

/*string validation*/
bool ValidString(std::string str, std::string dictionary, int length) {
    if (str.length() != length) return false;
    else {
        bool inDictionary = true;

        for (int i = 0; inDictionary && i < str.length(); ++i) {
            for (int j = 0; j < dictionary.length(); ++j) {
                if (str[i] == dictionary[j]) {
                    inDictionary = true;
                    break;
                } else {
                    inDictionary = false;
                };
            }
            if (!inDictionary) return false;
        }
    }
    return true;
}

/*get the count of specified characters from the text*/
int CharCounter(std::string text, char c){
    int count = 0;
    for (int i = 0; i < text.length(); ++i) {
        if (text[i] == c) count++;
    }
    return count;
}

/*get a character in the "field" at the specified coordinates. "/n" -
vertical separator*/
char GetCharInFieldByCrdnt(std::string text, int x, int y) {
    int row = 1, symbol = 1;
    for (int i = 0; i < text.length(); ++i) {
        if (text[i] == '\n') {
            row++;
            symbol = 1;
        } else if (row == y && symbol == x) {
            return text[i];
        } else
            symbol++;
    }
    return '-';
}

int TicTacToeWinner(std::string gameField){
    int cross = 0, zero = 0;
    int crossWin = 0, zeroWin = 0;

    /*horizontal check*/
    for (int y = 1; y < 4; ++y) {
        for (int x = 1; x < 4; ++x) {
            char c = GetCharInFieldByCrdnt(gameField, x, y);
            if (c == 'X') cross++;
            else if (c == 'O') zero++;
        }
        if (cross == 3)
            crossWin++;
        else if (zero == 3)
            zeroWin++;

        cross = 0;
        zero = 0;
        }
    /*-------------end check-------------*/

    /*vertical check*/
    for (int x = 1; x < 4; ++x) {
        for (int y = 1; y < 4; ++y) {
            char c = GetCharInFieldByCrdnt(gameField, x, y);
            if (c == 'X') cross++;
            else if (c == 'O') zero++;
        }
        if (cross == 3)
            crossWin++;
        else if (zero == 3)
            zeroWin++;

        cross = 0;
        zero = 0;
    }
    /*-------------end check-------------*/

    /*diagonal (11-22-33) check*/
    for (int x = 1; x < 4; ++x) {
        char c = GetCharInFieldByCrdnt(gameField, x, x);

        if (c == 'X')
            cross++;
        else if (c == 'O')
            zero++;
    }
    if (cross == 3)
        crossWin++;
    else if (zero == 3)
        zeroWin++;

    cross = 0;
    zero = 0;
    /*-------------end check-------------*/

    //diagonal (12-22-31) check
    for (int x = 1; x < 4; ++x) {
        char c = GetCharInFieldByCrdnt(gameField, x, 4 - x);

        if (c == 'X')
            cross++;
        else if (c == 'O')
            zero++;
    }
    if (cross == 3)
        crossWin++;
    else if (zero == 3)
        zeroWin++;

    /*-------------end check-------------*/

    /*validation*/
    int crossCount = CharCounter(gameField, 'X');
    int zeroCount = CharCounter(gameField, 'O');

    if (crossWin > 0 && zeroWin > 0) return 0;
    if (zeroWin > 0 && crossCount > zeroCount) return 0;
    if (crossWin > 0 && zeroCount >= crossCount) return 0;
    if (crossWin > 1 || zeroWin > 1) return 0;
    if (zeroCount > crossCount) return 0;

    if (crossWin > 0) return 1;
    if (zeroWin > 0) return 2;
    if (crossWin == 0 && zeroWin == 0) return 3;
    /*-------------end check-------------*/

    return 4;
}

int main() {
    std::string firstRow, secondRow, thirdRow;
    std::string dictionary = ".OX";
    int resultFunction;
    std::string result;
    bool correct = false;

    while (!correct) {
        std::cout << "input 3 rows" << std::endl;
        std::cin >> firstRow >> secondRow >> thirdRow;
        correct = (ValidString(firstRow, dictionary, 3)
                && ValidString(secondRow, dictionary, 3)
                && ValidString(thirdRow, dictionary, 3));
        if (!correct) (std::cout << "incorrect data.\n");
    }
    std::string gameField = firstRow + '\n' + secondRow + '\n' + thirdRow;

    resultFunction = TicTacToeWinner(gameField);
    if (resultFunction == 0) result = "Incorrect";
    else if (resultFunction == 1) result = "Petya won";
    else if (resultFunction == 2) result = "Vanya won";
    else if (resultFunction == 3) result = "Nobody";
    else result = "Something went wrong (error " + std::to_string(resultFunction) + ")";

    std::cout << result;
}
