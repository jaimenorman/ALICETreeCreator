#include <Riostream.h>
#include <TFile.h>
#include <AliRDHFCutsD0toKpi.h>
#include <AliRDHFCutsDstoKKpi.h>
#include <AliRDHFCutsDplustoKpipi.h>
#include <AliRDHFCutsBPlustoD0Pi.h>
#include <TClonesArray.h>
#include <TParameter.h>

#include "makeInputCutsD0toKpi.C"
#include "makeInputCutsDstoKKpi.C"
#include "makeInputCutsDplustoKpipi.C"
#include "makeInputCutsBplustoD0pi.C"
#include "makeInputCutsLctopKpi.C"

Float_t minCent=0.;
Float_t maxCent=100.;


void makeCutsTreeCreator()
{
    Printf("D0 filtering cuts");
    AliRDHFCutsD0toKpi  *looseCutsD0toKpi    = makeInputCutsD0toKpi(0,"D0toKpiFilteringCuts",minCent,maxCent);
    Printf("\n\n");
    Printf("D0 analysis cuts");
    AliRDHFCutsD0toKpi  *analysisCutsD0toKpi = makeInputCutsD0toKpi(1,"D0toKpiAnalysisCuts",minCent,maxCent);
    Printf("\n\n");
    Printf("*************************************************************");
    Printf("Ds filtering cuts");
    AliRDHFCutsDstoKKpi  *looseCutsDstoKKpi    = makeInputCutsDstoKKpi(0,"DstoKKpiFilteringCuts",minCent,maxCent);
    Printf("\n\n");
    Printf("Ds analysis cuts");
    AliRDHFCutsDstoKKpi  *analysisCutsDstoKKpi = makeInputCutsDstoKKpi(1,"DstoKKpiAnalysisCuts",minCent,maxCent);
    Printf("\n\n");
    Printf("*************************************************************");
    Printf("Dplus filtering cuts");
    AliRDHFCutsDplustoKpipi  *looseCutsDplustoKpipi    = makeInputCutsDplustoKpipi(0,"DplustoKpipiFilteringCuts",minCent,maxCent);
    Printf("\n\n");
    Printf("Dplus analysis cuts");
    AliRDHFCutsDplustoKpipi  *analysisCutsDplustoKpipi = makeInputCutsDplustoKpipi(1,"DplustoKpipiAnalysisCuts",minCent,maxCent);
    Printf("\n\n");
    Printf("*************************************************************");
    Printf("Bplus filtering cuts");
    AliRDHFCutsBPlustoD0Pi  *looseCutsBplustoD0pi    = makeInputCutsBplustoD0pi(0,"BplustoD0piFilteringCuts",minCent,maxCent);
    Printf("\n\n");
    Printf("Bplus analysis cuts");
    AliRDHFCutsBPlustoD0Pi  *analysisCutsBplustoD0pi = makeInputCutsBplustoD0pi(1,"BplustoD0piAnalysisCuts",minCent,maxCent);
    Printf("*************************************************************");
    Printf("Lc filtering cuts");
    AliRDHFCutsLctopKpi  *looseCutsLctopKpi    = makeInputCutsLctopKpi(0,"LctopKpiFilteringCuts",minCent,maxCent);
    Printf("\n\n");
    Printf("Lc analysis cuts");
    AliRDHFCutsLctopKpi  *analysisCutsLctopKpi = makeInputCutsLctopKpi(1,"LctopKpiAnalysisCuts",minCent,maxCent);

    TFile* fout=new TFile("D0DsDplusLcBplusCuts.root","recreate");
    fout->cd();
    looseCutsD0toKpi->Write();
    analysisCutsD0toKpi->Write();
    looseCutsDstoKKpi->Write();
    analysisCutsDstoKKpi->Write();
    looseCutsDplustoKpipi->Write();
    analysisCutsDplustoKpipi->Write();
    looseCutsBplustoD0pi->Write();
    analysisCutsBplustoD0pi->Write();
    looseCutsLctopKpi->Write();
    analysisCutsLctopKpi->Write();
    fout->Close();
    
}
