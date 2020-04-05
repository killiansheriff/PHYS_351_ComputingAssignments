#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "num_integ.h"

#define error_handler(tag) { printf(tag); exit(0);} //defined error handler

double test_func(double x); //to test intergrand
int TestNumInteg();

double NumIntegrate (double *f, double h, int down, int up, int nmax){
        int tmp;
        double sum;

        if(up > nmax || down > nmax) error_handler("Up or down is larger than nmax ") //exits
                if(up < 0 || down < 0) error_handler("Up or down is less than zero ")

                        if(down > up) { //switch sign of integral and bounds
                                tmp = up;
                                up = down;
                                down = tmp;
                                h *= -1;
                        }

        if(up == down) { //if the bounds are the same
                return 0;
        }
        else if(up == down +1) { //single interval
                sum = f[down] + f[down +1];
                sum *= h/2.0;
        }
        else if(up == down +2) { // 2 intervals (Simpson's Rule)
                sum = f[down] + 4*f[down +1] + f[down +2];
                sum *= h/3.0;
        }
        else if(up == down +3) { // 3 intervals (simpson's 3/8 rule)
                sum = 3*f[down] + 9*f[down +1] + 9*f[down +2] + 3*f[down +3];
                sum *= h/8.0;
        }
        else if(up == down +4) { // 4 intervals (Boole's rule)
                sum = 14*f[down] + 64*f[down +1] + 24*f[down +2] + 64*f[down +3] +14*f[down +4];
                sum *= h/45.0;
        }
        else if(up == down +5) { // 5 intervals (6 point rule)
                sum = 19*f[down] + 75*f[down +1] + 50*f[down +2] + 50*f[down +3] +75*f[down +4]+19*f[down +5];
                sum *= 5*h/45.0;
        }

        else { // more than 7 points
                sum = (3/8.0)*f[down] + (7/6.0)*f[down +1] + (23/24.0)*f[down +2] + (23/24.0)*f[down +(nmax -2)] + (7/6.0)*f[down +(nmax-1)]+ (3/8.0)*f[down + nmax];
                for(int i = 3; i <= (nmax -3); i++) {
                        sum += f[down +i];
                }
                sum *= h;
        }
        //{
        // Implement Eq.(99)
        // Put it in sum
        //sum = 0;
        //for (int i = 2; i <= (up - down); i=i+2)
        //{
        //        sum += f[down+i-2] + 4*f[down+i-1] + f[down+i];
        //    }
        //sum *= h/3.0;
        //}
        return sum;
}

double NumIntegrateV (double (*func)(double), double x_down, double x_up, int num_intervals){ //wrapper for NumIntegrate
        double f,h;
        double *vf;
        vf = (double *) malloc(sizeof(double)*(num_intervals+1)); //allocating memory
        h = (x_up - x_down)/(num_intervals); //calculates inverval size
        for(int n = 0; n <= num_intervals; n++) { //popultate vf
                vf[n] = func(x_down + n*h);
        }
        f = NumIntegrate(vf, h, 0, num_intervals, num_intervals);
        free(vf);
        return f;
}


double AdaptiveIntegrate(double (*func)(double), double x_down, double h, double *f_prev, double ans_prev, double tol, int *count){
        double h_half, ans_l=0, ans_r=0, ans_now, err;
        double fl[3], fr[3];
        double w[3] = {1.0/3.0, 4.0/3.0, 1.0/3.0}; //simpson rule weights
        h_half = h/2.0;
        fl[0] = f_prev[0];
        fl[2] = f_prev[1];
        fl[1] = func(x_down + h_half);

        fr[0] = f_prev[1];
        fr[2] = f_prev[2];
        fr[1] = func(x_down + 3*h_half);

        *count += 2;
        for (int i = 0; i < 3; i++) { //apply simpsons rule for right and left hand sides
                ans_l += (h/2.0)*w[i]*fl[i];
                ans_r += (h/2.0)*w[i]*fr[i];
        }

        ans_now = ans_l + ans_r; //computes anser now
        err = (ans_now - ans_prev)/15.0; //computes error

        if(fabs(err) > tol) { //if error is larger than tolerance then run again
                ans_l = AdaptiveIntegrate(func, x_down, h_half, fl, ans_l, tol, count);
                ans_r = AdaptiveIntegrate(func, x_down+h, h_half, fr, ans_r, tol, count);
                ans_now = ans_l + ans_r;
        }
        else{
                ans_now += err;
        }

        return ans_now;
}

double Integrate(double (*integrand)(double), double x_down, double x_up, double tol, int *count, int limit) {
        double w[3] = {1.0/3.0, 4.0/3.0, 1.0/3.0}; //simpson rule weights
        double f_prev[3];
        double ans_prev, f;
        double h = (x_up - x_down)/2;

        f_prev[0]=integrand(x_down); //setting f_prev
        f_prev[1]=integrand(x_down + h);
        f_prev[2]=integrand(x_up);
        for (int i = 0; i < 3; i++) { //apply simpsons rule for right and left hand sides
                ans_prev += (h)*w[i]*f_prev[i];
        }

        *count += 3;
        f = AdaptiveIntegrate(integrand, x_down, h, f_prev, ans_prev, tol, count);

        if(*count > limit) error_handler("Count number has exceeded limit set") //exits

                return f;
}
/*
   int main(){
        TestNumInteg();
        return 1;
   }
*/ 
int TestNumInteg(){
        double f_prev[3];
        double w[3] = {1.0/3.0, 4.0/3.0, 1.0/3.0};
        double (*integrand)(double); //function pointer for the integrand
        FILE *output;
        double x_down, x_up, tol,err,f,g;
        int count, limit, num_intervals;
        integrand = test_func; //setting values to test
        x_down=0.001;
        x_up= 10.0;
        g = 2.726201989096137;
        output = fopen("num_integ_test.dat", "w+"); //open file for writing

        num_intervals=100;
        f= NumIntegrateV(integrand, x_down, x_up, num_intervals);
        err=fabs((f-g)/g);
        fprintf(output,"f= %lf, Number of Intervals = %d, Relative Error =  %e\n",f, num_intervals, err);

        num_intervals=1000;
        f= NumIntegrateV(integrand, x_down, x_up, num_intervals);
        err=fabs((f-g)/g);
        fprintf(output,"f= %lf, Number of Intervals = %d, Relative Error =  %e\n",f, num_intervals, err);

        tol= 1.0e-10;
        limit=10000;
        count=0;
        f = Integrate(integrand, x_down, x_up, tol, &count, limit);
        err=fabs((f-g)/g);
        fprintf(output,"f= %lf, Number of Intervals = %d, Relative Error =  %e\n",f, count, err);

        num_intervals=count;
        f= NumIntegrateV(integrand, x_down, x_up, num_intervals);
        err=fabs((f-g)/g);
        fprintf(output,"f= %lf, Number of Intervals = %d, Relative Error =  %e\n",f, num_intervals, err);
        fclose(output);
        return 1;
}
double test_func(double x){
        double f,R, a;
        f = sin(1.0/x);
        return f;
}
