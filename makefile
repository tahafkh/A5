CC := g++ -std=c++11
Obj_files = main.o FieldRunner.o Path.o SuperTrooper.o Scrambler.o StubbornRunner.o Runner.o Tesla.o Missile.o Gattling.o Tower.o Shot.o Enemy.o functions.o rsdl.o
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
all: FieldRunners.out

FieldRunners.out: ${Obj_files}
	${CC} ${Obj_files} $(CCFLAGS) -o FieldRunners.out
main.o: main.cpp FieldRunner.hpp
	${CC} -c main.cpp -o main.o
FieldRunner.o: FieldRunner.cpp FieldRunner.hpp Tower.hpp Path.hpp Enemy.hpp functions.hpp Gattling.hpp Missile.hpp Tesla.hpp Runner.hpp StubbornRunner.hpp Scrambler.hpp SuperTrooper.hpp
	${CC} -c FieldRunner.cpp -o FieldRunner.o
Path.o: Path.cpp Path.hpp rsdl.hpp Enemy.hpp UpdatedPoint.hpp functions.hpp
	${CC} -c Path.cpp -o Path.o
SuperTrooper.o: SuperTrooper.cpp SuperTrooper.hpp functions.hpp Enemy.hpp
	${CC} -c SuperTrooper.cpp -o SuperTrooper.o
Scrambler.o: Scrambler.cpp Scrambler.hpp functions.hpp Enemy.hpp
	${CC} -c Scrambler.cpp -o Scrambler.o
StubbornRunner.o: StubbornRunner.cpp StubbornRunner.hpp functions.hpp Enemy.hpp
	${CC} -c StubbornRunner.cpp -o StubbornRunner.o
Runner.o: Runner.cpp Runner.hpp functions.hpp Enemy.hpp
	${CC} -c Runner.cpp -o Runner.o
Tesla.o: Tesla.cpp Tesla.hpp Tower.hpp functions.hpp
	${CC} -c Tesla.cpp -o Tesla.o
Missile.o: Missile.cpp Missile.hpp Tower.hpp functions.hpp
	${CC} -c Missile.cpp -o  Missile.o
Gattling.o: Gattling.cpp Gattling.hpp Tower.hpp functions.hpp
	${CC} -c Gattling.cpp -o Gattling.o
Tower.o: Tower.cpp Tower.hpp rsdl.hpp Enemy.hpp Shot.hpp
	${CC} -c Tower.cpp -o Tower.o
Shot.o: Shot.cpp Shot.hpp rsdl.hpp Enemy.hpp UpdatedPoint.hpp
	${CC} -c Shot.cpp -o Shot.o
Enemy.o: Enemy.cpp Enemy.hpp UpdatedPoint.hpp
	${CC} -c Enemy.cpp -o Enemy.o
functions.o: functions.cpp functions.hpp rsdl.hpp
	${CC} -c functions.cpp -o functions.o
rsdl.o: rsdl.cpp rsdl.hpp
	${CC} -c rsdl.cpp -o rsdl.o
clean:
	rm -r *.o