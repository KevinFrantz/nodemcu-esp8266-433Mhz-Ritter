#include "../Actuator.cpp";

void Actuator::on(void){
	this->status = Actuator::Status::ON;
}
void Actuator::off(void){
	this->status = Actuator::Status::OFF;
}
int void Actuator::getStatus(void){
	return this->status;
}
