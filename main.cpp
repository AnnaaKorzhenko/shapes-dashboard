#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;
class Board;
class Figure {
protected:
    int id;
public:
    string filling;
    char color = '*';
    int getId() {
        return id;
    }
    void setId(int theId) {
        id = theId;
    }
    virtual void setter(){};
    virtual void drawFigure(Board& board){};
    virtual void figureDetails(){};
    virtual void loadDetails(ifstream& file){};
    virtual ~Figure(){};
};

class Board {
    vector<Figure*> figures;
public:
    int width = 10;
    int height = 10;
    vector<vector<char>> grid;
    Board(){};
    void setDimensions(int w, int h) {
        if (w <= 0 || h <= 0) {
            throw std::invalid_argument("Width or height out of range");
        }
        width = w;
        height = h;
        grid.resize(height, vector<char>(width, ' '));
    }

    void drawBoard() {
        grid.assign(height, vector<char>(width, ' '));
        for (auto& figure : figures) {
            figure->drawFigure(*this);
        }

        for(auto& row : grid) {
            for (char c : row) {
                cout << c;
            }
            cout << "\n";
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
        cout << "Circle - Filled or frame - Color - Radius - Coordinates of the center" << endl;
        cout << "Square - Filled or frame - Color - Side length - Left Top corner coordinates" << endl;
        cout << "Triangle - Filled or frame - Color - Height - Left vertex coordinates" << endl;
        cout << "Line - Filled or frame - Color - Length - Starting point coordinates" << endl;

    };
    void add(Figure* figure) {
        figure->setter();
        if (figures.size() == 0) {
            figure->setId(1);
        }
        else {
            figure->setId(figures.size()+1);
        }
        figures.push_back(figure);
    };
    Figure* select() {
        int id;
        cout << "Enter ID of the figure to select" << endl;
        cin >> id;
    };
    void edit() {};
    void paint(){};
    void move(){};
    void undo(int id) {
        if (!figures.empty()) {
            if(figures.at(id)) {
                Figure* figure = figures.at(id);
                delete figures.at(figure->getId());
                figures.erase(figures.begin()+figure->getId()+1);
            }
            else {
                cout << "Remove failed :(" << endl;
            }
        }
        else {
            cout << "There are no any figures to remove at all" << endl;
        }
    };
    void clear() {
        for (auto& figure : figures) {
            delete figure;
        }
        figures.clear();
    };
    void save(const string& filename);
    void load(const string& filename);

};

class Triangle : public Figure {
    int height, x, y;
public:
    void setter() override {
        cout << "Do you want the triangle filled or just frame? fi/fr" << endl;
        cin >> filling;
        cout << "Which color do you want it to be?" << endl;
        cout << "r - red\ng - green\nb - blue\ny - yellow\no - orange\np - pink" << endl;
        cin >> color;
        cout << "Enter the triangle height" << endl;
        cin >> height;
        cout << "Enter the x-coordinate of the top vertex" << endl;
        cin >> x;
        cout << "Enter the y-coordinate of the top vertex" << endl;
        cin >> y;
    }

    void drawFigure(Board& board) override{
        if (height <= 0) return;

        for (int i = 0; i < height; ++i) {
            int leftMost = x - i;
            int rightMost = x + i;
            int posY = y + i;

            if (posY >= 0 && posY < board.height) {
                if (leftMost >= 0 && leftMost < board.width) {
                    board.grid[posY][leftMost] = color;
                }
                if (rightMost >= 0 && rightMost < board.width && leftMost != rightMost) {
                    board.grid[posY][rightMost] = color;
                }
            }
        }

        for (int j = 0; j < 2 * height - 1; ++j) {
            int baseX = x - height +1 + j;
            int baseY = y + height - 1;
            if (baseX >= 0 && baseX < board.width && baseY >= 0 && baseY < board.height) {
                board.grid[baseY][baseX] = color;
            }
        }
        if (filling == "fi") {
            for (int i = 0; i < height; ++i) {
                int leftMost = x - i;
                int rightMost = x + i;
                int posY = y + i;
                if (posY >= 0 && posY < board.height) {
                    for (int j = leftMost + 1; j < rightMost; ++j) {
                        if (j >= 0 && j < board.width) {
                            board.grid[posY][j] = color;
                        }
                    }
                }
            }
        }
    }

    void figureDetails() override {
        cout << "Triangle: height = " << height << ", top vertex at (" << x << ", " << y << ")\n";
        cout << "Filling: " << filling << ", color: " << color;
    }
    void loadDetails(ifstream& file) override {
        file >> height >> x >> y;
    }
    ~Triangle() override {}
};

class Circle : public Figure {
    int radius, x, y;
public:
    void setter() override {
        cout << "Do you want the circle filled or just frame? fi/fr" << endl;
        cin >> filling;
        cout << "Which color do you want it to be?" << endl;
        cout << "r - red\ng - green\nb - blue\ny - yellow\no - orange\np - pink" << endl;
        cin >> color;
        cout << "Enter radius" << endl;
        cin >> radius;
        cout << "Enter x-coordiante of the center" << endl;
        cin >> x;
        cout << "Enter y-coordiante of the center" << endl;
        cin >> y;
    }
    void drawFigure(Board& board) override {
        if (radius <= 0) return;

        for (int i = 0; i < board.height; ++i) {
            for (int j = 0; j < board.width; ++j) {
                if (filling == "fi") {
                    if (pow(j - x, 2) + pow(i - y, 2) <= pow(radius, 2)) {
                        board.grid[i][j] = color;
                    }
                }
                else {
                    if (pow(j - x, 2) + pow(i - y, 2) == pow(radius, 2)) {
                        board.grid[i][j] = color;
                    }
                }
            }
        }
    };
    void figureDetails() override {
        std::cout << "Circle: radius = " << radius << ", center at (" << x << ", " << y << ")\n";
        cout << "Filling: " << filling << ", color: " << color;
    }
    void loadDetails(ifstream& file) override {
        file >> radius >> x >> y;
    }
    ~Circle() override{};
};

class Square : public Figure {
    int side, x, y;
public:
    void setter() override {
        cout << "Do you want the square filled or just frame? fi/fr" << endl;
        cin >> filling;
        cout << "Which color do you want it to be?" << endl;
        cout << "r - red\ng - green\nb - blue\ny - yellow\no - orange\np - pink" << endl;
        cin >> color;
        cout << "Enter side length" << endl;
        cin >> side;
        cout << "Enter x-coordiante of the left top vertex" << endl;
        cin >> x;
        cout << "Enter y-coordiante of the left top vertex" << endl;
        cin >> y;
    }
    void drawFigure(Board& board) override {
        if (side <= 0) return;
        for (int j = x; j < x + side; ++j) {
            if (j >= 0 && j < board.width && y >= 0 && y < board.height) {
                board.grid[y][j] = color;
            }
        }

        for (int j = x; j < x + side; ++j) {
            if (j >= 0 && j < board.width && y + side - 1 >= 0 && y + side - 1 < board.height) {
                board.grid[y + side - 1][j] = color;
            }
        }

        for (int i = y; i < y + side; ++i) {
            if (x >= 0 && x < board.width && i >= 0 && i < board.height) {
                board.grid[i][x] = color;
            }
        }

        for (int i = y; i < y + side; ++i) {
            if (x + side - 1 >= 0 && x + side - 1 < board.width && i >= 0 && i < board.height) {
                board.grid[i][x + side - 1] = color;
            }
        }

        if (filling == "fi") {
            for (int i = y + 1; i < y + side - 1; ++i) {
                for (int j = x + 1; j < x + side - 1; ++j) {
                    if (i >= 0 && i < board.height && j >= 0 && j < board.width) {
                        board.grid[i][j] = color;
                    }
                }
            }
        }
    };
    void figureDetails() override {
        std::cout << "Square: side = " << side << ", with the left top vertex at at (" << x << ", " << y << ")\n";
        cout << "Filling: " << filling << ", color: " << color;
    }
    void loadDetails(ifstream& file) override {
        file >> side >> x >> y;
    }
    ~Square() override{};
};

class Line : public Figure {
    int length, x, y;
public:
    void setter() override {
        filling = "fi";
        cout << "Which color do you want the line to be?" << endl;
        cout << "r - red\ng - green\nb - blue\ny - yellow\no - orange\np - pink" << endl;
        cin >> color;
        cout << "Enter legth of the line" << endl;
        cin >> length;
        cout << "Enter x-coordiante of the strating point" << endl;
        cin >> x;
        cout << "Enter y-coordiante of the starting point" << endl;
        cin >> y;
    }
    void drawFigure(Board& board) override {
        if (length <= 0) return;

        for (int j = 0; j < length; ++j) {
            int posX = x + j;
            if (posX >= 0 && posX < board.width && y >= 0 && y < board.height) {
                board.grid[y][posX] = color;
            }
        }
    };
    void figureDetails() override {
        std::cout << "Line: length = " << length << ", with the start at (" << x << ", " << y << ")\n";
        cout << "Color: " << color;
    }
    void loadDetails(ifstream& file) override {
        file >> length >> x >> y;
    }
    ~Line() override{};
};

void Board::save(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file for saving." << endl;
        return;
    }

    file << width << " " << height << "\n";

    for (auto& row : grid) {
        for (auto& cell : row) {
            file << cell;
        }
        file << "\n";
    }

    file << figures.size() << "\n";
    for (const auto& figure : figures) {
        figure->figureDetails();
    }

    file.close();
}

void Board::load(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file for loading." << endl;
        return;
    }

    file >> width >> height;
    grid.clear();
    grid.resize(height, vector<char>(width, ' '));

    string line;
    getline(file, line);
    for (int i = 0; i < height; ++i) {
        getline(file, line);
        for (int j = 0; j < width; ++j) {
            grid[i][j] = line[j];
        }
    }

    clear();
    int numFigures;
    file >> numFigures;
    for (int i = 0; i < numFigures; ++i) {
        string figureType;
        file >> figureType;

        Figure* figure = nullptr;
        if (figureType == "Triangle") {
            figure = new Triangle();
        } else if (figureType == "Circle") {
            figure = new Circle();
        }

        if (figure != nullptr) {
            figure->loadDetails(file);
            add(figure);
        }
    }

    file.close();
}


class Communicator {
    int input = 0;
    Figure* selected = nullptr;
public:
    int getCommand() {
        cout << "To draw board enter 1" << endl;
        cout << "To print a list of existing figures enter 2" << endl;
        cout << "To print info about available shapes enter 3" << endl;
        cout << "To add a new figure enter 4" << endl;
        cout << "To select a figure enter 5" << endl;
        cout << "To remove the selected figure enter 6" << endl;
        cout << "To edit the selected figure enter 7" << endl;
        cout << "To paint the selected figure enter 8" << endl;
        cout << "To move the selected figure enter 9" << endl;
        cout << "To clear the whole board enter 10" << endl;
        cout << "To save the board to the file enter 11" << endl;
        cout << "To load the board from the file enter 12" << endl;
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
                        board.add(figure);
                        cout << "The figure has been added" << endl;
                    }
                    cout << "Do you want to continue?" << endl;
                    cin >> tocontinue;
                    break;
                }
                case 5: {
                    selected = board.select();
                    break;
                }
                case 6: {
                    if(selected!=nullptr) {
                        board.undo(selected->getId());
                        cout << "Selected figure has been removed" << endl;
                    }
                    else {
                        cout << "You have not selected any figure. Please? select and try again" << endl;
                    }
                    cout << "Do you want to continue?" << endl;
                    cin >> tocontinue;
                    break;
                }
                case 7: {
                    board.edit();
                    break;
                }
                case 8: {
                    board.paint();
                }
                case 9: {
                    board.move();
                }
                case 10: {
                    board.clear();
                    cout << "The board has been cleaned" << endl;
                    cout << "Do you want to continue?" << endl;
                    cin >> tocontinue;
                    break;
                }
                case 11: {
                    string filename;
                    cout << "Enter a file name to save to" << endl;
                    cin >> filename;
                    board.save(filename);
                    cout << "Do you want to continue?" << endl;
                    cin >> tocontinue;
                    break;
                }
                case 12: {
                    string filename;
                    cout << "Enter a file name to load from" << endl;
                    cin >> filename;
                    board.load(filename);
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
    board.setDimensions(20, 20);
    Communicator communicator;
    communicator.executeCommand(board);
}

// edit
// paint
// move
// check the save and load, need to change them
// check all the constarints and just add conditions and additional elses for handling unexpected behaviour