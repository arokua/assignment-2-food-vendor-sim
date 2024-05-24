Github repo link: https://github.com/arokua/assignment-2-cosc1076.git


Makefile commands:
make  : compiles the program

./ftt data-files/foods.dat data-files/coins.dat  : run the program (You can move the foods.dat and coins.dat to the same directory as ./ftt so it would follow the original commands from the specs sheet)

make test  : copy data files and then move them to the /testing-files directory, then execute the test using input files and compare the actual_output files with the expected_output files

make clean  : delete/remove all of the object files, executables, copy of the data files and the actual_output files


Shell script: (was also used to testing)

chmod -x testing_script.sh  : allow the shell script to run

./testing_script.sh  : run the script
