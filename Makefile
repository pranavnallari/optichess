clean:
	rm -rf build optichess && clear

run:
	mkdir build && cd build && cmake .. && make && cp src/optichess ../
