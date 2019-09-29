#include "../FieldDevice.cpp";

/**
 * This class represents a actuator
 * @see https://en.wikipedia.org/wiki/Actuator
 * @author Kevin Veen-Birkenbach [kevin@veen.world]
 */
class Actuator: FieldDevice {
protected:
	int status;
public:
	enum Status {
		OFF = 0, ON = 1, UNKNOWN = 3
	};
	Actuator(String name, String location, int status); //: FieldDevice(name, location);
	void on(void);
	void off(void);
	int getStatus(void);
};
