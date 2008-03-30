LIBS = `pkg-config gtk+-2.0 --libs` `pkg-config lua5.1 --libs`
INCS = `pkg-config gtk+-2.0 --cflags` `pkg-config lua5.1 --cflags`


all: main.o vlg.o vlgform.o	vlgbutton.o vlglabel.o vlgedit.o propertyEdit.o
	g++ -g $(LIBS) main.o vlg.o vlgform.o vlgbutton.o vlglabel.o vlgedit.o propertyEdit.o -o main

main.o: main.cpp
	g++ -g -c main.cpp $(INCS) -o main.o
	
vlg.o: VLG.cpp VLG.h
	g++ -g -c VLG.cpp $(INCS) -o vlg.o 
	
vlgform.o: VLGform.cpp VLGform.h
	g++ -g -c VLGform.cpp $(INCS) -o vlgform.o 

vlgbutton.o: VLGbutton.cpp VLGbutton.h
	g++ -g -c VLGbutton.cpp $(INCS) -o vlgbutton.o 

vlglabel.o: VLGlabel.cpp VLGlabel.h
	g++ -g -c VLGlabel.cpp $(INCS) -o vlglabel.o
	 
vlgedit.o: VLGedit.cpp VLGedit.h
	g++ -g -c VLGedit.cpp $(INCS) -o vlgedit.o 
	
propertyEdit.o: propertyEdit.cpp
	g++ -g -c propertyEdit.cpp $(INCS) -o propertyEdit.o 

clean:
	rm *.o -rf
	rm *~ -rf
	rm main -rf
