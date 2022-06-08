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
	int size // size in bytes
) {
	std::vector<int> tensor(size / 4, 0);
	//PackageSize = global const variable, defined in dep.h
	int iterations = (size / sizeof(int32_t) + PackageSize - 1) / PackageSize;

	for (int i = 0; i < iterations; i++){
		zmq_msg_t buffer;
		int nbytes = zmq_msg_init(&buffer);
		nbytes = socket.recv(&buffer, PackageSize);
		if(nbytes == -1){
			printf("socket did not receive anything\n");
			return;
		}
		// std::vector<int> msmTemp(zmq_msg_size(&buffer));
		// std::memcpy(msmTemp.data(), zmq_msg_data(&buffer), zmq_msg_size(&buffer));
		// tensor.insert(tensor.end(), std::begin(msmTemp), std::end(msmTemp));

		//nightly likely not to work, but if it does, it would make 1 copy instead of
		// allocation and 2 copies
		tensor.insert(tensor.end(), zmq_msg_get(&buffer, 0), zmq_msg_size(&buffer));
	}
}
void Server::listen() {
	zmq::message_t msg;
	int32_t sizeOfIncommingBuffer;
	HTTPReq request = HTTPReq::None;

	//  Wait for next request from client
	int size = 	socket.recv(&msg);
	int sizeOfBufferInBytes = jsonSend::getReqAndSize(
		msg.to_string(),
	 	request
	);
	if (sizeOfBufferInBytes == -1) {
		//TODO: here you should request
		//to the client for another message
		return;
	}
	catchPostRequest(sizeOfBufferInBytes);
	//loop here
}