# Using vpython to create virtual world
# Reading data from arduino ultrasonic sensor using pyserial

import serial
import vpython


arduino_serial_data = serial.Serial('/dev/ttyACM0', baudrate = 9600, timeout = 1)

#MyScene=vpython.canvas(title='My Virtual World') #Create your scene and give it a title.
 
#MyScene.width=800  #We can set the dimension of your visual box. 800X800 pixels works well on my screen
#MyScene.height= 800
#MyScene.autoscale=False #We want to set the range of the scene manually for better control. Turn autoscale off
#MyScene.range = vpython.vector(20,20,20) #Set range of your scene to be 12 inches by 12 inches by 12 inches. 

target=vpython.box(color=vpython.color.green, length=.1, width=10,height=5, pos=vpython.vector(-6,0,0)) 
sensor=vpython.box(length=1.5, width=10,height=5, pos=vpython.vector(-9.5,0,0)) #back of the ultrasonic sensor
sensor_tube_left=vpython.cylinder(color=vpython.color.blue, pos=vpython.vector(-8.5,0,-2.5), radius=1.5,length=2.5 ) 
sensor_tube_right=vpython.cylinder(color=vpython.color.blue, pos=vpython.vector(-8.5,0,2.5), radius=1.5,length=2.5 ) 
myBall=vpython.sphere(color=vpython.color.red, radius=.3)

measuring_rod = vpython.cylinder(length=6+2.5, color= vpython.color.yellow, radius = .1, pos = vpython.vector(-9.5,-2,0) )
length_label = vpython.label(text = "Target distance is:", pos = vpython.vector(0,5,0), height=30, box = False)
#target = vpython.box(color=vpython.color.green, length=.2, width=3, height = 3, pos = vpython.vector(0,-.5,0))

while True:
    # to dynamically change a property in vpython, tell it how many times each second
    vpython.rate(10)

    if arduino_serial_data.in_waiting > 0:
        myData = arduino_serial_data.readline()
        #print(myData)
        distance = float(myData.decode().rstrip())
        print(distance)
        my_label = f"Target distance is: {distance}"
        if (distance>=1.5 and distance<=25):    #only change color or target if target is between 1.5 and 20 cm from sensor
            target.pos=vpython.vector(-6 + distance,0,0)  #Adjust the position of the target object to match the distance of the real target from the real sensor


            length_label.text = my_label
            measuring_rod.length = distance + 3.5
            #target.pos = vpython.vector(-3+distance,-.5,0)

