FieldDevice::FieldDevice(String name, String location){
	this->name = name;
	this->location = location;
}

FieldDevice::getLocation(void){
	return this->location;
}

String FieldDevice::getName(void){
	return this->name;
}
