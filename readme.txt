The game here is contained in main.c, and is a Georgia Tech football themed version of Arkanoid, or Brick Breaker. There are 9 different colors of blocks, although they aren't all used in the game. The game keeps track of score and high-score throughout the game, although it doesn't save across instances of the game. Your usual platform is instead a Ramblin' Wreck, the ball is a football, and the backgrounds are usually pictures of Georgia Tech winning games; except when you hit game over, of course.

You only have one life, because I figured I already made the game easy enough when I doubled the speed of the car. There are three levels, beginning with Virginia Tech, followed by Miami, then by UGA.

Note that what would normally be in myLib.c or myLib.h is instead split up into input.h, graphics.h, and graphics.c

Here are the controls for the game:

GameBoy  |  Keyboard  |  In-Game
--------------------------------
Select   |  Backspace |  Return to Game Start
A        |  Z         |  Used to Move Between Different Screens
Left     | Left Arrow |  Move the Ramblin' Wreck left
Right    | Right Arrow|  Move the Ramblin' Wreck right
