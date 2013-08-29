ROOT := /development
BASE := src/rec
PROTO_DIR := externals/mac/protobuf
GENFILES := genfiles/proto
BUILD_DIR := /development/rec/projects/slow/Builds/MacOSX

PROTOC := $(PROTO_DIR)/bin/protoc\
 -I src\
 -I $(PROTO_DIR)/include\
 --python_out=$(GENFILES)\
 --cpp_out=$(GENFILES)

TOP := $(foreach dir, $(BASE), $(wildcard $(dir)/*))
SECOND := $(foreach dir, $(TOP), $(wildcard $(dir)/*))

TOP_PROTO := $(foreach dir, $(TOP), $(wildcard $(dir)/*.proto))
SECOND_PROTO := $(foreach dir, $(SECOND), $(wildcard $(dir)/*.proto))
ALL_PROTOS := $(TOP_PROTO) $(SECOND_PROTO)

TARGETS_H := $(patsubst src/%.proto, $(GENFILES)/%.pb.h, $(ALL_PROTOS))
TARGETS_CC := $(patsubst src/%.proto, $(GENFILES)/%.pb.cc, $(ALL_PROTOS))

TARGETS := $(TARGETS_H) $(TARGETS_CC)

all: debug # release
	echo "Make complete!"

genfiles/proto/rec/app/%.pb.h: src/rec/app/%.proto
	$(PROTOC) $<

genfiles/proto/rec/audio/%.pb.h: src/rec/audio/%.proto
	$(PROTOC) $<

genfiles/proto/rec/audio/source/%.pb.h: src/rec/audio/source/%.proto
	$(PROTOC) $<

genfiles/proto/rec/audio/stretch/%.pb.h: src/rec/audio/stretch/%.proto
	$(PROTOC) $<

genfiles/proto/rec/audio/util/%.pb.h: src/rec/audio/util/%.proto
	$(PROTOC) $<

genfiles/proto/rec/base/%.pb.h: src/rec/base/%.proto
	$(PROTOC) $<

genfiles/proto/rec/command/%.pb.h: src/rec/command/%.proto
	$(PROTOC) $<

genfiles/proto/rec/command/map/%.pb.h: src/rec/command/map/%.proto
	$(PROTOC) $<

genfiles/proto/rec/data/%.pb.h: src/rec/data/%.proto
	$(PROTOC) $<

genfiles/proto/rec/data/proto/%.pb.h: src/rec/data/proto/%.proto
	$(PROTOC) $<

genfiles/proto/rec/gui/%.pb.h: src/rec/gui/%.proto
	$(PROTOC) $<

genfiles/proto/rec/music/%.pb.h: src/rec/music/%.proto
	$(PROTOC) $<

genfiles/proto/rec/slow/%.pb.h: src/rec/slow/%.proto
	$(PROTOC) $<

genfiles/proto/rec/util/%.pb.h: src/rec/util/%.proto
	$(PROTOC) $<

genfiles/proto/rec/util/file/%.pb.h: src/rec/util/file/%.proto
	$(PROTOC) $<

genfiles/proto/rec/util/thread/%.pb.h: src/rec/util/thread/%.proto
	$(PROTOC) $<

genfiles/proto/rec/widget/%.pb.h: src/rec/widget/%.proto
	$(PROTOC) $<

 genfiles/proto/rec/widget/status/%.pb.h: src/rec/widget/status/%.proto
	$(PROTOC) $<

genfiles/proto/rec/widget/tree/%.pb.h: src/rec/widget/tree/%.proto
	$(PROTOC) $<

genfiles/proto/rec/widget/waveform/%.pb.h: src/rec/widget/waveform/%.proto
	$(PROTOC) $<

proto: $(TARGETS_H)
	echo "Make all protocol buffers"

clean_proto:
	rm $(TARGETS)

release: proto
	cd $(BUILD_DIR) && xcodebuild -project SlowGold.xcodeproj -configuration Release

debug: proto
	cd $(BUILD_DIR) && xcodebuild -project SlowGold.xcodeproj -configuration Debug
