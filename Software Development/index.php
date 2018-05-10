<?php
$zerO = new PDO("mysql:host=localhost;dbname=schedule", "root", "");
$zerO->exec('use train');

$stmt = "SELECT DISTINCT depart FROM schedule;";
$sqll = $zerO->prepare($stmt);
$sqll->execute(array());
$cities_from = $sqll->fetchAll();

$stmt = "SELECT DISTINCT arrive FROM schedule;";
$sqll = $zerO->prepare($stmt);
$sqll->execute(array());
$cities_to = $sqll->fetchAll();

$stmt = "SELECT DISTINCT class FROM schedule;";
$sqll = $zerO->prepare($stmt);
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
		<div id="text"><font size="6" color="white">Egypt Trains</font></div>
		<div id="logo"><img src="Untitled-31.png"/></div>
		<div id="logo2"><a href="index.php"><img src="Untitled-1.png"/></a></div>
	</div>

	<div id="bgImg"><img src="great_sphinx.jpg" /></div>
	
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
