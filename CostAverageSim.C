#include <iostream>
#include <cmath>

#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
//#include "TApplication.h"
#include "TRandom.h"
#include "TRandom2.h"
#include "TMath.h"
#include "TH1D.h"
#include "TF1.h"
#include "TCanvas.h"

using namespace std;

TRandom *rng = new TRandom2();
TH1D *yield_distr = new TH1D("yield_distr", "yearly yields", 800, 0.6, 1.4);

// one simulation run
// return value: <number, value> for each year
std::vector< std::pair<double,double> > sample(
  double start_value,
  double add_monthly,
  double avg_yield,
  double yield_sigma,
  int years)
{
  double current_price = 100.; // without loss of generality
  // number of shares (or whatever)
  double current_amount = (start_value+add_monthly)/current_price;; 
  std::vector< std::pair<double,double> > re_sample;
  double y=1;
  
  for (int i=0; i<12*years; i++)
  {
    double this_month_yield = rng->Gaus(avg_yield, yield_sigma-1.);
    
    if(i%12==0)
    {
      yield_distr->Fill(y);
      y = 1;
    }
    y *= this_month_yield;
    
    current_price = current_price * this_month_yield;
    re_sample.push_back(
      std::make_pair(current_amount, current_price)
    );
    // value after the month (that's why current_amount will be calulated hereafter) 
    
    current_amount = add_monthly/current_price;
    
  }
  
  return re_sample;
}

double integrated_value(std::vector< std::pair<double,double> > v)
{
  double n = 0;
  for (auto& i:v) n += i.first; // sum up all the shares
  return n*v.back().second; // number of shares × value of shares at the end
}

// main ROOT function
void CostAverageSim()
{
//----------------------------------------------------------------------------//
  double monthly_payment = 100;   // currency
  double average_yield = 5;       // percent points
  double yield_sigma   = 15;     // percent points
  int number_of_years = 30;       // duration in years
  
//----------------------------------------------------------------------------//
  int runs = 250000;                // number of simulation runs
  double xmin = 0.;
  double xmax = 150000.;
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
  
  const double mon_yield = TMath::Power(1.+(average_yield/100.), 1./12.);
  const double mon_sigma = TMath::Power(1.+(yield_sigma/100.), 1./12.);
  
  // main loop
  for (int y=0; y<runs; y++)
  {
      // receive this simulation run's results
      std::vector< std::pair<double,double> > my_sample 
        = sample(0, monthly_payment, mon_yield, mon_sigma, number_of_years);
      
      result->Fill( integrated_value(my_sample) );
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
