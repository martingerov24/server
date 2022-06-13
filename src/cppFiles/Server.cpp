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

//there ain't no way for this to work
void Server::catchPostRequest(
<<<<<<< HEAD
	std::vector<int32_t>& tensor,
	int size // size in bytes
) {
=======
	std::vector<int32_t> tensor,// output tensor
	int size 					// size in bytes
) {
	tensor.resize(size / 4, 0);
	//PackageSize = global const variable, defined in dep.h
>>>>>>> 8b836fd3a26a4f1b9ac092ae39fed31db9e5d7d7
	int iterations = (size / sizeof(int32_t) + PackageSize - 1) / PackageSize;
	zmq::message_t buffer(size);
	Dprintf("initing zmq::message_t, size -> %d", buffer.size());
	socket.recv(&buffer, size);

<<<<<<< HEAD
	zmq_sleep(1);
	socket.send(zmq::buffer("kakvo stavaa be brato"), zmq::send_flags::none);

	tensor.resize(size);
	std::memcpy(tensor.data(), &buffer, buffer.size());
	// tensor.insert(tensor.end(), &buffer, buffer.size());
=======
	Dprintf("%d -> iterations ", iterations);
	for (int i = 0; i < iterations; i++){
		zmq_msg_t buffer;
		int nbytes = zmq_msg_init(&buffer);

		Dprintf("%d -> nbytes before", nbytes);
		nbytes = zmq_recv(&socket, &buffer, PackageSizeInBytes, ZMQ_DONTWAIT);
		// nbytes = socket.recv(&buffer, PackageSizeInBytes);
		Dprintf("%d -> nbytes after", nbytes);

		if(nbytes == -1){
			Dprintf("function send returned -> %d", nbytes);
			return;
		}
		// std::vector<int> msmTemp(zmq_msg_size(&buffer));
		// std::memcpy(msmTemp.data(), zmq_msg_data(&buffer), zmq_msg_size(&buffer));
		// tensor.insert(tensor.end(), std::begin(msmTemp), std::end(msmTemp));

		// highly likely not to work, but if it does, it would make 1 copy instead of
		// allocation and 2 copies
		socket.send(zmq::buffer("cross fingers mfuckers!\n"), zmq::send_flags::none);
		tensor.insert(tensor.end(), zmq_msg_get(&buffer, 0), zmq_msg_size(&buffer));
	}
>>>>>>> 8b836fd3a26a4f1b9ac092ae39fed31db9e5d7d7
}
void Server::listen() {
	zmq::message_t msg;
	int32_t sizeOfIncommingBuffer;
	HTTPReq request = HTTPReq::None;

<<<<<<< HEAD
	//  Wait for next request from client
	socket.recv(&msg);
=======
	socket.recv(&msg);
	Dprintf("%s -> iterations", msg.to_string().c_str());
>>>>>>> 8b836fd3a26a4f1b9ac092ae39fed31db9e5d7d7
	int sizeOfBufferInBytes = jsonSend::getReqAndSize(
		msg.to_string(),
	 	request
	);
	Dprintf("message is %s",msg.to_string().c_str());
	if (sizeOfBufferInBytes == -1) {
		return;
	}
<<<<<<< HEAD
	socket.send(zmq::buffer("potato"), zmq::send_flags::dontwait);
=======
	Dprintf("%d -> sizeOfBufferInBytes", sizeOfBufferInBytes);
	socket.send(zmq::buffer("good soup\n"));
>>>>>>> 8b836fd3a26a4f1b9ac092ae39fed31db9e5d7d7
	std::vector<int32_t> tensor;
	catchPostRequest(tensor, sizeOfBufferInBytes);
	//loop here
}