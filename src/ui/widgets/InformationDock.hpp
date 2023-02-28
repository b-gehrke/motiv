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
#ifndef MOTIV_INFORMATIONDOCK_HPP
#define MOTIV_INFORMATIONDOCK_HPP


#include "TimeUnitLabel.hpp"
#include "src/ui/TraceDataProxy.hpp"
#include "src/ui/widgets/infostrategies/InformationDockElementStrategy.hpp"
#include <QLabel>
#include <QFormLayout>
#include <QDockWidget>

/**
 * @brief A UI component that shows additional information
 *
 * An InformationDock shows more detailed and additional information about the current selected item.
 */
class InformationDock : public QDockWidget {
Q_OBJECT
public:
    /**
     * @brief Creates a new instance of the InformationDock class
     * @param parent The parent QWidget
     */
    explicit InformationDock(QWidget *parent = nullptr);
    ~InformationDock() override;

public:
    /**
     * @brief Add a strategy to display information for specific items
     *
     * When the selection changes the InformationDock instance iterates over all added InformationDockElementStrategy s
     * and tries to update them until the first reports it accepted the update by returning True from the update function.
     *
     * @param s The strategy to add
     */
    void addElementStrategy(InformationDockElementStrategy *s);

public:
Q_SIGNALS:
    /**
     * @brief Signal indicating to zoom to a specific time window
     *
     * @param from The time at which the new time window should start
     * @param to The time at which the new time window should end
     */
    void zoomToWindow(types::TraceTime from, types::TraceTime to);

private Q_SLOTS:

    /**
     * @brief Handler for clicked event of the zoom into view button
     */
    void zoomIntoViewPressed();

public Q_SLOTS:

    /**
     * @brief Sets the current element.
     *
     * This triggers an updateView call
     *
     * @param element The newly selected element
     */
    void setElement(TimedElement *element);

protected:
    /**
     * @brief Updates the view
     *
     * This function iterates over all added InformationDockElementStrategy s
     * and tries to update them until the first reports it accepted the update by returning True from the update function.
     */
    virtual void updateView();

private: // fields
    TimedElement *element_ = nullptr;

private:
    std::vector<std::pair<QWidget*, InformationDockElementStrategy*>> strategies_ {};
};


#endif //MOTIV_INFORMATIONDOCK_HPP
