#include "biot.h"


BIoT::Brick::NodeMCU n;
BIoT::Interface::Console c(115200);
BIoT::Interface::Protocol p("Bitspark", "rbN92fTmm7z6mD53Hc5T", "b6k-oled", "slang-0.fritz.box");
BIoT::Device::OLED d("OLED_128x32");

void callback(std::string topic, char bytes[], unsigned int length) {
  d.clear();
  d.text("Incoming...", 10, 16);
  d.display();
  delay(600);
  d.clear();
  d.text(bytes, 0, 0);
  d.display();
}

void setup() {
    p.setCallback(callback);
    p.subscribe("/b6k-demoNight/oled");
  
    n.attach(&c);
    n.attach(&p);

    n.plug(&d, std::vector < BIoT::Brick::Pin * > {n.pinD1(), n.pinD2()});
    n.setup();

    d.textSize(1);

    delay(100);
    d.clear();
    d.text("Setup...", 10,16);
    d.display();
    delay(800);
}

void loop() {
  n.loop();
}
