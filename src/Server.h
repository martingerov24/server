#pragma once
#include "../cppzmq/zmq.hpp"
class Server
{
	Server(Server& other) = delete;
	Server operator=(Server& other) = delete;
public:
	Server() = default;
	Server(Server&& other) noexcept;
	void bind(const std::string&& port);
	Server& operator=(Server&& other) noexcept;
	void testFuncRecvJob(std::vector<std::string>& jsons);
	void ConvertStringtoJson(std::vector<std::string>& strings);
	~Server() = default;
private:
	zmq::context_t context{ 1 };
	zmq::socket_t  socket{ context, zmq::socket_type::rep};
};
