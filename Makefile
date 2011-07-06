new := ~/Documents/development/rec/scripts/new/new.py

icons := $(wildcard src/rec/gui/icon/*.svg)
icon_code := $(patsubst %.svg, %.svg.cpp, $(icons))

binaries := $(wildcard src/rec/command/*.xml)
binary_code := $(patsubst %.xml, %.xml.cpp, $(binaries))

%.svg.cpp:: %.svg
	$(new) svg $*

%.xml.cpp:: %.xml
	$(new) xml $*

all:
	make $(icon_code)
	make $(binary_code)

clean:
	rm $(icon_code)