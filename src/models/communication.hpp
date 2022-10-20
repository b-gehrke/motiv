//
// Created by bjoern on 20.10.22.
//

#ifndef MOTIV_COMMUNICATION_HPP
#define MOTIV_COMMUNICATION_HPP

#include <otf2xx/otf2.hpp>

class Communication {
public:
    Communication(const otf2::chrono::duration &start, const otf2::chrono::duration &anEnd, std::string from,
                  std::string to);

    otf2::chrono::duration start;
    otf2::chrono::duration end;
    std::string from;
    std::string to;

};

#endif //MOTIV_COMMUNICATION_HPP
