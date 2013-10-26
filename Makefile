TARGET=main2
CC=gcc
CXX=g++
# Heh.
STD=-std=gnu99
CFLAGS= -std=gnu99 -Wall -pedantic -O2
LDFLAGS=-L/usr/lib 
LIBS=-lm
ALLEGROLIBS=-lallegro_color -lallegro_main -lallegro_memfile -lallegro_primitives -lallegro_acodec -lallegro_audio -lallegro_dialog -lallegro_image -lallegro_physfs -lallegro_ttf -lallegro_font -lallegro  
INCLUDE=-I. -I/usr/include/allegro5

OBJS=$(TARGET).o
OUT=game

all: $(TARGET)_rule

clean:
	@echo Cleaning
	@rm -rf *.o $(TARGET) $(OUT)

$(TARGET)_rule: $(OBJS)
	$(CXX) $(STD) $(OBJS) -o $(OUT) $(INCLUDE) $(CFLAGS) $(LDFLAGS) $(LIBS) $(ALLEGROLIBS)
