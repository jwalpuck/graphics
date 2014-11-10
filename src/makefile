# set the C compiler, for C++ use g++
# use this setting on most sane machines
CC = gcc

# use this line on the engin linux machines
# CC = gcc296

# set the path to the include directory
INCDIR =../include

# set the flags for the C and C++ compiler to give lots of warnings
CFLAGS = -I$(INCDIR) -O2 -Wall -Wstrict-prototypes -Wnested-externs -Wmissing-prototypes -Wmissing-declarations
CPPFLAGS = $(CFLAGS)

# path to the object file directory
ODIR = obj

# path to the lib directory
LIBDIR =../lib

# path to the bin directory
BINDIR =../bin

# libraries to include
LIBS = -lm -limageIO
LFLAGS = -L$(LIBDIR)

# put all of the relevant include files here
_DEPS = ppmIO.h 

# convert them to point to the right place
DEPS = $(patsubst %,$(INCDIR)/%,$(_DEPS))

# put a list of the executables here
EXECUTABLES = ppmtest

# put a list of all the object files here for all executables (with .o endings)
_OBJ = ppmmain.o

# convert them to point to the right place
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# patterns for compiling source code
# $< is the file that caused the action to occur
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: %.C $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


all:
	for i in $(EXECUTABLES); do (make $$i) ; done


# put the specific executable rules here
ppmtest: $(ODIR)/ppmmain.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

lab1: $(ODIR)/lab1.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

mask: $(ODIR)/mask.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

mergeImages: $(ODIR)/mergeImages.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

imageCode: $(ODIR)/imageCode.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

fractles: $(ODIR)/fractles.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test3: $(ODIR)/test3.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test3a: $(ODIR)/test3a.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test3b: $(ODIR)/test3b.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test3c: $(ODIR)/test3c.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

donout: $(ODIR)/donout.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)


abstractArt: $(ODIR)/abstractArt.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

3Dthing: $(ODIR)/3Dthing.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test4a: $(ODIR)/test4a.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test4b: $(ODIR)/test4b.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

face: $(ODIR)/face.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

minion: $(ODIR)/minion.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

up: $(ODIR)/up.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

polyspeed: $(ODIR)/polyspeed.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test4c: $(ODIR)/test4c.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test4cloop: $(ODIR)/test4cloop.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test5a: $(ODIR)/test5a.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test5b: $(ODIR)/test5b.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test5c: $(ODIR)/test5c.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test5d: $(ODIR)/test5d.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

illusion: $(ODIR)/illusion.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

illusion2: $(ODIR)/illusion2.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

spaceScene: $(ODIR)/spaceScene.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

halloween: $(ODIR)/halloween.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

3DImage: $(ODIR)/3DImage.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS) 

test6a: $(ODIR)/test6a.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test6b: $(ODIR)/test6b.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

blueCube: $(ODIR)/blueCube.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

hotAir: $(ODIR)/hotAir.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

music: $(ODIR)/music.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test7a: $(ODIR)/test7a.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test7b: $(ODIR)/test7b.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

test7c: $(ODIR)/test7c.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

scene71: $(ODIR)/scene71.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

scene72: $(ODIR)/scene72.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

