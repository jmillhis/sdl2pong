
all: main.o game.o pong.o paddle.o ball.o collision.o
	g++ -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf main.o game.o pong.o paddle.o ball.o collision.o -o Pong
main.o: main.cpp game.hpp pong.hpp paddle.hpp ball.hpp
	g++ -I . -c main.cpp
game.o: game.cpp game.hpp
	g++ -I . -c game.cpp
collision.o: collision.cpp collision.hpp
	g++ -I . -c collision.cpp
pong.o: pong.cpp game.hpp pong.hpp paddle.hpp ball.hpp
	g++ -I . -c pong.cpp
paddle.o: paddle.cpp game.hpp pong.hpp paddle.hpp ball.hpp
	g++ -I . -c paddle.cpp
ball.o: ball.cpp game.hpp pong.hpp paddle.hpp ball.hpp collision.hpp
	g++ -I . -c ball.cpp
clean:
	rm -r *.o
	rm Pong
