new := ~/Documents/development/rec/scripts/new/new.py

icons := $(wildcard art/icon/*.svg)
icon_code := $(patsubst art/icon/%.svg, genfiles/rec/gui/icon/%.svg.cpp, $(icons))

binaries := $(wildcard src/rec/command/*.xml)
binary_code := $(patsubst %.xml, %.xml.cpp, $(binaries))

commands := $(wildcard src/rec/slow/commands/*.def)
command_code := $(patsubst %.def, %.def.cpp, $(commands))

ROOT := ~/Documents/development/rec

genfiles/rec/gui/icon/%.svg.cpp: art/icon/%.svg
	$(new) --namespace=$<

%.xml.cpp: %.xml
	$(new) $<

%.def.cpp: %.def
	$(new)\
    --include=command/Command\
    --proto=command::Commands\
    $<


all: code build

code: $(icon_code) $(binary_code) $(command_code)

.PHONY: build code all

build:
	cd /development/rec/projects/slow/Builds/MacOSX && xcodebuild -project "SlowGold.xcodeproj" -configuration Debug
	xcodebuild -project "projects/slow/Builds/MacOSX/SlowGold 8.xcodeproj" -configuration Debug

clean:
	rm $(icon_code) $(binary_code) $(command_code)
