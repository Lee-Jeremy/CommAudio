#pragma once

class Task {
	
public:
	virtual void start() = 0;
	virtual void stop() = 0;

	enum Type { fileTx, stream, chat, multicast };

};