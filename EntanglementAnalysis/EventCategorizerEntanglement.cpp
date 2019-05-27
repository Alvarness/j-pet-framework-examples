/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @file EventCategorizerEntanglement.cpp
 */

#include "EventCategorizerTools.h"
#include <JPetOptionsTools/JPetOptionsTools.h>
#include "EventCategorizerEntanglement.h"
#include <JPetWriter/JPetWriter.h>
#include <TMath.h>
#include <TVector3.h>
#include <iostream>

using namespace jpet_options_tools;

using namespace std;

double elipse(double x, double y, double X0, double Y0, double a, double b, double theta){
  return pow(((x - X0)*cos(theta) + (y - Y0)*sin(theta))/a ,2) + pow(((x - X0)*sin(theta) - (y - Y0)*cos(theta))/b ,2);

}

double elipse_test(double x, double y, double X0, double Y0, double a, double b){
  return pow((x - X0),2)/pow(a,2) + pow((y - Y0),2)/pow(b,2);
}

EventCategorizerEntanglement::EventCategorizerEntanglement(const char* name): JPetUserTask(name) {}

bool EventCategorizerEntanglement::init()
{
  INFO("Physics streaming started.");

  fOutputEvents = new JPetTimeWindow("JPetEvent");

  if (isOptionSet(fParams.getOptions(), kScatterTOFTimeDiffParamKey)) {
    fScatterTOFTimeDiff = getOptionAsFloat(fParams.getOptions(), kScatterTOFTimeDiffParamKey);
  } else {
    WARNING(Form("No value of the %s parameter provided by the user. Using default value of %lf.", kScatterTOFTimeDiffParamKey.c_str(), fScatterTOFTimeDiff));
  }
  if (isOptionSet(fParams.getOptions(), kMinAnnihilationParamKey)) {
    fMinAnnihilationTOT = getOptionAsFloat(fParams.getOptions(), kMinAnnihilationParamKey);
  } else {
    WARNING(Form("No value of the %s parameter provided by the user. Using default value of %lf.", kMinAnnihilationParamKey.c_str(), fMinAnnihilationTOT));
  }
  if (isOptionSet(fParams.getOptions(), kMaxAnnihilationParamKey)) {
    fMaxAnnihilationTOT = getOptionAsFloat(fParams.getOptions(), kMaxAnnihilationParamKey);
  } else {
    WARNING(Form("No value of the %s parameter provided by the user. Using default value of %lf.", kMaxAnnihilationParamKey.c_str(), fMaxAnnihilationTOT));
  }
  if (isOptionSet(fParams.getOptions(), kMinDeexcitationParamKey)) {
    fMinDeexcitationTOT = getOptionAsFloat(fParams.getOptions(), kMinDeexcitationParamKey);
  } else {
    WARNING(Form("No value of the %s parameter provided by the user. Using default value of %lf.", kMinDeexcitationParamKey.c_str(), fMinDeexcitationTOT));
  }
  if (isOptionSet(fParams.getOptions(), kMaxDeexcitationParamKey)) {
    fMaxDeexcitationTOT = getOptionAsFloat(fParams.getOptions(), kMaxDeexcitationParamKey);
  } else {
    WARNING(Form("No value of the %s parameter provided by the user. Using default value of %lf.", kMaxDeexcitationParamKey.c_str(), fMaxDeexcitationTOT));
  }
  if (isOptionSet(fParams.getOptions(), kMaxZPosParamKey)) {
    fMaxZPos = getOptionAsFloat(fParams.getOptions(), kMaxZPosParamKey);
  } else {
    WARNING(Form("No value of the %s parameter provided by the user. Using default value of %lf.", kMaxZPosParamKey.c_str(), fMaxZPos));
  }
  if (isOptionSet(fParams.getOptions(), kMaxDistOfDecayPlaneFromCenterParamKey)) {
    fMaxDistOfDecayPlaneFromCenter = getOptionAsFloat(fParams.getOptions(), kMaxDistOfDecayPlaneFromCenterParamKey);
  } else {
    WARNING(Form("No value of the %s parameter provided by the user. Using default value of %lf.", kMaxDistOfDecayPlaneFromCenterParamKey.c_str(), fMaxDistOfDecayPlaneFromCenter));
  }
  if (isOptionSet(fParams.getOptions(), kMaxTimeDiffParamKey)) {
    fMaxTimeDiff = getOptionAsFloat(fParams.getOptions(), kMaxTimeDiffParamKey);
  } else {
    WARNING(Form("No value of the %s parameter provided by the user. Using default value of %lf.", kMaxTimeDiffParamKey.c_str(), fMaxTimeDiff));
  }
  if (isOptionSet(fParams.getOptions(), kBackToBackAngleWindowParamKey)) {
    fBackToBackAngleWindow = getOptionAsFloat(fParams.getOptions(), kBackToBackAngleWindowParamKey);
  } else {
    WARNING(Form("No value of the %s parameter provided by the user. Using default value of %lf.", kBackToBackAngleWindowParamKey.c_str(), fBackToBackAngleWindow));
  }
  if (isOptionSet(fParams.getOptions(), kDecayInto3MinAngleParamKey)) {
    fDecayInto3MinAngle = getOptionAsFloat(fParams.getOptions(), kDecayInto3MinAngleParamKey);
  } else {
    WARNING(Form("No value of the %s parameter provided by the user. Using default value of %lf.", kDecayInto3MinAngleParamKey.c_str(), fDecayInto3MinAngle));
  }
  if (isOptionSet(fParams.getOptions(), kMaxXYAnnihilationPointDistanceFromCenter)) {
    fMaxXYAnnihilationPointDistanceFromCenter = getOptionAsFloat(fParams.getOptions(), kMaxXYAnnihilationPointDistanceFromCenter);
  } else {
    WARNING(Form("No value of the %s parameter provided by the user. Using default value of %lf.", kMaxXYAnnihilationPointDistanceFromCenter.c_str(), fMaxXYAnnihilationPointDistanceFromCenter));
  }

  if (fSaveControlHistos) {
    getStatistics().createHistogram(
      new TH1F("Z_pos_all", "Hit Z position", 1001, -50.05, 50.05)
    );
    getStatistics().getHisto1D("Z_pos_all")->SetXTitle("Hit Z position [cm]");
    getStatistics().getHisto1D("Z_pos_all")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("AllHitTOT", "TOT of all Hits", 200, 0.0, 100.0)
    );
    getStatistics().getHisto1D("AllHitTOT")->SetXTitle("TOT [ns]");
    getStatistics().getHisto1D("AllHitTOT")->SetYTitle("Number of hits");

    getStatistics().createHistogram(
      new TH1F("AnnihHitsNumber", "Number of Annihilation Hits in Event", 50, -0.5, 49.5)
    );
    getStatistics().getHisto1D("AnnihHitsNumber")->SetXTitle("Number of Annihilation Hits in a Event");
    getStatistics().getHisto1D("AnnihHitsNumber")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("DeexHitsNumber", "Number of Deexcitation Hits in Event", 50, -0.5, 49.5)
    );
    getStatistics().getHisto1D("DeexHitsNumber")->SetXTitle("Number of Deexcitation Hits in Event");
    getStatistics().getHisto1D("DeexHitsNumber")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("2Gamma_TimeDiff", "2 Gamma Hits Time Difference", 1000, 0.0, 10.0)
    );
    getStatistics().getHisto1D("2Gamma_TimeDiff")->SetXTitle("Hits time difference [ns]");
    getStatistics().getHisto1D("2Gamma_TimeDiff")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("2Gamma_TimeDiff_TOFcorrected", "2 Gamma Hits Time Difference", 1000, 0.0, 10.0)
    );
    getStatistics().getHisto1D("2Gamma_TimeDiff_TOFcorrected")->SetXTitle("Hits time difference [ns]");
    getStatistics().getHisto1D("2Gamma_TimeDiff_TOFcorrected")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("2Gamma_ThetaDiff", "2 Gamma Hits angles difference in 2D", 3600, -0.5, 359.5)
    );
    getStatistics().getHisto1D("2Gamma_ThetaDiff")->SetXTitle("Hits theta diff [deg]");
    getStatistics().getHisto1D("2Gamma_ThetaDiff")->SetYTitle("Counts");

    getStatistics().createHistogram(
     new TH1F("2Gamma_ThetaDiff2DAcos", "2 Gamma Hits angles difference in 2D acos", 3600, 0, 190)
    );
    getStatistics().getHisto1D("2Gamma_ThetaDiff2DAcos")->SetXTitle("Hits theta diff [deg]");
    getStatistics().getHisto1D("2Gamma_ThetaDiff2DAcos")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("2Gamma_ThetaDiff3DAcos", "2 Gamma Hits angles difference in 3D", 1900, 0, 190)
    );
    getStatistics().getHisto1D("2Gamma_ThetaDiff3DAcos")->SetXTitle("Hits theta diff [deg]");
    getStatistics().getHisto1D("2Gamma_ThetaDiff3DAcos")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("2Gamma_ThetaDiff3DAcos_timeDiffCut", "2 Gamma Hits angles", 1900, 0, 190)
    );
    getStatistics().getHisto1D("2Gamma_ThetaDiff3DAcos_timeDiffCut")->SetXTitle("Hits theta diff [deg]");
    getStatistics().getHisto1D("2Gamma_ThetaDiff3DAcos_timeDiffCut")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH2F("2Gamma_XY", "Reconstructed XY position of annihilation point", 220, -54.5, 54.5, 220, -54.5, 54.5)
    );
    getStatistics().getHisto2D("2Gamma_XY")->SetXTitle("Annihilation point X [cm]");
    getStatistics().getHisto2D("2Gamma_XY")->SetYTitle("Annihilation point Y [cm]");

    getStatistics().createHistogram(
      new TH2F("2Gamma_XY_cut", "Reconstructed XY position of annihilation point", 11+20*fMaxXYAnnihilationPointDistanceFromCenter, -1.1-fMaxXYAnnihilationPointDistanceFromCenter, 1.1+fMaxXYAnnihilationPointDistanceFromCenter,
                11+20*fMaxXYAnnihilationPointDistanceFromCenter, -1.1-fMaxXYAnnihilationPointDistanceFromCenter, 1.1+fMaxXYAnnihilationPointDistanceFromCenter)
    );
    getStatistics().getHisto2D("2Gamma_XY_cut")->SetXTitle("Annihilation point X [cm]");
    getStatistics().getHisto2D("2Gamma_XY_cut")->SetYTitle("Annihilation point Y [cm]");

    getStatistics().createHistogram(
      new TH1F("2Gamma_z_pos", "Annihilation point Z position", 601, -30.05, 30.05)
    );
    getStatistics().getHisto1D("2Gamma_z_pos")->SetXTitle("Annihilation point Z position [cm]");
    getStatistics().getHisto1D("2Gamma_z_pos")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("2Gamma_ThetaDiff3DAcos_Zcut", "2 Gamma Hits angles", 250, 160, 185)
    );
    getStatistics().getHisto1D("2Gamma_ThetaDiff3DAcos_Zcut")->SetXTitle("Hits theta diff [deg]");
    getStatistics().getHisto1D("2Gamma_ThetaDiff3DAcos_Zcut")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("BTBhits", "Number of back to back Hits in Event", 50, -0.5, 49.5)
    );
    getStatistics().getHisto1D("BTBhits")->SetXTitle("Number of Annihilation Hits in a Event");
    getStatistics().getHisto1D("BTBhits")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH2F("BTBhitsVsAnnihilation", "Number of back to back Hits in Event vs annihilation hits", 50, -0.5, 49.5, 50, -0.5, 49.5)
    );
    getStatistics().getHisto2D("BTBhitsVsAnnihilation")->SetXTitle("Number of back to back Hits in a Event");
    getStatistics().getHisto2D("BTBhitsVsAnnihilation")->SetYTitle("Number of Annihilation Hits in a Event");

    getStatistics().createHistogram(
      new TH2F("DeltaVsDelta", "#Delta_{1,i} Vs #Delta_{2,i}", 1200, -6, 6, 1200, -6, 6)
    );
    getStatistics().getHisto2D("DeltaVsDelta")->SetXTitle("#Delta_{1,i} [ns]");
    getStatistics().getHisto2D("DeltaVsDelta")->SetYTitle("#Delta_{2,i} [ns]");

    getStatistics().createHistogram(
      new TH1F("ComptonAnglesBig", "Compton scattering angles", 1800, 0.0, 180)
    );
    getStatistics().getHisto1D("ComptonAnglesBig")->SetXTitle("#varphi [deg]");
    getStatistics().getHisto1D("ComptonAnglesBig")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("ComptonAnglesSmall", "Compton scattering angles", 1800, 0.0, 180)
    );
    getStatistics().getHisto1D("ComptonAnglesSmall")->SetXTitle("#varphi [deg]");
    getStatistics().getHisto1D("ComptonAnglesSmall")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("PhiAngleBig", "Angle between scattering planes", 1800, 0.0, 180)
    );
    getStatistics().getHisto1D("PhiAngleBig")->SetXTitle("#varphi [deg]");
    getStatistics().getHisto1D("PhiAngleBig")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("PhiAngleR10Big", "Angle between scattering planes around center (R < 10#circ)", 1800, 0.0, 180)
    );
    getStatistics().getHisto1D("PhiAngleR10Big")->SetXTitle("#varphi [deg]");
    getStatistics().getHisto1D("PhiAngleR10Big")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("PhiAngleR15Big", "Angle between scattering planes around center (R < 15#circ)", 1800, 0.0, 180)
    );
    getStatistics().getHisto1D("PhiAngleR15Big")->SetXTitle("#varphi [deg]");
    getStatistics().getHisto1D("PhiAngleR15Big")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("PhiAngleR20Big", "Angle between scattering planes around center (R < 20#circ)", 1800, 0.0, 180)
    );
    getStatistics().getHisto1D("PhiAngleR20Big")->SetXTitle("#varphi [deg]");
    getStatistics().getHisto1D("PhiAngleR20Big")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("PhiAngleR30Big", "Angle between scattering planes around center (R < 30#circ)", 1800, 0.0, 180)
    );
    getStatistics().getHisto1D("PhiAngleR30Big")->SetXTitle("#varphi [deg]");
    getStatistics().getHisto1D("PhiAngleR30Big")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH2F("ThetaVsThetaBig", "ThetaVsTheta", 2001, -0.5, 200.5, 2001, -0.5, 200.5)
    );
    getStatistics().getHisto2D("ThetaVsThetaBig")->SetXTitle("First photon Compton scattering angle [deg]");
    getStatistics().getHisto2D("ThetaVsThetaBig")->SetYTitle("Second photon Compton scattering angle [deg]");

    getStatistics().createHistogram(
      new TH2F("ThetaVsThetaSmall", "ThetaVsTheta", 2001, -0.5, 200.5, 2001, -0.5, 200.5)
    );
    getStatistics().getHisto2D("ThetaVsThetaSmall")->SetXTitle("First photon Compton scattering angle [deg]");
    getStatistics().getHisto2D("ThetaVsThetaSmall")->SetYTitle("Second photon Compton scattering angle [deg]");


    getStatistics().createHistogram(
      new TH2F("2Gamma_ThetaDiff3DAcos_ZcutVsID", "2 Gamma Hits angles vs LayerIDs", 250, 160, 185, 9, 0.5, 9.5)
    );
    getStatistics().getHisto2D("2Gamma_ThetaDiff3DAcos_ZcutVsID")->SetXTitle("Hits theta diff [deg]");
    getStatistics().getHisto2D("2Gamma_ThetaDiff3DAcos_ZcutVsID")->SetYTitle("FirstHitLaterID * SecondHitLayerID");



    getStatistics().createHistogram(
      new TH2F("DeltaVsDeltaAfterCutBig", "#Delta_{1,i} Vs #Delta_{2,i} after cut", 1200, -6, 6, 1200, -6, 6)
    );
    getStatistics().getHisto2D("DeltaVsDeltaAfterCutBig")->SetXTitle("#Delta_{1,i} [ns]");
    getStatistics().getHisto2D("DeltaVsDeltaAfterCutBig")->SetYTitle("#Delta_{2,i} [ns]");

    getStatistics().createHistogram(
      new TH2F("DeltaVsDeltaAfterCutSmall", "#Delta_{1,i} Vs #Delta_{2,i} after cut", 1200, -6, 6, 1200, -6, 6)
    );
    getStatistics().getHisto2D("DeltaVsDeltaAfterCutSmall")->SetXTitle("#Delta_{1,i} [ns]");
    getStatistics().getHisto2D("DeltaVsDeltaAfterCutSmall")->SetYTitle("#Delta_{2,i} [ns]");

    getStatistics().createHistogram(
      new TH1F("PhiAngleSmall", "Angle between scattering planesSmall", 1800, 0.0, 180)
    );
    getStatistics().getHisto1D("PhiAngleSmall")->SetXTitle("#varphi [deg]");
    getStatistics().getHisto1D("PhiAngleSmall")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("PhiAngleR10Small", "Angle between scattering planes around center (R < 10#circ)Small", 1800, 0.0, 180)
    );
    getStatistics().getHisto1D("PhiAngleR10Small")->SetXTitle("#varphi [deg]");
    getStatistics().getHisto1D("PhiAngleR10Small")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("PhiAngleR15Small", "Angle between scattering planes around center (R < 15#circ)Small", 1800, 0.0, 180)
    );
    getStatistics().getHisto1D("PhiAngleR15Small")->SetXTitle("#varphi [deg]");
    getStatistics().getHisto1D("PhiAngleR15Small")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("PhiAngleR20Small", "Angle between scattering planes around center (R < 20#circ)Small", 1800, 0.0, 180)
    );
    getStatistics().getHisto1D("PhiAngleR20Small")->SetXTitle("#varphi [deg]");
    getStatistics().getHisto1D("PhiAngleR20Small")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("PhiAngleR30Small", "Angle between scattering planes around center (R < 30#circ)Small", 1800, 0.0, 180)
    );
    getStatistics().getHisto1D("PhiAngleR30Small")->SetXTitle("#varphi [deg]");
    getStatistics().getHisto1D("PhiAngleR30Small")->SetYTitle("Counts");

    // for(int first = 1; first < 4; first++){
    //   for(int second = 1; second < 4; second++){
    //     const char* histo_name = Form("DeltaVsDelta%i%i", first, second);

    //     getStatistics().createHistogram(
    //       new TH2F(histo_name, Form("#Delta_{1,i} Vs #Delta_{2,i}, Layer %i and %i", first, second), 120, -6, 6, 120, -6, 6)
    //     );
    //     getStatistics().getHisto2D(histo_name)->SetXTitle("#Delta_{1,i} [ns]");
    //     getStatistics().getHisto2D(histo_name)->SetYTitle("#Delta_{2,i} [ns]");

    //   }
    // }

    // getStatistics().createHistogram(
    //   new TH1F("DeexAnnihTimeDiff", "Deexcitation-Annihilation Hits Time Difference", 200, -200.0, 200.0)
    // );
    // getStatistics().getHisto1D("DeexAnnihTimeDiff")->SetXTitle("Time difference between deexcitation and annihilation hits [ns]");
    // getStatistics().getHisto1D("DeexAnnihTimeDiff")->SetYTitle("Counts");

    // getStatistics().createHistogram(
    //   new TH1F("2Annih_TimeDiff", "2 gamma annihilation Hits Time Difference", 200, 0.0, fMaxTimeDiff/1000.0)
    // );
    // getStatistics().getHisto1D("2Annih_TimeDiff")->SetXTitle("Time difference between 2 annihilation hits [ns]");
    // getStatistics().getHisto1D("2Annih_TimeDiff")->SetYTitle("Counts");

    // getStatistics().createHistogram(
    //   new TH1F("2Annih_ThetaDiff", "Annihilation Hits Theta Diff",
    //   (int) 1000*fBackToBackAngleWindow, 180.-fBackToBackAngleWindow, 180.+fBackToBackAngleWindow)
    // );
    // getStatistics().getHisto1D("2Annih_ThetaDiff")->SetXTitle("Annihilation hits theta diff [deg]");
    // getStatistics().getHisto1D("2Annih_ThetaDiff")->SetYTitle("Counts");


    // getStatistics().createHistogram(
    //   new TH1F("2Gamma_Z", "Reconstructed Z position of annihilation point", 220, -54.5, 54.5)
    // );
    // getStatistics().getHisto1D("2Gamma_Z")->SetXTitle("Annihilation point Z [cm]");
    // getStatistics().getHisto1D("2Gamma_Z")->SetYTitle("Counts");

    // getStatistics().createHistogram(
    //   new TH2F("3GammaThetas", "3 Gamma Thetas plot", 251, -0.5, 250.5, 201, -0.5, 200.5)
    // );
    // getStatistics().getHisto2D("3GammaThetas")->SetXTitle("Transformed thetas 1-2 [deg]");
    // getStatistics().getHisto2D("3GammaThetas")->SetYTitle("Transformed thetas 2-3 [deg]");

    // getStatistics().createHistogram(
    //   new TH1F("3GammaPlaneDist", "3 Gamma Plane Distance to Center", 200, 0.0, 50.0)
    // );
    // getStatistics().getHisto1D("3GammaPlaneDist")->SetXTitle("Distance [cm]");
    // getStatistics().getHisto1D("3GammaPlaneDist")->SetYTitle("Counts");

    // getStatistics().createHistogram(
    //   new TH1F("3GammaTimeDiff", "3 gamma last and first hit time difference", 200, 0.0, 20.0)
    // );
    // getStatistics().getHisto1D("3GammaTimeDiff")->SetXTitle("Time difference [ns]");
    // getStatistics().getHisto1D("3GammaTimeDiff")->SetYTitle("Counts");

    // getStatistics().createHistogram(
    //   new TH1F("3AnnihPlaneDist", "3 Gamma Annihilation Plane Distance to Center",
    //   100, 0.0, fMaxDistOfDecayPlaneFromCenter)
    // );
    // getStatistics().getHisto1D("3AnnihPlaneDist")->SetXTitle("Distance [cm]");
    // getStatistics().getHisto1D("3AnnihPlaneDist")->SetYTitle("Counts");

    // getStatistics().createHistogram(
    //   new TH1F("3AnnihTimeDiff", "3 gamma Annihilation last and first hit time difference", 200, 0.0, fMaxTimeDiff/1000.0)
    // );
    // getStatistics().getHisto1D("3AnnihTimeDiff")->SetXTitle("Time difference [ns]");
    // getStatistics().getHisto1D("3AnnihTimeDiff")->SetYTitle("Counts");


    // getStatistics().createHistogram(
    //   new TH1F("2AnnihDistanceFromCenter", "2AnnihDistanceFromCenter", 1001, -0.5, 500.5)
    // );
    // getStatistics().getHisto1D("2AnnihDistanceFromCenter")->SetXTitle("Annihilation hits Delta LOR [cm]");
    // getStatistics().getHisto1D("2AnnihDistanceFromCenter")->SetYTitle("Counts");





  }
  return true;
}

bool EventCategorizerEntanglement::exec()
{
  vector<JPetEvent> events;
  if (auto timeWindow = dynamic_cast<const JPetTimeWindow* const>(fEvent)) {
    uint n = timeWindow->getNumberOfEvents();
    for (uint i = 0; i < n; ++i) {
      const auto& event = dynamic_cast<const JPetEvent&>(timeWindow->operator[](i));
      vector<JPetHit> hits = event.getHits();
      JPetEvent physicEvent = physicsAnalysis(hits);
      // if (physicEvent.getHits().size()) { events.push_back(physicEvent); }
    }
  } else {
    return false;
  }
  // if (events.size()) { saveEvents(events); }
  events.clear();
  return true;
}

bool EventCategorizerEntanglement::terminate()
{
  INFO("Physics streaming ended.");
  return true;
}

void EventCategorizerEntanglement::saveEvents(const vector<JPetEvent>& events)
{
  for (const auto& event : events) {
    fOutputEvents->add<JPetEvent>(event);
  }
}

JPetEvent EventCategorizerEntanglement::physicsAnalysis(vector<JPetHit> hits)
{
  JPetEvent physicEvent;
  JPetEvent annihilationHits;
  JPetEvent deexcitationHits;

  for (unsigned i = 0; i < hits.size(); i++) {
      if (fSaveControlHistos) {
        getStatistics().getHisto1D("Z_pos_all")->Fill(hits[i].getPosZ());
      }
    if (fabs(hits[i].getPosZ()) < fMaxZPos) {
      double TOTofHit = EventCategorizerTools::calculateTOT(hits[i]);
      if (fSaveControlHistos) {
        getStatistics().getHisto1D("AllHitTOT")->Fill(TOTofHit / 1000.);
      }
      if (TOTofHit >= fMinAnnihilationTOT && TOTofHit <= fMaxAnnihilationTOT) {
        annihilationHits.addHit(hits[i]);
      }
      if (TOTofHit >= fMinDeexcitationTOT && TOTofHit <= fMaxDeexcitationTOT) {
        deexcitationHits.addHit(hits[i]);
      }
    }
  }

  if (fSaveControlHistos) {
    getStatistics().getHisto1D("AnnihHitsNumber")->Fill(annihilationHits.getHits().size());
    getStatistics().getHisto1D("DeexHitsNumber")->Fill(deexcitationHits.getHits().size());
  }


  if (annihilationHits.getHits().size() > 3) {

    JPetHit firstHit, secondHit, firstScatter, secondScatter;
    bool firstScatterSetBig = false, secondScatterSetBig = false;
    bool firstScatterSetSmall = false, secondScatterSetSmall = false;
    vector<int> hitNr;
    TVector3 detectorCenter(0.0, 0.0, 0.0);

    for (uint i = 0; i < annihilationHits.getHits().size(); i++) {
      for (uint j = i + 1; j < annihilationHits.getHits().size(); j++) {
        JPetHit firstSuspect, secondSuspect;
        if (annihilationHits.getHits().at(i).getTime() < annihilationHits.getHits().at(j).getTime()) {
          firstSuspect = annihilationHits.getHits().at(i);
          secondSuspect = annihilationHits.getHits().at(j);
        }
        else {
          firstSuspect = annihilationHits.getHits().at(j);
          secondSuspect = annihilationHits.getHits().at(i);
        }

        /*----------  Get times of interactions and times of emmission for both hits  ----------*/
        double firstInteractionTime = firstSuspect.getTime();
        double secondInteractionTime = secondSuspect.getTime();

        double firstEmmisionTime = firstSuspect.getTime() - 1000.0*firstSuspect.getPos().Mag()/kLightVelocity_cm_ns;
        double secondEmmisionTime = secondSuspect.getTime() - 1000.0*secondSuspect.getPos().Mag()/kLightVelocity_cm_ns;

        double timeDiff = fabs(firstInteractionTime - secondInteractionTime);
        double timeDiffTof = fabs(firstEmmisionTime - secondEmmisionTime);

        getStatistics().getHisto1D("2Gamma_TimeDiff")->Fill(timeDiff / 1000.0);
        getStatistics().getHisto1D("2Gamma_TimeDiff_TOFcorrected")->Fill(timeDiffTof / 1000.0);


        double thetaDiff = fabs(firstSuspect.getBarrelSlot().getTheta() - secondSuspect.getBarrelSlot().getTheta());

        TVector3 positionOfCenter(0.0, 0.0, 0.0);

        TVector3 firstXYpos(firstSuspect.getPosX(), firstSuspect.getPosY(), 0);
        TVector3 secondXYpos(secondSuspect.getPosX(), secondSuspect.getPosY(), 0);


        double thetaDiff2Dacos = TMath::RadToDeg()*firstXYpos.Angle(secondXYpos);
        double thetaDiff3Dacos = TMath::RadToDeg()*(firstSuspect.getPos() - positionOfCenter).Angle((secondSuspect.getPos() - positionOfCenter));

        getStatistics().getHisto1D("2Gamma_ThetaDiff3DAcos")->Fill(thetaDiff3Dacos);
        getStatistics().getHisto1D("2Gamma_ThetaDiff2DAcos")->Fill(thetaDiff2Dacos);
        getStatistics().getHisto1D("2Gamma_ThetaDiff")->Fill(thetaDiff);

        double minTheta = 180.0 - fBackToBackAngleWindow;
        double maxTheta = 180.0 + fBackToBackAngleWindow;



        /*----------  Cut on time difference of interaction, default value: 1ns  ----------*/
        if (timeDiffTof < fMaxTimeDiff) {

          getStatistics().getHisto1D("2Gamma_ThetaDiff3DAcos_timeDiffCut")->Fill(thetaDiff3Dacos);

          TVector3 annihilationPoint = EventCategorizerTools::calculateAnnihilationPoint(firstSuspect, secondSuspect);
          getStatistics().getHisto2D("2Gamma_XY")->Fill(annihilationPoint.X(), annihilationPoint.Y());


        /*----------  Cut on distance of annihilation point from center on XY plane, default value: 5cm  ----------*/

          if(pow(annihilationPoint.X(), 2) + pow(annihilationPoint.Y(), 2) < pow(fMaxXYAnnihilationPointDistanceFromCenter, 2)){

            getStatistics().getHisto2D("2Gamma_XY_cut")->Fill(annihilationPoint.X(), annihilationPoint.Y());
            getStatistics().getHisto1D("2Gamma_z_pos")->Fill(annihilationPoint.Z());


            if(fabs(annihilationPoint.Z()) < 4 ){

              getStatistics().getHisto1D("2Gamma_ThetaDiff3DAcos_Zcut")->Fill(thetaDiff3Dacos);
              getStatistics().getHisto2D("2Gamma_ThetaDiff3DAcos_ZcutVsID")->Fill(thetaDiff3Dacos, firstSuspect.getBarrelSlot().getLayer().getID() * secondSuspect.getBarrelSlot().getLayer().getID());

              firstHit = firstSuspect;
              secondHit = secondSuspect;
              physicEvent.addHit(firstHit);
              physicEvent.addHit(secondHit);
              hitNr.push_back(i);
              hitNr.push_back(j);
            }
          }
        }
      }
    }

    getStatistics().getHisto1D("BTBhits")->Fill(physicEvent.getHits().size()/2.0);
    getStatistics().getHisto2D("BTBhitsVsAnnihilation")->Fill(physicEvent.getHits().size()/2.0, annihilationHits.getHits().size());



    if(physicEvent.getHits().size() == 2){
      for(int i=0; i<annihilationHits.getHits().size(); i++){
        double DeltaFirst, DeltaSecond;

        DeltaFirst = fabs(EventCategorizerTools::calculateTOF(firstHit, annihilationHits.getHits().at(i))) - EventCategorizerTools::calculateScatteringTime(firstHit, annihilationHits.getHits().at(i));
        DeltaSecond = fabs(EventCategorizerTools::calculateTOF(secondHit, annihilationHits.getHits().at(i))) - EventCategorizerTools::calculateScatteringTime(secondHit, annihilationHits.getHits().at(i));


        int firstHitLayerID = firstHit.getBarrelSlot().getLayer().getID();
        int secondHitLayerID = secondHit.getBarrelSlot().getLayer().getID();
        // if(elipse(DeltaFirst/1000, DeltaSecond/1000, 0.5, -2, 0.5, 0.75, -3.14/4) < 1){
        // if((firstHit.getPos() -  annihilationHits.getHits().at(i).getPos()).Mag() > 70 and (secondHit.getPos() -  annihilationHits.getHits().at(i).getPos()).Mag() > 70){
        if((firstHit.getScintillator().getID() != annihilationHits.getHits().at(i).getScintillator().getID()) && \
          (secondHit.getScintillator().getID() != annihilationHits.getHits().at(i).getScintillator().getID())){
          getStatistics().getHisto2D("DeltaVsDelta")->Fill(DeltaFirst/1000.0, DeltaSecond/1000.0);

          if(EventCategorizerTools::elipseCut(DeltaFirst/1000.0, DeltaSecond/1000.0, 0.445344, -2.42528, 1.7, 0.7, TMath::DegToRad()*60.0)){
            firstScatter = annihilationHits.getHits().at(i);
            physicEvent.addHit(firstScatter);
            firstScatterSetBig = true;
            getStatistics().getHisto1D("ComptonAnglesBig")->Fill(EventCategorizerTools::calculateScatteringAngle(firstHit, firstScatter));
            getStatistics().getHisto2D("DeltaVsDeltaAfterCutBig")->Fill(DeltaFirst/1000.0, DeltaSecond/1000.0);

            if(EventCategorizerTools::elipseCut(DeltaFirst/1000.0, DeltaSecond/1000.0, 0.202429, -2.54194, 1, 0.26, TMath::DegToRad()*50.0) or \
               EventCategorizerTools::elipseCut(DeltaFirst/1000.0, DeltaSecond/1000.0, 0.42915, -3.18569, 0.75, 0.15, TMath::DegToRad()*50.0)){
                firstScatterSetSmall = true;
                getStatistics().getHisto1D("ComptonAnglesSmall")->Fill(EventCategorizerTools::calculateScatteringAngle(firstHit, firstScatter));
                getStatistics().getHisto2D("DeltaVsDeltaAfterCutSmall")->Fill(DeltaFirst/1000.0, DeltaSecond/1000.0);
            }
          }

          if(EventCategorizerTools::elipseCut(DeltaFirst/1000.0, DeltaSecond/1000.0, -2.30769, 0.475791, 1.7, 0.7, TMath::DegToRad()*30.0)){
            secondScatter = annihilationHits.getHits().at(i);
            physicEvent.addHit(secondScatter);
            secondScatterSetBig = true;
            getStatistics().getHisto1D("ComptonAnglesBig")->Fill(EventCategorizerTools::calculateScatteringAngle(secondHit, secondScatter));
            getStatistics().getHisto2D("DeltaVsDeltaAfterCutBig")->Fill(DeltaFirst/1000.0, DeltaSecond/1000.0);

            if(EventCategorizerTools::elipseCut(DeltaFirst/1000.0, DeltaSecond/1000.0, -2.375443, 0.27543, 1, 0.26, TMath::DegToRad()*40.0) or \
               EventCategorizerTools::elipseCut(DeltaFirst/1000.0, DeltaSecond/1000.0, -3.16473518, 0.473518, 0.7, 0.15, TMath::DegToRad()*40.0)){
                secondScatterSetSmall = true;
                getStatistics().getHisto1D("ComptonAnglesSmall")->Fill(EventCategorizerTools::calculateScatteringAngle(secondHit, secondScatter));
                getStatistics().getHisto2D("DeltaVsDeltaAfterCutSmall")->Fill(DeltaFirst/1000.0, DeltaSecond/1000.0);
            }
          }
        // }
        }

      }
    }

    if((physicEvent.getHits().size() == 4) && firstScatterSetBig && secondScatterSetBig){
      TVector3 AnnihilationPoint = EventCategorizerTools::calculateAnnihilationPoint(firstHit, secondHit);

      TVector3 FirstMomentum = firstHit.getPos() - AnnihilationPoint;
      TVector3 SecondMomentum = secondHit.getPos() - AnnihilationPoint;
      TVector3 FirstScatteredMomentum = firstScatter.getPos() - firstHit.getPos();
      TVector3 SecondScatteredMomentum = secondScatter.getPos() - secondHit.getPos();

      double Theta1 = EventCategorizerTools::calculateScatteringAngle(firstHit, firstScatter);
      double Theta2 = EventCategorizerTools::calculateScatteringAngle(secondHit, secondScatter);

      getStatistics().getHisto2D("ThetaVsThetaBig")->Fill(Theta1, Theta2);

      TVector3 Orthogonal1 = FirstMomentum.Cross(FirstScatteredMomentum);
      TVector3 Orthogonal2 = SecondMomentum.Cross(SecondScatteredMomentum);

      double AngleBetweenPlanes = 180*(Orthogonal1.Angle(Orthogonal2))/TMath::Pi();

      getStatistics().getHisto1D("PhiAngleBig")->Fill(AngleBetweenPlanes);

      if( (pow(Theta1 - 81.66, 2) + pow(Theta2 - 81.66, 2)) < pow(30,2)) {
        getStatistics().getHisto1D("PhiAngleR30Big")->Fill(AngleBetweenPlanes);

        if( (pow(Theta1 - 81.66, 2) + pow(Theta2 - 81.66, 2)) < pow(20,2)) {
        getStatistics().getHisto1D("PhiAngleR20Big")->Fill(AngleBetweenPlanes);

        if( (pow(Theta1 - 81.66, 2) + pow(Theta2 - 81.66, 2)) < pow(15,2)) {
        getStatistics().getHisto1D("PhiAngleR15Big")->Fill(AngleBetweenPlanes);

        if( (pow(Theta1 - 81.66, 2) + pow(Theta2 - 81.66, 2)) < pow(10,2)) {
        getStatistics().getHisto1D("PhiAngleR10Big")->Fill(AngleBetweenPlanes);

        }
        }

        }
      }

      if(firstScatterSetSmall && secondScatterSetSmall){
        getStatistics().getHisto1D("PhiAngleSmall")->Fill(AngleBetweenPlanes);
        getStatistics().getHisto2D("ThetaVsThetaSmall")->Fill(Theta1, Theta2);

      if( (pow(Theta1 - 81.66, 2) + pow(Theta2 - 81.66, 2)) < pow(30,2)) {
        getStatistics().getHisto1D("PhiAngleR30Small")->Fill(AngleBetweenPlanes);

        if( (pow(Theta1 - 81.66, 2) + pow(Theta2 - 81.66, 2)) < pow(20,2)) {
        getStatistics().getHisto1D("PhiAngleR20Small")->Fill(AngleBetweenPlanes);

        if( (pow(Theta1 - 81.66, 2) + pow(Theta2 - 81.66, 2)) < pow(15,2)) {
        getStatistics().getHisto1D("PhiAngleR15Small")->Fill(AngleBetweenPlanes);

        if( (pow(Theta1 - 81.66, 2) + pow(Theta2 - 81.66, 2)) < pow(10,2)) {
        getStatistics().getHisto1D("PhiAngleR10Small")->Fill(AngleBetweenPlanes);

        }
        }

        }
      }

      }

    }




  }



  return physicEvent;
}
