all:
	#g++ -I../include -DSIMD_MODE -march=native driver.cpp
	g++ -I../include -DSIMD_MODE driver.cpp
	#g++ -I../include -D_POSIX_C_SOURCE=200112L -D_ISOC99_SOURCE -DSIMD_MODE -march=native driver.cpp

asm:
	g++ -S -I../include -DSIMD_MODE -march=native driver.cpp

clean:
	rm a.out
