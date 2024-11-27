Welcome to the town of Summerside!
================================
There's been a murder. As the new detective in town, it's your job to solve the mystery. 
Using the previous detective's notes, piece together the story by investigating the evidence
board and clicking on the clues to view them. 

There are three clues in total: a map, a picture, and a letter. When you’re ready, pick the 
person you think committed the crime! But be careful, as you only have 2 attempts to get it right.  

Starting at the introduction page, navigate through the game by clicking on the different clues. 
To exit each clue, either close the window, or click the "Done" button. To make a guess, another 
window will appear with the three suspect names. Click on the name you believe is the murderer.  
The number of attempts will be displayed on the screen.

================================

Before playing the game, the relevant libraries for SDL2 must be downloaded ahead of time. For WSL on the terminal, install these three libraries: 

	1. SDL2 library: 
	sudo apt install libsdl2-dev
	
	2. SDL2 image library: 
	sudo apt install libsdl2-image-dev

	3. SDL2 true type font library: 
	sudo apt install libsdl2-ttf-dev
	
When compiling in c, make sure to use the correct flags: 
 -lSDL2 -lSDL2_image -lSDL2_ttf