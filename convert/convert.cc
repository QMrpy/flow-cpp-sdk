#include "convert.h"

ConvertResponse::ConvertResponse() {}

std::string ConvertResponse::get_sha256_from_raw_bytes(const std::string& bytes) {
    std::stringstream stream;

    for (int i = 0; i < bytes.size(); i++) {
        stream << std::setw(2) << std::setfill('0') << std::hex << (uint16_t(bytes[i]) & 0xff);
    }

    return stream.str();
}

ConvertResponse::~ConvertResponse() {}