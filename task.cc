#include <iostream>
#include <cmath>
#include <thread>
#include "common.h"
#include "main_storage.h"
#include "task_queue_manager.h"
#include "task.h"

/*
The test assignment is designed to suggest a real-time application, in the sense that the intervals are strictly defined, 
and data should be generated precisely on schedule. However, I recognize that absolute synchronization and exact timing cannot be guaranteed in Linux user space, 
especially in a multithreaded environment.

The data may-and likely will-fluctuate within acceptable limits for this test, because execution depends on process priority and the Linux scheduler's load. 
Nonetheless, I have done my best to ensure good performance while avoiding unnecessary complexity in the code, which is not required for the test task.
*/

constexpr float PERIOD_SEC = 1.0f;

Task::~Task() {
	stop();
}

void Task::start() {
	if (working_) { return; }
	working_ = true;
	workerThread_ = std::thread(&Task::loop, this);
}

void Task::stop() {
	if (!working_) { return; }
    working_ = false;
    if (workerThread_.joinable()) {
        workerThread_.join();
    }
}

void Task::loop() {
	while(working_) {
		auto myQueue = TaskQueueManager::getQueue(name());
		if (!myQueue) { // paranoia
			std::cerr << "Can\'t find my (" << name() << ") queue. Will try again..." << std::endl;
			mySleep(); // to avoid a tight loop
			continue;
		}
		Message msg;
		if (myQueue->dequeue(msg)) {
			switch(msg.type) {
				case DataType::X:
					if (!MainStorage::instance()->setX(msg.data)) {
						std::cerr << "Bad x: " << msg.data << std::endl;
					}
					break;
				case DataType::Y:
					if (!MainStorage::instance()->setY(msg.data)) {
						std::cerr << "Bad y: " << msg.data << std::endl;
					}
					break;
				case DataType::Z:
					if (!MainStorage::instance()->setZ(msg.data)) {
						std::cerr << "Bad z: " << msg.data << std::endl;
					}
					break;
				case DataType::Roll:
					if (!MainStorage::instance()->setRoll(msg.data)) {
						std::cerr << "Bad roll: " << msg.data << std::endl;
					}
					break;
				case DataType::Pitch:
					if (!MainStorage::instance()->setPitch(msg.data)) {
						std::cerr << "Bad pitch: " << msg.data << std::endl;
					}
					break;
				case DataType::Yaw:
					if (!MainStorage::instance()->setYaw(msg.data)) {
						std::cerr << "Bad yaw: " << msg.data << std::endl;
					}
					break;
			}
		}
		float coord = 0.0f;
		float angle = 0.0f;
		calculate(coord, angle);
		sendMessages(coord, angle);
		mySleep();
	}
}

void Task::calculate(float & coord, float & angle) {
	if (startTime_ == std::chrono::steady_clock::time_point()) { // the first time the method called
		startTime_ = std::chrono::steady_clock::now();
	}
	auto now = std::chrono::steady_clock::now();
	float elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime_).count() / 1000.0f;
	coord = makeStep(elapsed, MIN_COORD, MAX_COORD);
	angle = makeStep(elapsed, MIN_ANGLE, MAX_ANGLE);
}

float Task::makeStep(float currentTime, float min, float max) {
    float curr = std::fmod(currentTime, PERIOD_SEC);
    float delta = max - min;
    float ret;
    if (curr < PERIOD_SEC / 2) {
        ret = min + delta * (curr / (PERIOD_SEC / 2));
    } else {
        ret = max - delta * ((curr - PERIOD_SEC / 2) / (PERIOD_SEC / 2));
    }
    return ret;
}


/************** children **************************/
// Task10
const std::string & Task10::name() const {
	return TASK10_NAME;
}

void Task10::sendMessages(float coord, float angle) const {
	auto sendCoordQueue = TaskQueueManager::getQueue(TASK20_NAME);
	if (sendCoordQueue) {
		Message msg {coord, DataType::Z};
		sendCoordQueue->enqueue(msg);
	} else {
		std::cerr << "Can\'t send coordinate " << coord << " to task: " << TASK20_NAME << ". The queue doesn\'t exist" << std::endl;
	}

	auto sendAngleQueue = TaskQueueManager::getQueue(TASK40_NAME);
	if (sendAngleQueue) {
		Message msg {angle, DataType::Roll};
		sendAngleQueue->enqueue(msg);
	} else {
		std::cerr << "Can\'t send roll" << angle << " to task: " << TASK40_NAME << ". The queue doesn\'t exist" << std::endl;
	}
}

void Task10::mySleep() const {
	std::this_thread::yield();
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}


// Task20
const std::string & Task20::name() const {
	return TASK20_NAME;
}

void Task20::sendMessages(float coord, float angle) const {
	auto sendCoordQueue = TaskQueueManager::getQueue(TASK10_NAME);
	if (sendCoordQueue) {
		Message msg {coord, DataType::X};
		sendCoordQueue->enqueue(msg);
	} else {
		std::cerr << "Can\'t send coordinate " << coord << " to task: " << TASK10_NAME << ". The queue doesn\'t exist" << std::endl;
	}
	
	auto sendAngleQueue = TaskQueueManager::getQueue(TASK40_NAME);
	if (sendAngleQueue) {
		Message msg {angle, DataType::Pitch};
		sendAngleQueue->enqueue(msg);
	} else {
		std::cerr << "Can\'t send pitch " << angle << " to task: " << TASK40_NAME << ". The queue doesn\'t exist" << std::endl;
	}
}

void Task20::mySleep() const {
	std::this_thread::yield();
	std::this_thread::sleep_for(std::chrono::milliseconds(20));
}


// Task40
const std::string & Task40::name() const {
	return TASK40_NAME;
}

void Task40::sendMessages(float coord, float angle) const {
	auto sendCoordQueue = TaskQueueManager::getQueue(TASK10_NAME);
	if (sendCoordQueue) {
		Message msg {coord, DataType::Y};
		sendCoordQueue->enqueue(msg);
	} else {
		std::cerr << "Can\'t send coordinate " << coord << " to task: " << TASK10_NAME << ". The queue doesn\'t exist" << std::endl;
	}
	
	auto sendAngleQueue = TaskQueueManager::getQueue(TASK20_NAME);
	if (sendAngleQueue) {
		Message msg {angle, DataType::Yaw};
		sendAngleQueue->enqueue(msg);
	} else {
		std::cerr << "Can\'t send yaw " << angle << " to task: " << TASK20_NAME << ". The queue doesn\'t exist" << std::endl;
	}
}

void Task40::mySleep() const {
	std::this_thread::yield();
	std::this_thread::sleep_for(std::chrono::milliseconds(40));
}