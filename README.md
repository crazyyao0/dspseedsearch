# dspseedsearch
This project is used to search the whole seed ranges for the game Dyson Sphere Program. Find the best seed meets your requirements.

It currently works for game version 0.9.26

I tried with the following conditions.
- The star should be type O, which is the best star type for dyson sphere
- The star is within 5LY from the birth planet.
- The galaxy contains all kinds of rare resources except mono mag ore, including sulphuric acid
- The galaxy has at least one Gas planet which produces hydrogen and deuterium. hydrogen is much useful than fire ice, because fire ice can be gatherd from the other plannets
- The galaxy's first planet is tidal locked.

It finishes in 45 minutes with about 1000 cores and there are more than 800 records meets the requirement. you can find the result in result.txt and csv.txt

To run the project
 1. You will need one feed server and several worker servers. 
 2. Modify DSPSeedSearch.py. Input the feed server ip address. 
 3. Run python3 feedserver.py on the feed server. 
 4. Run python3 DSPSeedSearch.py on each worker servers.
 5. Wait until 32768 batches have been processed by the worker servers. 

To compile the project

    g++ -O3 -DSUPPORT_AVX2 -mavx2 -o DSPSeedCalc DSPSeedCalc.cpp

Part of the code in LDB.hpp is generate by dsptheme.py and ThemeProtoSet.xml




