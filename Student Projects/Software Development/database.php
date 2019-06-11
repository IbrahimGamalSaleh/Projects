<!-- trains schedule website -->

<?php
function fillDB(){
if (!isset($_COOKIE["databaseIsCreated"])) {
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
		price1 VARCHAR(20) NOT NULL,
		price2 VARCHAR(20) NOT NULL );
TABLE;

	$b = $pdo->exec($tb);
	if ($b === false)
		die("couldn't create table");

}catch(Exception $e){
	die($e->getMessage());
}

try{
	$insert = file_get_contents('insert.sql');
	$b = $pdo->exec($insert);
	if ($b === false)
		die("couldn't add data");

}catch(Exception $e){
	die($e->getMessage());
}
setcookie("databaseIsCreated", "1",time()+60*60*24*30);
}
}
?>
<!-- else die("is already inserted"); -->