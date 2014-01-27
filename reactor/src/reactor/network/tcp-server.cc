#include <reactor/network/tcp-server.hh>
#include <reactor/scheduler.hh>

ELLE_LOG_COMPONENT("reactor.network.TCPServer");

namespace reactor
{
  namespace network
  {
    /*-------------.
    | Construction |
    `-------------*/
    TCPServer::TCPServer():
      Super()
    {}

    TCPServer::~TCPServer()
    {}

    /*----------.
    | Accepting |
    `----------*/
    std::unique_ptr<Socket>
    TCPServer::accept()
    {
      // Open a new raw socket.
      auto new_socket = elle::make_unique<TCPSocket::AsioSocket>(
        reactor::Scheduler::scheduler()->io_service());
      EndPoint peer;
      this->_accept(*new_socket, peer);
      // Socket is now connected so make it into a TCPSocket.
      std::unique_ptr<TCPSocket> res(
        new TCPSocket(std::move(new_socket), peer));
      ELLE_TRACE("%s: got connection: %s", *this, *res);
      return std::unique_ptr<Socket>(res.release());
    }
  }
}
