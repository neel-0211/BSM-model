#include <iostream>
#include <cmath>
#include "BSM_model.h"

using namespace std;

int main(){
        double spot{0}, strike{0}, rate{0}, time{0}, x{0}; 
        char v_p;
        bool is_vol{false}, is_call{false};
        
        while(true){
                cout<<"Do you want to price a Call or a Put option? (C/P): ";
                cin>>v_p;
                if(v_p=='C' || v_p=='c' || v_p=='P' || v_p=='p'){
                        if(v_p=='C' || v_p=='c'){is_call = true; break;}
                        break;
                }
                else
                        cout<<"Incorrect Input"<<endl;
        }
        cout<<endl<<"Please Enter:"<<endl;
        cout<<"Spot Price: ";
        cin>>spot;
        cout<<"Strike Price: ";
        cin>>strike;
        cout<<"Risk free rate: ";
        cin>>rate;
        cout<<"Time to maturity(in years): ";
        cin>>time;
        
        cout<<endl;
        
        while(true){
                cout<<"Do you want to enter Volatility or Option Price (V/P): ";
                cin>>v_p;
                if(v_p=='V' || v_p=='v' || v_p=='P' || v_p=='p'){
                        if(v_p=='V' || v_p=='v'){
                                cout<<"Enter Volatility: ";
                                cin>>x;
                                is_vol = true;
                                break;
                        }
                        else{
                                cout<<"Enter Price: ";
                                cin>>x;
                                break;
                        }
                }
                else
                        cout<<"Incorrect Input"<<endl;
        }
        
        Option c(spot, strike, rate, time, x,is_vol,is_call);
        cout<<endl;
        while(true){
                cout<<"Do you want Summary of the parameters of the options inputted or greeks of the option? (S/G) (Press E for exit): ";
                cin>>v_p;
                cout<<endl;
                if(v_p=='S' || v_p=='s' || v_p=='G' || v_p=='g' || v_p=='E' || v_p=='e'){
                        if(v_p=='S' || v_p=='s'){c.summary();cout<<endl;}
                        else if(v_p=='E' || v_p=='e'){break;}
                        else{c.greeks();cout<<endl;}
                }
                else
                        cout<<"Incorrect Input"<<endl;
        }
}