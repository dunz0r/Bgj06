TARGET=mining
CC=gcc
CXX=g++
# Heh.
STD=-std=gnu99
CFLAGS= -std=gnu99 -Wall -pedantic
LDFLAGS=-L/usr/lib 
LIBS=-lm
ALLEGROLIBS=-lallegro -lallegro_opengl -lallegro_image -lallegro_ttf -lallegro_primitives -lallegro_audio -lallegro_acodec -lallegro_ttf -lallegro_font
INCLUDE=-I. -I/usr/include/allegro5

OBJS=$(TARGET).o
OUT=game

all: $(TARGET)_rule

clean:
	@echo Cleaning
	@rm -rf *.o $(TARGET) $(OUT)

$(TARGET)_rule: $(OBJS)
	$(CXX) $(STD) $(OBJS) -o $(OUT) $(INCLUDE) $(CFLAGS) $(LDFLAGS) $(LIBS) $(ALLEGROLIBS)
