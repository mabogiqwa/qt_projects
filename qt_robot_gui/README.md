# qt_robot_gui
A repository for the files containing the code of a robot(traffic light) program
Traffic Light Simulator GUI Application
This GUI application simulates a traffic light (robot) with three possible lights: green, yellow, and red. The application adheres to specific conditions for user interaction and functionality.

Features:
Traffic Light Colors:
Green
Yellow
Red
User Interaction:
Setting Time Interval:

The user is allowed to specify the time interval once on the GUI.
Once set, the user cannot change the time during the execution of the application.
Traffic Light Sequence:

The application utilizes a QTimer to manage the time between different colors of the traffic light.
After the user has specified the time, the application displays the traffic light sequence: green, yellow, red.
The sequence repeats with uniform time intervals between different colors.
Display:

Traffic lights and the widget for specifying the time interval are on the same GUI.
The three different colors of the traffic light are represented using image files: green.jpg, yellow.jpg, and red.jpg.
How to Use:
Run the application.
Specify the time interval using the provided widget.
Observe the simulated traffic light changing colors with uniform time intervals.
Note:
The application assumes that the specified image files (green.jpg, yellow.jpg, red.jpg) are available and will be displayed to represent different colors of the traffic light.
Feel free to use and modify this application according to your needs. If you have any questions or suggestions, please let me know.
