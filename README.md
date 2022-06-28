# Projet CIR1 groupe 05
## Why this project
End years projet from [ISEN](https://isen-nantes.fr/)   
this project is a simulation of the solar system  
Build in c and show in javascript with a little website  

## How to run this project
download this project  

use this following command to run :  
`bash script.sh`  
then read the menu in the cmd

## How that work
in C, the trajectories of every planets is calculated with euler and euler asymetric method  
then the program write the trajectories in a .json file to work with javascript  

The program can also calculate the energy ratio to know if there is an energy conservation  

the script.sh file compile the c and create a .json file and move it in the script folder  
to run this .json file in javascript  