#include <iostream>
#include <cmath>

#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
//#include "TApplication.h"
#include "TRandom.h"
#include "TRandom2.h"
#include "TH1D.h"
#include "TF1.h"
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
  double xmin = 0.;
  double xmax = 30000.;
  TH1D* result 
    = new TH1D("result", "distribution of final amount", 1500, xmin, xmax);
  result->GetXaxis()->SetTitle("final amount");
  result->GetYaxis()->SetTitle("prevalence");
  
  // exponentially modified gauss function to fit
  TF1 *gauss_expo 
    = new TF1("gauss_expo",
              "[0]*[2]*[3] * TMath::Sqrt(TMath::Pi()/2.) * TMath::Exp( 0.5*[2]*[3]*[2]*[3] - [3]*(x-[1]) ) * TMath::Erfc( ([2]*[3] - (x-[1])/[2])/TMath::Sqrt(2.) )",
              xmin, xmax
              );
  gauss_expo->SetParName(0,"amp");
  gauss_expo->SetParName(1,"mu");
  gauss_expo->SetParName(2,"sigma");
  gauss_expo->SetParName(3,"lambda");
  
  // main loop
  for (int y=0; y<runs; y++)
  {
      // receive this simulation run's results
      std::vector< std::pair<double,double> > my_sample 
        = sample(0, annual_payment, average_yield/100., yield_sigma/100., number_of_years);
      
      result->Fill(
        my_sample.back().first * my_sample.back().second
      );
  }
  
  // fit parameters
  gauss_expo->SetParameters(runs/50., result->GetMean()*0.85, result->GetStdDev()/5., 0.0005);
  result->Fit("gauss_expo", "ML"); // add "ML" for Minuit-improved log-likelihood

	gStyle->SetOptStat(1101);
	gStyle->SetOptFit(01111);

  TCanvas *c1 = new TCanvas("c1","result",200,10,700,500);
  result->Draw();
  gauss_expo->Draw("same");
  c1->Update();
  
}
