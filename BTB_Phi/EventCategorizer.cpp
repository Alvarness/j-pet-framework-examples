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



    getStatistics().createHistogram( new TH1F("Hits", "Hits Distribution",
                                     10, 0.5, 10.5) );
    getStatistics().getHisto1D("Hits")->GetXaxis()->SetTitle("Hist Distribution");
    getStatistics().getHisto1D("Hits")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("TOT", "TOT",
                                     200, 0.0, 200.0) );
    getStatistics().getHisto1D("TOT")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH1F("TOT_first", "TOT for first Hit",
                                     200, 0.0, 200.0) );
    getStatistics().getHisto1D("TOT_first")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_first")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("TOT_second", "TOT for second Hit",
                                     200, 0.0, 200.0) );
    getStatistics().getHisto1D("TOT_second")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_second")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH1F("TOT_third", "TOT for third Hit",
                                     200, 0.0, 200.0) );
    getStatistics().getHisto1D("TOT_third")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_third")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH1F("TOT_fourth", "TOT for fourth Hit",
                                     200, 0.0, 200.0) );
    getStatistics().getHisto1D("TOT_fourth")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_fourth")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram( new TH2F("ScinID_vs_TOT", "ScinID_vs_TOT",
                                     1100, -5.5, 105.5,
                                     192, -0.5, 192.5 ));
    getStatistics().getHisto2D("ScinID_vs_TOT")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto2D("ScinID_vs_TOT")->GetYaxis()->SetTitle("Scintillator ID");

    getStatistics().createHistogram( new TH2F("DeltaT_vs_ScinID_big", "Time difference B-A vs scintillator ID, big range",
                                     192, 0.5, 192.5,
                                     2000, -100, 100 ) );
    getStatistics().getHisto2D("DeltaT_vs_ScinID_big")->GetXaxis()->SetTitle("Scintillator ID");
    getStatistics().getHisto2D("DeltaT_vs_ScinID_big")->GetYaxis()->SetTitle("Time difference BA [ns]");


    getStatistics().createHistogram( new TH1F("ScinID", "Scintillator ID Distribution",
                                     192, -0.5, 192.5) );
    getStatistics().getHisto1D("ScinID")->GetXaxis()->SetTitle("Scintillator ID");
    getStatistics().getHisto1D("ScinID")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("ScinID_After_All_Cuts", "ScinID_After_All_Cuts",
                                     192, -0.5, 192.5) );
    getStatistics().getHisto1D("ScinID")->GetXaxis()->SetTitle("Scintillator ID");
    getStatistics().getHisto1D("ScinID")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("TimeDiff", "Time Difference Distribution",
                                     750, -10, 10) );
    getStatistics().getHisto1D("TimeDiff")->GetXaxis()->SetTitle("Time Difference BA [ns]");
    getStatistics().getHisto1D("TimeDiff")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH2F("ScinID_vs_TOT_1", "ScinID_vs_TOT_1",
                                     1100, -5.5, 105.5,
                                     192, -0.5, 192.5 ));
    getStatistics().getHisto2D("ScinID_vs_TOT_1")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto2D("ScinID_vs_TOT_1")->GetYaxis()->SetTitle("Scintillator ID");



    getStatistics().createHistogram( new TH2F("ScinID_vs_TOT_2", "ScinID_vs_TOT_2",
                                     1100, -5.5, 105.5,
                                     192, -0.5, 192.5 ));
    getStatistics().getHisto2D("ScinID_vs_TOT_2")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto2D("ScinID_vs_TOT_2")->GetYaxis()->SetTitle("Scintillator ID");



    getStatistics().createHistogram( new TH2F("ScinID_vs_TOT_3", "ScinID_vs_TOT_3",
                                     1100, -5.5, 105.5,
                                     192, -0.5, 192.5 ));
    getStatistics().getHisto2D("ScinID_vs_TOT_3")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto2D("ScinID_vs_TOT_3")->GetYaxis()->SetTitle("Scintillator ID");


    getStatistics().createHistogram( new TH2F("ScinID_vs_TOT_4", "ScinID_vs_TOT_4",
                                     1100, -5.5, 105.5,
                                     192, -0.5, 192.5 ));
    getStatistics().getHisto2D("ScinID_vs_TOT_4")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto2D("ScinID_vs_TOT_4")->GetYaxis()->SetTitle("Scintillator ID");



    getStatistics().createHistogram( new TH1F("TOT_first_Cut", "TOT_first_Cut",
                                     200, 0.0, 200.0) );
    getStatistics().getHisto1D("TOT_first_Cut")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_first_Cut")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("TOT_second_Cut", "TOT_second_Cut",
                                     200, 0.0, 200.0) );
    getStatistics().getHisto1D("TOT_second_Cut")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_second_Cut")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH1F("TOT_third_Cut", "TOT_third_Cut",
                                     200, 0.0, 200.0) );
    getStatistics().getHisto1D("TOT_third_Cut")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_third_Cut")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH1F("TOT_fourth_Cut", "TOT_fourth_Cut",
                                     200, 0.0, 200.0) );
    getStatistics().getHisto1D("TOT_fourth_Cut")->GetXaxis()->SetTitle("TOT [ns]");
    getStatistics().getHisto1D("TOT_fourth_Cut")->GetYaxis()->SetTitle("Counts");




    getStatistics().createHistogram(new TH2F("Angle1+0_Angle1-0_123", "Angle1+0_Angle1-0_123", 360, -0.5, 359.5, 360, -0.5, 359.5));
    getStatistics().getHisto2D("Angle1+0_Angle1-0_123")->GetXaxis()->SetTitle("Angle 1+0 [deg]");
    getStatistics().getHisto2D("Angle1+0_Angle1-0_123")->GetYaxis()->SetTitle("Angle 1-0 [deg]");


    getStatistics().createHistogram(new TH2F("Angle1+0_Angle1-0_124", "Angle1+0_Angle1-0_124", 360, -0.5, 359.5, 360, -0.5, 359.5));
    getStatistics().getHisto2D("Angle1+0_Angle1-0_124")->GetXaxis()->SetTitle("Angle 1+0 [deg]");
    getStatistics().getHisto2D("Angle1+0_Angle1-0_124")->GetYaxis()->SetTitle("Angle 1-0 [deg]");





    getStatistics().createHistogram(new TH2F("Angle1+0_Angle1-0_123_Cut", "Angle1+0_Angle1-0_123_Cut", 360, -0.5, 359.5, 360, -0.5, 359.5));
    getStatistics().getHisto2D("Angle1+0_Angle1-0_123_Cut")->GetXaxis()->SetTitle("Angle 1+0 [deg]");
    getStatistics().getHisto2D("Angle1+0_Angle1-0_123_Cut")->GetYaxis()->SetTitle("Angle 1-0 [deg]");


    getStatistics().createHistogram(new TH2F("Angle1+0_Angle1-0_124_Cut", "Angle1+0_Angle1-0_124_Cut", 360, -0.5, 359.5, 360, -0.5, 359.5));
    getStatistics().getHisto2D("Angle1+0_Angle1-0_124_Cut")->GetXaxis()->SetTitle("Angle 1+0 [deg]");
    getStatistics().getHisto2D("Angle1+0_Angle1-0_124_Cut")->GetYaxis()->SetTitle("Angle 1-0 [deg]");




    getStatistics().createHistogram( new TH1F("timeScat31", "timeScat31" , 10000, -200.5, 200.5 ));
    getStatistics().getHisto1D("timeScat31")->GetXaxis()->SetTitle("timeScat31 [ns]");
    getStatistics().getHisto1D("timeScat31")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("timeScat32", "timeScat32" , 10000, -200.5, 200.5 ));
    getStatistics().getHisto1D("timeScat32")->GetXaxis()->SetTitle("timeScat32 [ns]");
    getStatistics().getHisto1D("timeScat32")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("timeScat41", "timeScat41" , 10000, -200.5, 200.5 ));
    getStatistics().getHisto1D("timeScat41")->GetXaxis()->SetTitle("timeScat41 [ns]");
    getStatistics().getHisto1D("timeScat41")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("timeScat42", "timeScat42" , 10000, -200.5, 200.5 ));
    getStatistics().getHisto1D("timeScat42")->GetXaxis()->SetTitle("timeScat42 [ns]");
    getStatistics().getHisto1D("timeScat42")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram(new TH2F("Scatter_of_3_from_1_and_2", "Scatter_of_3_from_1_and_2", 140, -7.5, 7.5, 140, -7.5, 7.5));
    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2")->GetXaxis()->SetTitle("Scatter Time 3-2 [ns]");
    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2")->GetYaxis()->SetTitle("Scatter Time 3-1 [ns]");


    getStatistics().createHistogram(new TH2F("Scatter_of_4_from_1_and_2", "Scatter_of_4_from_1_and_2", 140, -7.5, 7.5, 140, -7.5, 7.5));
    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2")->GetXaxis()->SetTitle("Scatter Time 4-2 [ns]");
    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2")->GetYaxis()->SetTitle("Scatter Time 4-1 [ns]");


    getStatistics().createHistogram( new TH1F("Angle_All", "Angle_All" , 360, -0.5, 360.5 ));
    getStatistics().getHisto1D("Angle_All")->GetXaxis()->SetTitle("Angle_All [deg]");
    getStatistics().getHisto1D("Angle_All")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH1F("Angle_All_Cut", "Angle_All_Cut" , 360, -0.5, 360.5 ));
    getStatistics().getHisto1D("Angle_All_Cut")->GetXaxis()->SetTitle("Angle_All_Cut [deg]");
    getStatistics().getHisto1D("Angle_All_Cut")->GetYaxis()->SetTitle("Counts");




    getStatistics().createHistogram(new TH2F("Scatter_of_3_from_1_and_2_AngleCut", "Scatter_of_3_from_1_and_2_AngleCut", 140, -7.5, 7.5, 140, -7.5, 7.5));
    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2_AngleCut")->GetXaxis()->SetTitle("Scatter Time 3-2 [ns]");
    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2_AngleCut")->GetYaxis()->SetTitle("Scatter Time 3-1 [ns]");


    getStatistics().createHistogram(new TH2F("Scatter_of_4_from_1_and_2_AngleCut", "Scatter_of_4_from_1_and_2_AngleCut", 140, -7.5, 7.5, 140, -7.5, 7.5));
    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2_AngleCut")->GetXaxis()->SetTitle("Scatter Time 4-2 [ns]");
    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2_AngleCut")->GetYaxis()->SetTitle("Scatter Time 4-1 [ns]");




    getStatistics().createHistogram(new TH2F("Scatter_of_3_from_1_and_2_For_32_and_41", "Scatter_of_3_from_1_and_2_For_32_and_41", 140, -7.5, 7.5, 140, -7.5, 7.5));
    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2_For_32_and_41")->GetXaxis()->SetTitle("Scatter Time 3-2 [ns]");
    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2_For_32_and_41")->GetYaxis()->SetTitle("Scatter Time 3-1 [ns]");


    getStatistics().createHistogram(new TH2F("Scatter_of_4_from_1_and_2_For_32_and_41", "Scatter_of_4_from_1_and_2_For_32_and_41", 140, -7.5, 7.5, 140, -7.5, 7.5));
    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2_For_32_and_41")->GetXaxis()->SetTitle("Scatter Time 4-2 [ns]");
    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2_For_32_and_41")->GetYaxis()->SetTitle("Scatter Time 4-1 [ns]");



    getStatistics().createHistogram(new TH2F("Scatter_of_3_from_1_and_2_For_31_and_42", "Scatter_of_3_from_1_and_2_For_31_and_42", 140, -7.5, 7.5, 140, -7.5, 7.5));
    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2_For_31_and_42")->GetXaxis()->SetTitle("Scatter Time 3-2 [ns]");
    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2_For_31_and_42")->GetYaxis()->SetTitle("Scatter Time 3-1 [ns]");


    getStatistics().createHistogram(new TH2F("Scatter_of_4_from_1_and_2_For_31_and_42", "Scatter_of_4_from_1_and_2_For_31_and_42", 140, -7.5, 7.5, 140, -7.5, 7.5));
    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2_For_31_and_42")->GetXaxis()->SetTitle("Scatter Time 4-2 [ns]");
    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2_For_31_and_42")->GetYaxis()->SetTitle("Scatter Time 4-1 [ns]");






    getStatistics().createHistogram( new TH1F("Phi20_23", "Phi20_23" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi20_23")->GetXaxis()->SetTitle("Phi20_23 [deg]");
    getStatistics().getHisto1D("Phi20_23")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH1F("Phi10_14", "Phi10_14" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi10_14")->GetXaxis()->SetTitle("Phi10_14 [deg]");
    getStatistics().getHisto1D("Phi10_14")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("Phi_1", "Phi_1" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi_1")->GetXaxis()->SetTitle("Phi_1 [deg]");
    getStatistics().getHisto1D("Phi_1")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("Phi_2", "Phi_2" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi_2")->GetXaxis()->SetTitle("Phi_2 [deg]");
    getStatistics().getHisto1D("Phi_2")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram(new TH2F("Phi10_14_vs_Phi20_23", "Phi10_14_vs_Phi20_23", 770, -385.5, 385.5, 770, -385.5, 385.5));
    getStatistics().getHisto2D("Phi10_14_vs_Phi20_23")->GetXaxis()->SetTitle("Phi10_14 [deg]");
    getStatistics().getHisto2D("Phi10_14_vs_Phi20_23")->GetYaxis()->SetTitle("Phi20_23 [deg]");


    getStatistics().createHistogram(new TH2F("Phi1_vs_Phi2", "Phi1_vs_Phi2", 180, 0.0, 180.0, 180, 0.0, 180.0));
    getStatistics().getHisto2D("Phi1_vs_Phi2")->GetXaxis()->SetTitle("Phi1 [deg]");
    getStatistics().getHisto2D("Phi1_vs_Phi2")->GetYaxis()->SetTitle("Phi2 [deg]");


    getStatistics().createHistogram( new TH1F("Phi20_24", "Phi20_24" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi20_24")->GetXaxis()->SetTitle("Phi20_24 [deg]");
    getStatistics().getHisto1D("Phi20_24")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH1F("Phi10_13", "Phi10_13" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi10_13")->GetXaxis()->SetTitle("Phi10_13 [deg]");
    getStatistics().getHisto1D("Phi10_13")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram(new TH2F("Phi10_13_vs_Phi20_24", "Phi10_13_vs_Phi20_24", 770, -385.5, 385.5, 770, -385.5, 385.5));
    getStatistics().getHisto2D("Phi10_13_vs_Phi20_24")->GetXaxis()->SetTitle("Phi10_13 [deg]");
    getStatistics().getHisto2D("Phi10_13_vs_Phi20_24")->GetYaxis()->SetTitle("Phi20_24 [deg]");




    getStatistics().createHistogram( new TH1F("theta", "theta" , 180, 0.0, 180.0 ));
    getStatistics().getHisto1D("theta")->GetXaxis()->SetTitle("theta [deg]");
    getStatistics().getHisto1D("theta")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram( new TH1F("theta1", "theta1" , 38500, -5.5, 380.5 ));
    getStatistics().getHisto1D("theta1")->GetXaxis()->SetTitle("theta1 [deg]");
    getStatistics().getHisto1D("theta1")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram( new TH1F("theta2", "theta2" , 38500, -5.5, 380.5 ));
    getStatistics().getHisto1D("theta2")->GetXaxis()->SetTitle("theta2 [deg]");
    getStatistics().getHisto1D("theta2")->GetYaxis()->SetTitle("Counts");





    getStatistics().createHistogram( new TH1F("theta_Cut", "theta_Cut" , 180, 0.0, 180.0 ));
    getStatistics().getHisto1D("theta_Cut")->GetXaxis()->SetTitle("theta_Cut [deg]");
    getStatistics().getHisto1D("theta_Cut")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram( new TH1F("theta1_Cut", "theta1_Cut" , 38500, -5.5, 380.5 ));
    getStatistics().getHisto1D("theta1_Cut")->GetXaxis()->SetTitle("theta1_Cut [deg]");
    getStatistics().getHisto1D("theta1_Cut")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram( new TH1F("theta2_Cut", "theta2_Cut" , 38500, -5.5, 380.5 ));
    getStatistics().getHisto1D("theta2_Cut")->GetXaxis()->SetTitle("theta2_Cut [deg]");
    getStatistics().getHisto1D("theta2_Cut")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram(new TH2F("Phi10_14_vs_Phi20_23_Cut", "Phi10_14_vs_Phi20_23_Cut", 770, -385.5, 385.5, 770, -385.5, 385.5));
    getStatistics().getHisto2D("Phi10_14_vs_Phi20_23_Cut")->GetXaxis()->SetTitle("Phi10_14 [deg]");
    getStatistics().getHisto2D("Phi10_14_vs_Phi20_23_Cut")->GetYaxis()->SetTitle("Phi20_23 [deg]");


    getStatistics().createHistogram(new TH2F("Phi1_vs_Phi2_Cut", "Phi1_vs_Phi2_Cut", 180, 0.0, 180.0, 180, 0.0, 180.0));
    getStatistics().getHisto2D("Phi1_vs_Phi2_Cut")->GetXaxis()->SetTitle("Phi1 [deg]");
    getStatistics().getHisto2D("Phi1_vs_Phi2_Cut")->GetYaxis()->SetTitle("Phi2 [deg]");


    getStatistics().createHistogram(new TH2F("Phi10_13_vs_Phi20_24_Cut", "Phi10_13_vs_Phi20_24_Cut", 770, -385.5, 385.5, 770, -385.5, 385.5));
    getStatistics().getHisto2D("Phi10_13_vs_Phi20_24_Cut")->GetXaxis()->SetTitle("Phi10_13 [deg]");
    getStatistics().getHisto2D("Phi10_13_vs_Phi20_24_Cut")->GetYaxis()->SetTitle("Phi20_14 [deg]");



    getStatistics().createHistogram(new TH2F("Phi1_vs_Phi2_Cut_Cut", "Phi1_vs_Phi2_Cut_Cut", 180, 0.0, 180.0, 180, 0.0, 180.0));
    getStatistics().getHisto2D("Phi1_vs_Phi2_Cut_Cut")->GetXaxis()->SetTitle("Phi1_Cut_Cut [deg]");
    getStatistics().getHisto2D("Phi1_vs_Phi2_Cut_Cut")->GetYaxis()->SetTitle("Phi2_Cut_Cut [deg]");




    getStatistics().createHistogram( new TH1F("Phi20_23_Cut", "Phi20_23_Cut" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi20_23_Cut")->GetXaxis()->SetTitle("Phi20_23_Cut [deg]");
    getStatistics().getHisto1D("Phi20_23_Cut")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH1F("Phi10_14_Cut", "Phi10_14_Cut" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi10_14_Cut")->GetXaxis()->SetTitle("Phi10_14_Cut [deg]");
    getStatistics().getHisto1D("Phi10_14_Cut")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("Phi_1_Cut", "Phi_1_Cut" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi_1_Cut")->GetXaxis()->SetTitle("Phi_1_Cut [deg]");
    getStatistics().getHisto1D("Phi_1_Cut")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("Phi_2_Cut", "Phi_2_Cut" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi_2_Cut")->GetXaxis()->SetTitle("Phi_2_Cut [deg]");
    getStatistics().getHisto1D("Phi_2_Cut")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH1F("Phi20_24_Cut", "Phi20_24_Cut" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi20_24_Cut")->GetXaxis()->SetTitle("Phi20_24_Cut [deg]");
    getStatistics().getHisto1D("Phi20_24_Cut")->GetYaxis()->SetTitle("Counts");



    getStatistics().createHistogram( new TH1F("Phi10_13_Cut", "Phi10_13_Cut" , 7700, -385.5, 385.5 ));
    getStatistics().getHisto1D("Phi10_13_Cut")->GetXaxis()->SetTitle("Phi10_13_Cut [deg]");
    getStatistics().getHisto1D("Phi10_13_Cut")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("theta_Cut_Cut", "theta_Cut_Cut" , 180, 0.0, 180.0 ));
    getStatistics().getHisto1D("theta_Cut_Cut")->GetXaxis()->SetTitle("theta_Cut_Cut [deg]");
    getStatistics().getHisto1D("theta_Cut_Cut")->GetYaxis()->SetTitle("Counts");


    getStatistics().createHistogram( new TH1F("theta1_Cut_Cut", "theta1_Cut_Cut" , 38500, -5.5, 380.5 ));
    getStatistics().getHisto1D("theta1_Cut_Cut")->GetXaxis()->SetTitle("theta1_Cut_Cut [deg]");
    getStatistics().getHisto1D("theta1_Cut_Cut")->GetYaxis()->SetTitle("Counts");

    getStatistics().createHistogram( new TH1F("theta2_Cut_Cut", "theta2_Cut_Cut" , 38500, -5.5, 380.5 ));
    getStatistics().getHisto1D("theta2_Cut_Cut")->GetXaxis()->SetTitle("theta2_Cut_Cut [deg]");
    getStatistics().getHisto1D("theta2_Cut_Cut")->GetYaxis()->SetTitle("Counts");





getStatistics().createHistogram(new TH2F("Phi1_vs_Phi2_Cut_30", "Phi1_vs_Phi2_Cut_30", 180, 0.0, 180.0, 180, 0.0, 180.0));
    getStatistics().getHisto2D("Phi1_vs_Phi2_Cut_30")->GetXaxis()->SetTitle("Phi1 [deg]");
    getStatistics().getHisto2D("Phi1_vs_Phi2_Cut_30")->GetYaxis()->SetTitle("Phi2 [deg]");





getStatistics().createHistogram(new TH2F("Phi1_vs_Phi2_Cut_10", "Phi1_vs_Phi2_Cut_10", 180, 0.0, 180.0, 180, 0.0, 180.0));
    getStatistics().getHisto2D("Phi1_vs_Phi2_Cut_10")->GetXaxis()->SetTitle("Phi1 [deg]");
    getStatistics().getHisto2D("Phi1_vs_Phi2_Cut_10")->GetYaxis()->SetTitle("Phi2 [deg]");



getStatistics().createHistogram(new TH2F("Phi1_vs_Phi2_Cut_5", "Phi1_vs_Phi2_Cut_5", 180, 0.0, 180.0, 180, 0.0, 180.0));
    getStatistics().getHisto2D("Phi1_vs_Phi2_Cut_5")->GetXaxis()->SetTitle("Phi1 [deg]");
    getStatistics().getHisto2D("Phi1_vs_Phi2_Cut_5")->GetYaxis()->SetTitle("Phi2 [deg]");


  getStatistics().createHistogram( new TH1F("theta_Cut_30", "theta_Cut_30" , 180, 0.0, 180.0 ));
    getStatistics().getHisto1D("theta_Cut_30")->GetXaxis()->SetTitle("theta_Cut_30 [deg]");
    getStatistics().getHisto1D("theta_Cut_30")->GetYaxis()->SetTitle("Counts");


 getStatistics().createHistogram( new TH1F("theta_Cut_10", "theta_Cut_10" , 180, 0.0, 180.0 ));
    getStatistics().getHisto1D("theta_Cut_10")->GetXaxis()->SetTitle("theta_Cut_10 [deg]");
    getStatistics().getHisto1D("theta_Cut_10")->GetYaxis()->SetTitle("Counts");

getStatistics().createHistogram( new TH1F("theta_Cut_5", "theta_Cut_5" , 180, 0.0, 180.0 ));
    getStatistics().getHisto1D("theta_Cut_5")->GetXaxis()->SetTitle("theta_Cut_5 [deg]");
    getStatistics().getHisto1D("theta_Cut_5")->GetYaxis()->SetTitle("Counts");



  }



  return true;
}



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


double CalcTOF(const JPetHit& Hit)
{

  double Dist = sqrt( pow(Hit.getPosX(), 2) + pow(Hit.getPosY(), 2) + pow(Hit.getPosZ(), 2) );

  double CalTime = Dist / 29.979246;  //Velocity of Light in cm/s, returns time in ns

  double HitTime = Hit.getTime() / 1000.0 ;

  double TOF =  (HitTime - CalTime);

  return TOF;
}




bool EventCategorizer::exec()
{

  if (auto timeWindow = dynamic_cast<const JPetTimeWindow* const>(fEvent)) {
    uint n = timeWindow->getNumberOfEvents();
    for (uint i = 0; i < n; ++i) {

      const auto& event = dynamic_cast<const JPetEvent&>(timeWindow->operator[](i));

      double restmass = 2 * (0.5109989461);
      double pi = 3.14159 ;
      if (event.getHits().size() == 4) {

        getStatistics().getHisto1D("Hits")->Fill(event.getHits().size());

        const JPetHit firstHit = event.getHits().at(0);
        const JPetHit secondHit = event.getHits().at(1);
        const JPetHit thirdHit = event.getHits().at(2);
        const JPetHit fourthHit = event.getHits().at(3);

        if (fabs(firstHit.getPosZ()) <= 23.0 && fabs(secondHit.getPosZ()) <= 23.0 && fabs(thirdHit.getPosZ()) <= 23.0 && fabs(fourthHit.getPosZ()) <= 23.0)

        {


////TOT first Hit////

          double fTOT = CalcTOT( firstHit );
          getStatistics().getHisto1D("TOT_first")->Fill(fTOT);
          getStatistics().getHisto1D("TOT")->Fill(fTOT);

          auto scinID_first = firstHit.getScintillator().getID();			//Control Spectras for first Hit
          auto timeDifference_first = firstHit.getTimeDiff() / 1000.0;
          getStatistics().getHisto2D("ScinID_vs_TOT")->Fill(fTOT, scinID_first);
          getStatistics().getHisto2D("DeltaT_vs_ScinID_big")->Fill(scinID_first, timeDifference_first);
          getStatistics().getHisto1D("ScinID")->Fill(scinID_first);
          getStatistics().getHisto1D("TimeDiff")->Fill(timeDifference_first);

          getStatistics().getHisto2D("ScinID_vs_TOT_1")->Fill(fTOT, scinID_first);



////TOT second Hit////

          double sTOT = CalcTOT( secondHit );
          getStatistics().getHisto1D("TOT_second")->Fill(sTOT);
          getStatistics().getHisto1D("TOT")->Fill(sTOT);

          auto scinID_second = secondHit.getScintillator().getID();		//Control Spectras for second Hit
          auto timeDifference_second = secondHit.getTimeDiff() / 1000.0;
          getStatistics().getHisto2D("ScinID_vs_TOT")->Fill(sTOT, scinID_second);
          getStatistics().getHisto2D("DeltaT_vs_ScinID_big")->Fill(scinID_second, timeDifference_second);
          getStatistics().getHisto1D("ScinID")->Fill(scinID_second);
          getStatistics().getHisto1D("TimeDiff")->Fill(timeDifference_second);

	  getStatistics().getHisto2D("ScinID_vs_TOT_2")->Fill(sTOT, scinID_second);



////TOT third Hit////

          double tTOT = CalcTOT( thirdHit );
          getStatistics().getHisto1D("TOT_third")->Fill(tTOT);
          getStatistics().getHisto1D("TOT")->Fill(tTOT);

          auto scinID_third = thirdHit.getScintillator().getID();		//Control Spectras for third Hit
          auto timeDifference_third = thirdHit.getTimeDiff() / 1000.0;
          getStatistics().getHisto2D("ScinID_vs_TOT")->Fill(tTOT, scinID_third);
          getStatistics().getHisto2D("DeltaT_vs_ScinID_big")->Fill(scinID_third, timeDifference_third);
          getStatistics().getHisto1D("ScinID")->Fill(scinID_third);
          getStatistics().getHisto1D("TimeDiff")->Fill(timeDifference_third);


	  getStatistics().getHisto2D("ScinID_vs_TOT_3")->Fill(tTOT, scinID_third);


////TOT fourth Hit////

          double foTOT = CalcTOT( fourthHit );
          getStatistics().getHisto1D("TOT_fourth")->Fill(foTOT);
          getStatistics().getHisto1D("TOT")->Fill(foTOT);

          auto scinID_fourth = fourthHit.getScintillator().getID();		//Control Spectras for fourth Hit
          auto timeDifference_fourth = fourthHit.getTimeDiff() / 1000.0;
          getStatistics().getHisto2D("ScinID_vs_TOT")->Fill(foTOT, scinID_fourth);
          getStatistics().getHisto2D("DeltaT_vs_ScinID_big")->Fill(scinID_fourth, timeDifference_fourth);
          getStatistics().getHisto1D("ScinID")->Fill(scinID_fourth);
          getStatistics().getHisto1D("TimeDiff")->Fill(timeDifference_fourth);


          getStatistics().getHisto2D("ScinID_vs_TOT_4")->Fill(foTOT, scinID_fourth);


//TOF Correct and Order in Time//

         double fTOF =  CalcTOF( firstHit );
	 double sTOF =  CalcTOF( secondHit );
	 double tTOF =  CalcTOF( thirdHit );
	 double foTOF = CalcTOF( fourthHit );
 
	 std::vector<double> TOF1234;
         TOF1234.push_back( fTOF );
         TOF1234.push_back( sTOF );
         TOF1234.push_back( tTOF );
         TOF1234.push_back( foTOF );

         std::sort( TOF1234.begin(), TOF1234.begin() + 3 );


	if(fTOF < sTOF && sTOF < tTOF && tTOF < foTOF)

	{

	

////TOT Check////



          if (fTOT <= 30.0 && fTOT >= 10.0 && sTOT <= 30.0 && sTOT >= 10.0) {

            if ((tTOT < sTOT) || (tTOT < fTOT)) {

              if ((foTOT < sTOT) || (foTOT < fTOT))

              {



                getStatistics().getHisto1D("TOT_first_Cut")->Fill(fTOT);
                getStatistics().getHisto1D("TOT_second_Cut")->Fill(sTOT);
                getStatistics().getHisto1D("TOT_third_Cut")->Fill(tTOT);
                getStatistics().getHisto1D("TOT_fourth_Cut")->Fill(foTOT);



//Angle - 2D //



		double Angle_2D_1 = firstHit.getBarrelSlot().getTheta();
		double Angle_2D_2 = secondHit.getBarrelSlot().getTheta();
		double Angle_2D_3 = thirdHit.getBarrelSlot().getTheta();
		double Angle_2D_4 = fourthHit.getBarrelSlot().getTheta();



// 2D Angle between all four hits//

		double Angle_2D_12 = Angle_2D_2 - Angle_2D_1 ;
		double Angle_2D_13 = Angle_2D_3 - Angle_2D_1 ;
		double Angle_2D_14 = Angle_2D_4 - Angle_2D_1 ;
		double Angle_2D_23 = Angle_2D_3 - Angle_2D_2 ;
		double Angle_2D_24 = Angle_2D_4 - Angle_2D_2 ;
		double Angle_2D_34 = Angle_2D_4 - Angle_2D_3 ;



//Angle 12//


                double scalarProd12 = firstHit.getPosX() * secondHit.getPosX() + firstHit.getPosY() * secondHit.getPosY() + firstHit.getPosZ() * secondHit.getPosZ();
                double magProd12 = sqrt( ( pow(firstHit.getPosX(), 2)  // Pos in cm
                                           + pow(firstHit.getPosY(), 2)
                                           + pow(firstHit.getPosZ(), 2) ) * ( pow(secondHit.getPosX(), 2)
                                               + pow(secondHit.getPosY(), 2)
                                               + pow(secondHit.getPosZ(), 2) ) );
                double Angle12 = acos( scalarProd12 / magProd12 ) * 180.0 / 3.14159265;



//Angle 13//


                double scalarProd13 = firstHit.getPosX() * thirdHit.getPosX() + firstHit.getPosY() * thirdHit.getPosY() + firstHit.getPosZ() * thirdHit.getPosZ();
                double magProd13 = sqrt( ( pow(firstHit.getPosX(), 2)  // Pos in cm
                                           + pow(firstHit.getPosY(), 2)
                                           + pow(firstHit.getPosZ(), 2) ) * ( pow(thirdHit.getPosX(), 2)
                                               + pow(thirdHit.getPosY(), 2)
                                               + pow(thirdHit.getPosZ(), 2) ) );
                double Angle13 = acos( scalarProd13 / magProd13 ) * 180.0 / 3.14159265;



//Angle 14//


                double scalarProd14 = firstHit.getPosX() * fourthHit.getPosX() + firstHit.getPosY() * fourthHit.getPosY() + firstHit.getPosZ() * fourthHit.getPosZ();
                double magProd14 = sqrt( ( pow(firstHit.getPosX(), 2)  // Pos in cm
                                           + pow(firstHit.getPosY(), 2)
                                           + pow(firstHit.getPosZ(), 2) ) * ( pow(fourthHit.getPosX(), 2)
                                               + pow(fourthHit.getPosY(), 2)
                                               + pow(fourthHit.getPosZ(), 2) ) );
                double Angle14 = acos( scalarProd14 / magProd14 ) * 180.0 / 3.14159265;



//Angle 23//


                double scalarProd23 = secondHit.getPosX() * thirdHit.getPosX() + secondHit.getPosY() * thirdHit.getPosY() + secondHit.getPosZ() * thirdHit.getPosZ();
                double magProd23 = sqrt( ( pow(secondHit.getPosX(), 2)  // Pos in cm
                                           + pow(secondHit.getPosY(), 2)
                                           + pow(secondHit.getPosZ(), 2) ) * ( pow(thirdHit.getPosX(), 2)
                                               + pow(thirdHit.getPosY(), 2)
                                               + pow(thirdHit.getPosZ(), 2) ) );
                double Angle23 = acos( scalarProd23 / magProd23 ) * 180.0 / 3.14159265;



//Angle 24//

                double scalarProd24 = secondHit.getPosX() * fourthHit.getPosX() + secondHit.getPosY() * fourthHit.getPosY() + secondHit.getPosZ() * fourthHit.getPosZ();
                double magProd24 = sqrt( ( pow(secondHit.getPosX(), 2)  // Pos in cm
                                           + pow(secondHit.getPosY(), 2)
                                           + pow(secondHit.getPosZ(), 2) ) * ( pow(fourthHit.getPosX(), 2)
                                               + pow(fourthHit.getPosY(), 2)
                                               + pow(fourthHit.getPosZ(), 2) ) );
                double Angle24 = acos( scalarProd24 / magProd24 ) * 180.0 / 3.14159265;




//Angle 34//


                double scalarProd34 = thirdHit.getPosX() * fourthHit.getPosX() + thirdHit.getPosY() * fourthHit.getPosY() + thirdHit.getPosZ() * fourthHit.getPosZ();
                double magProd34 = sqrt( ( pow(thirdHit.getPosX(), 2)   // Pos in cm
                                           + pow(thirdHit.getPosY(), 2)
                                           + pow(thirdHit.getPosZ(), 2) ) * ( pow(fourthHit.getPosX(), 2)
                                               + pow(fourthHit.getPosY(), 2)
                                               + pow(fourthHit.getPosZ(), 2) ) );
                double Angle34 = acos( scalarProd34 / magProd34 ) * 180.0 / 3.14159265;



                std::vector<double> angles123;
                angles123.push_back( Angle12 );
                angles123.push_back( Angle23 );
                angles123.push_back( Angle13 );
                std::sort( angles123.begin(), angles123.begin() + 3 );

                getStatistics().getHisto2D("Angle1+0_Angle1-0_123")->Fill(angles123[1] + angles123[0], angles123[1] - angles123[0]);




                std::vector<double> angles124;
                angles124.push_back( Angle12 );
                angles124.push_back( Angle24 );
                angles124.push_back( Angle14 );
                std::sort( angles124.begin(), angles124.begin() + 3 );

                getStatistics().getHisto2D("Angle1+0_Angle1-0_124")->Fill(angles124[1] + angles124[0], angles124[1] - angles124[0]);



                if ((angles123[1] + angles123[0]) <= 185.0 && (angles123[1] + angles123[0]) >= 175.0 && (angles124[1] + angles124[0]) <= 185.0 && (angles124[1] + angles124[0]) >= 175.0)

                {


                  getStatistics().getHisto2D("Angle1+0_Angle1-0_123_Cut")->Fill(angles123[1] + angles123[0], angles123[1] - angles123[0]);
                  getStatistics().getHisto2D("Angle1+0_Angle1-0_124_Cut")->Fill(angles124[1] + angles124[0], angles124[1] - angles124[0]);



                  double firstHitTime = firstHit.getTime() / 1000.0;
                  double secondHitTime = secondHit.getTime() / 1000.0;
                  double thirdHitTime = thirdHit.getTime() / 1000.0;
                  double fourthHitTime = fourthHit.getTime() / 1000.0;



                  double scattimeDiff31 = (thirdHitTime - firstHitTime);
                  float scatDist31 = sqrt(pow(thirdHit.getPosX() - firstHit.getPosX(), 2) // Pos in cm
                                          + pow(thirdHit.getPosY() - firstHit.getPosY(), 2)
                                          + pow(thirdHit.getPosZ() - firstHit.getPosZ(), 2));
                  scatDist31 = scatDist31 / 29.979246;
                  double timeScat31 = (scattimeDiff31 - scatDist31);
                  getStatistics().getHisto1D("timeScat31")->Fill(timeScat31);



                  double scattimeDiff32 = (thirdHitTime - secondHitTime);
                  float scatDist32 = sqrt(pow(thirdHit.getPosX() - secondHit.getPosX(), 2) // Pos in cm
                                          + pow(thirdHit.getPosY() - secondHit.getPosY(), 2)
                                          + pow(thirdHit.getPosZ() - secondHit.getPosZ(), 2));
                  scatDist32 = scatDist32 / 29.979246;
                  double timeScat32 = (scattimeDiff32 - scatDist32);
                  getStatistics().getHisto1D("timeScat32")->Fill(timeScat32);




                  double scattimeDiff41 = (fourthHitTime - firstHitTime);
                  float scatDist41 = sqrt(pow(fourthHit.getPosX() - firstHit.getPosX(), 2) // Pos in cm
                                          + pow(fourthHit.getPosY() - firstHit.getPosY(), 2)
                                          + pow(fourthHit.getPosZ() - firstHit.getPosZ(), 2));
                  scatDist41 = scatDist41 / 29.979246;
                  double timeScat41 = (scattimeDiff41 - scatDist41);
                  getStatistics().getHisto1D("timeScat41")->Fill(timeScat41);



                  double scattimeDiff42 = (fourthHitTime - secondHitTime);
                  float scatDist42 = sqrt(pow(fourthHit.getPosX() - secondHit.getPosX(), 2) // Pos in cm
                                          + pow(fourthHit.getPosY() - secondHit.getPosY(), 2)
                                          + pow(fourthHit.getPosZ() - secondHit.getPosZ(), 2));
                  scatDist42 = scatDist42 / 29.979246;
                  double timeScat42 = (scattimeDiff42 - scatDist42);
                  getStatistics().getHisto1D("timeScat42")->Fill(timeScat42);



                  getStatistics().getHisto2D("Scatter_of_3_from_1_and_2")->Fill(timeScat32, timeScat31);
                  getStatistics().getHisto2D("Scatter_of_4_from_1_and_2")->Fill(timeScat42, timeScat41);

                  getStatistics().getHisto1D("Angle_All")->Fill(Angle12);
                  getStatistics().getHisto1D("Angle_All")->Fill(Angle13);
                  getStatistics().getHisto1D("Angle_All")->Fill(Angle14);
                  getStatistics().getHisto1D("Angle_All")->Fill(Angle23);
                  getStatistics().getHisto1D("Angle_All")->Fill(Angle24);
                  getStatistics().getHisto1D("Angle_All")->Fill(Angle34);


                 /* if (Angle12 > 10.0 && Angle13 > 10.0 && Angle14 > 10.0 && Angle23 > 10.0 && Angle24 > 10.0 && Angle34 > 10.0)

                  {
*/
                    getStatistics().getHisto1D("Angle_All_Cut")->Fill(Angle12);
                    getStatistics().getHisto1D("Angle_All_Cut")->Fill(Angle13);
                    getStatistics().getHisto1D("Angle_All_Cut")->Fill(Angle14);
                    getStatistics().getHisto1D("Angle_All_Cut")->Fill(Angle23);
                    getStatistics().getHisto1D("Angle_All_Cut")->Fill(Angle24);
                    getStatistics().getHisto1D("Angle_All_Cut")->Fill(Angle34);


                    getStatistics().getHisto2D("Scatter_of_3_from_1_and_2_AngleCut")->Fill(timeScat32, timeScat31);
                    getStatistics().getHisto2D("Scatter_of_4_from_1_and_2_AngleCut")->Fill(timeScat42, timeScat41);


                    double Check_For_32 = pow((timeScat32 - 0.5 ), 2) + pow((timeScat31 + 2.5), 2);
                    double Check_For_41 = pow((timeScat42 + 2.5 ), 2) + pow((timeScat41 - 1.0), 2);


                    double Check_For_31 = pow((timeScat32 + 2.5 ), 2) + pow((timeScat31 - 0.5), 2);
                    double Check_For_42 = pow((timeScat42 - 0.75 ), 2) + pow((timeScat41 + 2.5), 2);




		      getStatistics().getHisto1D("ScinID_After_All_Cuts")->Fill(scinID_first);
                      getStatistics().getHisto1D("ScinID_After_All_Cuts")->Fill(scinID_second);
                      getStatistics().getHisto1D("ScinID_After_All_Cuts")->Fill(scinID_third);
                      getStatistics().getHisto1D("ScinID_After_All_Cuts")->Fill(scinID_fourth);






                    if (Check_For_32 <= 4.0 && Check_For_41 <= 4.0)


                    {
                      

                      getStatistics().getHisto2D("Scatter_of_3_from_1_and_2_For_32_and_41")->Fill(timeScat32, timeScat31);
                      getStatistics().getHisto2D("Scatter_of_4_from_1_and_2_For_32_and_41")->Fill(timeScat42, timeScat41);


                      double x20 = secondHit.getPosX();
                      double y20 = secondHit.getPosY();
                      double z20 = secondHit.getPosZ();


                      double x23 = (thirdHit.getPosX() - secondHit.getPosX());
                      double y23 = (thirdHit.getPosY() - secondHit.getPosY());
                      double z23 = (thirdHit.getPosZ() - secondHit.getPosZ());

                      double cx23_20 = ((y20 * z23) - (z20 * y23));
                      double cy23_20 = -((x20 * z23) - (z20 * x23));
                      double cz23_20 = ((x20 * y23) - (y20 * x23));

                      double nume20_23 = ((x20 * x23) + (y20 * y23) + (z20 + z23));
                      double deno20_23 = sqrt(pow(x20, 2) + pow(y20, 2) + pow(z20, 2)) * sqrt(pow(x23, 2) + pow(y23, 2) + pow(z23, 2));

                      double Phi20_23 = (acos(nume20_23 / deno20_23) * 180.0 / pi);

                      getStatistics().getHisto1D("Phi20_23")->Fill(Phi20_23);
                      getStatistics().getHisto1D("Phi_2")->Fill(Phi20_23);


                      double x10 = firstHit.getPosX();
                      double y10 = firstHit.getPosY();
                      double z10 = firstHit.getPosZ();


                      double x14 = (fourthHit.getPosX() - firstHit.getPosX());
                      double y14 = (fourthHit.getPosY() - firstHit.getPosY());
                      double z14 = (fourthHit.getPosZ() - firstHit.getPosZ());


                      double cx14_10 = ((y10 * z14) - (z10 * y14));
                      double cy14_10 = -((x10 * z14) - (z10 * x14));
                      double cz14_10 = ((x10 * y14) - (y10 * x14));


                      double nume10_14 = ((x10 * x14) + (y10 * y14) + (z10 * z14));
                      double deno10_14 = sqrt(pow(x10, 2) + pow(y10, 2) + pow(z10, 2)) * sqrt(pow(x14, 2) + pow(y14, 2) + pow(z14, 2));

                      double Phi10_14 = (acos(nume10_14 / deno10_14) * 180.0 / pi);


                      getStatistics().getHisto1D("Phi10_14")->Fill(Phi10_14);
                      getStatistics().getHisto1D("Phi_1")->Fill(Phi10_14);



                      getStatistics().getHisto2D("Phi10_14_vs_Phi20_23")->Fill(Phi10_14 , Phi20_23);
                      getStatistics().getHisto2D("Phi1_vs_Phi2")->Fill(Phi10_14 , Phi20_23);



                      double numerator1 = ((cx23_20 * cx14_10) + (cy23_20 * cy14_10) + (cz23_20 * cz14_10));
                      double denominator1 = sqrt(pow(cx23_20, 2) + pow(cy23_20, 2) + pow(cz23_20, 2)) * sqrt(pow(cx14_10, 2) + pow(cy14_10, 2) + pow(cz14_10, 2));

                      double theta1 = (acos((numerator1) / (denominator1)) * 180.0 / pi );

                      getStatistics().getHisto1D("theta")->Fill(theta1);
                      getStatistics().getHisto1D("theta1")->Fill(theta1);


                      double  Phi_check_1 =  pow((Phi20_23 - 81.66), 2) + pow((Phi10_14 - 81.66), 2);


                      if ( Phi_check_1 < 900.00 )

                      {

                        getStatistics().getHisto1D("theta_Cut")->Fill(theta1);
                        getStatistics().getHisto1D("theta1_Cut")->Fill(theta1);

                        getStatistics().getHisto2D("Phi10_14_vs_Phi20_23_Cut")->Fill(Phi10_14 , Phi20_23);
                      

                        getStatistics().getHisto1D("Phi20_23_Cut")->Fill(Phi20_23);
                        getStatistics().getHisto1D("Phi_1_Cut")->Fill(Phi10_14);

                        getStatistics().getHisto1D("Phi10_14_Cut")->Fill(Phi10_14);
                        getStatistics().getHisto1D("Phi_2_Cut")->Fill(Phi20_23);



	getStatistics().getHisto2D("Phi1_vs_Phi2_Cut_30")->Fill(Phi10_14 , Phi20_23);
	getStatistics().getHisto1D("theta_Cut_30")->Fill(theta1);

			if(Phi_check_1 < 100.00){

			getStatistics().getHisto2D("Phi1_vs_Phi2_Cut_10")->Fill(Phi10_14 , Phi20_23);
			getStatistics().getHisto1D("theta_Cut_10")->Fill(theta1);

			if(Phi_check_1 < 25.00){

			getStatistics().getHisto2D("Phi1_vs_Phi2_Cut_5")->Fill(Phi10_14 , Phi20_23);
			getStatistics().getHisto1D("theta_Cut_5")->Fill(theta1);

                       // double Phi_Check_1 = pow((Phi20_23 - 90.0), 2) + pow((Phi10_14 - 90.0), 2);

                      /*  if (Phi_Check_1 <= 400.0) {

                          getStatistics().getHisto2D("Phi1_vs_Phi2_Cut_Cut")->Fill(Phi10_14 , Phi20_23);

                          getStatistics().getHisto1D("theta_Cut_Cut")->Fill(theta1);

                          getStatistics().getHisto1D("theta1_Cut_Cut")->Fill(theta1);

*/
			 
				

			
			}



                        }


                      }

                    }



                    else if (Check_For_31 <= 4.0 && Check_For_42 <= 4.0 ) {


                      getStatistics().getHisto2D("Scatter_of_3_from_1_and_2_For_31_and_42")->Fill(timeScat32, timeScat31);
                      getStatistics().getHisto2D("Scatter_of_4_from_1_and_2_For_31_and_42")->Fill(timeScat42, timeScat41);



                      double x20 = secondHit.getPosX();
                      double y20 = secondHit.getPosY();
                      double z20 = secondHit.getPosZ();


                      double x24 = (fourthHit.getPosX() - secondHit.getPosX());
                      double y24 = (fourthHit.getPosY() - secondHit.getPosY());
                      double z24 = (fourthHit.getPosZ() - secondHit.getPosZ());


                      double cx24_20 = ((y20 * z24) - (z20 * y24));
                      double cy24_20 = -((x20 * z24) - (z20 * x24));
                      double cz24_20 = ((x20 * y24) - (y20 * x24));


                      double nume20_24 = ((x20 * x24) + (y20 * y24) + (z20 + z24));
                      double deno20_24 = sqrt(pow(x20, 2) + pow(y20, 2) + pow(z20, 2)) * sqrt(pow(x24, 2) + pow(y24, 2) + pow(z24, 2));

                      double Phi20_24 = (acos(nume20_24 / deno20_24) * 180.0 / pi);

                      getStatistics().getHisto1D("Phi20_24")->Fill(Phi20_24);
                      getStatistics().getHisto1D("Phi_2")->Fill(Phi20_24);


                      double x10 = firstHit.getPosX();
                      double y10 = firstHit.getPosY();
                      double z10 = firstHit.getPosZ();


                      double x13 = (thirdHit.getPosX() - firstHit.getPosX());
                      double y13 = (thirdHit.getPosY() - firstHit.getPosY());
                      double z13 = (thirdHit.getPosZ() - firstHit.getPosZ());

                      double cx13_10 = ((y10 * z13) - (z10 * y13));
                      double cy13_10 = -((x10 * z13) - (z10 * x13));
                      double cz13_10 = ((x10 * y13) - (y10 * x13));



                      double nume10_13 = ((x10 * x13) + (y10 * y13) + (z10 * z13));
                      double deno10_13 = sqrt(pow(x10, 2) + pow(y10, 2) + pow(z10, 2)) * sqrt(pow(x13, 2) + pow(y13, 2) + pow(z13, 2));

                      double Phi10_13 = (acos(nume10_13 / deno10_13) * 180.0 / pi);


                      getStatistics().getHisto1D("Phi10_13")->Fill(Phi10_13);
                      getStatistics().getHisto1D("Phi_1")->Fill(Phi10_13);



                      getStatistics().getHisto2D("Phi10_13_vs_Phi20_24")->Fill(Phi10_13 , Phi20_24);
                      getStatistics().getHisto2D("Phi1_vs_Phi2")->Fill(Phi10_13 , Phi20_24);



                      double numerator2 = (cx24_20 * cx13_10) + (cy24_20 * cy13_10) + (cz24_20 * cz13_10);
                      double denominator2 = sqrt(pow(cx24_20, 2) + pow(cy24_20, 2) + pow(cz24_20, 2)) * sqrt(pow(cx13_10, 2) + pow(cy13_10, 2) + pow(cz13_10, 2));

                      double theta2 = (acos((numerator2) / (denominator2)) * 180.0 / pi);

                      getStatistics().getHisto1D("theta")->Fill(theta2);
                      getStatistics().getHisto1D("theta2")->Fill(theta2);



                      double  Phi_check_2 =  pow((Phi20_24 - 81.66), 2) + pow((Phi10_13 - 81.66), 2);


                      if ( Phi_check_2 < 900.00 )

                      {

                        
                        getStatistics().getHisto1D("theta2_Cut")->Fill(theta2);

                        getStatistics().getHisto2D("Phi10_13_vs_Phi20_24_Cut")->Fill(Phi10_13 , Phi20_24);
                        getStatistics().getHisto2D("Phi1_vs_Phi2_Cut")->Fill(Phi10_13 , Phi20_24);

                        getStatistics().getHisto1D("Phi20_24_Cut")->Fill(Phi20_24);
                        getStatistics().getHisto1D("Phi_1_Cut")->Fill(Phi10_13);

                        getStatistics().getHisto1D("Phi10_13_Cut")->Fill(Phi10_13);
                        getStatistics().getHisto1D("Phi_2_Cut")->Fill(Phi20_24);


	//getStatistics().getHisto2D("Phi1_vs_Phi2_Cut_30")->Fill(Phi10_14 , Phi20_23);

	getStatistics().getHisto2D("Phi1_vs_Phi2_Cut_30")->Fill(Phi10_13 , Phi20_24);
	getStatistics().getHisto1D("theta_Cut_30")->Fill(theta2);
		if ( Phi_check_2 < 100.00 )

                      {


	getStatistics().getHisto2D("Phi1_vs_Phi2_Cut_10")->Fill(Phi10_13 , Phi20_24);
	getStatistics().getHisto1D("theta_Cut_10")->Fill(theta2);



		if ( Phi_check_2 < 25.00 )

                      {



	getStatistics().getHisto2D("Phi1_vs_Phi2_Cut_5")->Fill(Phi10_13 , Phi20_24);
	getStatistics().getHisto1D("theta_Cut_5")->Fill(theta2);

                       // double Phi_Check_2 = pow((Phi20_24 - 90.0), 2) + pow((Phi10_13 - 90.0), 2);

  /*                     if (Phi_Check_2 <= 400.0) {

                          getStatistics().getHisto2D("Phi1_vs_Phi2_Cut_Cut")->Fill(Phi10_13 , Phi20_24);

                          getStatistics().getHisto1D("theta_Cut_Cut")->Fill(theta2);

                          getStatistics().getHisto1D("theta2_Cut_Cut")->Fill(theta2);
*/

                        }

			}




                      }







                    }





                  }




                }




              }


            }


          }





        }


      }

    }


  }

//}
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
