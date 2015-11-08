.PHONY: test
test:
	make testeq
	make testnm
	make testament

run:
	@./bin/testeq
	@./bin/testnm
	@./bin/testevent

testeq:
	gcc -c ./src/eventqueue.cpp -o ./obj/eventqueue.o
	gcc -c ./test/testeq.cpp -o ./obj/testeq.o

	gcc ./obj/*.o -o ./bin/testeq -lstdc++

testnm:
	gcc -c ./src/networkmanager.cpp -o ./obj/networkmanager.o
	gcc -c ./test/testnm.cpp -o ./obj/testeq.o

	gcc ./obj/*.o -o ./bin/testnm -lstdc++ 
	
testevent:
	gcc -c $(CXXFLAG) ./src/eventqueue.cpp -o ./obj/eventqueue.o
	gcc -c $(CXXFLAG) ./src/event.cpp -o ./obj/event.o
	gcc -c $(CXXFLAG) ./src/flow.cpp -o ./obj/flow.o
	gcc -c $(CXXFLAG) ./src/node.cpp -o ./obj/node.o
	gcc -c $(CXXFLAG) ./src/event/ackevent.cpp -o ./obj/ackevent.o
	gcc -c $(CXXFLAG) ./src/event/txevent.cpp -o ./obj/txevent.o
	gcc -c $(CXXFLAG) ./src/event/rxevent.cpp -o ./obj/rxevent.o
	gcc -c $(CXXFLAG) ./src/networkmanager.cpp -o ./obj/networkmanager.o
	gcc -c $(CXXFLAG) ./test/testevent.cpp -o ./obj/testevent.o
	
	gcc ./obj/*.o -o ./bin/testevent -lstdc++

.PHONY: clean
clean:
	rm -rf ./obj/*
	rm -rf ./bin/*
