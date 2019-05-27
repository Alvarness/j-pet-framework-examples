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
 *  @file EventCategorizer.cpp
 */

#include <JPetOptionsTools/JPetOptionsTools.h>
#include <JPetWriter/JPetWriter.h>
#include "EventCategorizerTools.h"
#include "EventCategorizer.h"
#include <iostream>

using namespace jpet_options_tools;
using namespace std;

EventCategorizer::EventCategorizer(const char* name): JPetUserTask(name) {}

EventCategorizer::~EventCategorizer() {}

bool EventCategorizer::init()
{
  INFO("Event categorization started.");
  // Parameter for back to back categorization
  fOutputEvents = new JPetTimeWindow("JPetEvent");

  outputFile.open("output.txt", std::ios_base::app | std::ios_base::out);

  return true;
}

bool EventCategorizer::exec()
{
  vector<JPetEvent> events;
  if (auto timeWindow = dynamic_cast<const JPetTimeWindow* const>(fEvent)) {
    for (uint i = 0; i < timeWindow->getNumberOfEvents(); i++) {
      const auto& event = dynamic_cast<const JPetEvent&>(timeWindow->operator[](i));

     // Check types of current event

      vector<JPetHit> hits = event.getHits();
      JPetEvent annihilationHits;

      for (unsigned i = 0; i < hits.size(); i++) {

        if (fabs(hits[i].getPosZ()) < 23) {
          double TOTofHit = EventCategorizerTools::calculateTOT(hits[i]);

          if (TOTofHit >= 1 && TOTofHit <= 25000) {
            annihilationHits.addHit(hits[i]);
          }
        }
      }

      if(annihilationHits.getHits().size() == 2 ){
        // cout << annihilationHits.getHits().size() << endl;

        JPetHit firstHit = annihilationHits.getHits().at(0);
        JPetHit secondHit = annihilationHits.getHits().at(1);


        if(EventCategorizerTools::DeltaAngle(firstHit, secondHit) > 20  && EventCategorizerTools::LORDistance(firstHit, secondHit) < 25){

          outputFile << firstHit.getPosX() << "\t" << firstHit.getPosY() << "\t" << firstHit.getPosZ() << "\t" << firstHit.getTime() << "\t" \
                     << secondHit.getPosX() << "\t" << secondHit.getPosY() << "\t" << secondHit.getPosZ() << "\t" << secondHit.getTime() << "\n";
        }

      }



    }
    // saveEvents(events);
  } else { return false; }

  events.clear();
  return true;
}

bool EventCategorizer::terminate()
{
  INFO("Event categorization completed.");

  outputFile.close();
  return true;
}

void EventCategorizer::saveEvents(const vector<JPetEvent>& events)
{
  for (const auto& event : events) { fOutputEvents->add<JPetEvent>(event); }
}

void EventCategorizer::initialiseHistograms(){

  // General histograms
 }
