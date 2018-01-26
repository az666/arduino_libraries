#include <PulseGenFree.h>
PulseGenFree pulseFree(9,5000,5000); //七號引腳 產生 5000us on, 5000us off 脈衝

void setup() {
}

void loop() {
  pulseFree.generator();
}
