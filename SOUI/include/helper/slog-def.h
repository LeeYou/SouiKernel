#pragma once

//����һ��ʹ��SOUI��logģ��ĺ�
//���������LOG_FILTER����ʹ��soui��Ϊfilter
//����Ϊ��ͬ��CPP���岻ͬ��filter
//������demos/demo��demo.cpp��ʹ���������������һ��demo��filter
/*
#define LOG_FILTER "demo"
#include <helper/slog-def.h>
*/
//�����������壬�Ϳ���ֱ��ʹ��SLOG_INFO("a="+100)��������ʽ����LOG�������demoΪfilter��LOG�ˡ�

#ifndef LOG_FILTER
#define LOG_FILTER "soui"
#endif

#define SLOG_TRACE(log) LOGT(LOG_FILTER, log) 
#define SLOG_DEBUG(log) LOGD(LOG_FILTER, log) 
#define SLOG_INFO(log) LOGI(LOG_FILTER, log)  
#define SLOG_WARN(log) LOGW(LOG_FILTER, log)  
#define SLOG_ERROR(log) LOGE(LOG_FILTER, log) 
#define SLOG_ALARM(log) LOGA(LOG_FILTER, log) 
#define SLOG_FATAL(log) LOGF(LOG_FILTER, log) 


#define SLOGFMTT( fmt, ...) LOGFMTT(LOG_FILTER,  fmt,  ##__VA_ARGS__)
#define SLOGFMTD( fmt, ...) LOGFMTD(LOG_FILTER,  fmt,  ##__VA_ARGS__)
#define SLOGFMTI( fmt, ...) LOGFMTI(LOG_FILTER,  fmt,  ##__VA_ARGS__)
#define SLOGFMTW( fmt, ...) LOGFMTW(LOG_FILTER,  fmt,  ##__VA_ARGS__)
#define SLOGFMTE( fmt, ...) LOGFMTE(LOG_FILTER,  fmt,  ##__VA_ARGS__)
#define SLOGFMTA( fmt, ...) LOGFMTA(LOG_FILTER,  fmt,  ##__VA_ARGS__)
#define SLOGFMTF( fmt, ...) LOGFMTF(LOG_FILTER,  fmt,  ##__VA_ARGS__)
