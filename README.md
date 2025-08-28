Github repo link: https://github.com/arokua/assignment-2-food-vendor-sim.git

A simulation of how a fast food vendor works via terminal input.

This program makes use of linkedlist data structures and dynamic programming to handle coin change.

The program support the following operations:
1. Load and save current availible food items and their prices (food.dat) and the current amount of notes, coins the vendor have in possesion (coins.dat) (( No encoding current exists for these files))
2. Display a menu that the user can choose from, this menu is contained as a linked list
3.
  3.1. Customers can: view sub menu and buying an item, the DP coin change algorithm was intended to be applied here for optimal calcuations.
  3.2. Administrators can 
    3.2.1. Add and remove food item(s) from the menu.
    3.2.2. Display the current balance, if current balance does not contain the correct quantities to give change to the customer, no transaction will occur.
Makefile commands:
make  : compiles the program

./ftt data-files/foods.dat data-files/coins.dat  : run the program (You can move the foods.dat and coins.dat to the same directory as ./ftt so it would follow the original commands from the specs sheet)

make test  : copy data files and then move them to the /testing-files directory, then execute the test using input files and compare the actual_output files with the expected_output files

make clean  : delete/remove all of the object files, executables, copy of the data files and the actual_output files


Shell script: (was also used to testing)

chmod -x testing_script.sh  : allow the shell script to run

./testing_script.sh  : run the script
