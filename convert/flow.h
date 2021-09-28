#ifndef FLOW_H
#define FLOW_H

#include "convert.h"
#include <string>

namespace flow {
    class Identifier {
        private:
            std::string id; // 32-byte ID

        public:
            Identifier(): id("") {}
            Identifier(std::string& _id) : id(_id) {}
            std::string Bytes() {}
            std::string Hex() {}
            std::string String() {}
            virtual ~Identifier(); 
    }
}

#endif
