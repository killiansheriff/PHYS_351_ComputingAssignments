The goal of this assignment is to solve the double pendulum problem numerically using adaptive rk4.
The dynamical variables are theta_1, theta_2, p_1, and p_2
They correspond to q[0], q[1], q[2], and q[3], respectively
On MacOS:


- Open a terminal and type "cd PATH_FILE_DIRECTORY" and click enter.


- In the terminal type "gcc main.c rk4.c evolve.c vector_mtx.c init.c forces.c -o exec" to compile and create an executable named exec. Click enter.

- In the terminal type "./exec inputs.txt" and hit enter to execute the program.

For run1 and run2 respectively we have q_i[3] = 2.0000000e+00 and q_i[3] = 2.0100000e+00.
Note: For clarity, the inputs.txt has to be formatted as the following:

num_eq = 4
q_i[0] = 1.000000e-01
q_i[1] = 5.000000e-02
q_i[2] = 0.000000e+00
q_i[3] = 2.0000000e+00
t_i = 0.000000e+00
t_f = 2.000000e+01
h = 1.000000e-01
mass1 = 4.000000e-01
length1 = 4.000000e-01
mass2 = 9.000000e-01
length2 = 7.000000e-01
prec_goal = 1.000000e-10





