<!-- trains schedule website -->

<?php

try{
	$pdo = new PDO("mysql:host=localhost", "root", "");

	$db = "CREATE DATABASE IF NOT EXISTS train";
	$b = $pdo->exec($db);

	if ($b === false)
		die("couldn't create database");

}catch(Exception $e){
	die("DB error, ".$e->getMessage());
}

$pdo->exec("use train");

try{
	$tb = <<<TABLE
	DROP TABLE IF EXISTS schedule;
	CREATE TABLE IF NOT EXISTS schedule (
		id INT(3) NOT NULL AUTO_INCREMENT PRIMARY KEY,
		depart VARCHAR(50) NOT NULL,
		depart_time VARCHAR(20) NOT NULL,
		arrive VARCHAR(50) NOT NULL,
		arrive_time VARCHAR(20) NOT NULL,
		class VARCHAR(20) NOT NULL,
		price VARCHAR(20) NOT NULL );
TABLE;

	$b = $pdo->exec($tb);
	if ($b === false)
		die("couldn't create table");

}catch(Exception $e){
	die($e->getMessage());
}

try{
	$insert = <<<INSERT
			INSERT INTO schedule(depart, depart_time, arrive, arrive_time, class, price) VALUES
			("Cairo","10:10","Assyut","11:11","Express","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Cairo","11:11","Express","1st: 50.50
	2nd: 40"),
			("Qena","10:10","Cairo","11:11","Express","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Qena","11:11","Express","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Alexandria","11:11","Express","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Aswan","11:11","Express","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Sohag","11:11","Express","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Luxor","11:11","Express","1st: 50.50
	2nd: 40"),
			("Luxor","10:10","Assyut","11:11","Express","1st: 50.50
	2nd: 40"),
			("Cairo","10:10","Assyut","11:11","Express","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Cairo","11:11","Express","1st: 50.50
	2nd: 40"),
			("Qena","10:10","Cairo","11:11","Express","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Qena","11:11","Express","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Alexandria","11:11","Express","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Aswan","11:11","Express","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Sohag","11:11","Express","1st: 50.50
	2nd: 40"),
			("Luxor","10:10","Assyut","11:11","Express","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Luxor","11:11","Express","1st: 50.50
	2nd: 40"),
			("Cairo","10:10","Assyut","11:11","VIP-1","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Cairo","11:11","VIP-1","1st: 50.50
	2nd: 40"),
			("Qena","10:10","Cairo","11:11","VIP-1","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Qena","11:11","VIP-1","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Alexandria","11:11","VIP-1","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Aswan","11:11","VIP-1","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Sohag","11:11","VIP-1","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Luxor","11:11","VIP-1","1st: 50.50
	2nd: 40"),
			("Luxor","10:10","Assyut","11:11","VIP-1","1st: 50.50
	2nd: 40"),
			("Cairo","10:10","Assyut","11:11","VIP-2","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Cairo","11:11","VIP-2","1st: 50.50
	2nd: 40"),
			("Qena","10:10","Cairo","11:11","VIP-2","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Qena","11:11","VIP-2","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Alexandria","11:11","VIP-2","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Aswan","11:11","VIP-2","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Sohag","11:11","VIP-2","1st: 50.50
	2nd: 40"),
			("Luxor","10:10","Assyut","11:11","VIP-2","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Luxor","11:11","VIP-2","1st: 50.50
	2nd: 40"),
			("Cairo","10:10","Assyut","11:11","SLEEPING-1","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Cairo","11:11","SLEEPING-1","1st: 50.50
	2nd: 40"),
			("Qena","10:10","Cairo","11:11","SLEEPING-1","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Qena","11:11","SLEEPING-1","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Alexandria","11:11","SLEEPING-1","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Aswan","11:11","SLEEPING-1","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Sohag","11:11","SLEEPING-1","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Luxor","11:11","SLEEPING-1","1st: 50.50
	2nd: 40"),
			("Luxor","10:10","Assyut","11:11","SLEEPING-1","1st: 50.50
	2nd: 40"),
			("Cairo","10:10","Assyut","11:11","SLEEPING-2","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Cairo","11:11","SLEEPING-2","1st: 50.50
	2nd: 40"),
			("Qena","10:10","Cairo","11:11","SLEEPING-2","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Qena","11:11","SLEEPING-2","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Alexandria","11:11","SLEEPING-2","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Aswan","11:11","SLEEPING-2","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Sohag","11:11","SLEEPING-2","1st: 50.50
	2nd: 40"),
			("Luxor","10:10","Assyut","11:11","SLEEPING-2","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Luxor","11:11","SLEEPING-2","1st: 50.50
	2nd: 40"),
			("Cairo","10:10","Assyut","11:11","DISTINCTIVE","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Cairo","11:11","DISTINCTIVE","1st: 50.50
	2nd: 40"),
			("Qena","10:10","Cairo","11:11","DISTINCTIVE","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Qena","11:11","DISTINCTIVE","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Alexandria","11:11","DISTINCTIVE","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Aswan","11:11","DISTINCTIVE","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Sohag","11:11","DISTINCTIVE","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Luxor","11:11","DISTINCTIVE","1st: 50.50
	2nd: 40"),
			("Luxor","10:10","Assyut","11:11","DISTINCTIVE","1st: 50.50
	2nd: 40"),
			("Cairo","10:10","Assyut","11:11","DISTINCTIVE","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Cairo","11:11","DISTINCTIVE","1st: 50.50
	2nd: 40"),
			("Qena","10:10","Cairo","11:11","DISTINCTIVE","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Qena","11:11","DISTINCTIVE","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Alexandria","11:11","DISTINCTIVE","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Aswan","11:11","DISTINCTIVE","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Sohag","11:11","DISTINCTIVE","1st: 50.50
	2nd: 40"),
			("Luxor","10:10","Assyut","11:11","DISTINCTIVE","1st: 50.50
	2nd: 40"),
			("Assyut","10:10","Luxor","11:11","DISTINCTIVE","1st: 50.50
	2nd: 40");
INSERT;

	$b = $pdo->exec($insert);
	if ($b === false)
		die("couldn't add data");

}catch(Exception $e){
	die($e->getMessage());
}

 ?>
