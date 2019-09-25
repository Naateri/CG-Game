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
	fd = open(this->file_name.c_str(), O_RDONLY);
}

void PS3Controller::read_fd(){
	int n = read(this->fd, &(this->e), sizeof(this->e));
	
	this->value = e.value;
	this->number = e.number;
}
