<?php
$data=$_POST['data'];
$ip=$_SERVER['REMOTE_ADDR'];	//client's ip add
$today=date("Y-m-d H:i:s");	//current time
$file="soundtest.log"; 	//specifies the log file name
if(file_exists($file)){
	$fp=fopen($file, "a");	//open file in append mode
}
else{
	$fp=fopen($file, "w");	//open file in write mode
}
$record=$today. "," .$data. "\n";	//line to be written to a file written in CSV(comma separated value) format
fwrite($fp, $record);	//writes to file
fclose($fp);	//closes file
echo "data stored\n";
?>
