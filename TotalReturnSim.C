#include <iostream>
#include <cmath>

#include "TROOT.h"
#include "TSystem.h"
//#include "TApplication.h"
#include "TRandom.h"
#include "TRandom2.h"
#include "TH1D.h"
#include "TCanvas.h"

using namespace std;

TRandom *rng = new TRandom2();

// one simulation run
// return value: <number, value> for each year
std::vector< std::pair<double,double> > sample(
  double start_value,
  double add_annual,
  double avg_yield,
  double yield_sigma,
  int years)
{
  double current_price = 100.; // without loss ov generality
  // number of shares (or whatever)
  double current_amount = start_value/current_price; 
  std::vector< std::pair<double,double> > re_sample;
  
  for (int i=0; i<years; i++)
  {
    double this_year_yield = rng->Gaus(avg_yield, yield_sigma);
    
    current_price = current_price * (1.+this_year_yield);
    current_amount += add_annual/current_price;
    
    re_sample.push_back(
      std::make_pair(current_amount, current_price)
    );
  }
  
  return re_sample;
}

// main ROOT function
void TotalReturnSim()
{
//----------------------------------------------------------------------------//
  double annual_payment = 100;    // currency
  double average_yield = 5;       // percent points
  double yield_sigma   = 7.5;     // percent points
  int number_of_years = 30;       // duration in years
  
//----------------------------------------------------------------------------//
  int runs = 250000;                // number of simulation runs
  TH1D* result 
    = new TH1D("result", "distribution of final amount", 1500, 0., 30000.);
  result->GetXaxis()->SetTitle("final amount");
  result->GetYaxis()->SetTitle("prevalence");
  
  // main loop
  for (int y=0; y<runs; y++)
  {
      std::vector< std::pair<double,double> > my_sample 
        = sample(0, annual_payment, average_yield/100., yield_sigma/100., number_of_years);
      
      result->Fill(
        my_sample.back().first * my_sample.back().second
      );
  }
  
  TCanvas *c1 = new TCanvas("c1","result",200,10,700,500);
  result->Draw();
  c1->Update();
  
}
