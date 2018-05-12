target=main
source=$(wildcard *.cpp)

$(target):main.o Tableop.o File.o Recordop.o
	g++ -o main main.o Tableop.o File.o Recordop.o
%.o:%.cpp Heads.h
	g++ -std=c++11 -c -o $@ $<

clean:
	rm main *.o
