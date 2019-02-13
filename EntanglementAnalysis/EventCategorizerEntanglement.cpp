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

#include "../LargeBarrelAnalysis/EventCategorizerTools.h"
#include <JPetOptionsTools/JPetOptionsTools.h>
#include "EventCategorizerEntanglement.h"
#include <JPetWriter/JPetWriter.h>
#include <TMath.h>
#include <TVector3.h>
#include <iostream>

using namespace jpet_options_tools;

using namespace std;

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

  if (fSaveControlHistos) {
    getStatistics().createHistogram(
      new TH1F("AllHitTOT", "TOT of all Hits in physics stream", 200, 0.0, 100.0)
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
      new TH1F("DeexAnnihTimeDiff", "Deexcitation-Annihilation Hits Time Difference", 200, -200.0, 200.0)
    );
    getStatistics().getHisto1D("DeexAnnihTimeDiff")->SetXTitle("Time difference between deexcitation and annihilation hits [ns]");
    getStatistics().getHisto1D("DeexAnnihTimeDiff")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("2Gamma_TimeDiff", "2 Gamma Hits Time Difference", 200, 0.0, 100.0)
    );
    getStatistics().getHisto1D("2Gamma_TimeDiff")->SetXTitle("Hits time difference [ns]");
    getStatistics().getHisto1D("2Gamma_TimeDiff")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("2Gamma_ThetaDiff", "2 Gamma Hits angles", 180, -0.5, 179.5)
    );
    getStatistics().getHisto1D("2Gamma_ThetaDiff")->SetXTitle("Hits theta diff [deg]");
    getStatistics().getHisto1D("2Gamma_ThetaDiff")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("2Gamma_DLOR", "Delta LOR distance", 100, 0.0, 50.0)
    );
    getStatistics().getHisto1D("2Gamma_DLOR")->SetXTitle("Delta LOR [cm]");
    getStatistics().getHisto1D("2Gamma_DLOR")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("2Annih_TimeDiff", "2 gamma annihilation Hits Time Difference", 200, 0.0, fMaxTimeDiff/1000.0)
    );
    getStatistics().getHisto1D("2Annih_TimeDiff")->SetXTitle("Time difference between 2 annihilation hits [ns]");
    getStatistics().getHisto1D("2Annih_TimeDiff")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("2Annih_ThetaDiff", "Annihilation Hits Theta Diff",
      (int) 4*fBackToBackAngleWindow, 180.-fBackToBackAngleWindow, 180.+fBackToBackAngleWindow)
    );
    getStatistics().getHisto1D("2Annih_ThetaDiff")->SetXTitle("Annihilation hits theta diff [deg]");
    getStatistics().getHisto1D("2Annih_ThetaDiff")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("2Annih_DLOR", "Delta LOR distance", 100, 0.0, 50.0)
    );
    getStatistics().getHisto1D("2Annih_ThetaDiff")->SetXTitle("Annihilation hits Delta LOR [cm]");
    getStatistics().getHisto1D("2Annih_ThetaDiff")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH2F("2Annih_XY", "Reconstructed XY position of annihilation point", 220, -54.5, 54.5, 220, -54.5, 54.5)
    );
    getStatistics().getHisto2D("2Annih_XY")->SetXTitle("Annihilation point X [cm]");
    getStatistics().getHisto2D("2Annih_XY")->SetYTitle("Annihilation point Y [cm]");

    getStatistics().createHistogram(
      new TH1F("2Annih_Z", "Reconstructed Z position of annihilation point", 220, -54.5, 54.5)
    );
    getStatistics().getHisto1D("2Annih_Z")->SetXTitle("Annihilation point Z [cm]");
    getStatistics().getHisto1D("2Annih_Z")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH2F("3GammaThetas", "3 Gamma Thetas plot", 251, -0.5, 250.5, 201, -0.5, 200.5)
    );
    getStatistics().getHisto2D("3GammaThetas")->SetXTitle("Transformed thetas 1-2 [deg]");
    getStatistics().getHisto2D("3GammaThetas")->SetYTitle("Transformed thetas 2-3 [deg]");

    getStatistics().createHistogram(
      new TH1F("3GammaPlaneDist", "3 Gamma Plane Distance to Center", 200, 0.0, 50.0)
    );
    getStatistics().getHisto1D("3GammaPlaneDist")->SetXTitle("Distance [cm]");
    getStatistics().getHisto1D("3GammaPlaneDist")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("3GammaTimeDiff", "3 gamma last and first hit time difference", 200, 0.0, 20.0)
    );
    getStatistics().getHisto1D("3GammaTimeDiff")->SetXTitle("Time difference [ns]");
    getStatistics().getHisto1D("3GammaTimeDiff")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("3AnnihPlaneDist", "3 Gamma Annihilation Plane Distance to Center",
      100, 0.0, fMaxDistOfDecayPlaneFromCenter)
    );
    getStatistics().getHisto1D("3AnnihPlaneDist")->SetXTitle("Distance [cm]");
    getStatistics().getHisto1D("3AnnihPlaneDist")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("3AnnihTimeDiff", "3 gamma Annihilation last and first hit time difference", 200, 0.0, fMaxTimeDiff/1000.0)
    );
    getStatistics().getHisto1D("3AnnihTimeDiff")->SetXTitle("Time difference [ns]");
    getStatistics().getHisto1D("3AnnihTimeDiff")->SetYTitle("Counts");

    getStatistics().createHistogram(
      new TH1F("PhiAngle", "Angle between scattering planes", 180, 0.0, 180)
    );
    getStatistics().getHisto1D("3AnnihTimeDiff")->SetXTitle("#varphi [deg]");
    getStatistics().getHisto1D("3AnnihTimeDiff")->SetYTitle("Counts");
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
      if (physicEvent.getHits().size()) { events.push_back(physicEvent); }
    }
  } else {
    return false;
  }
  if (events.size()) { saveEvents(events); }
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

        // Checking for back to back
        double thetaDiff = fabs(firstHit.getBarrelSlot().getTheta() - secondSuspect.getBarrelSlot().getTheta());
        double minTheta = 180.0 - fBackToBackAngleWindow;
        double maxTheta = 180.0 + fBackToBackAngleWindow;
        if (thetaDiff > minTheta && thetaDiff < maxTheta) {
          if (fSaveControlHistos) {
            double distance = EventCategorizerTools::calculateDistance(secondSuspect, firstSuspect);
            TVector3 annhilationPoint = EventCategorizerTools::calculateAnnihilationPoint(firstSuspect, secondSuspect);
            getStatistics().getHisto1D("2Gamma_Zpos")->Fill(firstSuspect.getPosZ());
            getStatistics().getHisto1D("2Gamma_Zpos")->Fill(secondSuspect.getPosZ());
            getStatistics().getHisto1D("2Gamma_TimeDiff")->Fill(secondSuspect.getTime() - firstSuspect.getTime());
            getStatistics().getHisto1D("2Gamma_Dist")->Fill(distance);
            getStatistics().getHisto1D("Annih_TOF")->Fill(EventCategorizerTools::calculateTOF(firstSuspect, secondSuspect));
            getStatistics().getHisto2D("AnnihPoint_XY")->Fill(annhilationPoint.X(), annhilationPoint.Y());
            getStatistics().getHisto2D("AnnihPoint_XZ")->Fill(annhilationPoint.X(), annhilationPoint.Z());
            getStatistics().getHisto2D("AnnihPoint_YZ")->Fill(annhilationPoint.Y(), annhilationPoint.Z());
          }
          firstHit = firstSuspect;
          secondHit = secondSuspect;
          physicEvent.addHit(firstHit);
          physicEvent.addHit(secondHit);

          annihilationHits.removeHitAtPosition(int(j));
          annihilationHits.removeHitAtPosition(int(i));
        }
      }
    }

    for(int i=0; i<annihilationHits.getHits().size(); i++){
      double DeltaFirst, DeltaSecond;

      DeltaFirst = EventCategorizerTools::calculateTOF(firstHit, annihilationHits.getHits().at(i)) - EventCategorizerTools::calculateScatteringTime(firstHit, annihilationHits.getHits().at(i));
      DeltaSecond = EventCategorizerTools::calculateTOF(secondHit, annihilationHits.getHits().at(i)) - EventCategorizerTools::calculateScatteringTime(secondHit, annihilationHits.getHits().at(i));

      if(fabs(DeltaFirst) < 0.5){
        firstScatter = annihilationHits.getHits().at(i);
        physicEvent.addHit(firstScatter);
      }
      if(fabs(DeltaSecond) < 0.5){
        secondScatter = annihilationHits.getHits().at(i);
        physicEvent.addHit(secondScatter);
      }

    }

    if(physicEvent.getHits().size() == 4){
      TVector3 AnnihilationPoint = EventCategorizerTools::calculateAnnihilationPoint(firstHit, secondHit);

      TVector3 FirstMomentum = firstHit.getPos() - AnnihilationPoint;
      TVector3 SecondMomentum = secondHit.getPos() - AnnihilationPoint;
      TVector3 FirstScatteredMomentum = firstScatter.getPos() - firstHit.getPos();
      TVector3 SecondScatteredMomentum = secondScatter.getPos() - secondHit.getPos();

      double Theta1 = EventCategorizerTools::calculateScatteringAngle(firstHit, firstScatter);
      double Theta2 = EventCategorizerTools::calculateScatteringAngle(secondHit, secondScatter);

      TVector3 Orthogonal1 = FirstMomentum.Cross(FirstScatteredMomentum);
      TVector3 Orthogonal2 = SecondMomentum.Cross(SecondScatteredMomentum);

      double AngleBetweenPlanes = 180*(Orthogonal1.Angle(Orthogonal2))/TMath::Pi();

      getStatistics().getHisto1D("PhiAngle")->Fill(AngleBetweenPlanes);
    }




  }



  return physicEvent;
}
