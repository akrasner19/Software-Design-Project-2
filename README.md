# Software-Design-Project-2
This project is a QT GUI that makes use of the interpreter from project 1. In addition to supporting the execution of  different functions in the GUI, the GUI permits drawing objects onto a canvas and gives feedback for errors and executed tasks.

Examples: 

(draw (line (point 10 0) (point 0 10)))

(draw (arc (point 0 0) (point 100 0) pi))

(draw (point (- 15 0) (* 2 3)))

Commands are tokenized and parsed into an execution tree. The commands are then recursively evaluated to a final result. Variables are stored in an environment map for the duration of the execution.

The objects to be drawn are created and then passed in a signal to the slot that draws them onto the canvas.

The goal of this project was to gain experience using QT and writing GUIs. 

ECE 3574 Project 2
