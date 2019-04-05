TRandom *rng = new TRandom2();

// one simulation run
std::vector<double> sample(
  double start_value,
  double add_annual,
  double avg_yield,
  double yield_sigma,
  int years)
{
  double this_value = start_value;
  std::vector<double> re_sample;
  
  for (int i=0; i<years; i++)
  {
    double this_year_yield = rng->Gaus(avg_yield, yield_sigma);
    
    this_value = (this_value * (1+this_year_yield)) + add_annual;
    re_sample.push_back(this_value);
  }
  
  return re_sample;
}

// main ROOT function
void TotalReturnSim()
{
//----------------------------------------------------------------------------//
  double annual_payment = 100;    // currency
  double average_yield = 6;       // percent points
  double yield_sigma   = 1.5;     // percent points
  int number_of_years = 30;       // duration in years
  
//----------------------------------------------------------------------------//
  int runs = 5000;                // number of simulation runs
  TH1D* result 
    = new TH1D("result", "distribution of final amount", 500, 0., 10000.);
  result->GetXaxis()->SetTitle("final amount");
  result->GetYaxis()->SetTitle("prevalence");
  
  // main loop
  for (int y=0; y<runs; y++)
  {
      std::vector<double> my_sample 
        = sample(0, annual_payment, average_yield/100., yield_sigma/100., number_of_years);
      result->Fill(my_sample.back());
  }
  
  TCanvas *c1 = new TCanvas("c1","result",200,10,700,500);
  result->Draw();
  c1->Update();
  
}
