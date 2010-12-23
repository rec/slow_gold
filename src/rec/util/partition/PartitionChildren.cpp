#include <vector>
#include <set>

#include "rec/util/partition/PartitionChildren.h"
#include "rec/util/partition/Partition.h"
#include "rec/util/partition/Convertors.h"
#include "rec/util/partition/Compare.h"

using std::vector;
using namespace juce;

namespace rec {
namespace util {
namespace partition {


void partitionChildren(const Array<File>& c, const Range<int>& r, int branch,
                       Array<int>* l) {
  JucePartition partition(c, r, branch, l);
}

void partitionChildren(const vector<string>& c, const Range<int>& r, int branch,
                       vector<int>* l) {
  STLPartition partition(c, r, branch, l);
}

}  // namespace partition
}  // namespace util
}  // namespace rec
