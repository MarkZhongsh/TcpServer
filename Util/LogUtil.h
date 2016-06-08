#ifndef LOGUTIL_H_H_
#define LOGUTIL_H_H_

#define safe_delete(x) if(x) { delete x; x = NULL; }

template<class T>
class FinalClass
{
private:
    friend T;
private:
    FinalClass(){}
    ~FinalClass(){}

};

class LogUtil : virtual FinalClass<LogUtil>
{
public:
    static void Log(const char *fmt, ...);
private:
    LogUtil(){}
    ~LogUtil(){}
    
};

#endif
