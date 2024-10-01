#include <iostream>
#include <vector>
using namespace std;

class Figure {
public:
    virtual void drawFigure(){};
    virtual void figureDetails(){};
};

class Board: Figure{
    const int width = 50;
    const int height = 30;
    vector<Figure> figures;
public:
    void drawBoard() {
        for(auto& figure : figures) {
            figure.drawFigure();
        }
    };
    void listExisting() {
        for(auto& figure : figures) {
            figure.figureDetails();
        }
    };
    void shapesPossible() {
        cout << "Circle - Radius - Coordinates of the center" << endl;
        cout << "Square - Side length - Left Top corner coordinates" << endl;
        cout << "Triangle - Height - Left vertex coordinates" << endl;
        cout << "Line - Length - Starting point coordinates" << endl;

    };
    void add(){};
    void undo(){};
    void clear(){};
    void save(){};
    void load(){};

};

class Triangle : public Figure{};

class Circle : public Figure{};

class Square : public Figure{};

class Line : public Square {
    // just the same as square but with height = 0;
};

class Communicator {
    int input = 0;
public:
    int getCommand() {
        cout << "To draw board enter 1" << endl;
        cout << "To print a list of existing figures enter 2" << endl;
        cout << "To print info about available shapes enter 3" << endl;
        cout << "To add a new figure enter 4" << endl;
        cout << "To remove the last shape added enter 5" << endl;
        cout << "To clear the whole board enter 6" << endl;
        cout << "To save the board to the file enter 7" << endl;
        cout << "To load the board from the file enter 8" << endl;
        cin >> input;
        return input;
    };
    void executeCommand( int command, Board board) {
        switch (command) {
            case 1: {
                board.drawBoard();
            }
            case 2: {
                board.listExisting();
            }
            case 3: {
                board.shapesPossible();
            }
            case 4: {
                board.add();
            }
            case 5: {
                board.undo();
            }
            case 6: {
                board.clear();
            }
            case 7: {
                board.save();
            }
            case 8: {
                board.load();
            }
            default: {
                cout << "Sorry, we don`t have such a command yet" << endl;
            }
        }
    }
};

int main() {
    Board board;
    Communicator communicator;
    int command = communicator.getCommand();
    communicator.executeCommand(command, board);

}