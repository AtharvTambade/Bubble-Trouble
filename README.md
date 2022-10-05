# Bubble-Trouble
Name: Tambade Atharv Rhushikesh
Roll No. : 210260057
Topic : CS101-Project-Bubble_Trouble

I implimented following features in program starter code given.


1. bubble.h

* The parabolic trajectory of the bubbles was introduced by using gravity means acceleration in downword direction and new y-position of bubble was determined by using the "Newton's Laws of Motion" ; S = ut + 0.5at^2

* The bubble movement was confined in window by changing the direction of velocity when bubble reaches the blue line and upper end of window



2. shooter.h

* No changes


3. bullet.h

* No Changes



4. main.cpp

The following functions are mentioned in the order of their appearance in the code.

* A void function named 'small_bubbles' was created with parameters as the vector bubbles, x(x-position), y(y-position), radius(radius of the bubble), to create smaller bubbles after larger bubble distroyed 

This function creates two bubbles moving opposite direction from each other at the same position where larger bubble was distroyed by bullet.


* An void function named 'collision' was created to check the collision between all the pairs of bubbles and bullets.

It checks distance between each bubble and bullet if the distance is smaller than some unique value then it distroys bubble as well as bullet.

if bubble radius is greater than threshhold value then it calls small_bubbles function and distriye the old bubble and bullet.


* A function with vector type return named 'create_bubbles' which was already present I just created two versions of it each one is called in corresponding level.


* A void function named 'collision_with_shooter'was created to check the collision between bubbles and shooter

It checks the distance between shooter and bubble if bubble is close to shooter than some particular value then it distroys bubble.


* Some variables are created
  a)seconds     : which increased by 1 after each STEP_TIME which in this case 0.02 seconds.
  b)health      : which increase by 1 when bubble collide with shooter.
  c)score       : which increase by 1 when bubble is destroyed by bullet.
  d)false _score: which increses by 1 each and every time when bubble is destroyed specialy when bubble is destroyed when it comes in contact with shooter.

* Some string massages are printed on canvas
  a)Health   : it shows how many healths out of 3 are exhausted.It is at top right corner of screen.
  b)Time left:it shows how much time left to complete the level.It is at top left corner of screen.
  c)level    :it shows the number of level in which you are currently in. It is at top of the screen.
  d)score    :it shows what is your current score. It is at bottom right corner of the screen.

* Initialisation of 'shooter', 'bubbles', 'bullets' & Xevent 'event'.

* Now we check is there at least one bubble from level 1 is there or not by checking Fals-score is less than 4 or not if yes we play the first level if not move
  towards second level. 

* Inside the 'while' Loop
   We check the event according to it shooter moves or shoots.
   check the timer and health counter if it is not according to requirments stop the game.
   Now I know that time health this are strings and numbers can't be printed as strings therefore I took help of "ASCII" valus I broje each number which I 
   wanted to print as unit place,tenth place and print that using its "ASCII" values.


* Move the bubbles & bullets using move_bubbles() and move_bullets() functions respectively passing the parameter as vector bubbles and bullets respectively.

* Wait for STEP_TIME.
	
8 After completion of first level following things are done
   Reseting of timer both level have different time constraints. In case of time to match with actual real life seconds scale some frequency matching nedd to be done
   Heaith counter and score as well as false_score counter are kept as it is.
   level increased on screen.
   Processes in second level are similar to first
*After completion of the game
   If player has successfully completed all the levels then "Congratualations" massage comes on the middle of screen
   If player lost due to lack of time then ""You ran out of Time" massage comes on screen
   If player lost due to lack of healths then ""You ran out of Health" massage comes on screen
 

Wait for the user to read and then prompt to click the screen to exit the game!

GAME OVER! :)



The complete video of the project output can be viewed at the following link:

https://drive.google.com/file/d/1dnPERPDB_sbxgWTCBErFJL3qgtFdAdxm/view?usp=sharing


