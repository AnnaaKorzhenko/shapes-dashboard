#include <iostream>
#include <vector>
using namespace std;

class Figure {
public:
    virtual void setter();
    virtual void drawFigure(){};
    virtual void figureDetails(){};
    virtual ~Figure();
};

class Board : Figure{
    const int width = 50;
    const int height = 30;
    vector<Figure*> figures;
    std::vector<std::vector<char>> grid;
public:
    Board() : grid(height, std::vector<char>(width, ' ')) {}
    void drawBoard() {
        for(auto& figure : figures) {
            for (auto& row : grid) {
                for (char c : row) {
                    std::cout << c;
                }
                std::cout << "\n";
            }
        }
    };
    void listExisting() {
        for(auto& figure : figures) {
            figure->figureDetails();
        }
    };
    void shapesPossible() {
        cout << "Circle - Radius - Coordinates of the center" << endl;
        cout << "Square - Side length - Left Top corner coordinates" << endl;
        cout << "Triangle - Height - Left vertex coordinates" << endl;
        cout << "Line - Length - Starting point coordinates" << endl;

    };
    void add(Figure* figure) {
        figures.push_back(figure);
    };
    void undo() {
        if (!figures.empty()) {
            delete figures.back();
            figures.pop_back();
        }
    };
    void clear() {
        for (auto& figure : figures) {
            delete figure;
        }
        figures.clear();
    };
    void save(){};
    void load(){};

};

class Triangle : public Figure{};

class Circle : public Figure {
    int radius, x, y;
public:
    void setter() override {
        cout << "Enter radius" << endl;
        cin >> radius;
        cout << "Enter x-coordiante of the center" << endl;
        cin >> x;
        cout << "Enter y-coordiante of the center" << endl;
        cin >> y;
    }
    void drawFigure() override{};
    void figureDetails() override {
        std::cout << "Circle: radius = " << radius << ", center at (" << x << ", " << y << ")\n";
    }

};

class Square : public Figure {
    int side, x, y;
public:
    void setter() override {
        cout << "Enter side length" << endl;
        cin >> side;
        cout << "Enter x-coordiante of the left top vertex" << endl;
        cin >> x;
        cout << "Enter y-coordiante of the left top vertex" << endl;
        cin >> y;
    }
    void drawFigure() override{};
    void figureDetails() override {
        std::cout << "Square: side = " << side << ", with the left top vertex at at (" << x << ", " << y << ")\n";
    }
};

class Line : public Figure {
    int length, x, y;
public:
    void setter() override {
        cout << "Enter legth of the line" << endl;
        cin >> length;
        cout << "Enter x-coordiante of the strating point" << endl;
        cin >> x;
        cout << "Enter y-coordiante of the starting point" << endl;
        cin >> y;
    }
    void drawFigure() override{};
    void figureDetails() override {
        std::cout << "Line: length = " << length << ", with the start at (" << x << ", " << y << ")\n";
    }
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
                break;
            }
            case 2: {
                board.listExisting();
                break;
            }
            case 3: {
                board.shapesPossible();
                break;
            }
            case 4: {
                cout << "Which figure do you want to add";
                string shapeType;
                cin >> shapeType;
                Figure* figure = nullptr;
                if (shapeType == "Circle") {
                    figure = new Circle;
                }
                else if(shapeType == "Square") {
                    figure = new Square;
                }
                else if (shapeType == "Line") {
                    figure = new Line;
                }
                else if (shapeType == "Triangle") {
                    figure = new Triangle;
                }
                if (figure != nullptr) {
                    figure->setter();
                    board.add(figure);
                }
                break;
            }
            case 5: {
                board.undo();
                break;
            }
            case 6: {
                board.clear();
                break;
            }
            case 7: {
                board.save();
                break;
            }
            case 8: {
                board.load();
                break;
            }
            default: {
                cout << "Sorry, we don`t have such a command yet" << endl;
                break;
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