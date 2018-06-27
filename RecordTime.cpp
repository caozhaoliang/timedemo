#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <vector>
#include <string.h>
using namespace std;

string  g_StartDateTime="2018-06-27 23:00:00";
void split(string strSrc,string sep,vector<string>& v_rsp){
	char* token = strtok(const_cast<char*>(strSrc.c_str()),sep.c_str());
	while(token){
		v_rsp.push_back(string(token));
		token = strtok(NULL,sep.c_str() );
	}
	return;
}
long str2Time(string sTime){
	struct tm tm_time;
	strptime(sTime.c_str(),"%Y-%m-%d %H:%M:%S",&tm_time);
//	printf("%ld\n",mktime(&tm_time));
	return mktime(&tm_time);
}
string time2Str(long time)
{
	char szBuf[256] = {0};
	time_t timer = time;
	strftime(szBuf, sizeof(szBuf), "%Y-%m-%d %H:%M:%S", localtime(&timer));	
//	printf("%s\n",szBuf);
	return string(szBuf);
}

//sTime=100 365 
void GetDateSpan(string start, string sTime="")
{
	time_t t_now;
	time(&t_now);
	if(sTime.empty()){
		//计算从开始时间到现在过去的日子
		long lstart = str2Time(start);
		printf("开始时间%s距今过去%ld天\n",start.c_str(),(t_now-lstart)/(60*60*24));
	}else{
		//输出距离某个时间剩余多少时间 sTime -(现在减去 开始时间) 如果少于0不输出
		long lstart = str2Time(start);
		long date=atol(sTime.c_str());
		long nspan= (t_now-lstart)/(60*60*24);
		if( (date - nspan) >=0 ){
		printf("开始时间%s 今天距离%ld天 还剩%ld天\n",start.c_str(),date,date-(t_now-lstart)/(60*60*24));
		}else{
			printf("date:%ld,t_now:%ld,lstart:%ld,nspan:%ld\n",date,t_now,lstart,nspan);
		}
	}
	return;
}

void GetTimeSecond(string sTime)
{
	//输出当前时间减去开始时间的总秒数
	long start = str2Time(sTime);
	time_t t_now;
	time(&t_now);
	long span = t_now-start;
	printf("开始时间%s距离距离现在%s过去%lds、%ld天\n",sTime.c_str(),
			time2Str(t_now).c_str(),span,span/(60*60*24));	

}

int main()
{
	vector<string> v_temp;
	string sep="|";
	split(g_StartDateTime,sep,v_temp);
	vector<string>::iterator it = v_temp.begin();
	for(; it != v_temp.end(); ++it){
		GetTimeSecond(*it);
		GetDateSpan(*it,string("100"));	
	}
	return 0;
}
