#Setup

This setup assumes ipython and the ipython notebook framework is available on your machine.  More details someday.  Most of these setup instructions come from [the ipython team](http://ipython.org/ipython-doc/rel-1.1.0/interactive/public_server.html) - have a look there for a second set of eyes.

###Security First:
First, we need a secure hashed password.  We can do this right from the ipython prompt:

```
from IPython.lib import passwd
passwd()
```

Enter and re-enter your desired password, and the big ugly string that comes out is your securely hashed password, which we'll be using in the profile creation step.

Of course, all the password hashing in the world won't help you if you're sending your password off unencrypted.  Make yourself a signed cert `mycert.pem` which we'll use in the next step:

```
openssl req -x509 -nodes -days 365 -newkey rsa:1024 -keyout mycert.pem -out mycert.pem
```

###Make a Profile
Your notebook is going to be served under an ipython profile, which for consistency's sake is going to be called `nbserver`.  Just do

```
ipython profile create nbserver
```

and the requisite `~/ipython/profile_nbserver` will be created.  In it, there should be a parameter file, `ipython_notebook_config.py`.  Uncomment and set the following:

    c = get_config()
    c.NotebookApp.ip = '*'
    c.NotebookApp.open_browser = False
    c.NotebookApp.port = <your fav port>
    c.NotebookApp.certfile = u'/path/to/your/mycert.pem'
    c.NotebookApp.password = u'superSecretHashedPassword'
    c.IPKernelApp.pylab = 'inline'
    c.IPKernelApp.extensions = ['GRSIextension']
    
And your profile should be good to go.


###Put stuff in the right place:
All the files controlled here have to be put in the appropriate places, after creating a profile to host your IPython notebook.  `distributeFiles.sh` will do these three bullet points for you, if you've created the directory structure exactly as prescribed.

- Under `~/.ipython/`, create a directory `extensions`; place `GRSIextension.py` in that new directory.
- Under `~/.ipython/profile_nbserver`, create a directory `static/custom`; place `custom.css`, `custom.js`, and `util.js` therein.
- Under `~/.ipython/profile_nbserver`, create a directory `startup`; place `utils.py` in this directory.

Then place `GRSISpoon.ipynb` in whatever directory you want to launch the notebook from.  Launch the notebook with
    
    ipython notebook --profile=nbserver
