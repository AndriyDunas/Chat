# Chat
Cross-platform chat application between any number of hosts.

Please, run the server just once, and run the client as many times as you need.

If you use some IDE, add existing in src folder .h and .cpp files into the new project,
build and run the application using IDE menu.
NOTE: if you use VisualStudio, please uncomment the following line in windows_socket.h:
//#pragma comment(lib, "ws2_32.lib")  // Need to link with Ws2_32.lib, use it in VS.
Because in MinGW we have a warning "ignoring pragma comment", but in VS we must use it.

If you use linux terminal or MinGW shell:
at first, browse to the directory with the app.

To build:

	make
	
To run:

You can choose your role manually, by running the app with the key in the command line 
(s - server, c - client) or to choose the role in the console menu.
If you choose server role in command line, you can set the path of the file for 
storing the conversation history with the third command line argument. 
By default it will be history.txt in the current directory.
Linux terminal examples:
	./chat c                   <-- client mode
	./chat s                   <-- server mode
	./chat s new_history.txt   <-- server mode with the settings of the file path
MinGW shell examples:
	chat.exe c                   <-- client mode
	chat.exe s                   <-- server mode
	chat.exe s new_history.txt   <-- server mode with the settings of the file path

To clean:

	make clean
	
Enjoy:)
	