icons := $(wildcard src/rec/gui/icon/*.svg)
icon_code := $(patsubst %.svg, %.svg.cpp, $(icons))
new := ~/Documents/development/rec/scripts/new/new.py

%.svg.cpp:: %.svg
	$(new) svg $*

%.xml.cpp:: %.xml
	$(new) xml $*

all:
	make $(icon_code)

clean:
	rm $(icon_code)