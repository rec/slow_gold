#include "null.h"
#include "yaml-cpp/include/node.h"

namespace YAML
{
	_Null Null;

	bool IsNull(const Node& node)
	{
		return node.Read(Null);
	}
}
