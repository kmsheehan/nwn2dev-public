//
// Created by Kevin Sheehan on 2/10/18.
//

#include "Precomp.h"
#include "OsCompat.h"

std::string
OsCompat::getFileExt(const std::string& s) {

    size_t i = s.rfind('.', s.length());
    if (i != std::string::npos) {
        return(s.substr(i+1, s.length() - i));
    }

    return("");
}

char * OsCompat::filename(const char *str) {
    char *result;
    char *last;
    char *tmpStr = const_cast<char *>(str);
    if ((last = strrchr(tmpStr, '.')) != NULL ) {
        if ((*last == '.') && (last == tmpStr))
            return tmpStr;
        else {
            result = (char*) malloc(_MAX_FNAME);
            snprintf(result, sizeof result, "%.*s", (int)(last - tmpStr), tmpStr);
            return result;
        }
    } else {
        return tmpStr;
    }
}

char * OsCompat::extname(const char *str) {
    char *result;
    char *last;
    char *tmpStr = const_cast<char *>(str);

    if ((last = strrchr(tmpStr, '.')) != NULL) {
        if ((*last == '.') && (last == tmpStr))
            return "";
        else {
            result = (char*) malloc(_MAX_EXT);
            snprintf(result, sizeof result, "%s", last + 1);
            return result;
        }
    } else {
        return ""; // Empty/NULL string
    }
}
