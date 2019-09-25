#include <linux/joystick.h>
#include <fcntl.h> //opening device
#include <unistd.h> //read
#include <string>

/**
	PS3 controller inputs values:
	X: 0 (0 if released, 1 if pressed)
	O: 1 (0 if released, 1 if pressed)
	Triangle: 2 (0 if released, 1 if pressed)
	Square: 3 (0 if released, 1 if pressed)
	
	DPAD-Up: 13 (0 if released, 1 if pressed)
	DPAD-Down: 14 (0 if released, 1 if pressed)
	DPAD-Left: 15 (0 if released, 1 if pressed)
	DPAD-Right: 16 (0 if released, 1 if pressed)
**/

class PS3Controller{
private:
	struct js_event e;
	std::string file_name;
	int fd;
	void close_fd();
public:
	int value; //value of button read
	int number; //button pressed
	PS3Controller(std::string);
	~PS3Controller(); //destructor
	void open_fd();
	void read_fd();
};
