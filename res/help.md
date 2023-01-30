# Views

In the center a visualisation of the otf2 trace is shown.

**Each line** represents the function calls in an MPI rank.

**Each block** represents a function call. Nested calls are shown on top. To see an entire call hover over it. The color of the block indicates its type. By default, these are:
- MPI calls: green
- OpenMP calls: red
- Any other calls: grey

**Arrows** depict MPI communications between ranks.

**Rectangles** stretching over all ranks show collective operations.  


# Usage

## Navigating the view

Use `CTRL` and scroll to **zoom in and out**. Use `SHIFT` and scroll to **move the view horizontally**. Reset the view with *View -> Reset* zoom or press `CTRL+R`. Alternatively, input the start and / or end time in the fields at the bottom of the view and press `ENTER` to zoom to a precise time window.

## Interactions

Click on any element to see more information on it in the right pane. Click the *Zoom into view* button to zoom to the current selected item.

## Filter

Use *View -> Filter* or press `CTRL+S` to open a filter window.

### Filter function call types

Check or uncheck the kinds of functions that should be shown.


