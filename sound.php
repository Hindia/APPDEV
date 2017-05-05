<?php
$data=$_POST['data'];	//data to be written, samples from the record
$ip=$_SERVER['REMOTE_ADDR'];	//client's ip add
$file="soundtest.log"; 	//specifies the log file name
if(file_exists($file)){
	$fp=fopen($file, "a");	//open file in append mode
}
else{
	$fp=fopen($file, "w");	//open file in write mode
}
$record=$data. "\n";	//line to be written to a file written in CSV(comma separated value) format
fwrite($fp, $record);	//writes to file
fclose($fp);	//closes file
?>
