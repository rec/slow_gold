#include "rec/util/cd/Socket.h"
#include "rec/util/Exception.h"

#include "JuceLibraryCode/JuceHeader.h"

using namespace juce;

namespace rec {
namespace util {
namespace cd {

void writeSocket(Socket* sock, const String& s) {
  int w = write(s.toCString(), s.size());
  if (w != out.size())
    throw Exception(String::formatted("Wrote %d of %d chars", w, s.size()));
}

void readSocket(Socket* sock, String* str, int timeout) {
  static const int BUFFER_SIZE = 4096;
  char buffer[BUFFER_SIZE];

  int error = sock->waitUntilReady(true, timeout);
  if (error <= 0)
    throw Exception("Socket wait error " + String(error));

  int read = sock->read(buffer, BUFFER_SIZE, false);
  if (read <= 0)
    throw Exception("Socket read error " + String(read));

  (*str) = String(buffer, read);
}

void connect(Socket* s, const String& server, int port, int timeout) {
  if (!s->connect(server, port, timeout))
    throw Exception("Couldn't open socket to " + server + ":" + String(port));
}

}  // namespace cd
}  // namespace util
}  // namespace rec
