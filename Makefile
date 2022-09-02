setup:
	mkdir -p bin
	cd TP1 && cd src && g++ -o pagerank tp1.cpp 
	mv TP1/src/pagerank bin

clean:
	rm -rf bin 
