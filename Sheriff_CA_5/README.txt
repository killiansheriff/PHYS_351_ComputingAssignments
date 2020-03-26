The goal of this assignment is to implement numerical integration routines and use them to plot a Kepler orbit.
On MacOS:


- Open a terminal and type "cd PATH_FILE_DIRECTORY" and click enter.

For generating num_integ_test.dat:
- Uncomment lines 137 to 142 of num_integ.c

- In the terminal type "gcc num_integ.c -o exec" to compile and create an executable named exec. Click enter.

- In the terminal type "./exec " and hit enter to execute the program.

For Kepler Orbits:
- Make sure lines 137 to 142 of num_integ.c are commented.

- In the terminal type "gcc main.c num_integ.c -o exec" to compile and create an executable named exec. Click enter.

- In the terminal type "./exec " and hit enter to execute the program.

Note:
The Kepler integrand parameters are:
K = 1.0/137.0;
mass = 0.511e+6;
pphi = 2.0;
ene = -1.0;
