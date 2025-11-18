#include "task_queue_manager.h"

std::map<std::string, std::shared_ptr<ThreadSafeQueue<Message>>> TaskQueueManager::queueMap;

void TaskQueueManager::createQueue(const std::string & name) {
	if (queueMap.find(name) == queueMap.end()) {
		queueMap.emplace(name, std::make_shared<ThreadSafeQueue<Message>>());
	}
}

std::shared_ptr<ThreadSafeQueue<Message>> TaskQueueManager::getQueue(const std::string & name) {
	if (queueMap.find(name) != queueMap.end()) {
		return queueMap[name];
	}
	return nullptr;
}