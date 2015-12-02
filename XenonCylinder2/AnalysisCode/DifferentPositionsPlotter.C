{

TChain * chain = new TChain("outTree");
chain->Add("../bin/BaccOut*Red*");

TFile * outFile = new TFile("DifferentPositions_OutputPlots.root","RECREATE");

// Create total spectrum
printf("Drawing total spectrum...\n");
chain->Draw("fTotEDep>>h_totalSpectrum(300,0.,100.)","fTotEDep<100.");
h_totalSpectrum->SetName("h_totalSpectrum");

// Create XY plot
printf("Drawing XY plot...\n");
chain->Draw("fPositionX_cm:fPositionY_cm>>h_XY(200,-42.,42.,200,-42.,42.)","fTotEDep < 100.","colz");
h_XY->SetName("h_XY");

// Create ZY plot
printf("Drawing ZY plot...\n");
chain->Draw("fPositionZ_cm:fPositionY_cm>>h_ZY(200,-40.,40.,200,-40.,40.)","fTotEDep < 100.","colz");
h_ZY->SetName("h_ZY");

// Create spectrum at 0 degrees
printf("Drawing spectrum at 0 degrees...\n");
chain->Draw("fTotEDep>>h_0deg(100,0.,90.)",
             "fTotEDep < 90. && abs(fPositionZ_cm) < 3. && abs(fPositionY_cm-25.)<3. && abs(fPositionX_cm)<3.");
h_0deg->SetName("h_0deg");
h_0deg->SetLineColor(2);
h_0deg->SetLineWidth(2);
h_0deg->SetTitle("Spectra from 6x6cm cubes at 0, 45, and 90 degrees (r = 25cm)");
h_0deg->GetXaxis()->SetTitle("Energy deposited (keV)");



// Create spectrum at 45 degrees
printf("Drawing spectrum at 45 degrees...\n");
chain->Draw("fTotEDep>>h_45deg(100,0.,90.)",
             "fTotEDep < 90. && abs(fPositionZ_cm) < 3. && abs(fPositionY_cm-17.7)<3. && (abs(fPositionX_cm-17.7)<3. || abs(fPositionX_cm+17.7)<3.)");
h_45deg->SetName("h_45deg");
h_45deg->SetLineColor(4);
h_45deg->SetLineWidth(2);


// Create spectrum at 90 degrees
printf("Drawing spectrum at 90 degrees...\n");
chain->Draw("fTotEDep>>h_90deg(100,0.,90.)",
             "fTotEDep < 90. && abs(fPositionZ_cm) < 3. && abs(fPositionY_cm)<3. && (abs(fPositionX_cm-25.)<3. || abs(fPositionX_cm+25.)<3.)");
h_90deg->SetName("h_90deg");
h_90deg->SetLineColor(8);
h_90deg->SetLineWidth(2);

TCanvas * c1 = new TCanvas("c1","c1");
h_0deg->Draw();
h_45deg->Draw("same");
h_90deg->Draw("same");

printf("Write and close file...\n\n");
outFile->Write();
outFile->Close();


}
