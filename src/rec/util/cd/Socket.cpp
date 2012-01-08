#include "rec/util/cd/Socket.h"
#include "rec/util/Exception.h"

using namespace juce;

namespace rec {
namespace util {
namespace cd {

void writeSocket(Socket* sock, const String& s) {
  // TODO: unneeded copy
  int w = sock->write(str(s).c_str(), s.length());
  if (w != s.length()) {
    throw Exception(string("Wrote ") + String(w) + " of " + String(s.length()) + " chars.");
  }
}

String readSocket(Socket* sock, int timeout) {
  static const int BUFFER_SIZE = 4096;
  char buffer[BUFFER_SIZE];

  int error = sock->waitUntilReady(true, timeout);
  if (error <= 0)
    throw Exception("Socket wait error " + error);

  int read = sock->read(buffer, BUFFER_SIZE, false);
  if (read <= 0)
    throw Exception("Socket read error " + read);

  // TODO: this will fail and crash for bad UTF-8 strings.
  return String(juce::CharPointer_UTF8(buffer), read);
}

void connect(Socket* s, const String& server, int port, int timeout) {
  if (!s->connect(server, port, timeout)) {
    throw Exception(str("Couldn't open socket to " +
                    server + ":" + String(port)));
  }
}

}  // namespace cd
}  // namespace util
}  // namespace rec
