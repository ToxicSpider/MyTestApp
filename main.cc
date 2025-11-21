/*
Author: Alex Timonov
email: crudus.spider@gmail.com
*/
#include <iostream>
#include "common.h"
#include "main_storage.h"
#include "task_queue_manager.h"
#include "task.h"

int main() {
	TaskQueueManager::createQueue(TASK10_NAME);
	TaskQueueManager::createQueue(TASK20_NAME);
	TaskQueueManager::createQueue(TASK40_NAME);

	Task10 t10;
	Task20 t20;
	Task40 t40;
	t10.start();
	t20.start();
	t40.start();

	for (int i = 0; i < 200; i++) { // Mock consumer
		float x, y, z, roll, pitch, yaw;
		MainStorage::instance()->getData(x, y, z, roll, pitch, yaw);
		std::cout << "x: " << x << ", y: " << y << ", z: " << z << ", roll: " << roll << ", pitch: " << pitch << ", yaw: " << yaw << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	t10.stop();
	t20.stop();
	t40.stop();

	return 0;

}
