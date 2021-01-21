all:
	clang++ -Wunused src/*.cpp src/**/*.cpp -o main && ./main
db:
	clang++ -fstandalone-debug -g -O0 src/**/*.cpp src/*.cpp  -o main && lldb main
clean:
	rm main 
