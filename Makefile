ROOT := /development/rec
BUILD_ROOT := $(ROOT)/projects/slow/Builds/MacOSX

new := $(ROOT)/scripts/new/new.py

icons := $(wildcard art/icon/*.svg)
icon_code := $(patsubst art/icon/%.svg, genfiles/icon/rec/gui/icon/%.svg.cpp, $(icons))

binaries := $(wildcard src/rec/command/*.xml)
binary_code := $(patsubst %.xml, %.xml.cpp, $(binaries))

commands := $(wildcard src/rec/slow/commands/*.def)
command_code := $(patsubst %.def, %.def.cpp, $(commands))

all: code builddebug

release: code builddebug buildrelease compress

code: $(icon_code) $(binary_code) $(command_code)

builddebug:
	cd $(BUILD_ROOT) && xcodebuild -project "SlowGold.xcodeproj" -configuration Debug

buildrelease:
	cd $(BUILD_ROOT) && xcodebuild -project "SlowGold.xcodeproj" -configuration Release

compress: compressrelease compressdebug

compressdebug: builddebug
	cd $(BUILD_ROOT)/build/Debug && zip -r $(BUILD_ROOT)/build/"SlowGold 8-debug.zip" "SlowGold 8-debug.app"

compressrelease: buildrelease
	cd $(BUILD_ROOT)/build/Release && zip -r $(BUILD_ROOT)/build/"SlowGold 8.zip" "SlowGold 8.app"

.PHONY: build code all buildrelease builddebug compress

clean:
	rm $(icon_code) $(binary_code) $(command_code)

genfiles/icon/rec/gui/icon/%.svg.cpp: art/icon/%.svg
	$(new) --namespace=rec.gui.icon --output=genfiles/icon/rec/gui/icon $<

%.xml.cpp: %.xml
	$(new) $<

%.def.cpp: %.def
	$(new)\
    --include=command/Command\
    --proto=command::Commands\
    $<

