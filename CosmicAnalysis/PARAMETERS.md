# Cosmics stream - data selection of cosmic radiation events parameters

## Contents
Description of available parameters in CosmicAnalysis example.
Note that configuration/calibration files can be obtained from [PetWiki](http://koza.if.uj.edu.pl/petwiki/index.php/Default_settings_and_parameters_used_in_the_analyses)

- `Save_Control_Histograms_bool`  
Common for each module, if set to `true`, in the output `ROOT` files folder with statistics will contain control histograms. Set to `false` if histograms not needed.

- `TimeWindowCreator_MainStrip_int`  
Dedicated for files with data from measurement with Reference Detector - it denotes which `ID` has the reference scintillator. If option not set, part with reference detector is ignored

- `TimeWindowCreator_MinTime_float`  
Time Slots have certain duration for specific runs, minimum time is usually negative, default value `-1*10^6 ps`

- `TimeWindowCreator_MaxTime_float`  
default value `0.0 ps`

- `TimeCalibLoader_ConfigFile_std::string`  
name of ASCII file of required structure, containing time calibrations, specific for each run

- `SignalFinder_EdgeMaxTime_float`  
time window for matching Signal Channels on Leading Edge. Default value: `5 000 ps`

- `SignalFinder_LeadTrailMaxTime_float`  
time window for matching Signal Channels on the same thresholds from Leading and Trailing edge. Default value: `25 000 ps`

- `HitFinder_VelocityFile_std::string`  
name of ASCII file of required format, containing values of effective velocities of light in each scintillator

- `HitFinder_ABTimeDiff_float`  
time window for matching Signals on the same scintillator and different sides. Default value: `6 000 ps`

- `HitFinder_RefDetScinID_int`  
`ID` of Reference Detector Scintillator, needed for creating reference hits

- `EventFinder_EventTime_float`  
time window for grouping hits in one event. Default value `5 000 ps`

- `EventFinder_MinEventMultiplicity_int`  
events of minimum multiplicity will only be saved in output file. Default value is 1, so all events are saved.

- `EventCategorizer_MinCosmicTOT_float`  
value of minimum `Time over Threshold` of a hit in the to classify this event as `Cosmic`
