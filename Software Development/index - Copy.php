<?php
include_once('database.php');
fillDB();
$db = new PDO("mysql:host=localhost;dbname=train", "root", "");

$stmt = "SELECT DISTINCT depart FROM schedule;";
$sqll = $db->prepare($stmt);
$sqll->execute(array());
$cities_from = $sqll->fetchAll();

$stmt = "SELECT DISTINCT arrive FROM schedule;";
$sqll = $db->prepare($stmt);
$sqll->execute(array());
$cities_to = $sqll->fetchAll();

$stmt = "SELECT DISTINCT class FROM schedule;";
$sqll = $db->prepare($stmt);
$sqll->execute(array());
$classes = $sqll->fetchAll();

// echo print_r($cities_from);
// echo print_r($cities_to);
// echo print_r($classes);

$head=<<<HEAD
<head>
	<title>Welcome</title>
	<meta http-equiv="content-type" content="text/html;charset=utf-8" />
	<link rel="stylesheet" href="style.css" type="text/css" />
</head>
HEAD;
echo $head;

$body=<<< BODY
<body>
    <div id="header">
        <div id="text">Egypt Trains</div>
		<div id="logo"><img src="left-logo.png"/></div>
		<div id="logo2"><a href="index.php"><img src="Untitled-1.png"/></a></div>
	</div>

	<div id="bgImg"><img src="sphinx.jpg" /></div>
	
	<div id="form">
		<form action="display.php" method="GET">
BODY;
echo $body;
    
    echo"<select id=\"depart\" name=\"depart\">";
    foreach ($cities_from as $c)
        echo "<option> $c[depart] </option>";
    echo "</select>";
	echo "<br />";
			
    echo "<select id=\"destination\" name=\"destination\">";
    foreach ($cities_to as $c)
        echo "<option> $c[arrive] </option>";
	echo "</select>";
    echo "<br />";

    echo "<select id=\"types\" name=\"class\" >";
    echo "<option> ALL </option>";
    foreach ($classes as $c)
        echo "<option> $c[class] </option>";
    echo "</select>";
	echo "<br />";
			
    echo "<input type=\"submit\" id=\"show_submit\" name=\"submit\" value=\"show\" />";
    echo "</form>";
echo "</body>";
?>

<!-- <option value='ALL'>All</option>
<option value="Conditioned">Conditioned</option>
<option value='VIP'>VIP</option>
<option value='Sleeping'>Sleeping</option>
<option value='Express'>Express</option>
<option value='Upgraded'>Upgraded</option>
<option value='Commuter'>Commuter</option> -->
