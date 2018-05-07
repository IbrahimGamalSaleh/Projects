<!-- trains schedule website -->

<?php
if (isset($_GET['depart']) & isset($_GET['arrive'])){
	$_depart = $_GET['depart'];
	$_arrive = $_GET['arrive'];

}else {
	die("invalid parameters");
}
?>

<!-- <meta http-equiv="refresh" content=".1"/> -->




<form action="." method="POST">
	<input type="submit" value="Back"/> <br> <br>

	<table border="1px">
	<tr>
		<th> ID </th>
		<th> depart </th>
                <th> depart_time </th>
		<th> arrive </th>
                <th> arrive_time </th>
		<th> class </th>
                <th> Price </th>
	</tr>

       	<?php
       	$pdo = new PDO("mysql:host=localhost;dbname=train","root","");
        $stmt = $pdo->prepare("SELECT * FROM schedule");
        $stmt->execute(array());
        $Rz = $stmt->fetchAll();
        if (count($Rz) > 0)
		foreach($Rz as $r)
			echo "<tr>"
                	. "<td>" . $r['id'] . "</td>"
			. "<td>" . $r['depart'] . "</td>"
	                . "<td>" . $r['depart_time'] . "</td>"
			. "<td>" . $r['arrive'] . "</td>"
			. "<td>" . $r['arrive_time'] . "</td>"
			. "<td>" . $r['class'] . "</td>"
			. "<td>" . $r['price'] . "</td>"
			. "</tr>";
	else
        	echo "No trains travelling between these stations found.";
	 ?>

</form>       
</table>

