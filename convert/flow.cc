#include "flow.h"

namespace flow {
    std::string Identifier::Bytes() {
        return this->id;
    }
    std::string Identifier::Hex() {
        return ConvertResponse().get_sha256_from_raw_bytes(this->id);
    }
    std::string Identifier::String() {
        return this->Hex();
    }
}