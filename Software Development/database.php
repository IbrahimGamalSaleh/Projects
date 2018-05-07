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

try{
$pdo->exec("use train");
$tb = <<<TABLE
	DROP TABLE IF EXISTS schedule;
	CREATE TABLE IF NOT EXISTS schedule (
		id INT(3) NOT NULL AUTO_INCREMENT PRIMARY KEY,
		depart VARCHAR(50) NOT NULL,
		depart_time VARCHAR(20) NOT NULL,
		arrive VARCHAR(50) NOT NULL,
		arrive_time VARCHAR(20) NOT NULL,
		class VARCHAR(20) NOT NULL,
		price DECIMAL(5,2) NOT NULL );
TABLE;

	$b = $pdo->exec($tb);
	if ($b === false){
		die("couldn't create table");
	}

}catch(Exception $e){
	die($e->getMessage());
}

try{

	$insert = <<<INSERT
		INSERT INTO schedule(depart, depart_time, arrive, arrive_time, class, price) VALUES
		("A","10:10","B","11:11","Express-1",50.5),
		("A","10:10","B","11:11","Express-1",50.5),
		("A","10:10","B","11:11","Express-1",50.5);
INSERT;

	$b = $pdo->exec($insert);
	if ($b === false)
		die("couldn't add data");
}catch(Exception $e){
	die($e->getMessage());
}

 ?>
