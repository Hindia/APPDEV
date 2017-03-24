#include "comm.h"
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>


void send_data_curl(double Leq[]){
	char postdata[200]="data=", temp[30];
	int i;
	CURL *curl;
	CURLcode res;
	for(i=0;i<8;i++){
		sprintf(temp,(i==7)?"%.2f":"%.2f;",Leq[i]);
		strcat(postdata, temp);	//appends temp to postdata
	}
	//postdata is ready,next lines copied from test.c
	if(curl){
		curl_easy_setopt(curl, CURLOPT_URL,URL);
	 	curl_easy_setopt(curl, CURLOPT_POSTFIELDS,postdata); 
	 	res=curl_easy_perform(curl);
		if(res!= CURLE_OK){
	 		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
		curl_easy_cleanup(curl); 
	}	
	curl_global_cleanup();
	
}	
