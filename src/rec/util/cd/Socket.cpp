#include "rec/util/cd/Socket.h"
#include "rec/util/Exception.h"

using namespace juce;

namespace rec {
namespace util {
namespace cd {

void writeSocket(Socket* sock, const String& s) {
  int w = sock->write(s.toCString(), s.length());
  if (w != s.length()) {
    throw Exception((String("Wrote ") + String(w) + " of " +
                     String(s.length()) + " chars.").toCString());
  }
}

String readSocket(Socket* sock, int timeout) {
  static const int BUFFER_SIZE = 4096;
  char buffer[BUFFER_SIZE];

  int error = sock->waitUntilReady(true, timeout);
  if (error <= 0)
    throw Exception(string("Socket wait error ") + String(error).toCString());

  int read = sock->read(buffer, BUFFER_SIZE, false);
  if (read <= 0)
    throw Exception(string("Socket read error ") + String(read).toCString());

  return String(buffer, read);
}

void connect(Socket* s, const String& server, int port, int timeout) {
  if (!s->connect(server, port, timeout)) {
    throw Exception("Couldn't open socket to " +
                    string(server.toCString()) +
                    ":" + string(String(port).toCString()));
  }
}

}  // namespace cd
}  // namespace util
}  // namespace rec
