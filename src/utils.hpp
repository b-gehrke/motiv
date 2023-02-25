/*
 * Marvelous OTF2 Traces Interactive Visualizer (MOTIV)
 * Copyright (C) 2023 Florian Gallrein, Björn Gehrke
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef MOTIV_UTILS_HPP
#define MOTIV_UTILS_HPP

#include <QLayout>
#include <QWidget>
#include <QDebug>
#include "src/models/communication/CommunicationKind.hpp"
#include "src/models/Range.hpp"

/**
 * Resets a QLayout and deletes all child widgets.
 *
 * Source: https://stackoverflow.com/a/56966160
 *
 * @param apLayout layout to reset
 */
void resetLayout(QLayout *apLayout);

std::string communicationKindName(CommunicationKind kind);

std::string collectiveCommunicationOperationName(otf2::collective_type type);

template<typename T, typename K, typename C = std::less<K>>
std::map<K, Range<T>, C> groupBy(Range<T> range, std::function<K(const T)> keySelector, std::function<bool(const T, const T)> compare) {

    std::map<K, Range<T>, C> group;

    if(range.empty()) {
        return group;
    }

    C keyComparator;

    std::sort(range.begin(), range.end(), compare);

    auto start = range.begin();
    auto it = range.begin() + 1;
    while(it != range.end()) {
        auto key = keySelector(*it);
        auto startKey = keySelector(*start);
        if((keyComparator(key, startKey) || keyComparator(startKey, key))) {
            auto r = std::vector<T>(start, it);
            group[startKey] = Range<T>(r);
            start = it;
        }

        it++;
    }
    auto startKey = keySelector(*start);
    auto r = std::vector<T>(start, it);
    group[startKey] = Range<T>(r);

    return group;
}

template<typename T, typename K, typename C = std::less<K>>
std::map<K, Range<T>, C> groupBy(Range<T> range, std::function<K(const T)> keySelector) {
    return groupBy(range, keySelector, [](const T lhs, const T rhs) {return lhs < rhs;});
}


#endif //MOTIV_UTILS_HPP
