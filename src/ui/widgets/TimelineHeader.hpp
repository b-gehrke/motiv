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
#ifndef MOTIV_TIMELINEHEADER_HPP
#define MOTIV_TIMELINEHEADER_HPP


#include <QWidget>

#include "src/ui/TraceDataProxy.hpp"

/**
 * @brief The TimelineHeader displays a horizontal bar with evenly distributed labels marking a time point.
 */
class TimelineHeader : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Creates a new instance of the TimelineHeader class
     *
     * @param data A pointer to a TraceDataProxy
     * @param parent The parent QWidget
     */
    TimelineHeader(TraceDataProxy *data, QWidget *parent = nullptr);

public Q_SLOTS:
    /**
     * @brief Updates the view
     *
     * The view is rerendered to reflect the current state of the TraceDataProxy
     */
    void updateView();

private: // widgets
    std::vector<QWidget *> labels;

private: // data
    TraceDataProxy *data = nullptr;
};


#endif //MOTIV_TIMELINEHEADER_HPP
