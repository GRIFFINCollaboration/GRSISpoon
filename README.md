GRSISpoon
=========

Welcome to GRSISpoon (GRSI Sort Program for Online / Offline Nuclear data), a web-facing nuclear data sorter being developed by the GRIFFIN Collaboration.

##The Plan

In light of GRIFFIN's enormous (200 TB/week) throughput of raw data to disk, a new fast sort code GRSISpoon is being developed to meet user needs.  Beyond algorithmic efficiency goals, the developers are taking this opportunity to build a modular, well factored suite of tools around this sort code that will allow it to be easily used on any experimental dataset or GEANT4 simulation, with minimal case-specific coding required.  The overall program structure is a chain modularized as follows:

1.  Data format interface tool: a preprocessor that translates any arbitrary data format (GRIFFIN, TIGRESS, GPS, GEANT4, whatever) into the format needed by GRSISpoon.  This is the ONLY piece of experiment specific code; everything downstream from here must be strictly experiment agnostic.  Developers must produce a well defined specification of the data format required so third parties can write their own preprocessor, and the preprocessor logic must be factored in a way that makes it trivial to swap out.

2.  Sort core: the sort core does the computational heavy lifting of sorting the data into the requisite structure.  Sorting the raw data is expected to be an O(n) process, since data needs only be replayed once and grouped by trigger ID.  The sort core should be able to produce ROOT trees / ntuples, as well as flat histograms.  Furthermore, the sort core must have an exposed API that an external server can control it by.

3.  Independent web server: a relatively simple web server that waits for AJAX get requests from a web page, parses them into commands for the sort core's API, and returns the result in a way that can be parsed by the page's visualization.  

4.  Visualization web page: a web app sitting on top of the server described above, which will allow any Chrome or Firefox user to visualize (via the gammaSpectrum framework) any histogram that can be defined by the sort core's API (specific feature list TBD).
