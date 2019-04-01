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
 *  @file EventCategorizerEntanglement.h
 */

#ifndef EVENTCATEGORIZERENTANGLEMENT_H
#define EVENTCATEGORIZERENTANGLEMENT_H

#include <JPetStatistics/JPetStatistics.h>
#include <JPetUserTask/JPetUserTask.h>
#include <JPetEventType/JPetEventType.h>
#include <JPetEvent/JPetEvent.h>
#include <JPetHit/JPetHit.h>
#include <vector>
#include <map>

class JPetWriter;

#ifdef __CINT__
#	define override
#endif

class EventCategorizerEntanglement : public JPetUserTask{
public:
	EventCategorizerEntanglement(const char * name);
	virtual ~EventCategorizerEntanglement(){}
	virtual bool init() override;
	virtual bool exec() override;
	virtual bool terminate() override;
	JPetEvent physicsAnalysis(std::vector<JPetHit> hits);

protected:
	const std::string kScatterTOFTimeDiffParamKey = "Scatter_Categorizer_TOF_TimeDiff_float";
	const std::string kMaxDistOfDecayPlaneFromCenterParamKey = "EventCategorizer_MaxDistOfDecayPlaneFromCenter_float";
	const std::string kBackToBackAngleWindowParamKey = "EventCategorizer_BackToBackAngleWindow_float";
	const std::string kDecayInto3MinAngleParamKey = "EventCategorizer_DecayInto3MinAngle_float";
	const std::string kMinAnnihilationParamKey = "EventCategorizer_MinAnnihilationTOT_float";
	const std::string kMaxAnnihilationParamKey = "EventCategorizer_MaxAnnihilationTOT_float";
	const std::string kMinDeexcitationParamKey = "EventCategorizer_MinDeexcitationTOT_float";
	const std::string kMaxDeexcitationParamKey = "EventCategorizer_MaxDeexcitationTOT_float";
	const std::string kMaxTimeDiffParamKey = "EventCategorizer_MaxTimeDiff_float";
	const std::string kMaxZPosParamKey = "EventCategorizer_MaxHitZPos_float";
	const std::string kMaxXYAnnihilationPointDistanceFromCenter = "EventCategorizer_MaxXYAnnihilationPointDistanceFromCenter_float";

	double fMaxXYAnnihilationPointDistanceFromCenter = 5.0;
	double fScatterTOFTimeDiff = 2000.0;
	double fMaxDistOfDecayPlaneFromCenter = 5.;
	double fMinAnnihilationTOT = 1000.0;
	double fMaxAnnihilationTOT = 25000.0;
	double fMinDeexcitationTOT = 30000.0;
	double fMaxDeexcitationTOT = 50000.0;
	double fBackToBackAngleWindow = 3.;
	double fDecayInto3MinAngle = 190.;
	double fMaxTimeDiff = 1000.;
	double fMaxZPos = 23.;
	bool fSaveControlHistos = true;

	void saveEvents(const std::vector<JPetEvent>& event);
};

#endif /* !EVENTCATEGORIZERENTANGLEMENT_H */
