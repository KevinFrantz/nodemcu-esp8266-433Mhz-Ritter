#include <DHT.h>
/*
 * @author Kevin Veen-Birkenbach
 */
class GUI{
  private:
    String titel;
    String subtitel;
    DHT* dht;
    const int *switch_status; //deprectated
    const String *switchs; //deprectated
    int pirPin;
    //String template(void);
    String html_template(void);
    String switch_button(String number, String name,int status);
    String switch_template(void);
    String footer(void);
    String temperatur(void);
  public:
    GUI(String titel, String subtitel, DHT* dht, int *switch_status, String *switchs, int pirPin);
    String printOutput(void);
};
