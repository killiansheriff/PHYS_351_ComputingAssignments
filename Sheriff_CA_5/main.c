#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "num_integ.h"

double Kepler(double r); //kepler integrand

int main(){
        FILE *output;
        double K, mass, pphi, ene, r_up, r_down, dr, r, phi, x, y, tol, limit;
        int nmax, count;
        K = 1.0/137.0;
        mass = 0.511e+6;
        pphi = 2.0;
        ene = -1.0;

        r_up= K + pow(K*K-2*fabs(ene)*pphi*pphi/mass,0.5);; //calculating upper bound
        r_up /= 2*fabs(ene);
        r_down= K-pow(K*K-2*fabs(ene)*pphi*pphi/mass,0.5); // calculating lower bound
        r_down /= 2*fabs(ene);
        printf("r_down = %lf, r_up = %lf\n",r_down,r_up ); //for reference

        tol = 1e-10;
        limit = 10000;
        output = fopen("kepler.dat", "w+");
        nmax = 100;
        dr = (r_up-r_down)/nmax;

        for(int n=0; n<=nmax; n++) {
                r = r_down + n*dr;
                count = 0;
                phi = Integrate(Kepler, r_down, r, tol, &count, limit); //integrating to get phi
                x = r*cos(phi); //get varibles from phi
                y = r*sin(phi);
                fprintf(output,"%lf %lf\n",x,y);
        }
        fclose(output);
        return 0;
}

double Kepler(double r){
        double f, K, mass, pphi, ene, arg, root;
        K = 1.0/137.0;
        mass = 0.511e+6;
        pphi = 2.0;
        ene = -1.0;

        f = pphi/(mass*r*r); //define integrand for total energy
        root= fabs(2.0/mass*(ene-pow(pphi,2)/(2*mass*pow(r,2))+K/r)+1e-16);
        f/= pow(root,0.5);
        return f;

}
