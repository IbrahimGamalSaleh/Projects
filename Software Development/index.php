<!-- trains schedule website -->

<!-- <meta http-equiv="refresh" content=".1"/> -->
<style>

</style>

<title>Train Schedule</title>

<body>
	<form name="Form0" action="show.php">
		<table>
			<tr id="dep">
				<td> departing from: </td>
				<td>
					<select name="depart">
						<option value='A'>A</option>
						<option value='B'>B</option>
						<option value='C'>C</option>
						<option value='D'>D</option>
					</select>
				</td>
                <td></td>
				<td rowspan=3>
                	<input id="show" type="submit" value="submit"/>
                </td>

			</tr>
			<tr id="arrival">
				<td> arriving at: </td>
				<td>
					<select name="arrive">
						<option value='A'>A</option>
						<option value='B'>B</option>
						<option value='C'>C</option>
						<option value='D'>D</option>
					</select>
				</td>
			</tr>
		</table>
	</form>
</body>
