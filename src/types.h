#ifndef MOTIV_TYPES_H
#define MOTIV_TYPES_H

#include <variant>
#include <otf2xx/otf2.hpp>

namespace types {
    typedef std::variant<otf2::definition::detail::weak_ref<otf2::definition::comm>, otf2::definition::detail::weak_ref<otf2::definition::inter_comm>> communicator;
}

#endif //MOTIV_TYPES_H
