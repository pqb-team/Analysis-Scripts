#Data Analysis Repository

This repository should be where we place analysis scripts we create & use for our data analysis

Add any scripts you create to this README as you go

#spotsize.C
Used to analyze data from beam spot-size studies
Takes the following inputs:
  * Run number - Currently just one at a time
  * BPMs - Takes a vector of these, so add or subtract as needed
  * X Positions - Takes a vector
  * Y Positions - Takes a vector

    
Below are the objects within spotsize.C

spotsize_grid
  * Takes a bpm, XPos, and YPos and plots the bpm's result at each coordinate combination
    
spotsize_fit
  * Plots the change in the bpm as a function of either XPos or YPos
