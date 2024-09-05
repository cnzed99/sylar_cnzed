#include<iostream>
#include"sylar/log.h"
#include"sylar/util.h"

int main(int argc, char **argv)
{
    //创建Logger实例
    sylar::Logger::ptr logger(new sylar::Logger());

     // 创建一个控制台日志输出
    sylar::LogAppender::ptr consoleAppender(new sylar::StdoutLogAppender());
    logger->addAppender(consoleAppender);

     // 创建一个文件日志输出
    sylar::FileLogAppender::ptr file_appender(new sylar::FileLogAppender("./log.txt"));
    sylar::LogFormatter::ptr fmt(new sylar::LogFormatter("%d%T%p%T%m%n"));
    file_appender->setFormatter(fmt);
    file_appender->setLevel(sylar::LogLevel::ERROR);

    logger->addAppender(file_appender);

    // 创建 LogEvent 实例
    // sylar::LogEvent::ptr event(new sylar::LogEvent(logger,sylar::LogLevel::DEBUG, __FILE__, __LINE__, 0, 1, 1, time(0)));
    // // 设置日志内容
    // event->getSS() << "this is a debug test";
    
    // logger->log(sylar::LogLevel::DEBUG, event);
    std::cout << "hello sylar log" << std::endl;

    SYLAR_LOG_DEBUG(logger) << "test debug" ;
    SYLAR_LOG_ERROR(logger) << "test macro error";

    SYLAR_LOG_FMT_ERROR(logger, "test macro fmt error %d", 123456);
    SYLAR_LOG_FMT_ERROR(logger, "test macro fmt error %s", "aa");

    auto l = sylar::LoggerMgr::GetInstance()->getLogger("xx");
    SYLAR_LOG_INFO(l) << "xxx";
    return 0;
}