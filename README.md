# Data Analysis Repository

This repository should be where we place analysis scripts we create & use for our data analysis

Add any scripts you create to this README as you go

# spotsize.C
Used to analyze data from beam spot-size studies. Takes the following inputs:
  * Run number - Currently just one at a time
  * BPMs - Takes a vector of these, so add or subtract as needed
  * X Positions - Takes a vector
  * Y Positions - Takes a vector


### spotsize_grid()
Takes a bpm, XPos, and YPos, and plots the bpm's result at each coordinate combination
  * Plots are output as root files
    
### spotsize_fit()
Plots the change in the bpm as a function of either XPos or YPos
  * Plots are output as root files
  * The data needs to be fit separately at the moment. Looking into changing this



#simple_phase.C
Used to generate sinusoidal fits of bpm & magnet data and extract phase/frequency/amplitude information. Takes the following inputs:
  * Run number - The run you wish to analyze
  * event min/max - The range of events you wish to analyze
  * type & name - The type of device you are analyzing (bpm/magnet) & its name (BPM11Y, etc)


### phase_fit.C
This function does the fitting and is fed from simple_phase.C
  * Outputs the fit information to simple_phase.C to be used for plotting & further calculations


This script currently takes one value of each input, but this can easily be extended to vectors with loops. A data storage system (such as a plot or array) will need to be generated to hold those results, however.
