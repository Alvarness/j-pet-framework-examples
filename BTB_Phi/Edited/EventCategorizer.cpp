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
 *  @file EventCategorizer.cpp
 */

#include <iostream>
#include <JPetWriter/JPetWriter.h>
#include "EventCategorizer.h"

using namespace std;

EventCategorizer::EventCategorizer(const char* name): JPetUserTask(name) {}

bool EventCategorizer::init()
{

  INFO("Event categorization started.");
  INFO("Looking at two hit Events on Layer 1&2 only - creating only control histograms");

  fOutputEvents = new JPetTimeWindow("JPetEvent");

  if (fSaveControlHistos) {

//All Histograms//

    getStatistics().createHistogram( new TH1F("ScinID", "ScinID",
                                     192, -0.5, 192.5) );
    getStatistics().getHisto1D("ScinID")->GetXaxis()->SetTitle("Scintillator ID");
    getStatistics().getHisto1D("ScinID")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("TimeDiff", "Time Difference Distribution",
                                     210, -10.5, 10.5) );
    getStatistics().getHisto1D("TimeDiff")->GetXaxis()->SetTitle("Time Difference BA [ns]");
    getStatistics().getHisto1D("TimeDiff")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("TOT", "TOT",
                                     201, -0.5, 200.5) );
    getStatistics().getHisto1D("TOT")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram(new TH2F("Angle1+0_Angle1-0_123", "Angle1+0_Angle1-0_123", 361, -0.5, 360.5, 361, -0.5, 360.5));
    getStatistics().getHisto2D("Angle1+0_Angle1-0_123")->GetXaxis()->SetTitle("Angle 1+0 [deg]");
    getStatistics().getHisto2D("Angle1+0_Angle1-0_123")->GetYaxis()->SetTitle("Angle 1-0 [deg]");


    getStatistics().createHistogram(new TH2F("Angle1+0_Angle1-0_124", "Angle1+0_Angle1-0_124", 361, -0.5, 360.5, 361, -0.5, 360.5));
    getStatistics().getHisto2D("Angle1+0_Angle1-0_124")->GetXaxis()->SetTitle("Angle 1+0 [deg]");
    getStatistics().getHisto2D("Angle1+0_Angle1-0_124")->GetYaxis()->SetTitle("Angle 1-0 [deg]");


    getStatistics().createHistogram(new TH2F("Scatter_of_3_from_1_and_2", "Scatter_of_3_from_1_and_2", 150, -7.5, 7.5, 150, -7.5, 7.5));
    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2")->GetXaxis()->SetTitle("Scatter Time 3-1 [ns]");
    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2")->GetYaxis()->SetTitle("Scatter Time 3-2 [ns]");


 getStatistics().createHistogram(new TH2F("Scatter_of_4_from_1_and_2", "Scatter_of_4_from_1_and_2", 150, -7.5, 7.5, 150, -7.5, 7.5));
    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2")->GetXaxis()->SetTitle("Scatter Time 4-1 [ns]");
    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2")->GetYaxis()->SetTitle("Scatter Time 4-2 [ns]");



//All Histograms - Cut1//

    getStatistics().createHistogram( new TH1F("ScinID_Cut1", "ScinID_Cut1",
                                     192, -0.5, 192.5) );
    getStatistics().getHisto1D("ScinID_Cut1")->GetXaxis()->SetTitle("Scintillator ID");
    getStatistics().getHisto1D("ScinID_Cut1")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("TimeDiff_Cut1", "Time Difference Distribution_Cut1",
                                     210, -10.5, 10.5) );
    getStatistics().getHisto1D("TimeDiff_Cut1")->GetXaxis()->SetTitle("Time Difference BA [ns]");
    getStatistics().getHisto1D("TimeDiff_Cut1")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("TOT_Cut1", "TOT_Cut1",
                                     201, -0.5, 200.5) );
    getStatistics().getHisto1D("TOT_Cut1")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_Cut1")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram(new TH2F("Angle1+0_Angle1-0_123_Cut1", "Angle1+0_Angle1-0_123", 361, -0.5, 360.5, 361, -0.5, 360.5));
    getStatistics().getHisto2D("Angle1+0_Angle1-0_123_Cut1")->GetXaxis()->SetTitle("Angle 1+0 [deg]");
    getStatistics().getHisto2D("Angle1+0_Angle1-0_123_Cut1")->GetYaxis()->SetTitle("Angle 1-0 [deg]");


    getStatistics().createHistogram(new TH2F("Angle1+0_Angle1-0_124_Cut1", "Angle1+0_Angle1-0_124_Cut1", 361, -0.5, 360.5, 361, -0.5, 360.5));
    getStatistics().getHisto2D("Angle1+0_Angle1-0_124_Cut1")->GetXaxis()->SetTitle("Angle 1+0 [deg]");
    getStatistics().getHisto2D("Angle1+0_Angle1-0_124_Cut1")->GetYaxis()->SetTitle("Angle 1-0 [deg]");


    getStatistics().createHistogram(new TH2F("Scatter_of_3_from_1_and_2_Cut1", "Scatter_of_3_from_1_and_2", 150, -7.5, 7.5, 150, -7.5, 7.5));
    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2_Cut1")->GetXaxis()->SetTitle("Scatter Time 3-1 [ns]");
    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2_Cut1")->GetYaxis()->SetTitle("Scatter Time 3-2 [ns]");


 getStatistics().createHistogram(new TH2F("Scatter_of_4_from_1_and_2_Cut1", "Scatter_of_4_from_1_and_2", 150, -7.5, 7.5, 150, -7.5, 7.5));
    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2_Cut1")->GetXaxis()->SetTitle("Scatter Time 4-1 [ns]");
    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2_Cut1")->GetYaxis()->SetTitle("Scatter Time 4-2 [ns]");


//All Histograms Cut-2


  getStatistics().createHistogram( new TH1F("ScinID_Cut2", "ScinID_Cut2",
                                     192, -0.5, 192.5) );
    getStatistics().getHisto1D("ScinID_Cut2")->GetXaxis()->SetTitle("Scintillator ID");
    getStatistics().getHisto1D("ScinID_Cut2")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("TimeDiff_Cut2", "Time Difference Distribution_Cut2",
                                     210, -10.5, 10.5) );
    getStatistics().getHisto1D("TimeDiff_Cut2")->GetXaxis()->SetTitle("Time Difference BA [ns]");
    getStatistics().getHisto1D("TimeDiff_Cut2")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("TOT_Cut2", "TOT_Cut2",
                                     201, -0.5, 200.5) );
    getStatistics().getHisto1D("TOT_Cut2")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_Cut2")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram(new TH2F("Angle1+0_Angle1-0_123_Cut2", "Angle1+0_Angle1-0_123", 361, -0.5, 360.5, 361, -0.5, 360.5));
    getStatistics().getHisto2D("Angle1+0_Angle1-0_123_Cut2")->GetXaxis()->SetTitle("Angle 1+0 [deg]");
    getStatistics().getHisto2D("Angle1+0_Angle1-0_123_Cut2")->GetYaxis()->SetTitle("Angle 1-0 [deg]");


    getStatistics().createHistogram(new TH2F("Angle1+0_Angle1-0_124_Cut2", "Angle1+0_Angle1-0_124_Cut2", 361, -0.5, 360.5, 361, -0.5, 360.5));
    getStatistics().getHisto2D("Angle1+0_Angle1-0_124_Cut2")->GetXaxis()->SetTitle("Angle 1+0 [deg]");
    getStatistics().getHisto2D("Angle1+0_Angle1-0_124_Cut2")->GetYaxis()->SetTitle("Angle 1-0 [deg]");


    getStatistics().createHistogram(new TH2F("Scatter_of_3_from_1_and_2_Cut2", "Scatter_of_3_from_1_and_2", 150, -7.5, 7.5, 150, -7.5, 7.5));
    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2_Cut2")->GetXaxis()->SetTitle("Scatter Time 3-1 [ns]");
    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2_Cut2")->GetYaxis()->SetTitle("Scatter Time 3-2 [ns]");


 getStatistics().createHistogram(new TH2F("Scatter_of_4_from_1_and_2_Cut2", "Scatter_of_4_from_1_and_2", 150, -7.5, 7.5, 150, -7.5, 7.5));
    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2_Cut2")->GetXaxis()->SetTitle("Scatter Time 4-1 [ns]");
    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2_Cut2")->GetYaxis()->SetTitle("Scatter Time 4-2 [ns]");













  }



  return true;
}



Bool_t comparison(const pair < double, JPetHit > & a,
  const pair < double, JPetHit > & b) {
  return a.first < b.first;
}










bool EventCategorizer::exec()
{

  if (auto timeWindow = dynamic_cast<const JPetTimeWindow* const>(fEvent)) {
    uint n = timeWindow->getNumberOfEvents();
    for (uint i = 0; i < n; ++i) {

      const auto& event = dynamic_cast<const JPetEvent&>(timeWindow->operator[](i));

      if (event.getHits().size() == 4) {


	//All the Calculations//

	TVector3 Center(0.0, 0.0, 0.0);

        JPetHit Hit_1 = event.getHits().at(0);
        JPetHit Hit_2 = event.getHits().at(1);
        JPetHit Hit_3 = event.getHits().at(2);
        JPetHit Hit_4 = event.getHits().at(3);

	double TOF_1 = CalcTOF( Hit_1, Center);
        double TOF_2 = CalcTOF( Hit_2, Center);
	double TOF_3 = CalcTOF( Hit_3, Center);
	double TOF_4 = CalcTOF( Hit_4, Center);

  	vector <pair<double,JPetHit>> TOF_vec;
        TOF_vec.push_back({TOF_1, Hit_1});
	TOF_vec.push_back({TOF_2, Hit_2});
	TOF_vec.push_back({TOF_3, Hit_3});
	TOF_vec.push_back({TOF_4, Hit_4});

        std::sort(TOF_vec.begin(), TOF_vec.end(), comparison);

	JPetHit & Hit1 = TOF_vec.at(0).second;
        JPetHit & Hit2 = TOF_vec.at(1).second;
        JPetHit & Hit3 = TOF_vec.at(2).second;
 	JPetHit & Hit4 = TOF_vec.at(3).second;


//Preliminary Cuts//

	if(fabs(Hit1.getPosZ()) <= 23.0 && fabs(Hit2.getPosZ()) <= 23.0 && fabs(Hit3.getPosZ()) <= 23.0 && fabs(Hit4.getPosZ()) <= 23.0){




	auto ID_1 = Hit1.getScintillator().getID();	
        auto ID_2 = Hit2.getScintillator().getID();	
	auto ID_3 = Hit3.getScintillator().getID();
	auto ID_4 = Hit4.getScintillator().getID();



//Preliminary Cuts//


  if (ID_1 != ID_2 && ID_1 != ID_3 && ID_1 != ID_4)

          {

            if (ID_2 != ID_3 && ID_2 != ID_4)

            {

              if (ID_3 != ID_4)

              {




	auto TD_1 = Hit1.getTimeDiff() / 1000.0;
	auto TD_2 = Hit2.getTimeDiff() / 1000.0;
	auto TD_3 = Hit3.getTimeDiff() / 1000.0;
	auto TD_4 = Hit4.getTimeDiff() / 1000.0;




	double TOT_1 = CalcTOT( Hit1 );
        double TOT_2 = CalcTOT( Hit2 );
	double TOT_3 = CalcTOT( Hit3 );
	double TOT_4 = CalcTOT( Hit4 );

	double Angle12 = Calc3DAngle(Hit1, Hit2, Center);
        double Angle23 = Calc3DAngle(Hit2, Hit3, Center);
        double Angle34 = Calc3DAngle(Hit3, Hit4, Center);
	double Angle13 = Calc3DAngle(Hit1, Hit3, Center);
        double Angle14 = Calc3DAngle(Hit1, Hit4, Center);
        double Angle24 = Calc3DAngle(Hit2, Hit4, Center);

	std::vector<double> Angles123;
        Angles123.push_back( Angle12 );
        Angles123.push_back( Angle23 );
        Angles123.push_back( Angle13 );
        std::sort( Angles123.begin(), Angles123.begin() + 3 );

	std::vector<double> Angles124;
        Angles124.push_back( Angle12 );
        Angles124.push_back( Angle24 );
        Angles124.push_back( Angle14 );
        std::sort( Angles124.begin(), Angles124.begin() + 3 );


	double Scat_13 = CalScatterTest(Hit1 , Hit3);
	double Scat_23 = CalScatterTest(Hit2 , Hit3);
	double Scat_14 = CalScatterTest(Hit1 , Hit4);
	double Scat_24 = CalScatterTest(Hit2 , Hit4);

	double Theta_13 = CalcTheta(Hit1, Hit3, Center);
	double Theta_14 = CalcTheta(Hit1, Hit4, Center);
	double Theta_23 = CalcTheta(Hit2, Hit3, Center);
	double Theta_24 = CalcTheta(Hit2, Hit4, Center);

	
	//All the required histograms//

	  getStatistics().getHisto1D("ScinID")->Fill(ID_1);
	  getStatistics().getHisto1D("ScinID")->Fill(ID_2);
	  getStatistics().getHisto1D("ScinID")->Fill(ID_3);
	  getStatistics().getHisto1D("ScinID")->Fill(ID_4);

          getStatistics().getHisto1D("TimeDiff")->Fill(TD_1);
  	  getStatistics().getHisto1D("TimeDiff")->Fill(TD_2);
	  getStatistics().getHisto1D("TimeDiff")->Fill(TD_3);
	  getStatistics().getHisto1D("TimeDiff")->Fill(TD_4);

	  getStatistics().getHisto1D("TOT")->Fill(TOT_1);
          getStatistics().getHisto1D("TOT")->Fill(TOT_2);
          getStatistics().getHisto1D("TOT")->Fill(TOT_3);
          getStatistics().getHisto1D("TOT")->Fill(TOT_4);

getStatistics().getHisto2D("Angle1+0_Angle1-0_123")->Fill(Angles123[1]+Angles123[0], Angles123[1]-Angles123[0]);

getStatistics().getHisto2D("Angle1+0_Angle1-0_124")->Fill(Angles124[1]+Angles124[0], Angles124[1]-Angles124[0]);

         getStatistics().getHisto2D("Scatter_of_3_from_1_and_2")->Fill(Scat_13, Scat_23);
         getStatistics().getHisto2D("Scatter_of_4_from_1_and_2")->Fill(Scat_14, Scat_24);




	//Analysis Cut1//


	if(TOT_1 <= 25.0 && TOT_2 <= 25.0 && TOT_3 <= 25.0 && TOT_4 <= 25.0)
	{




	//All the required histograms - Cut1//

	  getStatistics().getHisto1D("ScinID_Cut1")->Fill(ID_1);
	  getStatistics().getHisto1D("ScinID_Cut1")->Fill(ID_2);
	  getStatistics().getHisto1D("ScinID_Cut1")->Fill(ID_3);
	  getStatistics().getHisto1D("ScinID_Cut1")->Fill(ID_4);

          getStatistics().getHisto1D("TimeDiff_Cut1")->Fill(TD_1);
  	  getStatistics().getHisto1D("TimeDiff_Cut1")->Fill(TD_2);
	  getStatistics().getHisto1D("TimeDiff_Cut1")->Fill(TD_3);
	  getStatistics().getHisto1D("TimeDiff_Cut1")->Fill(TD_4);

	  getStatistics().getHisto1D("TOT_Cut1")->Fill(TOT_1);
          getStatistics().getHisto1D("TOT_Cut1")->Fill(TOT_2);
          getStatistics().getHisto1D("TOT_Cut1")->Fill(TOT_3);
          getStatistics().getHisto1D("TOT_Cut1")->Fill(TOT_4);

getStatistics().getHisto2D("Angle1+0_Angle1-0_123_Cut1")->Fill(Angles123[1]+Angles123[0], Angles123[1]-Angles123[0]);

getStatistics().getHisto2D("Angle1+0_Angle1-0_124_Cut1")->Fill(Angles124[1]+Angles124[0], Angles124[1]-Angles124[0]);

         getStatistics().getHisto2D("Scatter_of_3_from_1_and_2_Cut1")->Fill(Scat_13, Scat_23);
         getStatistics().getHisto2D("Scatter_of_4_from_1_and_2_Cut1")->Fill(Scat_14, Scat_24);




	//Analysis Cut2//


	
	if(Angle12+Angle23 <= 185.0 && Angle12+Angle23 >= 175.0 && Angle12+Angle24 <= 185.0 && Angle12+Angle24 >= 175.0)
	{
  


	//All the required histograms - Cut2//

  	  getStatistics().getHisto1D("ScinID_Cut2")->Fill(ID_1);
	  getStatistics().getHisto1D("ScinID_Cut2")->Fill(ID_2);
	  getStatistics().getHisto1D("ScinID_Cut2")->Fill(ID_3);
	  getStatistics().getHisto1D("ScinID_Cut2")->Fill(ID_4);

          getStatistics().getHisto1D("TimeDiff_Cut2")->Fill(TD_1);
  	  getStatistics().getHisto1D("TimeDiff_Cut2")->Fill(TD_2);
	  getStatistics().getHisto1D("TimeDiff_Cut2")->Fill(TD_3);
	  getStatistics().getHisto1D("TimeDiff_Cut2")->Fill(TD_4);

	  getStatistics().getHisto1D("TOT_Cut2")->Fill(TOT_1);
          getStatistics().getHisto1D("TOT_Cut2")->Fill(TOT_2);
          getStatistics().getHisto1D("TOT_Cut2")->Fill(TOT_3);
          getStatistics().getHisto1D("TOT_Cut2")->Fill(TOT_4);

getStatistics().getHisto2D("Angle1+0_Angle1-0_123_Cut2")->Fill(Angles123[1]+Angles123[0], Angles123[1]-Angles123[0]);

getStatistics().getHisto2D("Angle1+0_Angle1-0_124_Cut2")->Fill(Angles124[1]+Angles124[0], Angles124[1]-Angles124[0]);











				}
			
				}
	
				}



			}

			}

			}




			}

                	}

                  } 

 else {
    return false;
  }
  return true;
}



bool EventCategorizer::terminate()
{

  INFO("More than one hit Events done. Writing conrtrol histograms.");
  return true;
}

void EventCategorizer::saveEvents(const vector<JPetEvent>& events)
{
  for (const auto& event : events) {
    fOutputEvents->add<JPetEvent>(event);
  }
}
