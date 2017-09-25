#pragma once

class NonMoveable {
public:
	NonMoveable() = default;
	NonMoveable& operator=(NonMoveable&&) = delete;
	NonMoveable(NonMoveable&&) = delete;
};