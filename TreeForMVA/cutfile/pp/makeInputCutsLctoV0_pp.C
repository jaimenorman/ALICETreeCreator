#include <Riostream.h>
#include <TFile.h>
#include <AliRDHFCutsLctoV0.h>
#include <TClonesArray.h>
#include <TParameter.h>

/*
 whichCuts=0, nameCuts="LctoV0FilteringCuts"
 whichCuts=1, nameCuts="LctoV0AnalysisCuts"
 */

const Int_t nvars=21;
//        Lc inv. mass if K0S [GeV/c2]
//        Lc inv. mass if Lambda [GeV/c2]
//        K0S inv. mass [GeV/c2]
//        Lambda/LambdaBar inv. mass[GeV/c2]
//        pT min bachelor track [GeV/c]
//        pT min V0-positive track [GeV/c]
//        pT min V0-negative track [GeV/c]
//        dca cascade (prong-to-prong) cut [cm]
//        dca V0 (prong-to-prong) cut [number of sigmas]
//        V0 cosPA min wrt PV
//        d0 max bachelor wrt PV [cm]
//        d0 max V0 wrt PV [cm]
//        mass K0S veto [GeV/c2]
//        mass Lambda/LambdaBar veto [GeV/c2]
//        mass Gamma veto [GeV/c2]
//        pT min V0 track [GeV/c]
//        Max Proton emission angle in Lc CMS
//        Min Proton emission angle in Lc CMS
//        Resigned d0
//        V0 qT/|alpha|
//        V0 type

AliRDHFCutsLctoV0 *makeInputCutsLctoV0(Int_t whichCuts=0, TString nameCuts="LctoV0FilteringCuts", Float_t minc=0.,Float_t maxc=20.)
{
  
  AliRDHFCutsLctoV0* cutsLctoV0=new AliRDHFCutsLctoV0();
  cutsLctoV0->SetName(nameCuts.Data());
  cutsLctoV0->SetTitle(nameCuts.Data());
  
  
  if(whichCuts==0){
    
    AliESDtrackCuts *esdTrackCuts = new AliESDtrackCuts("AliESDtrackCuts","default");
    esdTrackCuts->SetRequireTPCRefit(kTRUE);
    esdTrackCuts->SetRequireITSRefit(kTRUE);
    esdTrackCuts->SetMinNClustersTPC(50);
    esdTrackCuts->SetClusterRequirementITS(AliESDtrackCuts::kSPD,
                                           AliESDtrackCuts::kAny);
    esdTrackCuts->SetMaxDCAToVertexXY(1.e6);
    esdTrackCuts->SetMinDCAToVertexXY(0.);
    esdTrackCuts->SetPtRange(0.3,1.e10);
    esdTrackCuts->SetEtaRange(-0.9,+0.9);
    cutsLctoV0->AddTrackCuts(esdTrackCuts);
    
    AliESDtrackCuts *esdTrackCutsV0daughters = new AliESDtrackCuts("AliESDtrackCutsForV0D","default cuts for V0 daughters");
    esdTrackCutsV0daughters->SetRequireTPCRefit(kTRUE);
    esdTrackCutsV0daughters->SetMinNClustersTPC(30);
    esdTrackCutsV0daughters->SetRequireITSRefit(kFALSE);
    esdTrackCutsV0daughters->SetMinDCAToVertexXY(0.);
    esdTrackCutsV0daughters->SetPtRange(0.05,1.e10);
    esdTrackCutsV0daughters->SetEtaRange(-1.1,+1.1);
    esdTrackCutsV0daughters->SetAcceptKinkDaughters(kTRUE);
    esdTrackCutsV0daughters->SetRequireSigmaToVertex(kFALSE);
    cutsLctoV0->AddTrackCutsV0daughters(esdTrackCutsV0daughters);
    
    const Int_t nptbins=2;
    Float_t* ptbins;
    ptbins=new Float_t[nptbins+1];
    ptbins[0]=0.;
    ptbins[1]=5.;
    ptbins[2]=999.;
    cutsLctoV0->SetPtBins(nptbins+1,ptbins);
    Float_t cuts[nptbins][nvars]={
      1.0,1.0,0.05,0.05,0.0,0.0,0.0,1000.,1000.,0.99,3.,1000.,0.,0.,0.,0.,9999.,-9999.,-9999.,-9999.,0.0,
      1.0,1.0,0.05,0.05,0.0,0.0,0.0,1000.,1000.,0.99,3.,1000.,0.,0.,0.,0.,9999.,-9999.,-9999.,-9999.,0.0};
    Float_t** prodcutsval;
    prodcutsval=new Float_t*[nvars];
    for(Int_t ic=0;ic<nvars;ic++){prodcutsval[ic]=new Float_t[nptbins];}
    for(Int_t ipt=0; ipt<nptbins; ipt++){
      for(Int_t ic=0; ic<nvars; ic++){
        prodcutsval[ic][ipt]=cuts[ipt][ic];
      }
    }
    
    cutsLctoV0->SetUseTrackSelectionWithFilterBits(kFALSE);
    cutsLctoV0->SetMinPtCandidate(1.);
    cutsLctoV0->SetCuts(nvars,nptbins,prodcutsval);
    
    
    
    
  }
  else if(whichCuts==1){
    
    //single track cuts
    AliESDtrackCuts* esdTrackCuts=new AliESDtrackCuts();
    esdTrackCuts->SetRequireTPCRefit(kTRUE);
    esdTrackCuts->SetRequireITSRefit(kTRUE);
    esdTrackCuts->SetMinNClustersTPC(70);
    esdTrackCuts->SetClusterRequirementITS(AliESDtrackCuts::kSPD,
                                           AliESDtrackCuts::kAny);
    esdTrackCuts->SetMaxDCAToVertexXY(1.e6);
    esdTrackCuts->SetMinDCAToVertexXY(0.);
    esdTrackCuts->SetMinDCAToVertexZ(0.);
    esdTrackCuts->SetPtRange(0.3,1.e10);
    esdTrackCuts->SetEtaRange(-0.8,+0.8);
    esdTrackCuts->SetAcceptKinkDaughters(kFALSE);
    cutsLctoV0->AddTrackCuts(esdTrackCuts);
    
    AliESDtrackCuts *esdTrackCutsV0daughters = new AliESDtrackCuts("AliESDtrackCutsForV0D","default cuts for V0 daughters");
    esdTrackCutsV0daughters->SetRequireTPCRefit(kTRUE);
    esdTrackCutsV0daughters->SetMinNClustersTPC(70);
    esdTrackCutsV0daughters->SetRequireITSRefit(kFALSE);
    esdTrackCutsV0daughters->SetMinDCAToVertexXY(0.);
    esdTrackCutsV0daughters->SetMinDCAToVertexZ(0.);
    esdTrackCutsV0daughters->SetPtRange(0.1,1.e10);
    esdTrackCutsV0daughters->SetEtaRange(-0.8,+0.8);
    esdTrackCutsV0daughters->SetRequireSigmaToVertex(kFALSE);
    
    cutsLctoV0->SetUsePhysicsSelection(kTRUE);
    cutsLctoV0->SetKinkRejection(!esdTrackCuts->GetAcceptKinkDaughters());
    cutsLctoV0->AddTrackCuts(esdTrackCuts);
    cutsLctoV0->AddTrackCutsV0daughters(esdTrackCutsV0daughters);
    cutsLctoV0->SetUseTrackSelectionWithFilterBits(kFALSE);
    cutsLctoV0->SetGetNTPCSigmaCutForPreselection(3.0);
    cutsLctoV0->SetHighPtCut(3.0);
    cutsLctoV0->SetLowPtCut(1.0);
    cutsLctoV0->SetPidSelectionFlag(4);
    
    const Int_t nptbins=9;
    Float_t* ptbins;
    ptbins=new Float_t[nptbins+1];
    ptbins[0]=1.;
    ptbins[1]=2.;
    ptbins[2]=3.;
    ptbins[3]=4.;
    ptbins[4]=5.;
    ptbins[5]=6.;
    ptbins[6]=8.;
    ptbins[7]=12.;
    ptbins[8]=16.;
    ptbins[9]=24.;
    cutsLctoV0->SetPtBins(nptbins+1,ptbins);
    
    Float_t cuts[nptbins][nvars]={
      0.25, 1., 0.005,   0.05, 0.6, 0.2, 0.2, 1000., 1.5, 0.99, 0.05, 0.05, 0., 0.005, 0.1, 0.5, 9999, -9999, -9999, -9999, 0.,
      0.25, 1., 0.005,   0.05, 0.6, 0.2, 0.2, 1000., 1.5, 0.99, 0.05, 0.05, 0., 0.005, 0.1, 0.5, 9999, -9999, -9999, -9999, 0.,
      0.25, 1., 0.00812, 0.05, 0.6, 0.2, 0.2, 1000., 1.5, 0.99, 0.05, 0.05, 0., 0.005, 0.1, 0.6, 9999, -9999, -9999, -9999, 0.,
      0.25, 1., 0.00858, 0.05, 0.7, 0.2, 0.2, 1000., 1.5, 0.99, 0.1,  0.09, 0., 0.005, 0.3, 0.7, 9999, -9999, -9999, -9999, 0.,
      0.25, 1., 0.009,   0.05, 0.7, 0.2, 0.2, 1000., 1.5, 0.99, 0.1,  0.09, 0., 0.005, 0.3, 1.0, 9999, -9999, -9999, -9999, 0.,
      0.25, 1., 0.01,    0.05, 0.9, 0.2, 0.2, 1000., 1.5, 0.99, 0.1,  999., 0., 0.005, 0.3, 1.1, 9999, -9999, -9999, -9999, 0.,
      0.25, 1., 0.01,    0.05, 1.1, 0.3, 0.3, 1000., 1.5, 0.99, 0.1,  999., 0., 0.005, 0.3, 1.2, 9999, -9999, -9999, -9999, 0.,
      0.25, 1., 0.01,    0.05, 1.1, 0.3, 0.3, 1000., 1.5, 0.99, 0.1,  999., 0., 0.005, 0.3, 1.2, 9999, -9999, -9999, -9999, 0.,
      0.25, 1., 0.01,    0.05, 1.1, 0.3, 0.3, 1000., 1.5, 0.99, 0.1,  999., 0., 0.005, 0.3, 1.2, 9999, -9999, -9999, -9999, 0.
    };
    Float_t** prodcutsval;
    prodcutsval=new Float_t*[nvars];
    for(Int_t ic=0;ic<nvars;ic++){prodcutsval[ic]=new Float_t[nptbins];}
    for(Int_t ipt=0; ipt<nptbins; ipt++){
      for(Int_t ic=0; ic<nvars; ic++){
        prodcutsval[ic][ipt]=cuts[ipt][ic];
      }
    }
    cutsLctoV0->SetCuts(nvars,nptbins,prodcutsval);
    
    //pid settings
    //1. bachelor: default one
    AliAODPidHF* pidObjBachelor = new AliAODPidHF();
    Double_t sigmasBac[5]={3.,3.,3.,3.,3.}; // 0, 1(A), 2(A) -> TPC; 3 -> TOF; 4 -> ITS
    pidObjBachelor->SetSigma(sigmasBac);
    pidObjBachelor->SetAsym(kFALSE);
    pidObjBachelor->SetMatch(1);
    pidObjBachelor->SetTPC(kTRUE);
    pidObjBachelor->SetTOF(kTRUE);
    pidObjBachelor->SetTOFdecide(kFALSE);
    
    cutsLctoV0->SetPidHF(pidObjBachelor);
    Bool_t pidflag=kTRUE;
    cutsLctoV0->SetUsePID(pidflag);
    
  }
  
  //event selection
  cutsLctoV0->SetUsePhysicsSelection(kTRUE);
  cutsLctoV0->SetTriggerClass("");
  cutsLctoV0->SetTriggerMask(AliVEvent::kINT7);
  cutsLctoV0->SetOptPileup(AliRDHFCuts::kRejectMVPileupEvent);
  cutsLctoV0->ConfigurePileupCuts(5,0.8);
  cutsLctoV0->SetMaxVtxZ(10.);
  cutsLctoV0->SetCutOnzVertexSPD(3);
  cutsLctoV0->SetMinVtxContr(1);
  
  cout<<"This is the object I'm going to save:"<<endl;
  cutsLctoV0->SetName(nameCuts.Data());
  cutsLctoV0->SetTitle(nameCuts.Data());
  cutsLctoV0->PrintAll();
  
  return cutsLctoV0;
  
}


