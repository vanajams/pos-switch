#include "include/core/switch_core.h"
#include "fraud/fraud_engine.h"
#include "gateway/tcp_server.h"
#include "iso8583/iso_message.h"
#include "iso8583/iso_parser.h"
#include "issuer/issuer_simulator.h"
#include "router/router.h"
#include "utils/logger.h"


int main()
{
    tcpServer server(8080);
    server.start;
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }
    return 0;
}
