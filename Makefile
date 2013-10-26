TARGET=main
CC=gcc
CXX=g++
# Heh.
STD=-std=gnu99
CFLAGS= -std=gnu99 -Wall -pedantic -O2
LDFLAGS=-L/usr/lib 
LIBS=-lm
ALLEGRO_LIBS=$(pkg-config --libs allegro-5.0 allegro_color-5.0 allegro_font-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_primitives-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_dialog-5.0 allegro_image-5.0 allegro_physfs-5.0 allegro_ttf-5.0)
INCLUDE=-I. -I/usr/include/allegro5

OBJS=$(TARGET).o
OUT=game

all: $(TARGET)_rule

clean:
	@echo Cleaning
	@rm -rf *.o $(TARGET) $(OUT)

$(TARGET)_rule: $(OBJS)
	$(CXX) $(STD) $(OBJS) -o $(OUT) $(INCLUDE) $(CFLAGS) $(LDFLAGS) $(LIBS) $(ALLEGROLIBS)
