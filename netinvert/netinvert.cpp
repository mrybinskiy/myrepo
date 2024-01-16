/*
 * POCO server string invert example
 */

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/HelpFormatter.h"

#include <iostream>

using namespace Poco;
using namespace Poco::Net;
using namespace Poco::Util;
using Poco::Util::HelpFormatter;

class NetInvertApp: public ServerApplication
{
private:
	const UInt16 DEFAULT_PORT = 28888;
	const int INPUT_MAX = 255;
	const std::string s_helloStr = 
		"Welcome to the POCO TCP Server.\nEnter your string:\n";
	
private:
    bool m_helpRequested = false;
    UInt16 m_port = DEFAULT_PORT; 
    		
public:	
    void initialize(Application& self)
    {
        loadConfiguration();
        ServerApplication::initialize(self);
    }

    void defineOptions(OptionSet& options)
    {
        ServerApplication::defineOptions(options);
        options.addOption(
		    Option("port", "p", "Set port number", false, "<port>", true)
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<NetInvertApp>(
					this, &NetInvertApp::handlePort))); 
        options.addOption(
		    Option("help", "h", "Display this help")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<NetInvertApp>(
					this, &NetInvertApp::handleHelp)));
    }

    void handleHelp(const std::string& name, const std::string& value)
    {
        HelpFormatter hf(options());
        hf.setCommand(commandName());
        hf.setUsage("OPTIONS");
        hf.setHeader("Example POCO TCP Server that inverts received string.");
        hf.format(std::cout);
        stopOptionsProcessing();
        m_helpRequested = true;
    }

    void handlePort(const std::string& name, const std::string& value)
    {
        UInt16 port = atoi(value.c_str());
        printf("Set %s %s > %hu\n", name.c_str(), value.c_str(), port);
        if ( port != 0 )
        {
            m_port = port;
        }
    }

    int main(const std::vector<std::string>&)
    {
        if (!m_helpRequested)
        {		
			logger().information("Starting POCO TCP server on port %hu", m_port);
			ServerSocket srv(m_port);
			while (true)
			{
				StreamSocket ss = srv.acceptConnection();
                logger().information("Client connected from %s",
                                     ss.address().host().toString());
				ss.sendBytes(s_helloStr.data(), s_helloStr.size());
				char buf [INPUT_MAX];				
				while (true)
				{
					int n = ss.receiveBytes(buf, INPUT_MAX);
					if (n == 0) // Graceful shutdown from the peer
					{
                        logger().information("Connection closed by peer");
                        ss.shutdown();
						break;
					}
					std::string str(buf, n);
					std::cout << str;						
					auto strEnd = str.end();
					if (str[n - 1] == '\n')
					{
						// keep the last newline from reversing
						strEnd--;
					}				
					std::reverse(str.begin(), strEnd);
					ss.sendBytes(str.data(), str.size());
				}
			}
		}
        return Application::EXIT_OK;
    }      

};

POCO_SERVER_MAIN(NetInvertApp)

