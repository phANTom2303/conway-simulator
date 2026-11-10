
SRC=src
INC=includes


#defining wildcards to avoid typing all the files separately:
SOURCES= $(wildcard $(SRC)/*.c)
HEADERS= $(wildcard $(INC)/*.h)

# The 'all' target is the default one.
# It tells 'make' that the main goal is to build 'askai'.
all: conway 

# This rule builds the 'askai' executable from the source files
# and links it with the curl library.
# It runs if 'askai' doesn't exist, or if askai.c or cJSON.c have changed.
conway: conway.cpp $(SOURCES) $(HEADERS) 
	g++ -I$(INC) conway.cpp $(SOURCES) -o conway

# This is a 'clean' rule to remove the compiled program.
# You can run it with the command: make clean
clean:
	rm -f conway 

# The PHONY tag tells that 
# these targets are not actual files in our project,
#  important for things like 
# all, clean, (and if needed then test, install etc)
.PHONY: all clean
