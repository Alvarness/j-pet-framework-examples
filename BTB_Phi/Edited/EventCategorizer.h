/**
 *  @copyright Copyright 2017 The J-PET Framework Authors. All rights reserved.
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
 *  @file EventCategorizer.h
 */

#ifndef EVENTCATEGORIZER_H
#define EVENTCATEGORIZER_H

#include <vector>
#include <utility>
#include <map>
#include <JPetUserTask/JPetUserTask.h>
#include <JPetHit/JPetHit.h>
#include <JPetEvent/JPetEvent.h>

class JPetWriter;

#ifdef __CINT__
#	define override
#endif

class EventCategorizer : public JPetUserTask{
public:
	EventCategorizer(const char * name);
	virtual ~EventCategorizer(){}
	virtual bool init() override;
	virtual bool exec() override;
	virtual bool terminate() override;

//Calculate the TOT

double CalcTOT(const JPetHit& Hit)
{


  double TOT = 0.;
  double TOT_A = 0.;
  double TOT_B = 0.;

  auto lead_times_A = Hit.getSignalA().getRecoSignal().getRawSignal().getTimesVsThresholdNumber(JPetSigCh::Leading);
  auto trail_times_A = Hit.getSignalA().getRecoSignal().getRawSignal().getTimesVsThresholdNumber(JPetSigCh::Trailing);
  auto lead_times_B =  Hit.getSignalB().getRecoSignal().getRawSignal().getTimesVsThresholdNumber(JPetSigCh::Leading);
  auto trail_times_B = Hit.getSignalB().getRecoSignal().getRawSignal().getTimesVsThresholdNumber(JPetSigCh::Trailing);


  for (auto& thr_time_pair : lead_times_A) {
    int thr = thr_time_pair.first;
    if (trail_times_A.count(thr) > 0 ) {
      TOT_A = TOT_A + trail_times_A[thr] - lead_times_A[thr];
    }
  }

  for (auto& thr_time_pair : lead_times_B) {
    int thr = thr_time_pair.first;
    if ( trail_times_B.count(thr) > 0 ) {

      TOT_B = TOT_B + trail_times_B[thr] - lead_times_B[thr];
    }
  }
  TOT = (TOT_A + TOT_B) / 1000.;

  return TOT;

}


//TOF Calculation - Function (From Center (0,0,0))

double CalcTOF(const JPetHit & Hit, TVector3 Center) {

  double Dist = sqrt(pow(Hit.getPosX() - Center.X(), 2) + pow(Hit.getPosY() - Center.Y(), 2) + pow(Hit.getPosZ() - Center.Z(), 2));

  double CalTime = Dist / 29.979246; //velocity of light in cm/s, returns time in ns

  double HitTime = Hit.getTime() / 1000.0;

  double TOF = (HitTime - CalTime);

  return TOF;

}



//Calculation of the Scatter Test between Primary and Secondary hits

double CalScatterTest(const JPetHit & Hit1,
  const JPetHit & Hit2)

{

  double timeDiff = ((Hit2.getTime() / 1000.0) - (Hit1.getTime() / 1000.0));
  float Dist = sqrt(pow(Hit2.getPosX() - Hit1.getPosX(), 2) +
    pow(Hit2.getPosY() - Hit1.getPosY(), 2) +
    pow(Hit2.getPosZ() - Hit1.getPosZ(), 2));
  Dist = Dist / 29.979246;
  double Scat = (timeDiff - Dist);
  return Scat;

}



//3D-Angle Calculation - Function

  double Calc3DAngle(const JPetHit & Hit1,
  const JPetHit & Hit2 , TVector3 Center) {

  double scalarProd = (Hit1.getPosX() - Center.X()) * (Hit2.getPosX() - Center.X()) + (Hit1.getPosY() - Center.Y()) * (Hit2.getPosY() - Center.Y()) + (Hit1.getPosZ() - Center.Z()) * (Hit2.getPosZ() - Center.Z());

  double magProd = sqrt((pow(Hit1.getPosX() - Center.X(), 2) +
      pow(Hit1.getPosY() - Center.Y(), 2) +
      pow(Hit1.getPosZ() - Center.Z(), 2)) *
    (pow(Hit2.getPosX() - Center.X(), 2) +
      pow(Hit2.getPosY() - Center.Y(), 2) +
      pow(Hit2.getPosZ() - Center.Z(), 2)));

  double Angle = acos(scalarProd / magProd) * 180 / 3.14159;

  return Angle;
}


//Calculate Theta Angle - Function

double CalcTheta(const JPetHit & Hit1,
  const JPetHit & Hit2 , TVector3 Center){


TVector3 V1(Hit1.getPosX() - Center.X(), Hit1.getPosY() - Center.Y(), Hit1.getPosZ() - Center.Z());
TVector3 V2(Hit2.getPosX() - Hit1.getPosX(), Hit2.getPosY() - Hit1.getPosY(), Hit2.getPosZ() - Hit1.getPosZ());

double DotProd = V1.Dot(V2); 
double Mag = V1.Mag() * V2.Mag();

double Theta = acos(DotProd/Mag);


return Theta;


}


//Calculate Phi Angle - Function

//double CalcPhi(








protected:
	void saveEvents(const std::vector<JPetEvent>& event);
	bool fSaveControlHistos = true;
};
#endif /*  !EVENTCATEGORIZER_H */
