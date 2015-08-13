#include <unistd.h>
#include "powutil.h"

int main(int argc, char* argv[]) {

  setup("log.times", 100);

  startMeasuring();
  sleep( 5/*seconds*/ );
  stopMeasuring();

  teardown();

  return 0;
}
