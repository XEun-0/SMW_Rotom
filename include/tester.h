#ifndef TESTER_H
#define TESTER_H

class TouchscreenTester {
public:
    void begin();
    void loop();

private:
    const int screenWidth = 320;
    const int screenHeight = 240;
    const int fontSize = 2;

    void printTouchToSerial(int x, int y, int z);
    void printTouchToDisplay(int x, int y, int z);
};

#endif
