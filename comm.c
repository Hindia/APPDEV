#include "comm.h"	//includes the header file of communication
#include <stdio.h>	//includes the standard input output library
#include <curl/curl.h>	//includes the curl library
#include <string.h>	//includes the string library to use strings in this code

//send_data_curl function defined
void send_data_curl(double Leq[]){
	char postdata[200]="data=", temp[30];	//array to hold the sample recordings
	int i;	//variable for looping
	CURL *curl;	//pointer defined
	CURLcode res;
	//prepares the postdata
	for(i=0;i<8;i++){
		sprintf(temp,(i==7)?"%.2f":"%.2f;",Leq[i]);	//gives format the LEQ values and gives it to temp
		strcat(postdata, temp);	//appends temp to postdata
	}
	curl_global_init(CURL_GLOBAL_ALL);	//initializes  all curl
	curl = curl_easy_init();
	if(curl){
		 //set URL of server page
		curl_easy_setopt(curl, CURLOPT_URL, URL);
	 	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata);	//sends the postdata value to the post fields of curl 
	 	res=curl_easy_perform(curl);	 //performs a submit
		if(res!= CURLE_OK){	 //checks if server side is negative
	 		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));	//output error
		}
		curl_easy_cleanup(curl); 	 //clean up handler
	}
	curl_global_cleanup();	 //globally ended curl
}
