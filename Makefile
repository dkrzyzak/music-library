CO = g++
CFLAGS = -std=c++0x

%.x: %.o
	$(CO) $(CFLAGS) $^ -o $@

%.o: %.cpp main.h
	$(CO) $(CFLAGS) -c $<

run: main.x
	./main.x

clean:
	rm -f *.x
