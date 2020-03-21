/**
 * @Author: Killian Sheriff <Killian>
 * @Date:   05-Mar-2020
 * @Email:  killian.sheriff@gmail.com / killian.sheriff@mail.mcgill.ca
 * @Last modified by:   Killian
 * @Last modified time: 05-Mar-2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "params.h"
#include "forces.h"

void Translate(double *q, double *theta_1, double *theta_2, double *p_1, double *p_2,double *mass1, double *mass2, double *length1, double *length2);

double QVelo0(double *q, double t, int num_elems){ // dtheta1/dt
        double f;
        double theta_1, theta_2, p_1, p_2, l_1, l_2, m_1, m_2;
        double cos12, Mtot;

        Translate(q, &theta_1, &theta_2, &p_1, &p_2, &m_1, &m_2, &l_1, &l_2);
        cos12 = cos(theta_1-theta_2);
        Mtot = m_1+m_2;
        f = l_2*p_1 - l_1*p_2*cos12;
        f /= l_1*l_1*l_2*(Mtot - m_2*cos12*cos12);
        return f;
} //QVelo0

double QVelo1(double *q, double t, int num_elems){ // dtheta2/dt
        double f;
        double theta_1, theta_2, p_1, p_2, l_1, l_2, m_1, m_2;
        double cos12, Mtot;

        Translate(q, &theta_1, &theta_2, &p_1, &p_2, &m_1, &m_2, &l_1, &l_2);
        cos12 = cos(theta_1-theta_2);
        Mtot = m_1+m_2;
        f = l_1*Mtot*p_2-l_2*m_2*p_1*cos12;
        f /= l_1*pow(l_2,2)*m_2*(Mtot-m_2*pow(cos12,2));
        return f;
}

double QVelo2(double *q, double t, int num_elems){ // dp1/dt
        double f,a,b,c;
        double theta_1, theta_2, p_1, p_2, l_1, l_2, m_1, m_2;
        double cos12,sin12, Mtot;

        Translate(q, &theta_1, &theta_2, &p_1, &p_2, &m_1, &m_2, &l_1, &l_2);
        cos12 = cos(theta_1-theta_2);
        sin12= sin(theta_1-theta_2);
        Mtot = m_1+m_2;
        a = -1*p_1*p_2*sin12;
        a /= l_1*l_2*(Mtot-m_2*pow(cos12,2));
        b = (l_2/l_1)*pow(p_1,2)+(l_1/l_2)*(Mtot/m_2)*pow(p_2,2)-2*p_1*p_2*cos12;
        b *= m_2*cos12*sin12;
        b /= l_1*l_2*pow((Mtot-m_2*pow(cos12,2)),2);
        c = -1*Mtot*9.8*l_1*sin(theta_1);
        f = a+b+c;
        return f;
}

double QVelo3(double *q, double t, int num_elems){ // dp2/dt
        double f,a,b,c;
        double theta_1, theta_2, p_1, p_2, l_1, l_2, m_1, m_2;
        double cos12,sin12, Mtot;

        Translate(q, &theta_1, &theta_2, &p_1, &p_2, &m_1, &m_2, &l_1, &l_2);
        cos12 = cos(theta_1-theta_2);
        sin12= sin(theta_1-theta_2);
        Mtot = m_1+m_2;
        a = p_1*p_2*sin12;
        a /= l_1*l_2*(Mtot-m_2*pow(cos12,2));
        b = (l_2/l_1)*pow(p_1,2)+(l_1/l_2)*(Mtot/m_2)*pow(p_2,2)-2*p_1*p_2*cos12;
        b *= -1*m_2*cos12*sin12;
        b /= l_1*l_2*pow((Mtot-m_2*pow(cos12,2)),2);
        c = -1*m_2*9.8*l_2*sin(theta_2);
        f = a+b+c;
        return f;
}

void Translate(double *q, double *theta_1, double *theta_2, double *p_1, double *p_2, double *mass1, double *mass2, double *length1, double *length2){//changes coordinate system
        *theta_1=q[0];
        *theta_2=q[1];
        *p_1=q[2];
        *p_2=q[3];
        *mass1=PARAM_DATA.mass1;
        *mass2=PARAM_DATA.mass2;
        *length1=PARAM_DATA.length1;
        *length2=PARAM_DATA.length2;
}

double TotalEnergy(double *q){
        double E,a,b;
        double theta_1, theta_2, p_1, p_2, l_1, l_2, m_1, m_2;
        double cos12, Mtot;

        Translate(q, &theta_1, &theta_2, &p_1, &p_2, &m_1, &m_2, &l_1, &l_2);
        cos12 = cos(theta_1-theta_2);
        Mtot = m_1+m_2;

        a = (l_2/l_1)*pow(p_1,2)+(l_1/l_2)*(Mtot/m_2)*pow(p_2,2)-2*p_1*p_2*cos12;
        a /= 2*l_1*l_2*(Mtot-m_2*pow(cos12,2));
        b = -1*Mtot*9.8*l_1*cos(theta_1)-m_2*9.8*l_2*cos(theta_2);
        E=a+b;
        return E;
}
