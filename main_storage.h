#ifndef MAIN_STORAGE_H
#define MAIN_STORAGE_H

#include <mutex>


/*
This is the Main Storage specified in the task. It implements the Singleton design pattern. 
It must be guaranteed to be a single instance and accessible from anywhere in the program, including the "Consumer" which, according to the task requirements, I do not need to implement.  
The class is fully thread-safe, with a convenient set of getters and setters, ensuring the safety and accessibility of data.
*/

class MainStorage {
public:
	static MainStorage * instance();
    MainStorage(const MainStorage &) = delete;
    MainStorage & operator=(const MainStorage &) = delete;

	void getData(float & x, float & y, float & z, float & roll, float & pitch, float & yaw) const; // the consumer's getter
	bool setX(float val);
	float getX() const;
	bool setY(float val);
	float getY() const;
	bool setZ(float val);
	float getZ() const;
	bool setRoll(float val);
	float getRoll() const;
	bool setPitch(float val);
	float getPitch() const;
	bool setYaw(float val);
	float getYaw() const;

private:
	MainStorage() = default;
	~MainStorage() = default;

    static MainStorage * instance_;
    static std::once_flag initInstanceFlag_;
	float x_ = 0.0f;
	float y_ = 0.0f;
	float z_ = 0.0f;
	float roll_ = 0.0f;
	float pitch_ = 0.0f;
	float yaw_ = 0.0f;
    mutable std::mutex lock_;
};


#endif // MAIN_STORAGE_H