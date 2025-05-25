# arduino_car_v4.5.6
The initial topic of the work was "Visualization of data from automation systems by creating an embedded server", however, I have expanded the scope of the work so as to study and try to provide a solution for the creation of a vehicle that will be controlled by the embedded web server. I want this control to be done manually by the user, with or without the use of sensors for driving assistance, and automatically. The goal of automatic movement is to map space and present it to the user. Overall, I want the server to be created on the Arduino board and once a client connects via a browser, a website will be served from which he can control the movement of the vehicle.

The Arduino file which ends in .ino has the code inside.
The index.h file is the HTML code in a way that is usable for the Arduino IDE.
The HTML file is used to quickly edit the page and preview it.
After you have made the correct connections and you have set up the hardware part
of the project, you need to open the .ino file from its folder and load it to 
the Arduino Uno R4 Wi-Fi plate. You need to name the folder it is inside the same
name as the .ino file and also include inside that folder the index.h file.
Afterward just connect to the access point that has been created and type
192.48.56.2 in a browser search bar.
Happy driving !! ;)
