#pragma once

#include "rec/util/Copy.h"

namespace rec {
namespace util {
namespace file {

class InputImpl;
class OutputImpl;

class Input {
  public:
    explicit Input(const File&, copy::Style s = copy::DEFAULT_STYLE);
    ~Input();

    bool read(Message*);

  private:
    std::unique_ptr<InputImpl> impl_;
    DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Input);
};

class Output {
  public:
    explicit Output(const File&, copy::Style s = copy::DEFAULT_STYLE);
    ~Output();

    void write(const Message&);
    void flush();

  private:
    std::unique_ptr<OutputImpl> impl_;
    DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Output);
};

}  // namespace file
}  // namespace util
}  // namespace rec
