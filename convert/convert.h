#ifndef CONVERT_H
#define CONVERT_H

#include <iostream>
#include <iomanip>
#include <string>

class ConvertResponse {
    public:
        ConvertResponse();
        std::string static get_sha256_from_raw_bytes(const std::string& bytes);
        ~ConvertResponse();
};

#endif
