num_thread = 5
NUM_BALLS = $(num_thread)
Compiler = g++ -std=c++11
Obj = OBJ/
Src = SRC/
Exe = EXE/
libs = -lGL -lglut -lGLU -lpthread

# $@ means name of target eg execute or exec $< means name of first target

#Library = -Framework=OpenGL -Framework=GLUT -Framework=Pthread
#Header = ball.h vector.h

all: $(Obj)main.o $(Obj)ball.o $(Obj)vector.o $(Obj)cube.o $(Obj)imageloader.o
	$(Compiler) $(Obj)main.o $(Obj)ball.o $(Obj)vector.o $(Obj)cube.o $(Obj)imageloader.o -o exec $(libs)
	mv exec $(Exe)	
	$(Exe)./exec $(NUM_BALLS)

execute: exec
	$(Exe)./$< $(NUM_BALLS)

exec:
	$(Compiler) $(Obj)main.o $(Obj)ball.o $(Obj)vector.o $(Obj)cube.o $(Obj)imageloader.o -o $@ $(libs)
	mv $@ $(Exe)

$(Obj)main.o: $(Src)main.cpp $(Src)ball.h $(Src)vector.h
	$(Compiler) -c $< $(libs)
	mv main.o $(Obj)

$(Obj)ball.o: $(Src)ball.cpp $(Src)ball.h $(Src)vector.h
	$(Compiler) -c $< $(libs)
	mv ball.o $(Obj)

$(Obj)vector.o: $(Src)vector.cpp $(Src)vector.h
	$(Compiler) -c $< $(libs)
	mv vector.o $(Obj)

$(Obj)cube.o: $(Src)cube.cpp
	$(Compiler) -c $< $(libs)
	mv cube.o $(Obj)

$(Obj)imageloader.o: $(Src)imageloader.cpp $(Src)imageloader.h
	$(Compiler) -c $< $(libs)
	mv imageloader.o $(Obj)

clean:
	rm $(Exe)exec $(Obj)main.o $(Obj)ball.o $(Obj)vector.o $(Obj)cube.o $(Obj)imageloader.o
