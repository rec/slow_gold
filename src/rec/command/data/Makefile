

all: \
 Commands.def.cpp \
 Descriptions.def.cpp \
 KeyPresses.def.cpp \
 Repeated.def.cpp \
 Setters.def.cpp

%.def.cpp: %.def
	/development/rec/scripts/new/new.py --include=command/Command --proto=Commands $<