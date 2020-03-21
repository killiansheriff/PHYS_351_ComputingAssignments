
The goal of this program is to solve the Euler equations numerically.The dynamical variables are q[0], q[1], [2]
with the identification omega_1 = q[1], omega_2 = q[2], omega_3 = q[0]and I_1 = I[1], I_2 = I[2] and I_3 = I[0]The equations to solve are:I_1 domega_1/dt = (I_2 - I_3)omega_2 omega_3I_2 domega_1/dt = (I_3 - I_1)omega_3 omega_1I_3 domega_1/dt = (I_1 - I_2)omega_1 omega_2

On MacOS:

For Task 1: 

- Open a terminal and type "cd PATH_FILE_DIRECTORY" and click enter.


- In the terminal type "gcc main.c analysis.c evolve.c forces.c init.c vector_mtx.c -o exec" to compile and create an executable named exec. Click enter.

- In the terminal type "./exec InitParams.dat" and hit enter to execute the program.
Note: you can also replace the InitParams.dat by the InitParams.txt.

For run1: it_max = 1000, for run2: it_max =  100.
Note: For clarity, the InitParams.dat/InitParams.txt has to be formatted as the following:

num_eq = 3
q_i[0] = 2.000000e+00
q_i[1] = 4.000000e+00
q_i[2] = 1.000000e+00
t_i = 0.000000e+00
t_f = 2.000000e+01
it_max = 100
h = 2.000000e-02
I_prin[0] = 3.000000e+00
I_prin[1] = 4.000000e+00
I_prin[2] = 7.000000e+00




