#include "comm.h"
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

//
void send_data_curl(double Leq[]){
	char postdata[200]="data=", temp[30];
	int i;
	CURL *curl;
	CURLcode res;
	for(i=0;i<8;i++){
		sprintf(temp,(i==7)?"%.2f":"%.2f;",Leq[i]);
		strcat(postdata, temp);	//appends temp to postdata
	}
	printf("%s\n", postdata);
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if(curl){
		 //set URL of server page
		curl_easy_setopt(curl, CURLOPT_URL, URL);
	 	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata); 
	 	res=curl_easy_perform(curl);	 //perform a submit
		if(res!= CURLE_OK){	 //if server side is negative
	 		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));	//output error
		}
		curl_easy_cleanup(curl); 	 //clean up handler
	}	
	curl_global_cleanup();	 //globally ended curl
}
