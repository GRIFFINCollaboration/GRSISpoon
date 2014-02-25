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

GRSISpoon maintains a test suite to check that new code hasn't broken any existing features, and to ensure that bugs and regressions do not re-emerge when identified.  When working on a bug, please add whatever tests you are using to track down the bug to either of the independent test suites or the in-situ run flag.  When producing a new feature, please also construct a set of tests that check all assumptions made in its construction.

Currently, the test suite for GRSISpoon has two steps: fragment building and physics testing.  Both must pass with no complaints, or your changes will be reverted!  If you think there is a good reason why your changes make the tests fail, open an issue to discuss the situation before attempting a merge.

####Fragment Building

This simple test just makes sure raw data builds to the same fragment tree it always has.  The data is small and ships with GRSISpoon; to run the test, do:

1.  Sort the benchmark file ./testSuite/run27422_000.mid
2.  Run the root macro `root -b -l ./testSuite/testGauntlet.C`
3.  The macro will tell you all is well (so pls PR!), or that something failed (pls fix or justify before PR).

The test just compares the tree you get from sorting the benchmark file with the tree I got from sorting the benchmark file, and demands they are identical up to timestamps.

####Physics Testing
`./testSuite/testPhysics.C` runs a battery of tests to check that sensible physics results are being extracted when sorting a run of source data.  To run it:

1.  Near the top of `testPhysics.C` there is an example of how to compile it; change the paths to something appropriate, make sure you've sourced `SOURCEME.(c)sh`, and compile.
2.  The raw data for this test is too big to ship with the package; current prescribed file is at `grsmid01.triumf.ca:/data1/tigress/GRSISpoonEffTest/fragment27495_000.root`
3.  Run as `./testPhysics fragment27495_000.root`.

The physics testing runs the following tests [X].  

##Style Conventions
GRSISpoon code obeys the [Kronut Style Convention](http://root.cern.ch/drupal/content/c-coding-conventions).  A quick

    indent -i3 -kr -nut -l120 
    
should clean up any askew formatting.
