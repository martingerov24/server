#include "Server.h"
#include "json.h"
Server::Server(
	Server&& other
) noexcept {
	std::swap(*this, other);
}

Server::~Server()
{
	socket.close();
	context.close();
}

Server& Server::operator=(
	Server&& other
) noexcept {
	if (this != &other)
	{
		std::swap(*this, other);
	}
	return *this;
}

void Server::bind(
	const std::string& port
) {
	socket.bind(port);
}

void Server::catchPostRequest(
	std::vector<int32_t>& tensor,
	int size // size in bytes
) {
	int iterations = (size / sizeof(int32_t) + PackageSize - 1) / PackageSize;
	zmq::message_t buffer(size);
	Dprintf("initing zmq::message_t, size -> %d", buffer.size());
	socket.recv(&buffer, size);

	zmq_sleep(1);
	socket.send(zmq::buffer("kakvo stavaa be brato"), zmq::send_flags::none);

	tensor.resize(size);
	std::memcpy(tensor.data(), &buffer, buffer.size());
	// tensor.insert(tensor.end(), &buffer, buffer.size());
}
void Server::listen() {
	zmq::message_t msg;
	int32_t sizeOfIncommingBuffer;
	HTTPReq request = HTTPReq::None;

	//  Wait for next request from client
	socket.recv(&msg);
	int sizeOfBufferInBytes = jsonSend::getReqAndSize(
		msg.to_string(),
	 	request
	);
	Dprintf("message is %s",msg.to_string().c_str());
	if (sizeOfBufferInBytes == -1) {
		//TODO: here you should request
		//to the client for another message
		printf("the size of buffer in bytes is below 0\n");
		return;
	}
	socket.send(zmq::buffer("potato"), zmq::send_flags::dontwait);
	std::vector<int32_t> tensor;
	catchPostRequest(tensor, sizeOfBufferInBytes);
	//loop here
}