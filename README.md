
# Tower Attack
A console C++ game utilizing ncurses. Inverse of Tower Defense, here you are the one that sends soldiers into the battlefield and the AI places the towers.
Incudes 4 maps, 4 difficulity configurations and save/load capability.
The soldiers pathfind the shortest path to the nearest exit and the tower enemy ai tries to place towers in a way that makes is as difficult as possible.


## How to play
1) clone the repository and compile
```bash
$ git clone https://github.com/filipovskyj02/Tower-Attack.git; 
$ cd Tower-Attack;
$ make play;
```
   

2) Navigate the menu with up and down arrow keys
<image size=800% src="Images/menu.png">
3) Choose the enterance to spawn your soldiers at with up/down and which type of soldier to spawn with left/right arrow keys
<image size=800% src="Images/game.png">
Chosen soldiers and enterance will be highligted.
<image size=800% src="Images/game2.png">
4) Win by getting enough of your soldiers through the enemy gates.
