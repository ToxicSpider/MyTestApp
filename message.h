#ifndef MESSAGE_H
#define MESSAGE_H


/*
This is the structure of a "Message" 
These messages are exchanged between tasks by placing them in each other's queues. 
Each message has two fields: type and data. They are placed in a separate header to allow access to them from anywhere in the code, 
without the need to include unnecessaries in a specific *.cc or *.h file.
*/

enum class DataType {
	X, Y, Z, Roll, Pitch, Yaw
};


struct Message { // No need for copy constructors (except the default) because the data fields are primitive
	float data;
	DataType type;
};

#endif // MESSAGE_H