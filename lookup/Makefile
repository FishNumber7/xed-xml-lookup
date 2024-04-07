CC = g++
# change path to kit location
path = kits/xed-install-base-2024-04-06-lin-x86-64

# uncomment main in lookup.cc if you want to test this
lookup: lookup.o pugixml.o instructions.xml
	$(CC) -o lookup lookup.o pugixml.o $(path)/lib/libxed.a

lookup.o: lookup.cc lookup.hh pugixml.hh
	$(CC) -I$(path)/include -c lookup.cc

pugixml.o: pugixml.hh pugiconfig.hh pugixml.cc
	$(CC) -c pugixml.cc

instructions.xml:
	wget https://uops.info/instructions.xml

