CC = arm-mingw32ce-gcc
WRC = arm-mingw32ce-windres
#CC = i586-mingw32msvc-gcc
#WRC = i586-mingw32msvc-windres

CFLAGS += -O1 -Wall
LDFLAGS += -s
LIBS += -lcommctrl

first:	wscntfy.exe wscui.cpl

wscntfy.exe:	wscntfy.o wscntfy.rc.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)

wscntfy.rc.o:	wscntfy.rc
	$(WRC) wscntfy.rc -o $@

wscui.cpl:	wscui.o wscui.rc.o
	$(CC) --shared $(LDFLAGS) $^ -o $@ $(LIBS)

wscui.rc.o:	wscui.rc wsc.ico hand.ico
	$(WRC) wscui.rc -o $@

clean:
	rm -f *.o *.exe *.cpl


#Not a target
wscntfy.rc:
	#NULL
wscui.rc:
	#NULL
