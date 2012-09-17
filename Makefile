ROOT := /development/rec
BUILD_ROOT := $(ROOT)/projects/slow/Builds/MacOSX

new := $(ROOT)/scripts/new/new.py

icons := $(wildcard art/icon/*.svg)
binaries := $(wildcard src/rec/command/*.xml)
commands := $(wildcard src/rec/slow/commands/*.def)
translations := $(wildcard text/??-TranslatedStrings.def)

icon_code := $(patsubst art/icon/%.svg, genfiles/icon/rec/gui/icon/%.svg.cpp, $(icons))
binary_code := $(patsubst %.xml, %.xml.cpp, $(binaries))
command_code := $(patsubst %.def, %.def.cpp, $(commands))
translation_code := $(patsubst text/%-TranslatedStrings.def, genfiles/translations/rec/translation/%-TranslatedStrings.def.cpp, $(translations))

all: code builddebug

release: code builddebug buildrelease compress

code: $(icon_code) $(binary_code) $(command_code) $(translation_code)

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

genfiles/translations/rec/translation/%-TranslatedStrings.def.cpp: text/%-TranslatedStrings.def
	$(new)\
    --include=base/Trans.pb \
    --proto=TranslatedStrings \
    --namespace=rec.translation \
    --output=genfiles/translation/rec/translation \
    $<

%.xml.cpp: %.xml
	$(new) $<

%.def.cpp: %.def
	$(new)\
    --include=command/Command.pb \
    --proto=command::Commands \
    $<
