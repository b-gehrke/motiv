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
#ifndef MOTIV_TIMELINELABELLIST_HPP
#define MOTIV_TIMELINELABELLIST_HPP


#include <QListWidget>

#include "src/ui/TraceDataProxy.hpp"

/**
 * The TimelineLabelList displays a vertical bar with a list of rank names.
 *
 * @TODO for configurable region heights, the height of the labels should be adjusted here too
 */
class TimelineLabelList : public QListWidget {
    Q_OBJECT

public:
    TimelineLabelList(TraceDataProxy *data, QWidget *parent = nullptr);

protected:
    /*
     * NOTE: we override this function to prevent the items from being clicked/activated.
     * this is quite hacky and there might be a better solution.
     */
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    TraceDataProxy *data = nullptr;
};


#endif //MOTIV_TIMELINELABELLIST_HPP
