#include <string>
#include <iostream>
#include "Integration.h"
#pragma once

using namespace std;

class Option : public Integration{
public:

        Option(const double& S, const double& K, const double& r, const double& T, const double& x, const bool& is_vol, const bool& is_call);
        double get_price() {return price;}
        double get_rate() {return rate;}
        double get_time() {return time;}
        double get_vol() {return vol;}
        double get_strike() {return strike;}
        double get_spot() {return spot;}
        
        std::string option_type();
        
        double get_delta() {calculate_delta();
        return delta;}
        double get_gamma() {calculate_gamma();
        return gamma;}
        double get_vega() {calculate_vega();
        return vega;}
        double get_rho() {calculate_rho();
        return rho;}
        double get_theta() {calculate_theta();
        return theta;}
        void summary(){
                cout<<"Option's price is: "<<price<<endl;
                cout<<"Stock's price is: "<<spot<<endl;
                cout<<"Option's strike is: "<<strike<<endl;
                cout<<"Option's time to maturity is: "<<time<<" year"<<endl;
                cout<<"Option's risk free rate is: "<<rate*100<<"%"<<endl;
                cout<<"Option's volatility is: "<<vol*100<<"%"<<endl;
        }
        void greeks(){
                get_delta();
                get_gamma();
                get_vega();
                get_rho();
                get_theta();
                cout<<"Option's delta is: "<<delta<<endl;
                cout<<"Option's gamma is: "<<gamma<<endl;
                cout<<"Option's vega is: "<<vega<<endl;
                cout<<"Option's rho is: "<<rho<<endl;
                cout<<"Option's theta is: "<<theta<<endl;
        }
private:

        double spot, strike, rate, time, price, vol;
        double delta, gamma, vega, rho, theta;
        bool iscall;
        
        double call_price(const double&, const double&, const double&, const double&, const double&);
        double put_price(const double&, const double&, const double&, const double&, const double&);
        double volatility(const double&, const double&, const double&, const double&, const double&, const bool&);
        double vega_for_vol(const double& S, const double& K, const double& r, const double& v, const double& T);
        
        void calculate_delta();
        void calculate_gamma();
        void calculate_vega();
        void calculate_rho();
        void calculate_theta();
};