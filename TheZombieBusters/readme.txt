-IDE: Visual studio
-No changes made to project settings
-Tested Platform: Windows 10
-Not noticed any bugs, the game does not account for the fact that it is possible that there are zombies left in a place on the grid that is not accessible to the players anymore 
since both players already visited the surrounding cells on the grid
-Between 10th and 15th July (after 10, before 15)
-We have implemented the game slightly differently than in the instructions. The difference is that we have made our warrior, zombie and resource classes 
as abstract classes, while the entity class we made is more like an overarching class that stores and controls all the variables in the game. 
And the main just uses that entity class and the grid to run the game. We did it this way because it made it easier for us to keep things organized and control all classes together.