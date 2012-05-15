
CPP_FILES=Commands.def.cpp \
 Descriptions.def.cpp \
 KeyPresses.def.cpp \
 Repeated.def.cpp \
 Setters.def.cpp \
 AllCommands.def.cpp


all: $(CPP_FILES)

%.def.cpp: %.def
	/development/rec/scripts/new/new.py\
    --include=command/Command\
    --proto=command::Commands\
    $<

clean:
	rm $(CPP_FILES)