#ifndef TASK_QUEUE_MANAGER_H
#define TASK_QUEUE_MANAGER_H

#include <string>
#include <map>
#include <memory>
#include "thread_safe_queue.hpp"
#include "message.h"

/*
This is a task queue manager. 
It stores the queues and provides access to them from other tasks, as required by the assignment. 
I did not implement thread safety within this class because the creation of the queues occurs at the very start of the program in a single thread, 
making it unnecessary to complicate the code within a specific assignment. However, in a real project, 
it might be advisable to implement the singleton pattern and address potential vulnerabilities by protecting access with mutexes
*/

class TaskQueueManager {
public:
	static void createQueue(const std::string & name);
	static std::shared_ptr<ThreadSafeQueue<Message>> getQueue(const std::string & name);
private:
	static std::map<std::string, std::shared_ptr<ThreadSafeQueue<Message>>> queueMap;
};

#endif // TASK_QUEUE_MANAGER_H