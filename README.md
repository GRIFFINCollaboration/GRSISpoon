GRSISpoon
=========

Welcome to GRSISpoon (GRSI Sort Program for Online / Offline Nuclear data), a web-facing nuclear data sorter being developed by the GRIFFIN Collaboration.

##The Plan

In light of GRIFFIN's enormous (200 TB/week) throughput of raw data to disk, a new fast sort code GRSISpoon is being developed to meet user needs.  Beyond algorithmic efficiency goals, the developers are taking this opportunity to build a modular, well factored suite of tools around this sort code that will allow it to be easily used on any experimental dataset or GEANT4 simulation, with minimal case-specific coding required.  The overall program structure is a chain modularized as follows:

1.  Data format interface tool: a preprocessor that translates any arbitrary data format (GRIFFIN, TIGRESS, GPS, GEANT4, whatever) into the format needed by GRSISpoon.  This is the ONLY piece of experiment specific code; everything downstream from here must be strictly experiment agnostic.  Developers must produce a well defined specification of the data format required so third parties can write their own preprocessor, and the preprocessor logic must be factored in a way that makes it trivial to swap out.

2.  Sort core: the sort core does the computational heavy lifting of sorting the data into the requisite structure.  Sorting the raw data is expected to be an O(n) process, since data needs only be replayed once and grouped by trigger ID.  The sort core should be able to produce ROOT trees / ntuples, as well as flat histograms.  Furthermore, the sort core must have an exposed API that an external server can control it by.

3.  Independent web server: a relatively simple web server that waits for AJAX get requests from a web page, parses them into commands for the sort core's API, and returns the result in a way that can be parsed by the page's visualization.  

4.  Visualization web page: a web app sitting on top of the server described above, which will allow any Chrome or Firefox user to visualize (via the gammaSpectrum framework) any histogram that can be defined by the sort core's API (specific feature list TBD).

<img src = https://github.com/GRIFFINCollaboration/GRSISpoon/blob/master/img/GRSISpoonFlow.png?raw=true></img>

The above diagram visualizes some of the details of where data goes and who does what with it in GRSISpoon.

##Usage

GRSISpoon relies on MIDAS post-January 2014 and ROOT 5.34; it has successfully compiled and run on 64 bit SL6 and Ubuntu.  With the dependencies installed and working, follow these steps to get GRSISpoon off the ground:

1. Run the setup script, SOURCEME.sh or .csh depending on your shell preference.  Make sure the paths to ROOT and MIDAS are set correctly therein!  Note that if MIDASSYS and ROOTSYS environment vairables were set before running this script, this script won't overwrite them, so ensure they are set correctly first, or that they are unset initially and pointed correctly in the script.
2. do `make` at GRSISpoon's root; hopefully everything compiles
3. `./bin/grsisort` launches the program in interactive mode

Alternatively, you can launch as `./bin/grsisort -p 9091` to launch a server listening on port 9091 (or whatever port you want).  More usage docs coming soon!

##Testing

Currently, the test suite for GRSISpoon is a simple procedure:

1.  Sort the benchmark file ./testSuite/run27422_000.mid
2.  Run the root macro `root -b -l ./testSuite/testGauntlet.C`
3.  The macro will tell you all is well (so pls PR!), or that something failed (pls fix or justify before PR).

The test just compares the tree you get from sorting the benchmark file with the tree I got from sorting the benchmark file, and demands they are identical up to timestamps.  As an added bonus, `testGauntlet.C` should serve as an example of how to read GRSISpoon's ROOT output.

Please note that passing the test suite is *required* for merging code into the collaboration's repo!  If you think there is a good reason why your changes don't match, open an issue to discuss the situation before attempting a merge.

##Style Conventions
GRSISpoon code obeys the [Kronut Style Convention](http://root.cern.ch/drupal/content/c-coding-conventions).  A quick

    indent -i3 -kr -nut -l120 
    
should clean up any askew formatting.
