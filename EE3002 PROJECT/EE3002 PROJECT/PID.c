#include "PID.h"

/*1140*/


float P, D, I, previousError, PIDvalue, error;
float lfspeed =270;
float Kp =10;
float Ki = 13;
float Kd =34;
int lsp, rsp;
//float samplingPeriod=150*pow(10,-6);
uint8_t multiP = 2;
uint8_t multiI  = 5;
uint8_t multiD = 1;
uint8_t Kpfinal;
uint8_t Kifinal;
uint8_t Kdfinal;
float Pvalue;
float Ivalue;
float Dvalue;

void PID_Linefollow(int error, int distance){
    P = error;
    I = I + error;
    D = (error - previousError);
    
    Pvalue = (Kp/pow(10,multiP))*P; 
    Ivalue = (Ki/pow(10,multiI))*I; //x150 micro
    Dvalue = (Kd/pow(10,multiD))*D; // /150 micro

    float PIDvalue = Pvalue + Ivalue + Dvalue;
    previousError = error;

    lsp = (lfspeed - PIDvalue);
    rsp = (lfspeed + PIDvalue);
	  
		if(lsp > 0 && rsp > 0 && distance > 30){
			position(FORWARD, BACKWARD, FORWARD, BACKWARD);
		  timer4_pwm_microsV(1300, rsp, lsp);
		}else if(lsp > 0 && rsp > 0 && distance <= 30){
			position(BACKWARD, FORWARD, BACKWARD, FORWARD);
		  timer4_pwm_microsV(1300, rsp, lsp);
		}

}

