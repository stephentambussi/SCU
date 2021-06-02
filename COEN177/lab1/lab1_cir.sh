# Name: Stephen Tambussi
# Date: 4/1/2021
# Title: Lab1 - Basic Shell Programming
# Description: This program is a simple shell script that 
# computes the area of a rectangle and a circle
#!/bin/sh
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$

user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ $user = "stambuss" ]
then
	echo "Now you can proceed!"
else
	echo "Check who logged in!"
	exit 1
fi

response="Yes"
while [ $response != "No" ]
do
	echo "Enter height of rectangle: "
	read height
	echo "Enter width of rectangle: "
	read width
	area=`expr $height \* $width`
	echo "The area of the rectangle is $area"
	
	echo "Enter radius of circle: "
	read radius
	area=$(echo "scale = 2; 3.14 * $radius * $radius" | bc) #uses bc for float numbers and 3.14 for pi
	echo "The area of the circle is $area"

	echo "Would you like to repeat for another rectangle and circle [Yes/No]?"
	read response
done
