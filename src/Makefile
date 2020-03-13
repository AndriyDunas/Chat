CXX = g++
CXXFLAGS = -Wall -std=c++11

ifeq ($(OS), Windows_NT)
all: chat.exe

chat.exe: main.o windows_socket.o windows_thread.o windows_synchronizer.o file.o server.o client.o
	$(CXX) $(CXXFLAGS) main.o windows_socket.o windows_thread.o windows_synchronizer.o file.o server.o client.o -lws2_32 -o chat.exe

main.o: main.cpp server.h client.h file.h windows_socket.h abstract_socket.h windows_thread.h abstract_thread.h \
	windows_synchronizer.h abstract_synchronizer.h general.h
	$(CXX) $(CXXFLAGS) -c main.cpp

server.o: server.cpp client.cpp server.h client.h file.h windows_socket.h abstract_socket.h windows_thread.h abstract_thread.h \
	windows_synchronizer.h abstract_synchronizer.h general.h
	$(CXX) $(CXXFLAGS) -c server.cpp client.cpp

client.o: client.cpp server.cpp server.h client.h windows_socket.h abstract_socket.h windows_thread.h abstract_thread.h general.h
	$(CXX) $(CXXFLAGS) -c client.cpp server.cpp	

clean:
	rm *o chat.exe
	
else
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
all: chat

chat: main.o linux_socket.o linux_thread.o linux_synchronizer.o file.o server.o client.o
	$(CXX) $(CXXFLAGS) main.o linux_socket.o linux_thread.o linux_synchronizer.o file.o server.o client.o -o chat -pthread

main.o: main.cpp server.h client.h file.h linux_socket.h abstract_socket.h linux_thread.h abstract_thread.h \
	linux_synchronizer.h abstract_synchronizer.h general.h
	$(CXX) $(CXXFLAGS) -c main.cpp -pthread

server.o: server.cpp client.cpp server.h client.h file.h linux_socket.h abstract_socket.h linux_thread.h abstract_thread.h \
	linux_synchronizer.h abstract_synchronizer.h general.h
	$(CXX) $(CXXFLAGS) -c server.cpp client.cpp -pthread	

client.o: client.cpp server.cpp server.h client.h linux_socket.h abstract_socket.h linux_thread.h abstract_thread.h general.h
	$(CXX) $(CXXFLAGS) -c client.cpp server.cpp -pthread

clean:
	rm *o chat 

endif  # !ifeq ($(UNAME), Linux)
endif  # !ifeq ($(OS), Windows_NT)

windows_socket.o: windows_socket.cpp windows_socket.h general.h abstract_socket.h
	$(CXX) $(CXXFLAGS) -c windows_socket.cpp

windows_thread.o: windows_thread.cpp windows_thread.h general.h abstract_thread.h
	$(CXX) $(CXXFLAGS) -c windows_thread.cpp

windows_synchronizer.o: windows_synchronizer.cpp windows_synchronizer.h general.h abstract_synchronizer.h
	$(CXX) $(CXXFLAGS) -c windows_synchronizer.cpp

linux_socket.o: linux_socket.cpp linux_socket.h general.h abstract_socket.h
	$(CXX) $(CXXFLAGS) -c linux_socket.cpp

linux_thread.o: linux_thread.cpp linux_thread.h general.h abstract_thread.h
	$(CXX) $(CXXFLAGS) -c linux_thread.cpp -pthread

linux_synchronizer.o: linux_synchronizer.cpp linux_synchronizer.h general.h abstract_synchronizer.h
	$(CXX) $(CXXFLAGS) -c linux_synchronizer.cpp -pthread

file.o: file.cpp file.h
	$(CXX) $(CXXFLAGS) -c file.cpp