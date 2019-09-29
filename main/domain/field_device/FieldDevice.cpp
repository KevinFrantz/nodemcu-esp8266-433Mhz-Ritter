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
		FieldDevice(String name, String location);
		String getLocation(void);
		String getName(void);
}
