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
#ifndef MOTIV_TIMELINE_HPP
#define MOTIV_TIMELINE_HPP


#include <QWidget>

#include "TimelineHeader.hpp"
#include "TimelineLabelList.hpp"
#include "src/ui/views/TimelineView.hpp"
#include "src/ui/TraceDataProxy.hpp"

/**
 * The Timeline class holds the actual @ref TimeLineView and also includes
 * a header that changes with the selection, and a list of names of the shown ranks on the left.
 */
class Timeline : public QWidget {
    Q_OBJECT

public:
    explicit Timeline(TraceDataProxy *data, QWidget *parent = nullptr);

private: // widgets
    TimelineHeader *header = nullptr;
    TimelineLabelList *labelList = nullptr;
    TimelineView *view = nullptr;

private: // data
    TraceDataProxy *data = nullptr;
};


#endif //MOTIV_TIMELINE_HPP
