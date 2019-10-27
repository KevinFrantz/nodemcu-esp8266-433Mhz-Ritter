#include "../Transmitter.cpp"
#include <NewRemoteTransmitter.h>
/**
 * This class offers the interface to switch an RevRitter-433Mhz Plug On\Off
 * @author Kevin Veen-Birkenbach [kevin@veen.world]
 */
class RevRitterRemoteControl: public Transmitter {
	private:
		NewRemoteTransmitter* remoteTransmitter;
		int unit;
	public:
		RevRitterRemoteControl(String name, String location, int status,NewRemoteTransmitter* remoteTransmitter,int unit):Transmitter(name,location,status){
			this->remoteTransmitter = remoteTransmitter;
			this->unit = unit;
		};
		void on(void);
		void off(void);
};
