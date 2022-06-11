#include <iostream>
#include <cmath>
#include <string>
#include "BSM_model.h"

using namespace std;


Option::Option(const double& S, const double& K, const double& r, const double& T, const double& x, const bool& is_vol, const bool& is_call)
        :  Integration{0,0}, spot{S}, strike{K}, rate{r}, time{T}, iscall{is_call}{
                
        if(is_vol==true){
                vol=x;
                if(is_call==true)
                        price = call_price(spot, strike, rate, vol, T);
                else
                        price = put_price(spot, strike, rate, vol, T);
        }
        else{
                price = x;
                if(is_call==true)
                        vol = volatility(price, spot, strike, rate, time, true);
                else
                        vol = volatility(price, spot, strike, rate, time, false);
        }        
}

double Option::call_price(const double& S, const double& K, const double& r, const double& v, const double& T){
        double d1{0}, d2{0};
        
        d1 = (log(S/K) + (r+((v*v)/2))*T)/(v*sqrt(T));
        d2 = d1-v*sqrt(T);
        
        Integration nd1(-5.0, d1);
        Integration nd2(-5.0, d2);
        double nd1_val {nd1.integral()};
        double nd2_val {nd2.integral()};
        
        return S*nd1_val - K*exp(-r*T)*nd2_val;
}

double Option::put_price(const double& S, const double& K, const double& r, const double& v, const double& T){
        double d1{0}, d2{0};
        
        d1 = (log(S/K) + (r+((v*v)/2.0))*T)/(v*sqrt(T));
        d2 = d1-v*sqrt(T);
        
        Integration nd1(-5.0, -d1);
        Integration nd2(-5.0, -d2);
        double nd1_val {nd1.integral()};
        double nd2_val {nd2.integral()};
        
        return  K*exp(-r*T)*nd2_val - S*nd1_val;
}

double Option::volatility(const double& P, const double& S, const double& K, const double& r, const double& T, const bool& is_call){
        /*     http://www.codeandfinance.com/finding-implied-vol.html       */
        int max_iterations{1000};
        double precision {0.001};
        double sigma{0.1}; //Intial guess
        double vega_val{0.0};
        double temp_price{0.0};
         
         
         for(int i=0; i<max_iterations; i++){
                 if(is_call==true)
                         temp_price = call_price(S, K, r, sigma, T);
                else
                        temp_price = put_price(S, K, r, sigma, T);
                vega_val = vega_for_vol(S,K,r,sigma,T);
                if(abs(P-temp_price)<precision)
                        return sigma;
                 
                 sigma += (P-temp_price)/vega_val;
         }
         return sigma;
}

double Option::vega_for_vol(const double& S, const double& K, const double& r, const double& v, const double& T){
        double d1{0};
        d1 = (log(S/K) + (r+((v*v)/2))*T)/(v*sqrt(T));
        
        Integration nd1(-10.0, d1);
        double nd1_val {nd1.integral()};
        return S*sqrt(T)*nd1_val;
}



string Option::option_type(){
                if(iscall == true)
                        return "It is a call option.";
                else
                        return "It is a put option.";
}
     
void Option::calculate_delta(){
    double d1{0};
    d1 = (log(spot/strike) + (rate+((vol*vol)/2))*time)/(vol*sqrt(time));
    if(iscall==true){
            Integration nd1(-5.0, d1);
            double nd1_val {nd1.integral()};
            delta = nd1_val;
    }
    else{
            Integration nd1(-5.0, -d1);
            double nd1_val {nd1.integral()};
            delta = -nd1_val;
    }
}

void Option::calculate_gamma(){
    double d1{0};
    d1 = (log(spot/strike) + (rate+((vol*vol)/2))*time)/(vol*sqrt(time));
    gamma = (1/exp(pow(-d1,2)/2))/(pow((2*M_PI*time),0.5)*(spot*vol));
}
   
void Option::calculate_vega(){
        double d1{0};
        d1 = (log(spot/strike) + (rate+((vol*vol)/2))*time)/(vol*sqrt(time));
        vega = spot*pow(time*exp(-pow(d1,2)),0.5)/(pow(2*M_PI,0.5));
}

void Option::calculate_rho(){
    double d1{0}, d2{0};
    d1 = (log(spot/strike) + (rate+((vol*vol)/2))*time)/(vol*sqrt(time));
    d2 = d1-vol*sqrt(time);
    
    Integration nd2(-5.0, d2);
    Integration nd2_neg(-5.0, -d2);
    
    double nd2_val{nd2.integral()};
    double nd2_neg_val{nd2_neg.integral()};
    
    
    if (iscall == true){
        rho = strike*time*exp(-rate*time)*nd2_val;
    }
    else{
        rho = -strike*time*exp(-rate*time)*nd2_neg_val;
    }
}



void Option::calculate_theta(){
    double d1{0}, d2{0} ;
    
    d1 = (log(spot/strike) + (rate+((vol*vol)/2))*time)/(vol*sqrt(time));
    d2 = d1-vol*sqrt(time);
    
    Integration nd2(-5.0, d2);
    Integration nd2negative(-5.0, -d2);
    double nd2_val {nd2.integral()};
    if(iscall==true)
            theta = -(spot*vol)/(2*exp(pow(-d1,2)/2))/(pow(2*M_PI*time,0.5)) - rate*strike*(1/exp(rate*time))*nd2_val;
    else
            theta = -(spot*vol)/(2*exp(pow(-d1,2)/2))/(pow(2*M_PI*time,0.5)) - rate*strike*(1/exp(rate*time))*(1-nd2_val);
                
}



