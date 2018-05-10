<?php

$pdo = new PDO("mysql:host=localhost;dbname=train","root","");
$stmt = $pdo->prepare("SELECT * FROM schedule WHERE depart=? AND arrive=?");
$stmtClass = $pdo->prepare("SELECT * FROM schedule WHERE depart=? AND arrive=? AND class=?");

if (isset($_GET['depart']) & isset($_GET['destination'])){
	$_depart = $_GET['depart'];
	$_arrive = $_GET['destination'];
    $_class = $_GET['class'];
    
    $b = ($_depart !== $_arrive);
    $R = '';
    if ($b){
        $stmt->execute(array($_depart, $_arrive));
        $Rwz = $stmt->fetchAll();
        if (count($Rwz) < 1 )
            $R = 'No trains for selected stations';
        elseif (count($Rwz)>0 && $_class != 'ALL'){
            $stmtClass->execute(array($_depart, $_arrive, $_class));
            $Rwz = $stmtClass->fetchAll();
            if (count($Rwz) < 1 )
                $R = 'No trains for selected stations with this class';
        }
    } else
        $R = 'No trains from a station to itself';
}

$head=<<<HEAD
<head>
    <title>Welcome</title>
    <meta http-equiv="content-type" content="text/html;charset=utf-8" />
    <link rel="stylesheet" href="style.css" type="text/css" />
</head>
HEAD;
echo $head;

$body=<<<BODY
<body>
    <div id="header">
        <div id="text"><font size="6" color="white">Egypt Trains</font></div>
        <div id="logo"><img src="Untitled-31.png"/></div>
        <div id="logo2"><a href="index.php"><img src="Untitled-1.png"/></a></div>
    </div>
    </body>
BODY;
echo $body;

if($R !== '')
    echo $R;
else {
// <div id=\"ribbon\"><img src=\"Untitled-as1.png\"/></div>
echo "
    <table id=\"showtable\" cellspacing=\"3px\" cellpadding=\"3px\" >
        <tr>
            <th id=\"ID\">Train</th>
            <th id=\"DTime\">Take off</th>
            <th id=\"ATime\">Arrive</th>
            <th id=\"Class\">Degree</th>
            <th id=\"Price\">Price</th>
        </tr>
";

        foreach($Rwz as $r){
            echo "<tr>";
            echo "<td id=\"ID\"> $r[id] </td>";
            echo "<td id=\"DTime\"> $r[depart_time] </td>";
            echo "<td id=\"ATime\"> $r[arrive_time] </td>";
            echo "<td id=\"Class\"> $r[class] </td>";
            echo "<td id=\"Price\"> $r[price] </td>";
            echo "</tr>";
        }
    echo "</table>";
}
echo "</body>";
?>

<!-- for($row=1;$row<=7;$row++) {
            echo "<tr>";
            for($col=1;$col<=6;$col++)
                echo "<td height=30px width=30px bgcolor=gray></td>";
            echo "</tr>";
        } -->