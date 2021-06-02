# Name: Stephen Tambussi
# Date: 4/1/2021
# Title: Lab1 - Basic Shell Programming
# Description: This program is a simple shell script that 
# computes the area of a rectangle
#!/bin/sh
echo Executing $0
echo $(/bin/ls | wc -l) files #gets number of files in current directory
wc -l $(/bin/ls) #number of lines in the files in directory
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD #current working directory
echo "\$\$"=$$ #gets process id

user=`whoami` #gets current user's name
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on." 
if [ $user = "stambuss" ] #checks if user is me
then
	echo "Now you can proceed!"
else
	echo "Check who logged in!"
	exit 1
fi

response="Yes"
while [ $response != "No" ] #executes rectangle area calculation until user inputs No
do
	echo "Enter height of rectangle: "
	read height
	echo "Enter width of rectangle: "
	read width
	area=`expr $height \* $width` 
	echo "The area of the rectangle is $area"

	echo "Would you like to repeat for another rectangle [Yes/No]?"
	read response
done
