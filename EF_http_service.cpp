#include "EF_http_service.h"
#include <iostream>
#include <sys/types.h>          
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

#include "UrlResolve.h"

using namespace std;

EF_http_service::EF_http_service()
{
	socket_fd = -1;
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_fd < 0)
	{
		cout << "socket error!" << endl;
	}
}

EF_http_service::~EF_http_service()
{
	close(socket_fd);
}

bool EF_http_service::set_url(const string &url_addr)
{
	url_st url_temp;
	UrlResolve urlresolve;
	urlresolve.set_url(url_addr);
	if(!urlresolve.url_resolve(url_temp))
	{
		cout << "EF_http_service::set_url error!\n" << endl;
		return false;
	}
	m_url_host = url_temp.host;
	m_url_path = url_temp.path;
	cout << m_url_host << endl;
	cout << m_url_path << endl;

	m_request_line = "POST " + m_url_path + " HTTP/1.1\r\n";

	return true;
}

bool EF_http_service::add_request_head(string name, string value)
{
	m_request_head += name + ": " + value;
	return true;
}

bool EF_http_service::http_post()
{
	if(m_url_host.empty())
	{
		cout << "please set url!" << endl;
		return false;
	}
	
	struct hostent * hostaddr;
	hostaddr = gethostbyname(m_url_host.c_str());

	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)hostaddr->h_addr_list[0]));
    serv_addr.sin_port = htons((short)443);

    cout << serv_addr.sin_addr.s_addr <<endl;

     for(int i=0; hostaddr->h_addr_list[i]; i++){
        cout << "IP addr: " << inet_ntoa( *(struct in_addr*)hostaddr->h_addr_list[i] ) << endl;
    }

    if(connect(socket_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
    	perror("connect error");
    	cout << "connect error!\n" << endl;
    }

    if (send(socket_fd, m_request_line.c_str(), 1024, 0) < 0)  
    {  
        perror("send error!");  
    }

    char rcvBuf[2048] = {0};
	while(1)
	{ 
        if (recv(socket_fd, rcvBuf, 2048, 0)<0)  
        {  
            perror("recv error!");   
        }  
        else 
        {  
            printf("%s",rcvBuf);
        }  
    }
  
}