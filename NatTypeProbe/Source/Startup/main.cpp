#include <iostream>
#include "../Nat/NatProb.h"

#ifdef WIN32
#include <time.h>
#pragma comment(lib, "WS2_32.lib")
#else
#include <sys/time.h>
#endif


using namespace std;


UInt64 Milliseconds()
{
#ifndef WIN32
    struct timeval tv;
	if (-1 == gettimeofday(&tv, NULL))
	{
		return 0;
	}

	return (tv.tv_sec * (UInt64)1000 + tv.tv_usec / 1000);
#else
    SYSTEMTIME sysTime;
    FILETIME fileTime;
    LARGE_INTEGER li;

    GetLocalTime(&sysTime);
    SystemTimeToFileTime(&sysTime, &fileTime);

    li.LowPart = fileTime.dwLowDateTime;
    li.HighPart = fileTime.dwHighDateTime;

    return li.QuadPart / 10000;
#endif
}

int main()
{
    /*
     * 亲测可用的Nat穿透服务器
     * stun.ekiga.net
     * stun.ideasip.com
     * stun.schlund.de
     * stun.voiparound.com
     * stun.voipbuster.com
     * stun.voipstunt.com
     * stun.voxgratia.org
     * stun.xten.com
     */
    string strNatServerIP = "stun.xten.com";
    do
    {
        for (int i = 0; i < 5; ++i)
        {
            CNatProb natProb;
            if (!natProb.Init(strNatServerIP))
            {
                cout<<"natProb init failed."<<endl;
                break;
            }
            UInt64 nStart = Milliseconds();
            NatType natType = natProb.GetNatType();
            UInt64 nEnd = Milliseconds();
            cout<<"-------------------natType = " << CNatProb::DescribeNatType(natType) << "    time = " << nEnd - nStart << endl;


            for (int j = 0; j < 4; ++j)
            {
                const string strLocalIp = "0.0.0.0";
                const UInt16 uLocalPort = 10000+rand()%1000;
                string strPublicIp;
                UInt16 uPublicPort;

                nStart = Milliseconds();
                bool bRet = natProb.GetNatIpAndPort(strLocalIp, uLocalPort, strPublicIp, uPublicPort);
                nEnd = Milliseconds();
                cout<< "Is Ok ?  "<< bRet << "    uLocalPort = " << uLocalPort << "  strPublicIp = " << strPublicIp << " uPublicPort = " << uPublicPort << "   time = " << (nEnd - nStart)<<endl;
            }

        }

    }while (0);
	cout << "------end------" <<endl;
	getchar();

    return 0;
}