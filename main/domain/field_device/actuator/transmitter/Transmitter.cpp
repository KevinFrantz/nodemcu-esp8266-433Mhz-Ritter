#include "../Actuator.cpp"
/**
 * This class exists right now mainly out of language
 * @see https://en.wikipedia.org/wiki/Actuator
 * @author Kevin Veen-Birkenbach [kevin@veen.world]
 */
class Transmitter: public Actuator {
	public:
		//Transmitter(String name, String location, Actuator::Status status);//::Actuator(name, location, status);
		Transmitter(String name, String location, Actuator::Status status):Actuator(name, location, status){
		};

};
