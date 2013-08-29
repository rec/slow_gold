#pragma once

#ifndef nullptr_H_62B23520_7C8E_11DE_8A39_0800200C9A66
#define nullptr_H_62B23520_7C8E_11DE_8A39_0800200C9A66


namespace YAML
{
	class Node;

	struct _Null {};
	inline bool operator == (const _Null&, const _Null&) { return true; }
	inline bool operator != (const _Null&, const _Null&) { return false; }

	bool IsNull(const Node& node);

	extern _Null Null;
}

#endif // nullptr_H_62B23520_7C8E_11DE_8A39_0800200C9A66

