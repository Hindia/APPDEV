
----------------------------------------
	Acoustic sensor using RPi3
-----------------------------------------


This project will turn a raspberry pi 3 into an acoustic sensor.

Table of contents
 
1. Configuration instruction
2. Installation instruction
3. operating instruction
4. list of project files
------------------------------------------

1.CONFIGURATION

This section contains two parts:hardware and software configuration

1.1 HARDWARE CONFIGURATION

This project is done using raspberry pi. It is recommended an older version of pi is used, corresponding configuration might be changed.

The pi is mounted with USB sound card and a microphone is also plugged. It is recommended to have ethernet connection for your pi. A USB sound card as well

as a microphone is needed.

1.2. SOFTWARE CONFIGURATION

The USB soundcard has to be set as the default device. To do so you need to modify two files which are asound.conf in etc folder and .asoundrc file. you put the following content.
pcm.!default {
	type plug
	slave {
		pcm "hw:1,0"
	}
}
ctl.!default{
	type hw 
	card 1
}

Next, Go to your home directory type "nano .asoundrc" command and put the above content to the file. Then run "alsamixer". Do you see that USB sound card is the default audio device? If yes, you are good to go.

One more thing, If you are using Raspbian Jessie, you have to roll back alsa-utils to an early version by the following steps.

	STEP 1. type "sudo nano /etc/apt/sources.list" and add "deb http://mirrordirector.raspbian.org/raspbian/ wheezy main contrib non-free rpi" to the file. Please do not miss any space or any other character when doing so.

	STEP 2. Run "sudo apt-get update"

	STEP 3. Run "sudo aptitude versions alsa-utils". This is to check if version 1.0.25 of alsa-util is available.

	STEP 4. Run "sudo apt-get install alsa-utils=1.0.25-4"

	STEP 5. If necessary, Reboot device.

	STEP 6. Run "arecord -r44100 -c1 -f S16_LE -d5 test.wav". This is to test if your mic is working. You should see a "test.wav" file in the current folder if so.

	STEP 7. Put an earphone on and run "aplay test.wav". Did you hear what you recorded? if yes, you are good to go.  

----------------------------------

2. INSTALLATION INSTRUCTION

First insert your sd card into the Raspberry pi then connect the ethernet cable to the device. After checking everything is plugged in fire up your device. When the pi is turned on plug in the USB soundcard with a microphone plugged to it so you can collect sounds around you. 

- Note:- this installation is to be made after you have configured your Raspberry pi/sd card with the first steps i.e. booting procedures 
----------------------------

3.OPERATING INSTRUCTION

After the installation, simply execute "./sound.a" in the project file. Press "CTRL + C" to stop the execution. You can get the data accumulated when the 
program was running at http://www.cc.puv.fi/~e1500943/php/soundlog.txt

-----------------------------

4. List of project files

The project contains the following files:-

- makefile: makefile of this project

- wave.c: program conataining functions used to process wave files

- wave.h: contains the headers of wave.c

- screen.c: module containing the screen manipulation

- screen.h: headers used in the the screen.c file

- comm.c: communication module of the project to the webpage. Uses CURL

- comm.h: contains headers of comm.c

- main.c: contains the main function

- sound.php: the server webpage used to receive sound data 

- sound.html: the server page which visualizes the data using a graph 
