new := ~/Documents/development/rec/scripts/new/new.py

icons := $(wildcard src/rec/gui/icon/*.svg)
icon_code := $(patsubst %.svg, %.svg.cpp, $(icons))

binaries := $(wildcard src/rec/command/*.xml)
binary_code := $(patsubst %.xml, %.xml.cpp, $(binaries))

commands := $(wildcard src/rec/slow/commands/*.def)
command_code := $(patsubst %.def, %.def.cpp, $(commands))

%\.svg.cpp: %.svg
	$(new) $<

%\.xml.cpp: %.xml
	$(new) $<

%\.def.cpp: %.def
	$(new)\
    --include=command/Command\
    --proto=command::Commands\
    $<

all: $(icon_code) $(binary_code) $(command_code)

clean:
	rm $(icon_code) $(binary_code) $(command_code)
