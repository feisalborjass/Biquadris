# Tetris

CS246 - A5 Final Design Document
Introduction
This document outlines the implementation of Biquadris, a game that is similar to Tetris and programmed in C++.
Overview

Our project can be divided into six main classes:
Display: Renders each component of the game.
Player: Facilitates access to the Player’s Board, Level, current and next Blocks. Also computes and stores the Player’s score. 
Board: Handles row clearing and recursive block dropping.
Block: Handles the Block’s movement (left, right, down, drop, counterclockwise, clockwise). Also checks for collisions when the Block moves.
Square: Represents each individual tile in a Block, as well as the spaces to fill up the game board. The X and Y attributes in a Square are manipulated when “left”, “right”, and other move commands are triggered in a Block.
Level: Provides the next block based on the level of the game.

Each of these classes have very specific purposes and come together to form the full game. Our approach was to use a container class Player to store the game information for each user, including their respective Boards, the Blocks on each Board, points, the level currently active, and the Block that will be used for the next move. We render the game using a Display class that then takes the information from each Player and prints the game information for each move. We will outline our overall approach to solve the challenges that this game presented in the rest of this document.
Design

Displaying the Game
When the program runs, Display displays the games for each player. To do this, Display gets the level the Player is currently on, the score the Player has accumulated, the Player’s Board object, and the next Block from each player. The display class then renders the boards from 
player 1 and player 2. 

Command Interpreter
If the user inputs the command “right”, the current Player’s current Block’s right() method is called, which moves each of its Squares right by one as long as no collision is detected. After, the vector<vector<Square*>>, which represents the Board in a 2D vector, is updated, and display takes this new Board and displays it, showing that the Squares for the current Block all moved right by one. 

Block Movement
At the start of a player’s turn, they are able to move the block at the top of the board in a variety of different ways. Blocks move by adjusting the X and Y coordinates of each of the 4 Squares that they contain. When a Block’s position is changed, the Board’s grid is adjusted accordingly. Collision detection is implemented within the Block class. It checks whether or not the desired movement position is valid and executes the move if it is. The relationship between a single block and the overall board is what enables proper movement on a grid.

Clearing a Row
When a block is dropped, the Squares belonging to that Block move down one by one until a collision is detected and all Squares in the Block stop moving. Then, the vector<vector<Square*>> (representation of the Board) is checked if any of the rows are completed. If it is, we move all Squares that are above the row we are deleting down by one and we flag the Squares that are on the row we are deleting as deleted. Next, we clear the Board by replacing all Square* with a blank Square*, update the Board by populating the vector<vector<Square*>> with Squares that are not deleted, and the re-display it.


Block-Board Relationship
We noticed that whenever we needed to change the state of a block (movement, rotation, clearing, etc.), the Board had to update accordingly to reflect these changes on blocks. That’s why we chose to use the observer design pattern to facilitate the relationship between Blocks and the Board. 

In our design, the Board acts as the subject for all of the existing blocks. The board has pointers to each block and whenever there is a change in these blocks, the board is notified and updates accordingly. The Blocks then act as observers where the state of each Block updates whenever there is a movement, rotation, or clear command. The specific parallels between our implementation and the observer pattern are as follows:

AbstractObserver: Block
ConcreteObservers: I_Block, J_Block, L_Block, O_Block, S_Block, T_Block, Z_Block, Single_Block
notify() methods: left(), right(), down(), drop(), clockwise(), counterclockwise()
These methods all update the x and y positions of the Squares within each Block, so they notify the Board when a change is made 
Subject: Board
attach(): addBlock(Block *b)
Called at the start of the game and whenever a block is dropped. The blocks are stored in a vector containing Block pointers, which is how the Board keeps track of the existing Blocks.
detach(): removeBlock(Block *b)
Called whenever a Block needs to be removed from the Board, such as replacing the current Block with an ‘O’ or ‘L’ Block manually.
notifyObserver(): update_grid_squares()
Using the Board’s vector of Block pointers, this method updates the Board’s internal grid representation (grid_squares) to accurately reflect the positions and state of each block.

Changes from DD1
For the most part, we used the same design from the one we proposed in the first due date. Our strategy was to use the same kind of structure that we had in the UML. The most significant change however is the decision not to use the decorator design pattern for the special actions. Our original plan was to use a Decorator to change the state of the Board when a special effect is applied. Although we weren’t able to fully implement special actions, our new plan was to account for those changes within the individual classes the action affects. For example, if a hide effect was active, it would be accounted for in the Display class when rendering occurs. We decided that it would be a better approach to reduce the number of changes needed to be made within one single Board class.

Aside from the change with the decorator pattern, a positive improvement was emphasizing the observer pattern for when the Board and Blocks interact with each other. We realized when writing our implementation that this relationship needed to be handled carefully, and the observer pattern seemed to be like the right answer. This decision allowed us to perform transformations on blocks and updates on the board more efficiently. 
Resilience to Change

FLEXIBILITY

We kept flexibility in mind when creating our design. As such, the following modifications to our program would be simple with our implementation:

Change in Board Dimensions
Our boards are represented as a vector<vector<Square*>>, which means the board could be expanded or shrunk at easily. All the functions that iterate through the board are based on the board’s size and not on a fixed integer. To simply change the board’s dimensions, we can change the base board’s specifications.

New Levels
All levels inherit from an abstract Level class. To add a Level, simply inherit from this class, and add it to the vector<Level*> for both players. The new level can now be accessed by repeating the “levelup” command until that level is reached. If there is additional functionality that we want a new level to have, overloaded methods could be used to change the state of the game when this new level is active.

New Blocks
All blocks inherit from an abstract Block class. Subclasses represent each individual type of Block (I-blocks, S-blocks, O-blocks, etc.). Each subclass initializes its assortment of Squares in a different way and overloads the rotation methods accordingly. If we wanted to introduce a new kind of Block with a different shape, it would be simple to create a subclass that inherits from our abstract Block class.

New Players
The Player class we implemented stores all information about needed to store a player’s game information. When a Player is initialized, their own Board, Level, and Score are all tracked within the single class. Therefore, if we wanted to add multiple players to the game, our design would support this change. All we would need to do is change main.cc and create a new player.

COUPLING
Our program seeks to minimize interdependence between modules in various ways. In general, we mostly used pointers when working with objects and implementing code where different classes depend on each other. A great example of low coupling in our program is through the Observer design pattern that we implemented for the Board-Block relationship. The Board does not need to know implementation details for Block to function correctly, and vice versa, so the dependence is relatively loose. 

COHESION
Our program exhibits high cohesion since we designed each group of modules to be for a specific and focused purpose. Our design can be summarized with the following groups of classes:
Blocks: for each individual piece that can be used in the game
Display: to render the game
Player: to store all information that a player has and easily access it
Board: to store the state of a grid for a player (the main game map)
Levels: for determining which Block should be next for a player

Hence, we have high cohesion with this design.
Answers to Questions from project

How could you design your system (or modify your existing design) to allow for some generated blocks to disappear from the screen if not cleared before 10 more blocks have fallen? Could the generation of such blocks be easily confined to more advanced levels?

To allow for some generated blocks to disappear from the screen if not cleared before 10 more blocks have fallen, we can implement an Observer Pattern. We will create two new classes. The first is the AbstractSubject class which will have the attach(), detach(), and notify() methods, and a new counter attribute which keeps count of how many blocks are added after the current block. The second is the AbstractObserver class which will have a notify() method, and will be the parent class of all Board objects. When a new Block is created, it will inherit from the AbstractSubject class and attach itself to its respective Board. When the counter reaches ten, it will notify its Board, which will subsequently delete the Block.

By leveraging the Observer Pattern, we are given much more flexibility to change a single Block’s interaction with a Board. If we wanted to change the behaviour of the block in a more advanced way, we would do so by changing what happens within the notify() method. The idea is that having an observer relationship with the Board enables us to perform a special action on a Block when a particular event occurs. This is an easy way of allowing blocks to disappear after a certain number of moves have passed.

How could you design your program to accommodate the possibility of introducing additional levels into the system, with minimum recompilation?

The purpose of having different levels is to determine which block comes next. With our proposed implementation, we plan to have an abstract Level class, where subclasses (Level0, Level1, etc.) can override a getNext() method. The getNext() method will return the next block for a player depending on their current level. The overall benefit of using this design strategy is twofold. 

First of all, we would be minimizing recompilation. The abstract Level class is only owned by a Player class, which is contained within a Display class. Hence fewer files are recompiled with the addition of a new level since the only two dependencies affected are the Player class and Display class. Second of all, this design strategy is intuitive. If we wanted to introduce an additional level, all we would need to do is create another Level subclass with an overridden getNext() method. Additional functionality with a more difficult level could also be created by adding unique methods to this new subclass.

How could you design your program to allow for multiple effects to be applied simultaneously? What if we invented more kinds of effects? Can you prevent your program from having one else-branch for every possible combination?

Our strategy to accommodate for different kinds of effects is to use the Decorator Design Pattern. In our case, special actions will be represented as decorators and they can be used to modify the existing board. For example, if we wanted to blind a player’s board, we would decorate the necessary squares on the board and make them hidden. Similarly, a heavy decorator can be applied on a player’s board to ensure that blocks fall vertically two rows at a time. This approach can be used to easily decorate a player’s board with other kinds of special effects on top of blind, heavy, and force. 

In terms of control flow, the way we would handle multiple effects at once is by prompting a player to decorate their opponent's board with multiple effects at once. For instance, when two or more rows are cleared and “special effect mode” begins, a player can input a list of special effects and the respective decorators will be applied. This allows for multiple effects to be applied simultaneously because of the decorator design pattern’s ability to stack decorations on top of each other. Once an eof signal is sent, the opponent’s turn begins with the specified special effects applied to the board.

How could you design your system to accommodate the addition of new command names, or changes to existing command names, with minimal changes to source and minimal recompilation? (We acknowledge, of course, that adding a new command probably means adding a new feature, which can mean adding a non-trivial amount of code.) How difficult would it be to adapt your system to support a command whereby a user could rename existing commands (e.g. something like rename counterclockwise cc)? How might you support a \macro" language, which would allow you to give a name to a sequence of commands? Keep in mind the effect that all of these features would have on the available shortcuts for existing command names.

To design our system to accommodate the addition of new command names and support a “macro” system, we can use C++ maps. We can create a map that binds strings to strings and it can act as our command interpreter. At the beginning of our program, we would declare a map<string, string> and define a base set of supported commands (i.e. map m[“clockwise”] = “clockwise”). Every time the user enters a command from the command line, we would iterate through the map and check if there exists a key that matches their input. If a key was found that is binded to a valid command, then the correct code would execute. For example, entering “clockwise” would rotate a block clockwise since “clockwise” is a valid key in the map defined as m[“clockwise”] = “clockwise”.

The advantage of using maps for the command interpreter is that users are able to define key-value pairs to add new command names or rename commands at runtime. For instance, typing “rename clockwise cc” would call a function that replaces the pair ‘m[“clockwise”] = “clockwise”’ with ‘m[“cc”] = “clockwise”’. Then the user would be able to enter “cc” to execute the clockwise() command. If we also want to let the user give additional aliases to certain commands, they could type “add clockwise cc”, which would call a function that inserts the pair ‘m[“spinright”] = “clockwise”’, meaning that both spinright and clockwise execute the clockwise() command. As you can see, using maps gives the user a high degree of flexibility on the command line interface.

As for the ability to create macros, we could also leverage an interface that uses maps. When the user types “macroname list_of_commands”, we want the user to be able to type macroname then execute a custom list_of_commands. With our implementation that uses maps, this would be done by calling a function that does the following:
Adds “macroname” as a valid command that executes the user’s specified commands
Adds a binding ‘m[“macroname”] = “macroname”’

Hence, when the user types in the specified macroname, it would be stored in the map just like any other command. By adding the map functionality, we see through these examples that we are given a larger degree of flexibility at the command line.

To apply these features on the available shortcuts for existing command names, when a command is inputted, we use the find() method for strings between each of the map values and the command, and if it returns a match that starts from the first index in the string, then that command will be used.
Final Questions
1. What lessons did this project teach you about developing software in teams? If you
worked alone, what lessons did you learn about writing large programs?

There are a few lessons we learned from working working on this project in teams:

We learned how to communicate with each other in an effective manner so that everyone was on the same page at all times. This is because every part of the code was interdependent and any additional implementation features should be done while cognizant of the rest of the implementation details. When writing large programs, it is important to compile code often and carefully since errors can be much harder to address with so much code. It is always important to have at least a working relation with all of your group members. If conflicts arise you must take care of it professionally and handle it in a mature manner without affecting your relationship with them. 

2. What would you have done differently if you had the chance to start over?

If we were to start over we would design our timeline more rigorously and made sure we followed it more effectively. In addition, we would also be more strategic about the way we split up the work. There were many periods of time that we would work on our own pieces of code, then try to merge our work and get compilation errors. This was not only tedious for us to fix long lists of errors, but it also led us to waste large amounts of time when discovering that our design approaches were incompatible. A better approach would have been to work in short bursts together, rather than long bursts separately. That way, we would minimize our errors from compiling together and ensure that we have a loosely coupled and highly cohesive design in the end.
