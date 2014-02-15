#anything in this function under an ipython.ex('your line here') will be
#executed as if it was being run from the first cell in the notebook;
#use this for default imports, where the syntax is 'import blah' if 
#there is a file 'blah.py' in the same directory you launched the 
#IPython notebook server from.

def load_ipython_extension(ipython):
    #import useful python things
    ipython.ex('import rootnotes')
    ipython.ex('import rootprint')

    #do some javascript setup:
    #ipython.ex('from IPython.display import Javascript')
    #ipython.ex('Javascript("console.log(1337)")')
