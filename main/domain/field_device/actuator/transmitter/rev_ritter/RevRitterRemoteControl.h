#include "RevRitterRemoteControl.cpp";

/**
RevRitterRemoteControl::RevRitterRemoteControl(String name, String location, int status,NewRemoteTransmitter* remoteTransmitter,int unit):Transmitter(name,location,status){
	//Transmitter::Transmitter(name,location,status);
	this->remoteTransmitter = remoteTransmitter;
	this->unit = unit;
}*/

void RevRitterRemoteControl::on(void){
	Actuator::on();
	this->remoteTransmitter.sendUnit(this->unit,Actuator::Status::ON);
}

void RevRitterRemoteControl::off(void){
	Actuator::off();
	this->remoteTransmitter.sendUnit(this->unit,Actuator::Status::OFF);
}
