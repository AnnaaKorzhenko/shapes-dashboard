#include <iostream>
#include <vector>
using namespace std;

class Figure {
public:
    virtual void setter(){};
    virtual void drawFigure(){};
    virtual void figureDetails(){};
    virtual ~Figure(){};
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
        if (figures.empty()) {
            cout << "The board doesn't have any figues" << endl;
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

class Triangle : public Figure {
    int heihgt, x, y;
public:
    void setter() override {
        cout << "Enter the triangle height" << endl;
        cin >> heihgt;
        cout << "Enter the x-coordinate of the left vertex" << endl;
        cin >> x;
        cout << "Enter the y-coordinate of the left vertex" << endl;
        cin >> y;
    }
    void drawFigure() override {
        // Implement drawing logic for Triangle
    }
    void figureDetails() override {
        std::cout << "Triangle details\n";
    }

    ~Triangle() override {}
};

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
    ~Circle() override{};
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
    ~Square() override{};
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
    ~Line() override{};
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
    void executeCommand(Board board) {
        string tocontinue = "y";
        while (tocontinue == "y") {
            int command = getCommand();
            switch (command) {
                case 1: {
                    board.drawBoard();
                    cout << "Do you want to continue?" << endl;
                    cin >> tocontinue;
                    break;
                }
                case 2: {
                    board.listExisting();
                    cout << "Do you want to continue?" << endl;
                    cin >> tocontinue;
                    break;
                }
                case 3: {
                    board.shapesPossible();
                    cout << "Do you want to continue?" << endl;
                    cin >> tocontinue;
                    break;
                }
                case 4: {
                    cout << "Which figure do you want to add" << endl;
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
                    else {
                        cout << "We don't support such a figure type yet :(" << endl;
                        break;
                    }
                    if (figure != nullptr) {
                        figure->setter();
                        board.add(figure);
                        cout << "The figure has been added" << endl;
                    }
                    cout << "Do you want to continue?" << endl;
                    cin >> tocontinue;
                    break;
                }
                case 5: {
                    board.undo();
                    cout << "Last figure has been removed" << endl;
                    cout << "Do you want to continue?" << endl;
                    cin >> tocontinue;
                    break;
                }
                case 6: {
                    board.clear();
                    cout << "The board has been cleaned" << endl;
                    cout << "Do you want to continue?" << endl;
                    cin >> tocontinue;
                    break;
                }
                case 7: {
                    board.save();
                    cout << "Do you want to continue?" << endl;
                    cin >> tocontinue;
                    break;
                }
                case 8: {
                    board.load();
                    cout << "Do you want to continue?" << endl;
                    cin >> tocontinue;
                    break;
                }
                default: {
                    tocontinue = "n";
                    cout << "Sorry, we don`t have such a command yet" << endl;
                }
            }
        }
    }
};

int main() {
    Board board;
    Communicator communicator;
    communicator.executeCommand(board);
}