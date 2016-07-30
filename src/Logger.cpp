#include "Logger.hpp"

void Logger::print(Level level, const string& message)
{
    string msg;
    if(level == DEBUG)
        msg = "[DEBUG] " + message;
    else if(level == INFO)
        msg = "[INFO] " + message;
    else if(level == WARNING)
        msg = "[WARNING] " + message;
    else if(level == ERROR)
        msg = "[ERROR] " + message;
    else if(level == CRITICAL)
        msg = "[CRITICAL] " + message;

    if(is_tty)
    {
        if(level == DEBUG)
            msg = ANSI_COLOR_BLUE + msg;
        else if(level == INFO)
            msg = ANSI_COLOR_GREEN + msg;
        else if(level == WARNING)
            msg = ANSI_COLOR_YELLOW + msg;
        else if(level == ERROR)
            msg = ANSI_COLOR_RED + msg;
        else if(level == CRITICAL)
            msg = ANSI_COLOR_MAGENTA + msg;
        msg = msg + ANSI_COLOR_RESET;
    }

    cout << msg << endl;
}

Logger::Logger(Level min_verbosity)
{
    verbosity_level = min_verbosity;
#ifdef _WIN32
    is_tty = _isatty(_fileno(stdout));
#else
    is_tty = isatty(fileno(stdout));
#endif
}
