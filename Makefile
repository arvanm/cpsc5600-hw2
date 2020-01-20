CPPFLAGS = -std=c++11 -Wall -Werror -pedantic -ggdb -pthread
	
hw2 : hw2.cpp	
	g++ $(CPPFLAGS) $< -o $@

test_heaper : heaper.h test_heaper.cpp
	g++ $(CPPFLAGS) $< -o $@
	
clean :
	rm -f hw2 test_heaper *.o
