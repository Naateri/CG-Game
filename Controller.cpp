#include "Controller.h"

void PS3Controller::close_fd(){
	close(this->fd);
}

PS3Controller::PS3Controller(std::string name){
	this->file_name = name;
}

PS3Controller::~PS3Controller(){
	this->close_fd();
}

void PS3Controller::open_fd(){
	do{
		fd = open(this->file_name.c_str(), O_RDONLY);
	} while (fd <= 0);
}

void PS3Controller::read_fd(){
	int n = read(this->fd, &(this->e), sizeof(this->e));
	this->value = e.value;
	this->number = e.number;
}


void PS3Controller::init(){
	
	ioctl(this->fd, JSIOCGAXES, &num_of_axis);
	ioctl(this->fd, JSIOCGBUTTONS, &num_of_buttons);
	
	joy_axis.resize(num_of_axis,0);
	joy_button.resize(num_of_buttons,0);
	bool flag = false;
	
	read(this->fd, &(this->e), sizeof(js_event));
	
	switch (e.type & ~JS_EVENT_INIT){
		case JS_EVENT_AXIS:{
			int p = (int)e.number;
			joy_axis[p]= e.value;
			this->isButton = false;
			break;
		}
		case JS_EVENT_BUTTON:{
			int p = (int)e.number;
			joy_button[p]= e.value;
			this->isButton = true;
			this->num_button = p;
			break;
		}
	}
	
	
}

pair<float,float> PS3Controller::controls(){
	pair<float,float> res;
	if(this->isButton){
			res.first = num_button;
	}
	else{
		cout<<"X pe: "<<joy_axis[1]<<endl;
		if(joy_axis[0] == 0 && joy_axis[1] == 0 ){
			res.first = 0;
			res.second = 0;
		}
		else{
		
			float mag = sqrt(pow(joy_axis[0],2)+pow(joy_axis[1],2));
			
			res.first = joy_axis[0]/mag;
			
			res.second = joy_axis[1]/mag;	
		}
	}
	return res;
}




;
