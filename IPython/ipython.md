#Setup

##Create a Profile
TBD - name 'nbserver'.

All the files controlled here have to be put in the appropriate places, after creating a profile to host your IPython notebook.  Script coming soon :)

- Under `~/.ipython/`, create a directory `extensions`; place `GRSIextension.py` in that new directory.
- Under `/.ipython/profile_nbserver`, create a directory `static\custom`; place `custom.css`, `custom.js`, and `util.js` therein.
- Under `/.ipython/profile_nbserver`, create a directory `startup`; place `utils.py` in this directory.

Then place `GRSISpoon.ipynb` in whatever directory you want to launch the notebook from.  Launch the notebook with
    
    ipython notebook --profile=nbserver
