#g++ -g -o bin main.cpp myfunc.cpp bin.cpp testfunc.cpp
quick: bin.cpp main.cpp myfunc.cpp testfunc.cpp bin.h myfunc.h testfunc.h
	g++ -g -o bin main.cpp myfunc.cpp bin.cpp testfunc.cpp

bin.exe: bin.o main.o myfunc.o testfunc.o 
	g++ -g -c bin $^

bin.o: bin.cpp bin.h myfunc.h
	g++ -g -c $<

myfunc.o: myfunc.cpp myfunc.h
	g++ -g -c $<

testfunc.o: testfunc.cpp bin.h
	g++ -g -c $<

main.o: main.cpp myfunc.h bin.h
	g++ -c $<

%.o: %.cpp %.h
	g++ -c $<

%.o: %.cpp
	g++ -c $<

