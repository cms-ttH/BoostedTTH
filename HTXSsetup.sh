#goto cms working dir
p=$CMSSW_BASE
cd $p
cd src

#add RivetInterface and HTXSInteface to local installation
git cms-addpkg GeneratorInterface/RivetInterface
git cms-addpkg SimDataFormats/HTXS

#remove official (not working) HTXS skripts with Andrea Carlo Marini's solutions
cd GeneratorInterface/RivetInterface/plugins/
mv HTXSRivetProducer.cc HTXSRivetProducer.cc.old
wget https://raw.githubusercontent.com/amarini/cmssw/e8f5a557a46c6b0ea087e2ab8b130b8c0cf5fb7f/GeneratorInterface/RivetInterface/plugins/HTXSRivetProducer.cc

cd ../src
mv HiggsTemplateCrossSections.cc HiggsTemplateCrossSections.cc.old
wget https://raw.githubusercontent.com/amarini/cmssw/e8f5a557a46c6b0ea087e2ab8b130b8c0cf5fb7f/GeneratorInterface/RivetInterface/src/HiggsTemplateCrossSections.cc

cd $p
cd src/SimDataFormats/HTXS/interface
mv HiggsTemplateCrossSections.h HiggsTemplateCrossSections.h.old
wget https://raw.githubusercontent.com/amarini/cmssw/e8f5a557a46c6b0ea087e2ab8b130b8c0cf5fb7f/SimDataFormats/HTXS/interface/HiggsTemplateCrossSections.h

cd $p
cd src
scram b -j 8

echo "HTXS setup complete - start a short test"

#copy short HTXS test skript (works only on the NAF)
cd GeneratorInterface/RivetInterface/test
cp /nfs/dust/cms/user/pkraemer/CMSSW/9_4_10/CMSSW_9_4_10/src/GeneratorInterface/RivetInterface/test/testHTXSrun_cfg.py .
cmsRun testHTXSrun_cfg.py

echo -e "\e[31;5mHopefully everything worked. If not - ask Karim!"
