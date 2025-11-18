#ifndef TASK_H
#define TASK_H

#include <atomic>
#include <thread>
#include <chrono>
#include "message.h"
#include "thread_safe_queue.hpp"

/*
Task class. It implements the tasks themselves. 
The idea is that each task shares most of the common algorithm, which is implemented in the parent class, but each has its own small nuances, 
which are realized in specific child classes. This approach facilitates easy modification, addition, or removal of tasks as needed, supporting straightforward scalability of the project.

Note: In a real project, it might have been better to separate these tasks into individual .cc/.h files - this would be more logical, convenient, and readable. 
However, for this assignment, I decided not to do that to make it easier to check.
*/

class Task {
public:
	virtual ~Task();
	void start();
	void stop();
	virtual const std::string & name() const = 0;

protected:
	virtual void sendMessages(float coord, float angle) const = 0;
	virtual void mySleep() const = 0;
	std::atomic_bool working_ = false;

private:
	static float makeStep(float currentTime, float min, float max);
	void loop();
	void calculate(float & coord, float & angle);
	std::thread workerThread_;
	std::chrono::steady_clock::time_point startTime_ = std::chrono::steady_clock::time_point();
};


class Task10 : public Task {
public:
	const std::string & name() const override;

private:
	void sendMessages(float coord, float angle) const override;
	void mySleep() const override;
};


class Task20 : public Task {
public:
	const std::string & name() const override;

private:
	void sendMessages(float coord, float angle) const override;
	void mySleep() const override;
};


class Task40 : public Task {
public:
	const std::string & name() const override;

private:
	void sendMessages(float coord, float angle) const override;
	void mySleep() const override;
};

#endif // TASK_H