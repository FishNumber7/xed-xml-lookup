if [-d xed]; then
    git clone https://github.com/intelxed/xed.git xed

if [-d mbuild]; then
    git clone https://github.com/intelxed/xed.git mbuild

cd lookup
../xed/mfile.py install
wget https://uops.info/instructions.xml