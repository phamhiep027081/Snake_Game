# CPPND: Capstone Snake Game

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## Add new feature

1. Enter button "SPACE" to paused or remused
2. Enter button "ESC" to exit and a box will appear contain your score.
3. After five times nomal food are eaten, red food and green food will appear at the same time. If you eat red food, you will die immediately. If you eat green food, your score will increase 5 score.
4. Your highest score will be written to high_score_record.txt and read it from file to compare with current score.

## Code Rubic

1. Loops, Functions, I/O
	- The project demonstrates an understanding of C++ functions and control structures. (Yes: )
	- The project reads data from a file and process the data, or the program writes data to a file. (Yes: setHighScore() at player.cpp) 
	- The project accepts user input and processes the input.
	- The project uses data structures and immutable variables. (Yes: )

2. Object Oriented Programming
	- One or more classes are added to the project with appropriate access specifiers for class members. (Yes: class Player, class AStar)
    - Class constructors utilize member initialization lists. (Yes: All class members that are set to argument values are initialized through member initialization lists.)
    - Classes abstract implementation details from their interfaces. 
    - Overloaded functions allow the same function to operate on different parameters. (Yes: Oveloaded constrctor function in player.h)
    - Classes follow an appropriate inheritance hierarchy with virtual and override functions.
    - Templates generalize functions or classes in the project.

3. Memory Management
	- The project makes use of references in function declarations. (Yes: Snake.cpp)
    - The project uses destructors appropriately. (Yes: Renderer line 49)
    - The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
    - The project follows the Rule of 5.
    - The project uses move semantics to move data instead of copying it, where possible.
    - The project uses smart pointers instead of raw pointers. (Yes: game.h line 24)
    
4. Concurrency
	- The project uses multithreading. (Yes: std::async() is used in game.cpp in line 11 to create new food)
    - A promise and future is used in the project.
    - A mutex or lock is used in the project. (Yes: std::lock_gruad<> is used in snake.h line 41, snake.cpp line 23, 49 to to protect data that is shared across multiple threads)
    - A condition variable is used in the project.



