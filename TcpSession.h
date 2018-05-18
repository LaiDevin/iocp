#pragma once
#include "IIoObject.h"
#include "IoCallbackAccept.h"
#include "IoCallbackConnect.h"
#include "IoCallbackRecv.h"
#include "IoCallbackReuse.h"
#include "IoCallbackSend.h"

class Socket;
class TcpListener;
class TcpSession final : public IIoObject, public enable_shared_from_this<TcpSession>
{
public:
	TcpSession();
	~TcpSession();

	//	{{GET}}
	HANDLE GetHandle() const override;
	inline Socket* GetSocket() const
	{
		return _pSocket;
	}
	//	{{GET}}

	//	{{SET}}
	inline void SetLocalSockaddr( const SOCKADDR& sockaddr )
	{
		_localSockaddr = sockaddr;
	}
	inline void SetRemoteSockaddr( const SOCKADDR& sockaddr )
	{
		_remoteSockaddr = sockaddr;
	}
	//	{{SET}}

	bool Accept();
	bool Accept( shared_ptr<TcpListener> listenerPtr, const IoCallback::Fn&& fn );
	void Close();
	bool Create();
	bool ProcessRecvData( const function<bool( CircularBuffer& )>&& fn );
	bool Recv( const IoCallback::Fn&& fn );
	bool Reuse( const IoCallback::Fn&& fn );
	bool Send( const IoCallback::Fn&& fn );

private:
	bool _Accept();

private:
	Socket* _pSocket = nullptr;
	SOCKADDR _localSockaddr;
	SOCKADDR _remoteSockaddr;
	IoCallbackAccept _acceptCallback;
	IoCallbackConnect _connectCallback;
	IoCallbackRecv _recvCallback;
	IoCallbackReuse _reuseCallback;
	IoCallbackSend _sendCallback;
};