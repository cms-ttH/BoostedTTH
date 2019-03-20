HTXS Framework for BoostedTTH analysis
=======
CMSSW tools for analyzing TTH events with respect to the HTXS framework

To get an instruction for installing the BoostedTTH framework look at the BoostedTTH README

[![BoostedTTH framework](https://github.com/cms-ttH/BoostedTTH/blob/CMSSW_9_4_10/README.md)](https://github.com/cms-ttH/BoostedTTH/blob/CMSSW_9_4_10/README.md)

#Installation
Unfortunately the in CMSSW provided HTXS framework doesn't work with CMSSW_9_4_10 at the moment, so one has to install the cms packages GeneratorInterface/RivetInterface and SimDataFormats/HTXS locally and replace the official scripts with A. Marini's changes. This can be done by 
    source HTXSsetup.sh

To remove the local packages, simply deleting them doesn't suffice. Instead open .git/info/sparse-checkout and remove the lines with the package names you want to delete. Afterwards do
    git read-tree -mu HEAD

Now you can remove them.
