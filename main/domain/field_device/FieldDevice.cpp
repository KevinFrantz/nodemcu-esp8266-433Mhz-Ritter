/*
 * This class represents a field device
 * @see https://de.wikipedia.org/wiki/Feldger%C3%A4t
 * @author Kevin Veen-Birkenbach [kevin@veen.world]
 */
class FieldDevice{
	protected:
		String location;
		String name;
	public:
		// @todo remove following default constructor
		FieldDevice()
		{
			this->name = "UNKNOWN";
			this->location = "UNKNOWN";
		};
		FieldDevice(String name, String location)
		{
			this->name = name;
			this->location = location;
		};
		String getLocation(void);
		String getName(void);
};
