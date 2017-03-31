
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

A project done using raspberry pi. It is recommended an older version of pi is used, corresponding configuration might be changed.

The pi is mounted with USB sound card and a microphone is also plugged.

It is recommended to have ethernet connection for your pi. A USB sound card as well as a microphone is needed.

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

If you are using Raspbian Jessie, you have to roll back alsa-utils to an early version by #powerpoint on how. your task hindia

----------------------------------

2. INSTALLATION INSTRUCTION

----------------------------

3.OPERATING INSTRUCTION

After the installation, simply execute "./sound.a" in the project file

-----------------------------

4. List of project files

The project contains the following files:-

- makefile: makefile of this project

- wave.c: program conataining functions used to process wave files

- wave.h: contains the headers of wave.c

- screen.c: module containing the screen manipulation

-screen.h: headers used in the the screen.c file

-comm.c: communication module of the project to the webpage. Uses CURL

-comm.h: contains headers of comm.c

-main.c: contains the main function

-sound.php: the server webpage used to receive sound data 

-show.html: the server page which visualizes the data 
