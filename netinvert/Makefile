#
# Netinvert makefile
#

TARGET     = netinvert
LDFLAGS    += -L./ -L. \
			  -lPocoFoundation -lPocoNet -lPocoUtil

CC         = gcc
CXX        = g++
CFLAGS     = -g3 -Wall
CXXFLAGS   = -g3 -Wall -std=c++11

SRC_PATH   = .
INC_PATH   = inc
BUILD_PATH = .

DEST_PATH  = $(TARGET_DIR)/usr/bin
INCLUDES  := -I $(INC_PATH)


.PHONY: default all clean

default: build_path $(TARGET)

all: default

build_path:
	mkdir -p $(BUILD_PATH)

SOURCES += \
	netinvert.cpp 

OBJECTS=$(SOURCES:.cpp=.o)

%.o: $(SRC_PATH)/%.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) -o $(BUILD_PATH)/$@ $<

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(addprefix $(BUILD_PATH)/,$(OBJECTS)) $(LDFLAGS)

clean:
	$(RM) -f $(OBJECTS)
	$(RM) -f $(DEST_PATH)/$(TARGET)

install:
	cp $(BUILD_PATH)/$(TARGET) $(DEST_PATH)
