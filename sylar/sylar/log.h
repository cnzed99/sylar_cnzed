#pragma once

#include<string>
#include<stdint.h>
#include<memory>
#include<list>
#include<sstream>
#include<fstream>
#include<vector>
#include<stdarg.h>
#include<map>
#include "util.h"
#include "singleton.h"

namespace sylar
{
    class Logger;

    //日志级别
    class LogLevel
    {
        public:
        enum Level
        {
            UNKNOW = 0,
            DEBUG = 1,
            INFO = 2,
            WARN = 3,
            ERROR = 4,
            FATAL = 5
        };
        static const char* ToString(LogLevel::Level level);
    };
    
    //日志事件
    class LogEvent
    {
        public:
        typedef std::shared_ptr<LogEvent> ptr;
        LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level,
                 const char* file, int32_t m_line, uint32_t elapse,
                 uint32_t thread_id, uint32_t fiber_id, uint64_t time);

        const char* getFile() const { return m_file;}
        int32_t getLine() const { return m_line;}
        uint32_t getElapse() const { return m_elapse;}
        uint32_t getThreadId() const { return m_threadId;}
        uint32_t getFiberId() const { return m_fiberId;}
        uint64_t getTime() const { return m_time;}
        std::string getContent() const { return m_ss.str();}
        std::shared_ptr<Logger> getLogger() const { return m_logger;}
        LogLevel::Level getLevel() const { return m_level;}

        private:
        const char* m_file = nullptr;   //文件名
        int32_t m_line = 0;             //行号
        uint32_t m_elapse = 0;          //程序启动开始到现在的毫秒数
        uint32_t m_threadId = 0;        //线程id
        uint32_t m_fiberId = 0;         //协程id
        uint64_t m_time = 0;            //时间戳
        std::stringstream m_ss;

        std::shared_ptr<Logger> m_logger;
        LogLevel::Level m_level;
    };

    //日志格式器
    class LogFormatter {
    public:
        typedef std::shared_ptr<LogFormatter> ptr;
        LogFormatter(const std::string& pattern);

        //%t    %thread_id %m%n
        std::string format(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);
    public:
        class FormatItem {
        public:
            typedef std::shared_ptr<FormatItem> ptr;
            virtual ~FormatItem() {}
            virtual void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;
        };

        void init();
    private:
        std::string m_pattern;
        std::vector<FormatItem::ptr> m_items;

    };

    //日志输出位置
    class LogAppender
    {
        public:
        typedef std::shared_ptr<LogAppender> ptr;
        virtual ~LogAppender() {}

        virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;

        void setFormatter(LogFormatter::ptr val) ()

        protected:
        LogLevel::Level m_level = LogLevel::DEBUG;
        LOGFormatter::ptr m_formatter;
    };




} // namespace sylar
