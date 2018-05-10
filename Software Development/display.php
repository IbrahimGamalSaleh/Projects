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
            $R = "<h2> No trains for selected stations </h2>";
        elseif (count($Rwz)>0 && $_class != 'ALL'){
            $stmtClass->execute(array($_depart, $_arrive, $_class));
            $Rwz = $stmtClass->fetchAll();
            if (count($Rwz) < 1 )
                $R = "<h2> No trains for selected stations with this class </h2> ";
        }
    } else
        $R = "<h2> No trains from a station to itself </h2>";
}else {
    $R = "<h2> You entered this page by mistake. </h2>";
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
<body id="displayBody">
    <div id="header">
        <div id="text">Egypt Trains</div>
        <div id="logo"><img src="left-logo.png"/></div>
        <div id="logo2"><a href="index.php"><img src="Untitled-1.png"/></a></div>
    </div>
BODY;
echo $body;

if($R !== ''){
    echo $R;
    echo "<form action=\"index.php\"> <input id=\"show_submit\" type=\"submit\" value=\"Go HomePage\"/> </form>";
} else {
// <div id=\"ribbon\"><img src=\"Untitled-as1.png\"/></div>
echo "

    <h2 id=\"inf\"> Trains from $_depart to $_arrive </h2>
    <table id=\"showtable\" cellspacing=\"3px\" cellpadding=\"3px\" >
        <tr>
            <th id=\"ID\">Train</th>
            <th id=\"DTime\">Take off</th>
            <th id=\"ATime\">Arrive</th>
            <th id=\"Class\">Degree</th>
            <th id=\"Price\">Price</th>
        </tr>
";
    $i=0;
    foreach($Rwz as $r){
        if ($i == 1) $i=0;
        else $i=1;
        echo "<tr>";
        echo "<td id=\"i$i\"> $r[id] </td>";
        echo "<td id=\"i$i\"> $r[depart_time] </td>";
        echo "<td id=\"i$i\"> $r[arrive_time] </td>";
        echo "<td id=\"i$i\"> $r[class] </td>";
        echo "<td id=\"i$i\"> $r[price1] </td>";
        echo "</tr><tr><td id=\"i$i\"></td><td id=\"i$i\"></td><td id=\"i$i\"></td><td id=\"i$i\"></td>";
        echo "<td id=\"i$i\"> $r[price2] </td>";
        echo "</tr>";
    }
    echo "</table>";
    echo "<form action=\"index.php\"> <input id=\"show_submit\" type=\"submit\" value=\"Go HomePage\"/> </form>";
}
echo "</body>";
?>

<!-- for($row=1;$row<=7;$row++) {
            echo "<tr>";
            for($col=1;$col<=6;$col++)
                echo "<td height=30px width=30px bgcolor=gray></td>";
            echo "</tr>";
        } -->